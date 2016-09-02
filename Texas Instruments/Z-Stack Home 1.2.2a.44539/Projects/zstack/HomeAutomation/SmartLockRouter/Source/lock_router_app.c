

#include "ZComDef.h"
#include "OSAL.h"
#include "AF.h"
#include "MT.h"
#include "ZDApp.h"
#include "ZDObject.h"
#include "OSAL_Nv.h"
#include "onboard.h"
#include "hal_led.h"
#include "hal_ota.h"
#include <stdlib.h>
#include <string.h>
#include "hal_board_cfg.h"
#include "lock_router_app.h"
#include "lock_router_ota.h"
#include "router_print.h"
#include "zcl.h"


#define SB_TURN_OFF_LED1()  HAL_TURN_OFF_LED1()
#define SB_TURN_ON_LED1()   HAL_TURN_ON_LED1()
#define SB_TOGGLE_LED1()    HAL_TOGGLE_LED1()
#define SB_TURN_OFF_LED2()  HAL_TURN_OFF_LED2()
#define SB_TURN_ON_LED2()   HAL_TURN_ON_LED2()
#define SB_TOGGLE_LED2()    HAL_TOGGLE_LED2()

uint8 lock_router_offline_count = 0;
uint8 flag_deviceid_send_succeed = false;
uint8 lock_router_app_seq_num = 0;
uint8 lock_router_app_task_id = 0;
uint32 msg_tid = 0;
uint32 device_id = 0;
uint8 device_id_report_cnt = 0;
devStates_t lock_router_nework_state = DEV_INIT;
afAddrType_t lock_router_app_dest_addr = {0};
uint16 hb_tid;

SimpleDescriptionFormat_t lock_router_simple_desc =
{
    LOCK_ROUTER_END_POINT_NUM,             //  int Endpoint;
    LOCK_APP_PROFILE_ID,              //  uint16 AppProfId[2];
    LOCK_APP_DEVICE_ID,               //  uint16 AppDeviceId[2];
    0x01,                     //  int   AppDevVer:4;
    0x00,                     //  int   AppFlags:4;
    0,         //  byte  AppNumInClusters;
    NULL,   //  byte *pAppInClusterList;
    0,        //  byte  AppNumInClusters;
    NULL    //  byte *pAppInClusterList;
};

static endPointDesc_t lock_router_ep =
{
    LOCK_ROUTER_END_POINT_NUM,
    &lock_router_app_task_id,
    &lock_router_simple_desc,
    (afNetworkLatencyReq_t)0            // No Network Latency req
};

void lock_router_app_Init(uint8 task_id)
{
    lock_router_app_task_id = task_id;
    lock_router_app_seq_num = 0;

    // Set destination address to indirect
    lock_router_app_dest_addr.addrMode = (afAddrMode_t)Addr16Bit;
    lock_router_app_dest_addr.endPoint = LOCK_CENTER_END_POINT_NUM;
    lock_router_app_dest_addr.addr.shortAddr = 0x0000;

    // Register the Application to receive the unprocessed Foundation command/response messages
    //zcl_registerForMsg( zclSampleDoorLockController_TaskID );

    // Register endpoint
    afRegister(&lock_router_ep);

    /*init device id*/
    if ( NV_OPER_FAILED != osal_nv_item_init (ZCD_NV_DEVICE_ID, sizeof(uint32), NULL))
    {
        if (SUCCESS != osal_nv_read(ZCD_NV_DEVICE_ID, 0, sizeof(uint32), &device_id))
        {
            log_printf( "Error: read device id error.\r\n");
        }
    }
    else
    {
        log_printf( "Error: read device id error.\r\n");
    }

    ota_init();

    /*start network indication , led toggle*/
    osal_start_reload_timer(lock_router_app_task_id,
                LOCK_ROUTER_EVENT_LED_TOGGLE, TIME_INTERVAL_TOGGLE_LED);

    log_printf( "start router application, version = %s\r\n", SW_V);

    return ;
}

uint16 lock_router_app_event_loop( uint8 task_id, uint16 events )
{
    afIncomingMSGPacket_t *MSGpkt;

    (void)task_id;  // Intentionally unreferenced parameter

    if ( events & SYS_EVENT_MSG )
    {
        while ( (MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive( lock_router_app_task_id )) )
        {
            switch ( MSGpkt->hdr.event )
            {
                case MT_SYS_APP_MSG:
                    break;

                case ZDO_STATE_CHANGE:
                    lock_router_nework_state = (devStates_t)(MSGpkt->hdr.status);

                    // now on the network
                    if ( (lock_router_nework_state == DEV_ZB_COORD) ||
                       (lock_router_nework_state == DEV_ROUTER)   ||
                       (lock_router_nework_state == DEV_END_DEVICE) )
                    {
                        if (lock_router_nework_state == DEV_ZB_COORD)
                        {
                            log_printf( "Network established, address = 0x%x. \r\n", NLME_GetShortAddr());
                        }
                        if (lock_router_nework_state == DEV_ROUTER)
                        {
                            log_printf( "Joined network, address = 0x%x. \r\n", NLME_GetShortAddr());
                        }

                        /*stop toggle led*/
                        osal_stop_timerEx(lock_router_app_task_id, LOCK_ROUTER_EVENT_LED_TOGGLE);
                        SB_TURN_ON_LED1();
                        SB_TURN_ON_LED2();
#ifdef ROUTER
                        /*report device id every 5s untile response received*/
                        osal_start_reload_timer(lock_router_app_task_id,
                                    LOCK_ROUTER_EVENT_REPORT_DEVICE_ID, TIME_INTERVAL_REPORT_DEVICEID);

                        /*start offline detection*/
                        lock_router_offline_count = LOCK_ROUTER_OFFLINE_TIME;
                        osal_start_reload_timer( lock_router_app_task_id,
                            LOCK_ROUTER_EVENT_OFFLINE_DETECT, TIME_INTERVAL_OFFLINE_DETECT);
#endif
                    }
                    break;

                case AF_INCOMING_MSG_CMD:
#ifdef ROUTER
                    lock_router_msg_proc(MSGpkt);
#endif
                    break;

                default:
                    break;
            }

          // Release the memory
          osal_msg_deallocate( (uint8 *)MSGpkt );
        }

        // return unprocessed events
        return (events ^ SYS_EVENT_MSG);
    }

    if (events & LOCK_ROUTER_EVENT_OFFLINE_DETECT)
    {
        if (0 == lock_router_offline_count--)
        {
            lock_router_offline_count = LOCK_ROUTER_OFFLINE_TIME;
            SystemResetSoft();
        }

        if (lock_router_offline_count == 1)
        {
            log_printf( "WARNING: heart beat lost\r\n");
        }

        return ( events ^ LOCK_ROUTER_EVENT_OFFLINE_DETECT );
    }

#ifdef ROUTER
    if (events & LOCK_ROUTER_EVENT_REPORT_DEVICE_ID)
    {
        if (device_id_report_cnt == REPORT_DEVICE_ID_MAX_NUM)
        {
            log_printf( "report device id timeout, rejoin network.\r\n");
            SystemResetSoft();
            device_id_report_cnt = 0;
        }
        else
        {
            lock_router_report_device_id();
            device_id_report_cnt++;
        }

        return ( events ^ LOCK_ROUTER_EVENT_REPORT_DEVICE_ID );
    }

    if (events & LOCK_ROUTER_EVENT_HB_ACK)
    {
        log_printf( "Send heart beat ack\r\n");
        if (ZSuccess != send_msg_to_center((uint8 *)Device_List, sizeof(Device_List_t)*Max_Dev_Num,
                                MSG_TYPE_HEART_BEAT, hb_tid))
            log_printf( "Error: send associated device info failed.\r\n");

        return ( events ^ LOCK_ROUTER_EVENT_HB_ACK );
    }

    if (events & LOCK_ROUTER_EVENT_OTA_RESET)
    {
        SystemResetSoft();
        return ( events ^ LOCK_ROUTER_EVENT_OTA_RESET );
    }
#endif

    if (events & LOCK_ROUTER_EVENT_LED_TOGGLE)
    {
        log_printf( "Network status = %d, DEV_ROUTER=%d\n", lock_router_nework_state, DEV_ROUTER);
        SB_TOGGLE_LED1();
        SB_TOGGLE_LED2();
        return ( events ^ LOCK_ROUTER_EVENT_LED_TOGGLE );
    }

    return 0;
}


#ifdef ROUTER

uint8 lock_router_factory_test_crc(uint8 *data,uint16 datalen)
{
    uint8 crc=0;
    uint16 i=0,j=0;
    for (i=0; i<datalen; i++)
    {
        crc ^= *data++;
        for(j = 0; j<8; j++)
        {
            if(crc & 0x80 )
                crc = (crc << 1) ^ 0x07;
            else
                crc <<= 1;
        }
    }
    crc &= 0xff;
    return crc;
}

void MT_AppFactoryTest(uint8 *pBuf)
{
    uint8 SN_char[SN_MAX_LEN + 1] = {0};
    uint32 sn_int = 0;
    uint32 sn_int_read = 0;
    uint8 nvret = 0;

    strncpy((char *)SN_char , (char *)pBuf+MT_RPC_FRAME_HDR_SZ, SN_MAX_LEN);
    sn_int = atol((const char *)SN_char);
    nvret = osal_nv_item_init (ZCD_NV_DEVICE_ID, sizeof(uint32), &sn_int );
    if (nvret != NV_OPER_FAILED )
    {
        nvret = osal_nv_write(ZCD_NV_DEVICE_ID, 0, sizeof(uint32), &sn_int);
        if (nvret != SUCCESS)
        {
            log_printf( "Error: save device id error! error code is %d .\n", nvret);
        }
        else
        {
            nvret = osal_nv_read(ZCD_NV_DEVICE_ID, 0, sizeof(uint32), &sn_int_read);
            if (nvret != SUCCESS)
            {
                log_printf( "Error: read device id error! error code is %d .\n", nvret);
            }
            if (sn_int != sn_int_read)
            {
                log_printf( "Error: device id verification error! write %d but read %d.\n", sn_int, sn_int_read);
            }
            else
            {
                device_id = sn_int;
                osal_memset(SN_char, 0, SN_MAX_LEN + 1);
                int2str(SN_char, device_id);
                log_printf( "SN = %s.\n", SN_char); /*print %lu error*/
            }
        }
    }
    else
    {
        log_printf( "Error: save device id error! error code is %d .\n", nvret);
    }

    save_hw_ver(pBuf+MT_RPC_FRAME_HDR_SZ+SN_MAX_LEN);

    return ;
}


void lock_router_report_device_id(void)
{
    uint8 ret = 0;

    log_printf( "report device id %ld.\r\n", device_id);

    ret = send_msg_to_center((uint8*)&device_id, sizeof(uint32), MSG_TYPE_DEVICE_ID, msg_tid);
    if (ret != ZSuccess)
    {
        log_printf( "Error: send device id msg error, error code is %d.\r\n", ret);
        return ;
    }

    return ;
}


/**
 * Return CRC-8 of the data, using x^8 + x^2 + x + 1 polynomial.  A table-based
 * algorithm would be faster, but for only a few bytes it isn't worth the code
 * size. */
uint8 lock_router_msg_crc(const void *vptr, int len)
{
    const uint8 *data = vptr;
    uint32 crc = 0;
    int32 i, j;
    for (j = len; j; j--, data++) {
        crc ^= (*data << 8);
        for(i = 8; i; i--) {
            if (crc & 0x8000)
                crc ^= (uint32)(0x1070 << 3);
            crc <<= 1;
        }
    }
    return (uint8)(crc >> 8);
}

void lock_router_hb_proc(uint8 *pkt)
{
    uint16 SendDelay = 0;

    hb_tid = pkt[3];
    hb_tid = (hb_tid << 8) | pkt[2];

    lock_router_offline_count = LOCK_ROUTER_OFFLINE_TIME;

    log_printf( "Associated Devices:\r\n");
    for(uint8 i=0; i<Max_Dev_Num; i++)
    {
        Device_List[i].nwkAddr = AssociatedDevList[i].shortAddr;
        Device_List[i].lqi = AssociatedDevList[i].linkInfo.rxLqi;
//        Device_List[i].dev_type = 0x01;
        Device_List[i].nodeRelation = AssociatedDevList[i].nodeRelation;

        if (Device_List[i].nwkAddr != 0xFFFF)
        {
            log_printf( "index=%d, addr=0x%x, lqi=%d, relation=%d\r\n", i, Device_List[i].nwkAddr, Device_List[i].lqi, Device_List[i].nodeRelation);
        }
    }

    SendDelay = HB_ACK_DELAY_BASE + osal_rand() & HB_ACK_DELAY_MASK; //allows a jitter of 2 seconds

    log_printf( "Received heart beat package, Ack delay = %d\r\n", SendDelay);

    osal_start_timerEx(lock_router_app_task_id, LOCK_ROUTER_EVENT_HB_ACK, SendDelay);

    return ;
}

void lock_router_msg_proc(afIncomingMSGPacket_t *msg)
{
    uint8 len = 0;
    uint8 type = 0;
    uint8 *pdata = NULL;
    uint8 crc = 0;
    uint8 crc_cal = 0;

    pdata = msg->cmd.Data;
    len = pdata[0];
    type = pdata[1];
    crc = pdata[len];

#ifdef MSG_DEBUG_ON
    {
        log_printf("RECEIVED:");
        for (uint16 i = 0; i < len; i++)
            log_printf(" %X", pdata[i]);
        log_printf("\r\n");
    }
#endif

    crc_cal = lock_router_msg_crc(pdata, len);
    if (crc != crc_cal)
    {
        log_printf( "Error: crc error, received crc is %d, calculated crc is %d.\r\n", crc, crc_cal);
        return ;
    }

    switch (type)
    {
        case MSG_TYPE_DEVICE_ID:
            /*stop report*/
            flag_deviceid_send_succeed = true;
            osal_stop_timerEx(lock_router_app_task_id, LOCK_ROUTER_EVENT_REPORT_DEVICE_ID);

            log_printf( "report device id successfully.\r\n");

            break;

       case MSG_TYPE_HEART_BEAT:
            lock_router_hb_proc(pdata);
            break;

        case MSG_TYPE_OTA_GET_SW_VER:
            ota_notify(pdata, len);
            break;

        case MSG_TYPE_OTA_MSG:
            ota_msg_proc(pdata, len);
            break;

        case MSG_TYPE_OTA_CRC_CHK:
            ota_msg_check_crc(pdata, len);
            break;

        case MSG_TYPE_RESET:
            SystemResetSoft();
            break;

        default:
            break;
    }

    return ;
}

uint8 send_msg_to_center(uint8 *data, uint8 len, uint8 type, uint16 tid)
{
    uint8 buf[96] = {0};

    if (len > (96-6))
    {
        log_printf("Error: send message too long, len = %d.\r\n", len);
        return ZFailure;
    }

    buf[0] = 0XAA;
    buf[1] = 0X55;
    buf[2] = len;
    buf[3] = type;
    buf[4] = tid & 0XFF;
    buf[5] = (tid >> 8) & 0X00FF;
    osal_memcpy(&buf[6], data, len);

#ifdef MSG_DEBUG_ON
    {
        uint8 i;
        log_printf("SENT:");
        for (i = 0; i < len + 6; i++)
            log_printf(" %X", buf[i]);
        log_printf("\r\n");
    }
#endif

    lock_router_app_seq_num++;
/*
    return AF_DataRequest(&lock_router_app_dest_addr,
                                    &lock_router_ep, 0, len + 6, buf,
                                    &lock_router_app_seq_num, 0, AF_DEFAULT_RADIUS );*/
    return AF_DataRequest(&lock_router_app_dest_addr,
            &lock_router_ep, 5, len + 6, buf,
            &lock_router_app_seq_num, 0, 0xEE );
}


#endif

