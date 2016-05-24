

#include "ZComDef.h"
#include "OSAL.h"
#include "AF.h"
#include "MT.h"
#include "ZDApp.h"
#include "ZDObject.h"
#include "OSAL_Nv.h"
#include "onboard.h"
#include "hal_led.h"
#include <stdlib.h>
#include <string.h>
#include "hal_board_cfg.h"
#include "lock_router_app.h"
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
uint32 tid_report_deviceid = 0;
uint32 device_id = 0;
devStates_t lock_router_nework_state = DEV_INIT;
afAddrType_t lock_router_app_dest_addr = {0};

SimpleDescriptionFormat_t lock_router_simple_desc =
{
  LOCK_END_POINT_NUM,             //  int Endpoint;
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
  LOCK_END_POINT_NUM,
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
  lock_router_app_dest_addr.endPoint = LOCK_END_POINT_NUM;
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

  /*start network indication , led toggle*/
  osal_start_reload_timer(lock_router_app_task_id, 
    LOCK_ROUTER_EVENT_LED_TOGGLE, TIME_INTERVAL_TOGGLE_LED);

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
            
#ifdef ROUTER
            /*report device id every 5s untile response received*/
            osal_start_reload_timer(lock_router_app_task_id, 
                LOCK_ROUTER_EVENT_REPORT_DEVICE_ID, TIME_INTERVAL_REPORT_DEVICEID);

            /*start offline detection*/
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
    #if 0
    if (0 == lock_router_offline_count--)
    {
      lock_router_offline_count = LOCK_ROUTER_OFFLINE_TIME;
      SystemResetSoft();
    }
    log_printf( "lock_router_offline_count:%d.\r\n", lock_router_offline_count );
    #endif

    return ( events ^ LOCK_ROUTER_EVENT_OFFLINE_DETECT );
  }

#ifdef ROUTER
  if (events & LOCK_ROUTER_EVENT_REPORT_DEVICE_ID)
  {
    lock_router_report_device_id();

    return ( events ^ LOCK_ROUTER_EVENT_REPORT_DEVICE_ID );
  }
#endif

  if (events & LOCK_ROUTER_EVENT_LED_TOGGLE)
  {
    SB_TOGGLE_LED1();
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
    uint8 dataLen = 0;
    uint8 datalen_calc = 0;
    uint8 *SN_data = NULL;
    
    uint8 SN_char[SN_BUFFER_LENGTH] = {0};
    uint32 sn_int = 0;
    uint32 sn_int_read = 0;
    uint8 crc_sn = 0, crc_ver = 0;
    uint8 ret = RET_SUCCESS;
    uint8 nvret = 0;

    /* parse header */
    dataLen = pBuf[MT_RPC_POS_LEN];
    SN_data = pBuf + MT_RPC_FRAME_HDR_SZ;

    datalen_calc = /*4 + SN_data[4] + 2 + */16 + SN_data[16] + 2; /*header+sn_len+sn+sn_check+ver_len+ver+ver_check*/
    if (datalen_calc !=  dataLen)
    {
        ret = RET_LEN_ERR;
        log_printf( "Error: data length error! needed %d bytes but only %d bytes data received.\n", dataLen,  datalen_calc);
    }
    else if ((SN_data[0] + SN_data[2]) == (SN_data[1] + SN_data[3]))
    {
        crc_sn = lock_router_factory_test_crc(&SN_data[4], SN_data[4] + 1);//+1 include the SN length
        crc_ver = lock_router_factory_test_crc(&SN_data[16], SN_data[16] + 1);
        if (crc_sn == SN_data[SN_data[4] + 5] && crc_ver == SN_data[SN_data[16]+17])
        {
            strncpy((char *)SN_char , (char *)&SN_data[5], SN_data[4]);
            sn_int = atoi((const char *)SN_char);
            nvret = osal_nv_item_init (ZCD_NV_DEVICE_ID, sizeof(uint32), &sn_int );
            if (nvret != NV_OPER_FAILED )
            {
                nvret = osal_nv_write(ZCD_NV_DEVICE_ID, 0, sizeof(uint32), &sn_int);
                if (nvret != SUCCESS)
                {
                    ret = RET_SAVE_ERR;
                    log_printf( "Error: save data error! error code is %d .\n", nvret);
                }
                else
                {
                    nvret = osal_nv_read(ZCD_NV_DEVICE_ID, 0, sizeof(uint32), &sn_int_read);
                    if (nvret != SUCCESS)
                    {
                        ret = RET_VERIFY_ERR;
                        log_printf( "Error: verification error! error code is %d .\n", nvret);
                    }
                    if (sn_int != sn_int_read)
                    {
                        ret = RET_VERIFY_ERR;
                        log_printf( "Error: verification error! write %d but read %d.\n", sn_int, sn_int_read);
                    }
                    else
                    {
                        device_id = sn_int;
                        log_printf( "Save SN number successfully. SN = %d.\n", sn_int);
                    }
                }
            }
            else
            {
                ret = RET_SAVE_ERR;
                log_printf( "Error: save data error! error code is %d .\n", nvret);
            }
        }
        else
        {
            ret = RET_CRC_ERR;
            log_printf( "Error: crc error!\n");
        }
    }
    else
    {
        ret = RET_HEADER_ERR;
        log_printf( "Error: packet header error! packet header is %d %d %d %d.\n", SN_data[0], SN_data[1], SN_data[2], SN_data[3]);
    }

    ret = ret;
    return ;
}

void lock_router_report_device_id(void)
{
    uint8 buf[10] = {0};
    uint8 ret = 0;
    uint8 len = 0;
    
    buf[0] = 0XAA;
    buf[1] = 0X55;
    buf[2] = sizeof(uint32);
    buf[3] = MSG_TYPE_DEVICE_ID;
    buf[4] = tid_report_deviceid & 0XFF;
    buf[5] = (tid_report_deviceid >> 8) & 0X00FF;
    osal_memcpy(&buf[6], &device_id, sizeof(uint32));
    len = 6 + sizeof(uint32);
    tid_report_deviceid++;

    log_printf( "report device id %d.\r\n", device_id);

    ret = AF_DataRequest(&lock_router_app_dest_addr, 
                                    &lock_router_ep, 0, len, buf,
                                    &lock_router_app_seq_num, 0, AF_DEFAULT_RADIUS );
    /*
    ret = zcl_SendCommand(LOCK_END_POINT_NUM,
                    &lock_router_app_dest_addr,
                    0x0101,
                    0, TRUE,
                    0, TRUE,
                    0,
                    lock_router_app_seq_num++,
                    len, buf);*/
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
    uint8 crc = 0;
    int i, j;
    for (j = len; j; j--, data++) {
        crc ^= (*data << 8);
        for(i = 8; i; i--) {
            if (crc & 0x8000)
                crc ^= (0x1070 << 3);
            crc <<= 1;
        }
    }
    return (uint8)(crc >> 8);
}

void lock_router_hb_proc(uint8 *pkt)
{
  uint16 SendDelay = 0;
  uint8 ret = 0;
  
  lock_router_offline_count = LOCK_ROUTER_OFFLINE_TIME;

  for(uint8 i=0;i<Max_Dev_Num;i++)
  {
    Device_List[i].nwkAddr = AssociatedDevList[i].shortAddr;
    Device_List[i].lqi = AssociatedDevList[i].linkInfo.rxLqi;
    Device_List[i].dev_type = 0x01;
  }

  SendDelay = BASE_TIME + (osal_rand() & 0x007F); //allows a jitter between 0-127 milliseconds
  if ( SendDelay ) {
    ret = zcl_SendCommand(LOCK_END_POINT_NUM,
                    &lock_router_app_dest_addr,
                    0x0101,
                    0, TRUE,
                    0, TRUE,
                    0,
                    lock_router_app_seq_num++,
                    sizeof(Device_List_t)*Max_Dev_Num, (uint8 *)Device_List);
    if (ret != ZSuccess)
    {
        log_printf( "Error: send device id msg error, error code is %d.\r\n", ret);
        return ;
    }
  }

  return ;
}


void lock_router_msg_proc(afIncomingMSGPacket_t *msg)
{
    uint8 len = 0;
    uint8 type = 0;
    uint8 *pdata = NULL;
    uint8 crc = 0;
    uint8 crc_cal = 0;
    uint8 i = 0;

    pdata = msg->cmd.Data;
    len = pdata[0];
    type = pdata[1];
    crc = pdata[len];

    crc_cal = lock_router_msg_crc(pdata, len);
    if (crc != crc_cal)
    {
        log_printf( "Error: crc error, received crc is %d, calculated crc is %d.\r\n", crc, crc_cal);
        return ;
    }

    while(i < len)
    {
      log_printf("%x ", pdata[i++]);
    }

    switch (type)
    {
        case MSG_TYPE_DEVICE_ID_RESPONSE:
          /*stop report*/
          flag_deviceid_send_succeed = true;
          osal_stop_timerEx(lock_router_app_task_id, LOCK_ROUTER_EVENT_REPORT_DEVICE_ID);

          log_printf( "report device id successfully.\r\n");

          break;

       case MSG_TYPE_HEART_BEAT:
          #ifdef ROUTER
          lock_router_hb_proc(pdata);
          #endif
          break;
            
        default:
            break;
    }

    return ;
}
#endif

