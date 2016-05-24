


#ifndef LOCK_ROUTER_APP_H
#define LOCK_ROUTER_APP_H

#ifdef __cplusplus
extern "C"
{
#endif



#define LOCK_APP_PROFILE_ID  0xbf01  /*app profile, use manufacturer-specific profile*/
#define LOCK_END_POINT_NUM  0x01
#define LOCK_APP_DEVICE_ID  0x01

#define ZCD_NV_DEVICE_ID   0x0402

#define   LOCK_ROUTER_EVENT_LED_TOGGLE  0x0001
#define   LOCK_ROUTER_EVENT_REPORT_DEVICE_ID  0x0002
#define   LOCK_ROUTER_EVENT_OFFLINE_DETECT  0x0004


#define TIME_INTERVAL_REPORT_DEVICEID 5000
#define TIME_INTERVAL_TOGGLE_LED 1000
#define TIME_INTERVAL_OFFLINE_DETECT 5000

#define LOCK_ROUTER_OFFLINE_TIME  10  /*10x5s*/

//Base time with jitter
#define BASE_TIME               0x000A

#define MSG_TYPE_DEVICE_ID 0x09
#define MSG_TYPE_DEVICE_ID_RESPONSE  0x0a
#define MSG_TYPE_HEART_BEAT  0x0b

#define SN_BUFFER_LENGTH 48
#define RET_SUCCESS     0
#define RET_LEN_ERR     1
#define RET_SAVE_ERR    2
#define RET_HEADER_ERR 3
#define RET_CRC_ERR 4
#define RET_VERIFY_ERR 5


void lock_router_app_Init(uint8 task_id);
uint16 lock_router_app_event_loop( uint8 task_id, uint16 events );
#ifdef ROUTER
void lock_router_hb_proc(uint8 *pkt);
uint8 lock_router_factory_test_crc(uint8 *data,uint16 datalen);
void MT_AppFactoryTest(uint8 *pBuf);
void lock_router_report_device_id(void);
#endif
uint8 lock_router_msg_crc(const void *vptr, int len);
void lock_router_msg_proc(afIncomingMSGPacket_t *msg);

#endif


