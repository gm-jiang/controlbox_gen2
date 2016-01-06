/*
 * Copyright (c) 2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== sockets.c ========
 */

#include <stdbool.h>

#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* SimpleLink Wi-Fi Host Driver Header files */
#include <cc3000_host_driver/core_driver/inc/hci.h>
#include <cc3000_host_driver/include/netapp.h>
#include <cc3000_host_driver/include/nvmem.h>
#include <cc3000_host_driver/include/wlan.h>

#include <ti/drivers/GPIO.h>
#include <ti/drivers/WiFi.h>

/* Example/Board Header file */
#include "Board.h"

#define SPI_BIT_RATE    4000000

/* CC3000 firmware version compatible with this example */
#define PACKAGEID       1
#define PACKAGEBLDNUM   24

bool smartConfigFinished = false;
bool deviceConnected = false;
bool ipAcquired = false;

/* Buffer to hold IPv4 address */
char ipRecvd[4];

/*
 *  ======== asynchCallback ========
 *  Callback for handling unsolicited events. A function pointer is passed in
 *  through the WiFi_Params to register the callback with the Host Driver.
 */
void asynchCallback(long eventType, char *data, unsigned char length)
{
    switch (eventType) {
        case HCI_EVNT_WLAN_ASYNC_SIMPLE_CONFIG_DONE:
            /* Smart Config process has completed */
            smartConfigFinished = true;
            break;

        case HCI_EVNT_WLAN_UNSOL_CONNECT:
            /* CC3000 connected to an AP */
            deviceConnected = true;
            GPIO_write(Board_LED0, Board_LED_ON);
            break;

        case HCI_EVNT_WLAN_UNSOL_DISCONNECT:
            /* CC3000 disconnected from an AP */
            deviceConnected = false;
            GPIO_write(Board_LED0, Board_LED_OFF);
            break;

        case HCI_EVNT_WLAN_UNSOL_DHCP:
            /* DHCP report */
            ipAcquired = true;
            ipRecvd[0] = data[3];
            ipRecvd[1] = data[2];
            ipRecvd[2] = data[1];
            ipRecvd[3] = data[0];
            break;
    }
}

/*
 *  ======== smartConfigFxn ========
 *  Starts the Smart Config process which allows the user to tell the CC3000
 *  which AP to connect to, using a smart phone app. Downloads available here:
 *  http://www.ti.com/tool/smartconfig
 */
void smartConfigFxn(void)
{
    unsigned char subnetMask[]     = {0, 0, 0, 0};
    unsigned char ipAddr[]         = {0, 0, 0, 0};
    unsigned char defaultGateway[] = {0, 0, 0, 0};
    unsigned char dnsServer[]      = {0, 0, 0, 0};

    /* Acquire an IP address */
    netapp_dhcp((unsigned long *)ipAddr, (unsigned long *)subnetMask,
                (unsigned long *)defaultGateway, (unsigned long *)dnsServer);

    /* Delete current policy */
    wlan_ioctl_set_connection_policy(0, 0, 0);

    /* Restart the CC3000 */
    wlan_stop();
    Task_sleep(50);
    wlan_start(0);

    /* Set Smart Config prefix and start Smart Config */
    wlan_smart_config_set_prefix("TTT");
    wlan_smart_config_start(0);

    /* Wait for Smart Config to finish. LED will blink until complete. */
    while (smartConfigFinished == 0) {
        Task_sleep(400);
        GPIO_toggle(Board_LED0);
    }

    /* Configure to connect automatically to the AP retrieved */
    wlan_ioctl_set_connection_policy(0, 0, 1);

    GPIO_write(Board_LED0, Board_LED_OFF);

    /* Restart the CC3000 */
    wlan_stop();
    Task_sleep(50);
    wlan_start(0);

    /* Set connection flag to 'disconnected' */
    deviceConnected = 0;
    ipAcquired = 0;

    /* Mask out all non-required events */
    wlan_set_event_mask(HCI_EVNT_WLAN_KEEPALIVE | HCI_EVNT_WLAN_UNSOL_INIT |
            HCI_EVNT_WLAN_ASYNC_PING_REPORT);
}

/*
 *  ======== socketsShutDown ========
 *  Generic routine, defined to close down the WiFi in this case.
 */
void socketsShutDown(void *handle)
{
    WiFi_close((WiFi_Handle)handle);
}

/*
 *  ======== socketsStartUp ========
 *  Generic routine, in this case defined to open the WiFi and await a
 *  connection, using Smart Config if the appropriate button is pressed.
 */
void *socketsStartUp(void)
{
    unsigned char spNum[2] = {0};
    unsigned int currButton;
    unsigned int prevButton = 1;
    WiFi_Params wifiParams;
    WiFi_Handle handle;

    /* Turn LED off. It will be used as a connection indicator */
    GPIO_write(Board_LED0, Board_LED_OFF);

    /* Open WiFi driver */
    WiFi_Params_init(&wifiParams);
    wifiParams.bitRate = SPI_BIT_RATE;
    handle = WiFi_open(Board_WIFI, Board_SPI_CC3000, asynchCallback,
	        &wifiParams);
    if (handle == NULL) {
        System_abort("Error: WiFi driver failed to open.\n");
    }

    /* Mask out all non-required events */
    wlan_set_event_mask(HCI_EVNT_WLAN_KEEPALIVE | HCI_EVNT_WLAN_UNSOL_INIT |
            HCI_EVNT_WLAN_ASYNC_PING_REPORT);

    /* Check service pack version */
    nvmem_read_sp_version(spNum);
    if ((spNum[0] != PACKAGEID) || (spNum[1] != PACKAGEBLDNUM)) {
        System_printf("You are using service pack version %d.%d! This example "
                "is recommended for use\nwith %d.%d. Run the TI-RTOS "
                "CC3000 Patcher example to get this version.\n\n",
                spNum[0], spNum[1], PACKAGEID, PACKAGEBLDNUM);
        System_flush();
    }

    /*
     * Wait for the WiFi device to connect to an AP. If a profile for the AP in
     * use has not been stored yet, press Board_BUTTON0 to put the CC3000 in
     * Smart Config mode.
     */
    while ((deviceConnected != true) || (ipAcquired != true)) {
        /*
         *  Start Smart Config if a button is pressed. This could be done with
         *  GPIO interrupts, but for simplicity polling is used to check the
         *  button.
         */
        currButton = GPIO_read(Board_BUTTON0);
        if ((currButton == 0) && (prevButton != 0)) {
            smartConfigFxn();
        }
        prevButton = currButton;
        Task_sleep(50);
    }

    System_printf("CC3000 has connected to AP and acquired an IP address.\n");

    /* Print IP address */
    System_printf("IP Address: %d.%d.%d.%d\n", ipRecvd[0], ipRecvd[1],
            ipRecvd[2], ipRecvd[3]);
    System_flush();

    /* pass back the handle to our WiFi device */
    return ((void *)handle);
}
