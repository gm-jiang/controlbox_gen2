


#ifndef LOCK_ROUTER_APP_H
#define LOCK_ROUTER_APP_H

#ifdef __cplusplus
extern "C"
{
#endif

//#define MSG_DEBUG_ON    1


#define LOCK_APP_PROFILE_ID  0x0104 /*app profile, use manufacturer-specific profile*/
#define LOCK_CENTER_END_POINT_NUM  0x01
#define LOCK_ROUTER_END_POINT_NUM  0x08
#define LOCK_APP_DEVICE_ID  0x01

#define ZCD_NV_DEVICE_ID   0x0402
#define ZCD_NV_OTA_INFO    0x0404

#define   LOCK_ROUTER_EVENT_LED_TOGGLE  0x0001
#define   LOCK_ROUTER_EVENT_REPORT_DEVICE_ID  0x0002
#define   LOCK_ROUTER_EVENT_OFFLINE_DETECT  0x0004
#define   LOCK_ROUTER_EVENT_HB_ACK  0x0008
#define   LOCK_ROUTER_EVENT_OTA_RESET  0x0010
#define   LOCK_ROUTER_EVENT_LINK_STATUS  0x0020

#define TIME_INTERVAL_REPORT_DEVICEID 5000
#define REPORT_DEVICE_ID_MAX_NUM    10   /*rejoin network after max num times report*/
#define TIME_INTERVAL_TOGGLE_LED 1000
#define TIME_INTERVAL_OFFLINE_DETECT 5000
#define TIME_INTERVAL_LINK_STATUS  5000
#define AGE_LIMIT    4
#define INVALID_ADDR0    0x0000
#define INVALID_ADDR1    0xFFFF

#define LOCK_ROUTER_OFFLINE_TIME  (60000/TIME_INTERVAL_OFFLINE_DETECT)  /*restart if no heart beat for 60s, that is 4 heart beats*/

#define HB_ACK_DELAY_BASE 10
#define HB_ACK_DELAY_MASK   0x07FF  /*2 seconds*/

#define MSG_TYPE_HEART_BEAT  62
#define MSG_TYPE_DEVICE_ID 61
#define MSG_TYPE_OTA_GET_SW_VER  31
#define MSG_TYPE_OTA_MSG  30
#define MSG_TYPE_OTA_CRC_CHK  32
#define MSG_TYPE_RESET 65

#define SN_MAX_LEN 10

#define RET_SUCCESS     0
#define RET_LEN_ERR     1
#define RET_SAVE_ERR    2
#define RET_HEADER_ERR 3
#define RET_CRC_ERR 4
#define RET_VERIFY_ERR 5

#define SW_V            "0.1"

void lock_router_app_Init(uint8 task_id);
uint16 lock_router_app_event_loop( uint8 task_id, uint16 events );
void lock_router_hb_proc(uint8 *pkt);
uint8 lock_router_factory_test_crc(uint8 *data,uint16 datalen);
void MT_AppFactoryTest(uint8 *pBuf);
void lock_router_report_device_id(void);
uint8 lock_router_msg_crc(const void *vptr, int len);
void lock_router_msg_proc(afIncomingMSGPacket_t *msg);
uint8 send_msg_to_center(uint8 *data, uint8 len, uint8 type, uint16 tid);
static void RemoveStaleNode(uint16 nwkaddr);
static void RouterApp_CleanAssociatedDevList(void);
#endif


