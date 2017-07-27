#include <stdlib.h>
#include "hal_uart.h"

#include <stdlib.h>
#include <string.h>
#include "OSAL.h"
#include "AF.h"
#include "onboard.h"
#include "hal_led.h"
#include "hal_board_cfg.h"
#include "lock_router_app.h"
#include "router_print.h"
#include "panasonic_sensor.h"
#include "mt_uart.h"


extern uint8 lock_router_app_task_id;
uint8 report_infrare_success = false;
uint8 g_infrare_reporting = false;
uint8 report_infrare_count = 0;
uint8 report_dev_meta_success = false;
uint8 dev_meta_report_cn = 0;


extern uint8 send_msg_to_center(uint8 *data, uint8 len, uint8 type, uint16 tid);
extern uint8 sensor_heartbeat_lost;

void panasonic_sensor_init(void)
{
    uint8 cmd_start[] = {0xAA, 0x10, 0x02, 0x00, 0x02, 0xAA, 0x68};
    uint8 cmd_stop[]  = {0xAA, 0x10, 0x02, 0x00, 0x03, 0xAA, 0x69};
    HalUARTWrite(HAL_UART_PORT_0, cmd_stop, sizeof(cmd_stop));
    HalUARTWrite(HAL_UART_PORT_0, cmd_start, sizeof(cmd_stop));
}

void infrare_report(int8 infrared_status)
{
    uint8 ret = 0;
    uint16 tid = 0;

    ret = send_msg_to_center((uint8 *)&infrared_status, sizeof(infrared_status), MSG_TYPE_INFRARE, tid);
    if (ret != ZSuccess)
    {
        log_printf( "Error: send body detect status error, error code is %d.\r\n", ret);
        return ;
    }
    report_infrare_success = FALSE;
    return;
}

static uint32 get_dev_devid(void)
{
    uint32 dev_id = 0;
    dev_id = 1111100000;
    return dev_id;
}

static uint16 get_dev_type(void)
{
    uint16 dev_type = INVALID_TYPE;
    dev_type = PANASONIC_TYPE;
    return dev_type;
}

void report_dev_meta_info(short tid)
{
    uint8 ret = 0;
    dev_meta_t dev_meta;
    dev_meta.dev_id= get_dev_devid();
    dev_meta.dev_type = get_dev_type();

    ret = send_msg_to_center((uint8 *)&dev_meta, sizeof(dev_meta), MSG_TYPE_PANASONICID_REPORT, tid); //MSG_TYPE_PANASONICID_REPORT

    if (ret != ZSuccess)
    {
        log_printf( "Error: send dev meta error, ret = %d.\r\n", ret);
    }
    log_printf( "report_dev_meta_info: devid = %u, dev_type = %d.\r\n", dev_meta.dev_id, dev_meta.dev_type);
    report_dev_meta_success = FALSE;

    return;
}

void report_dev_meta_finish(void)
{
    if (!report_dev_meta_success)
    {
        log_printf("report dev meta successfully\r\n");
        report_dev_meta_success = TRUE;
        osal_stop_timerEx(lock_router_app_task_id, EVENT_REPORT_DEV_META);
    }
}

void infrare_report_success(void)
{
    if (!report_infrare_success)
    {
        log_printf("report infrare successfully\r\n");
        report_infrare_success = TRUE;
        g_infrare_reporting = FALSE;
        osal_stop_timerEx(lock_router_app_task_id, EVENT_REPORT_INFRARE);
    }
}

void panasonic_uart_cb ( uint8 port, uint8 event )
{
    uint8  ch;
    static uint8 state = 0;
    uint8 human = 0;
    uint8 fcs[2];
    (void)event;  // Intentionally unreferenced parameter
    static int8 last_status = -1;

    while (Hal_UART_RxBufLen(port))
    {
        HalUARTRead (port, &ch, 1);
        switch (state)
        {
        case SOP:
            if (ch == 0xCC)
                state = MODE;
            else
                state = SOP;
            break;

        case MODE:
            if (ch == 0x10)
                state = HEAD0;
            else
                state = SOP;
            break;

        case HEAD0:
            if (ch == 0x01)
                state = HEAD1;
            else
                state = SOP;
            break;

        case HEAD1:
            if (ch== 0x00)
                state = DATA;
            else
                state = SOP;
            break;

        case DATA:
            HalUARTRead (port, fcs, 2);
            if (fcs[0] == 0xCC && fcs[1] == 0x1F)
            {
                sensor_heartbeat_lost = 0;
                human = ch;
                if (last_status != human)
                {
                    last_status = human;
                    if (human)
                    {
                        osal_set_event (lock_router_app_task_id, HUMAN_DETECT_EVENT_SOMEONE);
                        P1_4 = 1;
                    }
                    else
                    {
                        osal_set_event (lock_router_app_task_id, HUMAN_DETECT_EVENT_NOBODY);
                        P1_4 = 0;
                    }
                }
            }
            state = SOP;
            break;

        default:
            state = SOP;
            break;
        }
    }
}

