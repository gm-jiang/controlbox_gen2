/*
 * Copyright (c) 2015, Texas Instruments Incorporated
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
/** ============================================================================
 *  @file       Board.h
 *
 *  @brief      CC2650SENSORTAG Board Specific header file.
 *
 *  The CC2650 header file should be included in an application as follows:
 *  @code
 *  #include <Board.h>
 *  @endcode
 *
 *  ============================================================================
 */
#ifndef __CC2650ST_H__
#define __CC2650ST_H__

#ifdef __cplusplus
extern "C" {
#endif

/** ============================================================================
 *  Symbol by generic Board.c to include the correct kit specific Board.c
 *  ==========================================================================*/
#define	CC2650ST_7ID
#define CC2650ST_0100

/** ============================================================================
 *  Includes
 *  ==========================================================================*/
#include <ti/drivers/PIN.h>
#include <driverlib/ioc.h>

/** ============================================================================
 *  Externs
 *  ==========================================================================*/
extern PIN_Config BoardGpioInitTable[];

/** ============================================================================
 *  Defines
 *  ==========================================================================*/

/* Mapping of pins to board signals using general board aliases
 *      <board signal alias>                <pin mapping>
 */

/* Discrete outputs */
#define Board_LED1                  IOID_10
#define Board_LED2                  IOID_15
#define Board_BUZZER                IOID_21
#define Board_LED_ON                1
#define Board_LED_OFF               0
#define Board_BUZZER_ON             1
#define Board_BUZZER_OFF            0

/* Discrete inputs */
#define Board_KEY_LEFT              IOID_0
#define Board_KEY_RIGHT             IOID_4
#define Board_RELAY                 IOID_3

/* Sensor outputs */
#define Board_MPU_INT               IOID_7
#define Board_TMP_RDY               IOID_1

/* I2C */
#define Board_I2C0_SDA0             IOID_5
#define Board_I2C0_SCL0             IOID_6
#define Board_I2C0_SDA1             IOID_8
#define Board_I2C0_SCL1             IOID_9

/* SPI */
#define Board_SPI_FLASH_CS          IOID_14
#define Board_SPI_DEVPK_CS          IOID_20
#define Board_FLASH_CS_ON           0
#define Board_FLASH_CS_OFF          1

#define Board_SPI0_CLK              IOID_11
#define Board_SPI0_MISO             IOID_18
#define Board_SPI0_MOSI             IOID_19

/* DevPack */
#define Board_AUDIOFS_TDO           IOID_16
#define Board_SCLK_TDI              IOID_17
#define Board_AUDIODO               IOID_22
#define Board_DP2                   IOID_23
#define Board_DP1                   IOID_24
#define Board_DP0                   IOID_25
#define Board_DP3                   IOID_27
#define Board_DP4_UARTRX            IOID_28
#define Board_DP5_UARTTX            IOID_29
#define Board_DEVPK_ID              IOID_30

/* UART (when connected to SRF06EB) */
#define Board_EB_UART_TX            IOID_16
#define Board_EB_UART_RX            IOID_17

/* Power control */
#define Board_MPU_POWER             IOID_12
#define Board_MPU_POWER_ON          1
#define Board_MPU_POWER_OFF         0

#define Board_MIC_POWER             IOID_13
#define Board_MIC_POWER_ON          1
#define Board_MIC_POWER_OFF         0
#define Board_AUDIO_DI              IOID_2


/** ============================================================================
 *  Instance identifiers
 *  ==========================================================================*/
/* Generic I2C instance identifiers */
#define Board_I2C                   CC2650_I2C0
/* Generic SPI instance identifiers */
#define Board_SPI0                  CC2650_SPI0
/* Generic UART instance identifiers */
#define Board_UART                  CC2650_UART0


/** ============================================================================
 *  Number of peripherals and their names
 *  ==========================================================================*/

/*!
 *  @def    CC2650_I2CName
 *  @brief  Enum of I2C names on the CC2650 dev board
 */
typedef enum CC2650_I2CName {
    CC2650_I2C0 = 0,
    CC2650_I2CCOUNT
} CC2650_I2CName;

/*!
 *  @def    CC2650_SPIName
 *  @brief  Enum of SPI names on the CC2650 dev board
 */
typedef enum CC2650_SPIName {
    CC2650_SPI0 = 0,
    CC2650_SPICOUNT
} CC2650_SPIName;

/*!
 *  @def    CC2650_UARTName
 *  @brief  Enum of UARTs on the CC2650 dev board
 */
typedef enum CC2650_UARTName {
    CC2650_UART0 = 0,
    CC2650_UARTCOUNT
} CC2650_UARTName;

/*!
 *  @def    CC2650_UdmaName
 *  @brief  Enum of DMA buffers
 */
typedef enum CC2650_UdmaName {
    CC2650_UDMA0 = 0,
    CC2650_UDMACOUNT
} CC2650_UdmaName;

#ifdef __cplusplus
}
#endif

#endif /* __CC2650ST_H__ */
