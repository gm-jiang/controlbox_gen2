#ifndef INFRARE_POWER_H
#define INFRARE_POWER_H

#ifdef __cplusplus
extern "C"
{
#endif

/*************this block is for *******************/
#define PANASONIC_DEV

/*************this block is for *******************/

//#define MT_POWER_DEBUG
//#define GATEWAY_IS_ALWAYS_POWERED


/*event definition*/
#define   INFRARE_DETECT_EVENT   0X0100
#define   PANASONIC_DETECT_EVENT 0X0100



/*time period definiton*/
#define   REPORT_INFRARE_PERIOD  3000  // 3s
#define   DETECT_INFRARE_PERIOD  120000 //2min
#define   REPORT_DEV_META_PERIOD   5000 //5s

/*general macro definition*/

#define   REPORT_DEV_META_MAX_NUM  10
#define   EXIST_SOMEONE          1
#define   NO_BODY                0

#define   SENSOR_HEARTBEAT_PERIOD      5000


#define TWO_HOURS 7200
#define KEY_ON_THRESHOLD TWO_HOURS

#define TWO_MINUTES     120
#define INFRARE_ON_THRESHOLD  TWO_MINUTES

extern uint8 dev_meta_report_cn;
extern uint8 report_infrare_success;
extern uint8 g_infrare_reporting;
extern uint8 report_infrare_count;

typedef struct dev_meta
{
    uint32 dev_id;
    uint16 dev_type;
    //unsigned short nwkAddr;
}dev_meta_t;

typedef enum dev_type
{
    INVALID_TYPE      = 0,
    POWER_SWITCH_TYPE =  91,
    INFRARE_MATRIX_TYEP = 92,
    ULTRA_SOUND_TYPE  = 93,
}dev_type_e;

#define PANASONIC_TYPE   POWER_SWITCH_TYPE  //in order to avoid modifing the code of controlbox, so use this, it will be modify when debuged down

void infrare_report_success(void);
void infrare_report(int8 infrared_status);//infrared_status
void report_dev_meta_finish(void);
void report_dev_meta_info(short tid);


#define SOP      0
#define MODE     1
#define HEAD0    2
#define HEAD1    3
#define DATA     4
#define FCS      5

#define PANASONIC_USART_PORT HAL_UART_PORT_1

void panasonic_sensor_init (void);
void panasonic_uart_cb ( uint8 port, uint8 event );


#endif
