#include <stdlib.h>
#include <string.h>
//#include "ZComDef.h"
#include "OSAL.h"
#include "AF.h"
#include "onboard.h"
#include "hal_led.h"
#include "hal_board_cfg.h"
#include "lock_router_app.h"
#include "router_print.h"
#include "infrare_power.h"


extern uint8 lock_router_app_task_id;
uint8 report_infrare_success = false;
uint8 g_infrare_reporting = false;
uint8 report_infrare_count = 0;
uint8 report_dev_meta_success = false;
uint8 dev_meta_report_cn = 0;

static switch_object_t switch_object;

static char read_power_key_value(void);
static key_status_e get_power_key_state(void);
static void infrare_detect_init(void);
static void power_control_init(void);
static void power_key_init(void);
static void power_turn_on(void);
static void power_turn_off(void);
static int8 get_infrare_statue(void);
static switch_object_t* get_switch_object(void);
static void update_switch_state(char reason);
static int8 is_turn_off(void);


/**configure the P0_1 pin to GPIO, input modem
*and configure the input mode to pull down
*configure the irq to rising trig
*/
static void infrare_detect_init(void)
{
    INFRARE_PORT_SEL &= ~BV(1);   //GPIO
    INFRARE_PORT_DIR &= ~BV(1);   //input

    PORT0_PULL_UPDOWN |= BV(5);
    INFRARE_PULL_UPDOWN_EN &= ~BV(1);

    INFRARE_PORT_IRQ_EN |= BV(1);    //使能P0_7引脚中断
    SYSTEM_IRQ_EN     = 1;       //开总中断
    PORT0_IRQ_IEN  |= BV(5);    //允许P0口中断
    INFRARE_PORT_PXIFG &= ~BV(1);   //初始化中断标志位
    INFRARE_IRQ_MODE &= 0x00;    //clear the edge bit
    INFRARE_IRQ_MODE |= 0x00;    //上升沿触发
}



/*configure the P0_5 pin to GPIO, output modem*/
static void power_control_init(void)
{
    POWER_CONTROL_PORT_SEL &= ~BV(5);   //GPIO
    POWER_CONTROL_PORT_DIR |= BV(5);   //output
    //reset_bit(POWER_CONTROL_PORT);
}

/*configure the P0_6 pin to GPIO, input modem, pull up*/
static void power_key_init(void)
{
    POWER_KEY_PORT_SEL &= ~BV(6);   //GPIO
    POWER_KEY_PORT_DIR &= ~BV(6);   //input

    //PORT0_PULL_UPDOWN &= ~BV(5);
    //POWER_PULL_UPDOWN_EN &= ~BV(6);
}

static void power_turn_on(void)
{
    //reset_bit(POWER_CONTROL_PORT);
    set_bit(POWER_CONTROL_PORT);
    log_printf( ">>>power_turn_on.\r\n");
}

static void power_turn_off(void)
{
    //set_bit(POWER_CONTROL_PORT);
    reset_bit(POWER_CONTROL_PORT);
    log_printf( ">>>power_turn_off.\r\n");
}

static int8 get_infrare_statue(void)
{
    return !!(INFRARE_PORT);
}

int8 infrare_event_process(void)
{
    int8 status = 0;
    status = get_infrare_statue();
    if (status == EXIST_SOMEONE)
    {
        power_turn_on();
        update_switch_state(INFRARE_ON);
        if (switch_object.switch_state == SWITCH_OFF)
        {
            switch_object.switch_state = SWITCH_ON;
        }
    }
    else if (status == NO_BODY)
    {
        log_printf( "there is no anyone.\r\n");
    }
    else
    {
        log_printf( "error happens.\r\n");
    }
    return status;
}

/**************************************************************************************************
 * @fn      halKeyPort0Isr
 *
 * @brief   Port0 ISR
 *
 * @param
 *
 * @return
 **************************************************************************************************/
HAL_ISR_FUNCTION( halKeyPort0Isr, P0INT_VECTOR )
{
  HAL_ENTER_ISR();

  if (P0IFG & 0X80)
  {
    //halProcessKeyInterrupt();
    //osal_set_event(lock_router_app_task_id, INFRARE_DETECT_EVENT);

     osal_set_event(lock_router_app_task_id, INFRARE_DETECT_EVENT);
  }

  /*
    Clear the CPU interrupt flag for Port_0
    PxIFG has to be cleared before PxIF
  */
  P0IFG = 0;
  P0IF = 0;

  CLEAR_SLEEP_MODE();
  HAL_EXIT_ISR();
}

void infrare_report(int8 infrared_status)
{
    uint8 ret = 0;
    uint16 tid = 0; //always is 0
    if (infrared_status < 0) {
        osal_stop_timerEx(lock_router_app_task_id, EVENT_REPORT_INFRARE);
        return;
    }

    ret = send_msg_to_center((uint8 *)&infrared_status, sizeof(infrared_status), MSG_TYPE_INFRARE, tid);
    if (ret != ZSuccess)
    {
        log_printf( "Error: send body detect status error, error code is %d.\r\n", ret);
        return ;
    }
#ifdef MT_POWER_DEBUG
    log_printf( "report infrare detect status:infrared_cmd = %d.\r\n", infrared_status);
#endif
    report_infrare_success = FALSE;
    return;

}

static uint32 get_dev_devid(void) //reserved interface, 2000020055
{
    uint32 dev_id = 0;

#ifdef POWER_SWITCH_DEV
    dev_id = 1111122222;
#endif

    return dev_id;
}

static uint16 get_dev_type(void)
{
    uint16 dev_type = INVALID_TYPE;
#ifdef POWER_SWITCH_DEV
    dev_type = POWER_SWITCH_TYPE;
#endif

    return dev_type;
}


void report_dev_meta_info(short tid)
{
    uint8 ret = 0;
    dev_meta_t dev_meta;
    dev_meta.dev_id= get_dev_devid();
    dev_meta.dev_type = get_dev_type();

    //return af send status
    ret = send_msg_to_center((uint8 *)&dev_meta, sizeof(dev_meta), MSG_TYPE_POWERID_REPORT, tid);
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

/*
-------------------------------
total len  | type | tid   | payload  |  crc
-------------------------------
  1 byte   |  1    |  2     |  var       |   1 byte
 -------------------------------
  */
void power_switch_proc(uint8* pdata)
{
    uint8 switch_cmd = pdata[4];
    int8 off_flag = 0;

    //log_printf("---recv power cmd, switch_cmd = %d.\r\n", switch_cmd);
    if (switch_cmd == SWITCH_ON)
    {
#ifdef GATEWAY_IS_ALWAYS_POWERED
        power_turn_on();
        update_switch_state(INFRARE_ON);
        if (switch_object.switch_state == SWITCH_OFF)//SWITCH_ON
        {
            switch_object.switch_state = SWITCH_ON;
        }
#endif
    }
    else if (switch_cmd == SWITCH_OFF)
    {
        off_flag = is_turn_off();
        if (off_flag == 1)
        {
            power_turn_off();
            update_switch_state(INFRARE_OFF);
            if (switch_object.switch_state == SWITCH_ON)//SWITCH_ON
            {
                switch_object.switch_state = SWITCH_OFF;
            }
        }
    }
    else
    {
        //log_printf("switch_cmd is error, switch_cmd = %d.\r\n", switch_cmd);
    }
}

static char read_power_key_value(void)
{
    unsigned char power_key_value = 0;

    power_key_value = !!(POWER_KEY_PORT);
#ifdef  MT_POWER_DEBUG
    log_printf( "---power_level = %x.\r\n",power_key_value);
#endif

    if (power_key_value == LOW_LEVEL)
    {
        //log_printf( "---read low level.\r\n");
    }
    else if (power_key_value == HIGH_LEVEL)
    {
        //log_printf( "---read high level.\r\n");
    }
    else
    {
        log_printf( "read power key error.\r\n");
    }

    return power_key_value;
}

/**
*LOW_LEVEL is pressed;HIGH_LEVEL is not pressed
*/
static key_status_e get_power_key_state(void)
{
    char power_level;
    static key_status_e key_status;
    power_level = read_power_key_value();

    switch(key_status)
    {
        case POWER_KEY_NO_PRESS:
            if (power_level == LOW_LEVEL)
            {
                key_status = POWER_KEY_FILTING;
            }
            break;

        case POWER_KEY_FILTING:
            if (power_level == LOW_LEVEL)
            {
                key_status = POWER_KEY_PRESS_DOWN;
            }
            else if (power_level == HIGH_LEVEL)
            {
                key_status = POWER_KEY_NO_PRESS;
            }
            break;

        case POWER_KEY_PRESS_DOWN:
            if (power_level == HIGH_LEVEL)
            {
                key_status = POWER_KEY_PRESS_UP;
            }
            else
            {
            }
            break;

        case POWER_KEY_PRESS_UP:
            if (power_level == HIGH_LEVEL)
            {
                key_status = POWER_KEY_NO_PRESS;
            }
            else if (power_level == LOW_LEVEL)
            {
                key_status = POWER_KEY_FILTING;
            }
            break;

        default:
            break;
    }

    return key_status;
}

void power_key_switch(void)
{
    //static char switch_flag = SWITCH_OFF;
    key_status_e key_status;
    key_status = get_power_key_state();

    if (key_status != POWER_KEY_PRESS_UP) //
    {
#ifdef  MT_POWER_DEBUG
        log_printf("power_key_switch return directly.\r\n");
#endif
        return;
    }

    switch_object_t* pswitch_obj = get_switch_object();
    pswitch_obj->switch_state = SWITCH_ON;
    power_turn_on();
    update_switch_state(KEY_ON);
    infrare_report(EXIST_SOMEONE);
#if 0
    //switch_flag = !switch_flag;
    switch_object_t* pswitch_obj = get_switch_object();
    pswitch_obj->switch_state = 1 - (pswitch_obj->switch_state);

    if (pswitch_obj->switch_state == SWITCH_ON)
    {
        power_turn_on();
        update_switch_state(KEY_ON);
        infrare_report(EXIST_SOMEONE);
    }
    else
    {
        power_turn_off();
        update_switch_state(KEY_OFF);
    }

#endif
    return;
}


#ifdef MT_TEST
void test_key(void)
{
    char temp;
    power_turn_on();
    power_turn_off();

    temp = POWER_KEY_PORT;
    log_printf( "!!!temp = %d.\r\n", temp);
}

void test_bit_value(void)
{
    log_printf( "BV(7): expected = 0x80, actual = %x.\r\n", BV(7));
    log_printf( "BV(6): expected = 0x40, actual = %x.\r\n", BV(6));
    log_printf( "BV(5): expected = 0x20, actual = %x.\r\n", BV(5));
    log_printf( "BV(4): expected = 0x10, actual = %x.\r\n", BV(4));
    log_printf( "BV(3): expected = 0x08, actual = %x.\r\n", BV(3));
    log_printf( "BV(2): expected = 0x04, actual = %x.\r\n", BV(2));
    log_printf( "BV(1): expected = 0x02, actual = %x.\r\n", BV(1));
    log_printf( "BV(0): expected = 0x01, actual = %x.\r\n", BV(9));
    reset_bit(POWER_CONTROL_PORT);
    set_bit(POWER_CONTROL_PORT);
    reset_bit(POWER_CONTROL_PORT);
    set_bit(POWER_CONTROL_PORT);
}
#endif

void smartpower_init(void)
{
    infrare_detect_init();
    power_control_init();
    power_key_init();
    switch_object.switch_state = SWITCH_ON;
}

static switch_object_t* get_switch_object(void)
{
    return &switch_object;
}

static void update_switch_state(char reason)
{
    switch_object_t* pswitch_obj = get_switch_object();

    log_printf( "change reason = %d.\r\n", reason);
    if(reason == KEY_ON || reason == KEY_OFF)
    {
        pswitch_obj->key_flag = reason;
        pswitch_obj->key_ts = osal_GetSystemClock() / 1000;
    }
    else if(reason == INFRARE_ON || reason == INFRARE_OFF)
    {
        pswitch_obj->infrare_flag = reason;
        pswitch_obj->infrare_ts = osal_GetSystemClock() / 1000;
    }
}

static int8 is_turn_off(void)
{
    switch_object_t* pswitch_obj = get_switch_object();

    uint32 now_second = osal_GetSystemClock() / 1000;

    if (pswitch_obj->key_flag == KEY_ON)
    {
        //log_printf( "===judge from KEY_ON.\r\n");
        if ((now_second - pswitch_obj->key_ts) > KEY_ON_THRESHOLD)
        {
            pswitch_obj->key_flag = KEY_OFF;
            return 1;
        }
        else
            return 0;
    }
    else if (pswitch_obj->infrare_flag == INFRARE_ON)
    {
        //log_printf( "===judge from INFRARE_ON.\r\n");
        if ((now_second - pswitch_obj->infrare_ts) > INFRARE_ON_THRESHOLD)
        {
            pswitch_obj->infrare_flag = INFRARE_OFF;
            return 1;
        }
        else
            return 0;
    }

    log_printf( "return 1 directly.\r\n");
    return 1;
}