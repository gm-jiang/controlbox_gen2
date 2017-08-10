#ifndef INFRARE_POWER_H
#define INFRARE_POWER_H

#ifdef __cplusplus
extern "C"
{
#endif

#define POWER_SWITCH_DEV    //
//#define MT_POWER_DEBUG
//#define GATEWAY_IS_ALWAYS_POWERED


/*port definition*/
#define INFRARE_PORT         P0_7
#define POWER_KEY_PORT       P0_6
#define POWER_CONTROL_PORT   P0_5
#define LED_PORT   P0_0

/*port bit definition*/
#define INFRARE_BIT         BV(7) //0x80
#define PORT0_PULL_BIT      BV(5) //0x20
#define POWER_CONTROL_BIT   BV(5)
#define POWER_KEY_BIT       BV(6) //0X40


/*infrare port configure*/
#define INFRARE_PORT_SEL        P0SEL
#define INFRARE_PORT_DIR        P0DIR

/*pull up and pull down configure*/
#define PORT0_PULL_UPDOWN       P2INP
#define INFRARE_PULL_UPDOWN_EN  P0INP


/*infrare irq configure*/
#define INFRARE_PORT_IRQ_EN     P0IEN
#define SYSTEM_IRQ_EN           EA
#define PORT0_IRQ_IEN           IEN1
#define INFRARE_PORT_PXIFG      P0IFG
#define INFRARE_IRQ_MODE        PICTL


/*power control port configure*/
#define POWER_CONTROL_PORT_SEL  P0SEL
#define POWER_CONTROL_PORT_DIR  P0DIR

/*power key port configure*/
#define POWER_KEY_PORT_SEL      P0SEL
#define POWER_KEY_PORT_DIR      P0DIR
#define PORT0_PULL_UPDOWN       P2INP
#define POWER_PULL_UPDOWN_EN    P0INP


/*event definition*/
#define   INFRARE_DETECT_EVENT   0X0100


/*time period definiton*/
#define   REPORT_INFRARE_PERIOD  3000  // 3s
#define   DETECT_INFRARE_PERIOD  120000 //2min
//#define   DETECT_INFRARE_PERIOD  10000  //for debug, 10s
#define   REPORT_DEV_META_PERIOD   5000 //5s

/*general macro definition*/
#define   KEY_DETECT_PERIOD      10  //10ms
//#define   KEY_DETECT_PERIOD      1000  //10ms
#define   REPORT_DEV_META_MAX_NUM  10
//#define   SWITCH_OFF             0
//#define   SWITCH_ON              1
#define   EXIST_SOMEONE          1
#define   NO_BODY                0


#define TWO_HOURS 7200
#define KEY_ON_THRESHOLD TWO_HOURS

#define TWO_MINUTES     120
#define INFRARE_ON_THRESHOLD  TWO_MINUTES


#ifndef set_bit
    #define set_bit( x )     do { x = 1; } while (__LINE__ == -1)
#endif

#ifndef reset_bit
    #define reset_bit( x )     do { x = 0; } while (__LINE__ == -1)
#endif

typedef enum _switch_state
{
    SWITCH_OFF = 0,
    SWITCH_ON,
}switch_state_t;

typedef enum _switch_reason
{
    SWITCH_INIT=0,
    KEY_ON = 1,
    KEY_OFF = 2,
    INFRARE_ON = 3,
    INFRARE_OFF = 4,
}switch_reason_T;

typedef struct _switch_object
{
    char switch_state;//
    char key_flag;
    char infrare_flag;
    uint32 key_ts;
    uint32 infrare_ts;
}switch_object_t;


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


typedef enum _level_status
{
    LOW_LEVEL = 0,
    HIGH_LEVEL = 1,
}level_status_e;

typedef enum _key_status
{
    POWER_KEY_NO_PRESS = 0,
    POWER_KEY_FILTING,
    POWER_KEY_PRESS_DOWN,
    POWER_KEY_PRESS_UP
}key_status_e;

int8 infrare_event_process(void);
void infrare_report_success(void);
void power_switch_proc(uint8* pdata);
void infrare_report(int8 infrared_status);//infrared_status
void report_dev_meta_finish(void);
void report_dev_meta_info(short tid);
void power_key_switch(void);
void test_key(void);
void test_bit_value(void);
void smartpower_init(void);


#endif
