/**
  @file  tempsensor.c
  @brief TI RTOS ZCL Home Automation Temperature Sensor sample application
         interfacing with ZStack.

         The application interacts with the ZStack Thread
         via both messaging interface and C function interface.

  <!--
  Copyright 2015 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
  -->
*/

/**

  Main Screen Description:

                                KEY UP (or S1)
                                  - Send current temperature
                                 |
    KEY LEFT (or S4)             |      KEY RIGHT(or S2)
     -                         --+-----  - Invoke EZMode
                                 |
                                 |
                                KEY DOWN
                                 - Adjust temperature

    KEY_SELECT (or S5)
     -  Go to Help screen


  Temperature Screen Description:

                                KEY UP (or S1)
                                  - Increase temperature
                                 |
    KEY LEFT (or S4)             |      KEY RIGHT(or S2)
     -                         --+-----  -
                                 |
                                 |
                                KEY DOWN
                                 - Decrease temperature

    KEY_SELECT (or S5)
     -  Enter temperature

*/

//*****************************************************************************
// Includes
//*****************************************************************************

#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/family/arm/cc26xx/Power.h>
#include <string.h>
#include <inc/hw_ints.h>
#include "ICall.h"

#include "zstackapi.h"

#include <ioc.h>

#include "Board.h"

#include "board_key.h"
#include "board_lcd.h"
#include "board_led.h"

#include "zcl.h"
#include "zcl_general.h"
#include "zcl_ha.h"
#include "zcl_ms.h"

#if defined (ZCL_EZMODE)
#include "zcl_ezmode.h"
#endif

#include "util.h"
#include "zcl_port.h"
#include "tempsensor.h"
#include "znwk_config.h"

//*****************************************************************************
// Constants
//*****************************************************************************

/* Event IDs */
#define TEMPSENSOR_IDENTIFY_TIMEOUT_EVT       0x0001
#define TEMPSENSOR_POLL_CONTROL_TIMEOUT_EVT   0x0002
#define TEMPSENSOR_EZMODE_TIMEOUT_EVT         0x0004
#define TEMPSENSOR_EZMODE_NEXTSTATE_EVT       0x0008
#define TEMPSENSOR_MAIN_SCREEN_EVT            0x0010
#define TEMPSENSOR_TEMP_SEND_EVT              0x0020
#define TEMPSENSOR_KEY_EVENT                  0x0040

/* Debounce timeout in ticks */
#define TEMPSENSOR_KEY_DEBOUNCE_TIMEOUT       200

#define TEMPSENSOR_MAX_ATTRIBUTES             17

#define TEMPSENSOR_EP                         8

#define TEMPSENSOR_DEVICE_VERSION             0
#define TEMPSENSOR_FLAGS                      0

#define TEMPSENSOR_HWVERSION                  0
#define TEMPSENSOR_ZCLVERSION                 0

#define TEMPSENSOR_LIGHT_OFF                  0x00
#define TEMPSENSOR_LIGHT_ON                   0x01

#define TEMPSENSOR_MAX_INCLUSTERS             3
#define TEMPSENSOR_MAX_OUTCLUSTERS            1

// Application Display Modes
#define TEMPSENSOR_MAINMODE                   0x00
#define TEMPSENSOR_HELPMODE                   0x01

#define TEMPSENSOR_MAINSCREEN_TIMEOUT         3000  // 3 Seconds

#define TEMPSENSOR_INIT_TIMEOUT_VALUE         100

#define TEMPSENSOR_MAX_LCD_LINE               20

#define TEMPSENSOR_1SEC_MSEC                  1000

#define TEMPSENSOR_CONVERT_TO_SECONDS(a)      ((a)/TEMPSENSOR_1SEC_MSEC)

//*****************************************************************************
// Global Variables
//*****************************************************************************

//*****************************************************************************
// Local Variables
//*****************************************************************************

// Semaphore used to post events to the application thread
static ICall_Semaphore sem;
static ICall_EntityID ztsEntity;

// Passed in function pointers to the NV driver
static NVINTF_nvFuncts_t *pfnZtsNV = NULL;

// Hold the device's Zstack state when recieved
static zstack_DevState savedState = zstack_DevState_HOLD;

// Task pending events
static uint16_t events = 0;

// Destination address to send the temperature reading
zstack_AFAddr_t ztsDstAddr;

// Transaction ID used to send data messages
static uint8_t ztsTransID = 0;

// ZStack Thread network information
static zstack_sysNwkInfoReadRsp_t *pNwkInfo = NULL;

// Key press parameters
static uint8_t keys;

// Clock/timer resources
static Clock_Struct identifyClkStruct;
static Clock_Handle identifyClkHandle;
static Clock_Struct mainScreenClkStruct;
static Clock_Handle mainScreenClkHandle;

#if defined (ZCL_EZMODE)
// Clock resources
static Clock_Struct ezmodeTimeoutClkStruct;
static Clock_Struct ezmodeStateClkStruct;

// Clock object for Ezmode timeout
static Clock_Handle ezmodeTimeoutClkHandle;
static Clock_Handle ezmodeStateClkHandle;
#endif // ZCL_EZMODE

// Display the main screen mode first
static uint8_t giTsScreenMode = TEMPSENSOR_MAINMODE;

// Permit joining default to disabled
static uint8_t gPermitDuration = 0;

// Cluster lists for the simple descriptor
static uint16_t inputClusters[TEMPSENSOR_MAX_INCLUSTERS] =
{
    ZCL_CLUSTER_ID_GEN_BASIC,
    ZCL_CLUSTER_ID_GEN_IDENTIFY,
    ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT
};
static uint16_t outputClusters[TEMPSENSOR_MAX_OUTCLUSTERS] =
{
    ZCL_CLUSTER_ID_GEN_IDENTIFY
};

// Endpoint descriptor
static endPointDesc_t zdlEpDesc = {0};
static SimpleDescriptionFormat_t afSimpleDesc = {0};

#if defined (ZCL_EZMODE)
// EZMode Commissioning control structure
static void ezmodeCB(zlcEZMode_State_t state, zclEZMode_CBData_t *pData);
static const zclEZMode_RegisterData_t ezmodeRegisterData =
{
    &zdlEpDesc.endPoint,
    TEMPSENSOR_EZMODE_NEXTSTATE_EVT,
    TEMPSENSOR_EZMODE_TIMEOUT_EVT,
    &ztsTransID,
    ezmodeCB
};
#endif // ZCL_EZMODE

// Strings used to display on the LCD
static const char sClearLine[]    = " ";
static const char sDeviceName[]   = "  Temp Sensor";
static const char sSwTempUp[]     = "Up: Raise Temp";
static const char sSwEZMode[]     = "Rt: EZ-Mode";
static const char sSwTempDown[]   = "Dn: Lower Temp";
static const char sSwHelp[]       = "Select: Help";
static const char zcStr[]  = "ZC: ";
static const char zrStr[]  = "ZR: ";
static const char zedStr[] = "Zed:";
static const char unknownStr[] = "Unk:";
static const char *const devInfoStrs[] = { zcStr, zrStr, zedStr, unknownStr };

/**
 * @internal A semaphore used to wait on a clock event
 */
extern ti_sysbios_knl_Semaphore_Handle semaphore0;

//*****************************************************************************
// Attribute Variables
//*****************************************************************************

// Attributes that aren't writable
static const uint8_t ztsHWRevision = TEMPSENSOR_HWVERSION;
static const uint8_t ztsZCLVersion = TEMPSENSOR_ZCLVERSION;
static const uint8_t ztsManufacturerName[] =
{
    16,
    'T', 'e', 'x', 'a', 's', 'I', 'n', 's',
    't', 'r', 'u', 'm', 'e', 'n', 't', 's'
};
static const uint8_t ztsModelId[] =
{
    16,
    'T', 'I', '0', '0', '0', '1', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
};
static const uint8_t ztsDateCode[] =
{
    16,
    '2', '0', '0', '6', '0', '8', '3', '1',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
};
static const uint8_t ztsPowerSource = POWER_SOURCE_BATTERY;

// Device location - updatable over the air
static uint8_t ztsLocationDescription[17] =
{
    16,
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
};
static uint8_t ztsPhysicalEnvironment = PHY_UNSPECIFIED_ENV;

// Attribute to control the device
static uint8_t ztsDeviceEnable = DEVICE_ENABLED;

// Identify Cluster
static uint16_t ztsIdentifyTime = 0;

// Temperature Sensor Cluster
static int16_t ztsMeasuredValue = 2200;  // 22.00C
static const int16_t ztsMinMeasuredValue = 1700;   // 17.00C
static const uint16_t ztsMaxMeasuredValue = 2700;  // 27.00C

// On/Off Cluster
static uint8_t  ztsOnOff = TEMPSENSOR_LIGHT_OFF;

//*****************************************************************************
// Local Function Prototypes
//*****************************************************************************

static void TempSensor_initialization(void);
static void TempSensor_initializeClocks(void);
static void TempSensor_registerEndpoints(void);
static void TempSensor_setupZStackIndications(void);
static void TempSensor_writeZStackParameters(void);
static void TempSensor_initializeZStack(void);
static void TempSensor_process(void);
static void TempSensor_processZStackMsgs(zstackmsg_genericReq_t *pMsg);
static void TempSensor_processAfIncomingMsgInd(
                                    zstack_afIncomingMsgInd_t *pInMsg);
static void TempSensor_handleKeys(uint8_t keys);

static void TempSensor_updateLcdDisplay(void);
static void TempSensor_updateLcdLine1Status(void);
static void TempSensor_updateLcdMainScreen(void);
static void TempSensor_updateLcdHelpScreen(void);

static void TempSensor_processKeyChangeCallback(uint8_t keysPressed);

static void TempSensor_processIdentifyTimeChange(void);
static void TempSensor_processIdentifyQueryResponseCallback(
    zclIdentifyQueryRsp_t *pRsp);
static void TempSensor_processIdentifyCallback(zclIdentify_t *pCmd);

static void TempSensor_sendTemp(void);

#if defined (ZCL_EZMODE)
static void TempSensor_processEzmodeTimerCallback(bool     start,
                                                  uint16_t event_id,
                                                  uint32_t timeout_value);
static void TempSensor_processEzmodeTimeoutCallback(UArg a0);
static void TempSensor_processEzmodeStateChangeCallback(UArg a0);
#endif // ZCL_EZMODE

static void TempSensor_processIdentifyTimeoutCallback(UArg a0);
static void TempSensor_processMainScreenTimeoutCallback(UArg a0);
static void TempSensor_setPollRate(uint32_t newPollRate);
static void TempSensor_startEzMode(void);
static void TempSensor_changeTemp(bool increment);

/*********************************************************************
 * ZCL General Profile Callback table
 */
static zclGeneral_AppCallbacks_t cmdCallbacks =
{
    NULL,                             // Basic Cluster Reset command
    TempSensor_processIdentifyCallback, // Identify command
#ifdef ZCL_EZMODE
    NULL,                             // Identify EZ-Mode Invoke command
    NULL,                             // Identify Update Commission State cmd
#endif
    NULL,                             // Identify Trigger Effect command
    TempSensor_processIdentifyQueryResponseCallback, // Identify Query Response
    NULL,        // On/Off cluster commands
    NULL,        // On/Off cluster enhanced command Off with Effect
    NULL,        // On/Off cluster enhanced command On with Recall Global Scene
    NULL,        // On/Off cluster enhanced command On with Timed Off
#ifdef ZCL_LEVEL_CTRL
    NULL,                             // Level Control Move to Level command
    NULL,                             // Level Control Move command
    NULL,                             // Level Control Step command
    NULL,                             // Level Control Stop command
#endif
#ifdef ZCL_GROUPS
    NULL,                             // Group Response commands
#endif
#ifdef ZCL_SCENES
    NULL,                             // Scene Store Request command
    NULL,                             // Scene Recall Request command
    NULL,                             // Scene Response command
#endif
#ifdef ZCL_ALARMS
    NULL,                            // Alarm (Response) commands
#endif
#ifdef SE_UK_EXT
    NULL,                            // Get Event Log command
    NULL,                            // Publish Event Log command
#endif
    NULL,                            // RSSI Location command
    NULL                             // RSSI Location Response command
};

const zclAttrRec_t ztsAttrs[TEMPSENSOR_MAX_ATTRIBUTES] =
{
    // *** General Basic Cluster Attributes ***
    {
        ZCL_CLUSTER_ID_GEN_BASIC, // Cluster IDs - defined in the foundation
                                  //    (ie. zcl.h)
        { // Attribute record
            ATTRID_BASIC_HW_VERSION, // Attribute ID - Found in Cluster Library
                                     //     header (ie. zcl_general.h)
            ZCL_DATATYPE_UINT8, // Data Type - found in zcl.h
            ACCESS_CONTROL_READ, // Variable access control - found in zcl.h
            (void *)&ztsHWRevision // Pointer to attribute variable
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_ZCL_VERSION,
            ZCL_DATATYPE_UINT8,
            ACCESS_CONTROL_READ,
            (void *)&ztsZCLVersion
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_MANUFACTURER_NAME,
            ZCL_DATATYPE_CHAR_STR,
            ACCESS_CONTROL_READ,
            (void *)ztsManufacturerName
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_MODEL_ID,
            ZCL_DATATYPE_CHAR_STR,
            ACCESS_CONTROL_READ,
            (void *)ztsModelId
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_DATE_CODE,
            ZCL_DATATYPE_CHAR_STR,
            ACCESS_CONTROL_READ,
            (void *)ztsDateCode
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_POWER_SOURCE,
            ZCL_DATATYPE_UINT8,
            ACCESS_CONTROL_READ,
            (void *)&ztsPowerSource
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_LOCATION_DESC,
            ZCL_DATATYPE_CHAR_STR,
            (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
            (void *)ztsLocationDescription
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_PHYSICAL_ENV,
            ZCL_DATATYPE_UINT8,
            (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
            (void *)&ztsPhysicalEnvironment
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_DEVICE_ENABLED,
            ZCL_DATATYPE_BOOLEAN,
            (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
            (void *)&ztsDeviceEnable
        }
    },

    // *** Identify Cluster Attribute ***
    {
        ZCL_CLUSTER_ID_GEN_IDENTIFY,
        { // Attribute record
            ATTRID_IDENTIFY_TIME,
            ZCL_DATATYPE_UINT16,
            (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
            (void *)&ztsIdentifyTime
        }
    },

    // *** On/Off Cluster Attributes ***
    {
        ZCL_CLUSTER_ID_GEN_ON_OFF,
        { // Attribute record
            ATTRID_ON_OFF,
            ZCL_DATATYPE_BOOLEAN,
            ACCESS_CONTROL_READ,
            (void *)&ztsOnOff
        }
    },

    // *** Temperature Measurement Attriubtes ***
    {
        ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT,
        { // Attribute record
            ATTRID_MS_TEMPERATURE_MEASURED_VALUE,
            ZCL_DATATYPE_INT16,
            ACCESS_CONTROL_READ,
            (void *)&ztsMeasuredValue
        }
    },
    {
        ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT,
        { // Attribute record
            ATTRID_MS_TEMPERATURE_MIN_MEASURED_VALUE,
            ZCL_DATATYPE_INT16,
            ACCESS_CONTROL_READ,
            (void *)&ztsMinMeasuredValue
        }
    },
    {
        ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT,
        { // Attribute record
            ATTRID_MS_TEMPERATURE_MAX_MEASURED_VALUE,
            ZCL_DATATYPE_UINT16,
            ACCESS_CONTROL_READ,
            (void *)&ztsMaxMeasuredValue
        }
    },
};

/**
 * @internal Clock handler function
 * @param a0 ignored
 */
Void tirtosapp_clock(UArg a0)
{
    /* Wake up the application thread when it waits for clock event */
    Semaphore_post(semaphore0);
}


/******************************************************************************
 * @fn          TempSensor_task
 *
 * @brief       Application task entry point for the ZStack HA Temperature
 *              Sensor Application.
 *
 * @param       pfnNV - pointer to the NV functions
 *
 * @return      none
 */
void TempSensor_task(NVINTF_nvFuncts_t *pfnNV)
{
    // Save and register the function pointers to the NV drivers
    pfnZtsNV = pfnNV;
    zclport_registerNV(pfnZtsNV, ZCL_PORT_SCENE_TABLE_NV_ID);

    // Initialize application
    TempSensor_initialization();

    // No return from task process
    TempSensor_process();
}

/******************************************************************************
 * @fn          TempSensor_initialization
 *
 * @brief       Initialize the application
 *
 * @param       none
 *
 * @return      none
 */
static void TempSensor_initialization(void)
{
    /* Initialize variables */
    ztsDstAddr.addrMode = zstack_AFAddrMode_NONE;
    ztsDstAddr.addr.shortAddr = 0;
    ztsDstAddr.endpoint = 0;
    ztsDstAddr.panID = 0;

#if defined (ZCL_EZMODE)
    zclport_registerEZModeTimerCB(TempSensor_processEzmodeTimerCallback);
#endif

    TempSensor_initializeClocks();

    /* Initialize keys */
    Board_Key_initialize(TempSensor_processKeyChangeCallback);

    /* Initialize the LCD */
    Board_LCD_open();
    LCD_WRITE_STRING( (char *)sDeviceName,  LCD_PAGE1 );
    LCD_WRITE_STRING( (char *)sSwEZMode,  LCD_PAGE2 );
    LCD_WRITE_STRING( (char *)sSwHelp,  LCD_PAGE3 );

    /* Initialize the LEDS */
    Board_Led_initialize();

    // Register the current thread as an ICall dispatcher application
    // so that the application can send and receive messages.
    ICall_registerApp(&ztsEntity, &sem);

    // Initialize the ZStack
    TempSensor_initializeZStack();
}

/******************************************************************************
 * @fn      TempSensor_initializeClocks
 *
 * @brief   Initialize Clocks
 *
 * @param   none
 *
 * @return  none
 */
static void TempSensor_initializeClocks(void)
{
    // Initialize the timers needed for this application
    identifyClkHandle = Util_constructClock(
        &identifyClkStruct,
        TempSensor_processIdentifyTimeoutCallback,
        TEMPSENSOR_INIT_TIMEOUT_VALUE,
        0,
        false,
        0);

    mainScreenClkHandle = Util_constructClock(
        &mainScreenClkStruct,
        TempSensor_processMainScreenTimeoutCallback,
        TEMPSENSOR_MAINSCREEN_TIMEOUT,
        0,
        false,
        0);

#if defined (ZCL_EZMODE)
    ezmodeTimeoutClkHandle = Util_constructClock(
        &ezmodeTimeoutClkStruct,
        TempSensor_processEzmodeTimeoutCallback,
        TEMPSENSOR_INIT_TIMEOUT_VALUE,
        0,
        false,
        0);

    ezmodeStateClkHandle = Util_constructClock(
        &ezmodeStateClkStruct,
        TempSensor_processEzmodeStateChangeCallback,
        TEMPSENSOR_INIT_TIMEOUT_VALUE,
        0,
        false,
        0);
#endif // ZCL_EZMODE
}

/******************************************************************************
 * @fn      TempSensor_registerEndpoints
 *
 * @brief   Setup a Zigbee HA Temperature Sensor Endpoint
 *
 * @param   none
 *
 * @return  none
 */
static void TempSensor_registerEndpoints(void)
{
    // Initialize the Temperature Sensor Simple Descriptor
    zdlEpDesc.endPoint = TEMPSENSOR_EP;
    afSimpleDesc.EndPoint = TEMPSENSOR_EP;
    afSimpleDesc.AppProfId = ZCL_HA_PROFILE_ID;
    afSimpleDesc.AppDeviceId = ZCL_HA_DEVICEID_TEMPERATURE_SENSOR;
    afSimpleDesc.AppDevVer = TEMPSENSOR_DEVICE_VERSION;
    afSimpleDesc.AppNumInClusters = sizeof(inputClusters) / sizeof(uint16_t);
    afSimpleDesc.pAppInClusterList = inputClusters;
    afSimpleDesc.AppNumOutClusters = sizeof(outputClusters) / sizeof(uint16_t);
    afSimpleDesc.pAppOutClusterList = outputClusters;
    zdlEpDesc.simpleDesc = &afSimpleDesc;
    (void)zclport_registerEndpoint(ztsEntity, &zdlEpDesc);
}

/******************************************************************************
 * @fn      TempSensor_setupZStackIndications
 *
 * @brief   Setup the Zstack Callbacks wanted
 *
 * @param   none
 *
 * @return  none
 */
static void TempSensor_setupZStackIndications(void)
{
    zstack_devZDOCBReq_t zdoCBReq = {0};

    // Register for Callbacks, turn on:
    //  Device State Change,
    //  ZDO Match Descriptor Response,
    zdoCBReq.has_devStateChange = true;
    zdoCBReq.devStateChange = true;

#if defined (ZCL_EZMODE)
    zdoCBReq.has_matchDescRsp = true;
    zdoCBReq.matchDescRsp = true;
#endif

    (void)Zstackapi_DevZDOCBReq(ztsEntity, &zdoCBReq);
}

/******************************************************************************
 * @fn      TempSensor_writeZStackParameters
 *
 * @brief   Initialize ZStack Parameters
 *
 * @param   none
 *
 * @return  none
 */
static void TempSensor_writeZStackParameters(void)
{
    zstack_sysConfigWriteReq_t writeReq = {0};
    uint8_t extendedPANID[] = ZNWK_CONFIG_EXTENDED_PAN_ID;

    // HA specifies no Multicast, use group broadcast
    writeReq.has_nwkUseMultiCast = true;
    writeReq.nwkUseMultiCast = false;

    // Update the Default Channel List, defined in znwk_config.h
    writeReq.has_chanList = true;
    writeReq.chanList = ZNWK_DEFAULT_CHANLIST;

    // Update the Extended PAN ID, defined in znwk_config.h
    writeReq.has_extendedPANID = true;
    memcpy(&(writeReq.extendedPANID), extendedPANID, 8);

    // Update the config PAN ID, defined in znwk_config.h
    writeReq.has_panID = true;
    writeReq.panID = ZNWK_CONFIG_PAN_ID;

    (void)Zstackapi_sysConfigWriteReq(ztsEntity, &writeReq);
}

/******************************************************************************
 * @fn      TempSensor_initializeZStack
 *
 * @brief   Initialize ZStack
 *
 * @param   none
 *
 * @return  none
 */
static void TempSensor_initializeZStack(void)
{
    // Initialize the ZStack Thread
    bool startDev = true; // default to start the ZStack thread

    // Setup the endpoints
    TempSensor_registerEndpoints();

    // Setup indications from ZStack
    TempSensor_setupZStackIndications();

#if defined (ZCL_EZMODE)
    startDev = zclport_isAlreadyPartOfNetwork(ztsEntity);

    // Register EZ-Mode
    zcl_RegisterEZMode(&ezmodeRegisterData);
    Board_Led_control(board_led_type_LED1, board_led_state_BLINK);
#endif

    if(startDev)
    {
        zstack_devStartReq_t startReq = {0};

        // Start the ZStack Thread
        startReq.startDelay = 0;
        (void)Zstackapi_DevStartReq(ztsEntity, &startReq);

#if defined (ZCL_EZMODE)
        LCD_WRITE_STRING( (char *)sClearLine, LCD_PAGE2 );
#endif
    }

    // Register the ZCL General Cluster Library callback functions
    zclGeneral_RegisterCmdCallbacks(TEMPSENSOR_EP, &cmdCallbacks);

    // Register the application's attribute list
    zcl_registerAttrList(TEMPSENSOR_EP, TEMPSENSOR_MAX_ATTRIBUTES, ztsAttrs);

    // Update the ZStack Parameters
    TempSensor_writeZStackParameters();
}

/******************************************************************************
 * @fn      TempSensor_process
 *
 * @brief   Application task processing start.
 *
 * @param   none
 *
 * @return  void
 */
static void TempSensor_process(void)
{
    /* Forever loop */
    for(;;)
    {
        ICall_ServiceEnum stackid;
        ICall_EntityID dest;
        zstackmsg_genericReq_t *pMsg;

        /* Wait for response message */
        if(ICall_wait(ICALL_TIMEOUT_FOREVER) == ICALL_ERRNO_SUCCESS)
        {
            /* Retrieve the response message */
            if(ICall_fetchServiceMsg(&stackid, &dest, (void **)&pMsg)
               == ICALL_ERRNO_SUCCESS)
            {
                if( (stackid == ICALL_SERVICE_CLASS_ZSTACK) &&
                    (dest == ztsEntity) )
                {
                    if(pMsg)
                    {
                        TempSensor_processZStackMsgs(pMsg);

                        // Free any separately allocated memory
                        Zstackapi_freeIndMsg(pMsg);
                    }
                }

                if(pMsg)
                {
                    ICall_freeMsg(pMsg);
                }
            }

            if(events & TEMPSENSOR_KEY_EVENT)
            {
                // Process Key Presses
                TempSensor_handleKeys(keys);
                keys = 0;
                events &= ~TEMPSENSOR_KEY_EVENT;
            }

            if(events & TEMPSENSOR_IDENTIFY_TIMEOUT_EVT)
            {
                // Process the Identify timer expiration
                if(ztsIdentifyTime > 0)
                {
                    ztsIdentifyTime--;
                }
                TempSensor_processIdentifyTimeChange();

                events &= ~TEMPSENSOR_IDENTIFY_TIMEOUT_EVT;
            }

            if(events & TEMPSENSOR_MAIN_SCREEN_EVT)
            {
                // Update the display
                giTsScreenMode = TEMPSENSOR_MAINMODE;
                TempSensor_updateLcdMainScreen();
                events &= ~TEMPSENSOR_MAIN_SCREEN_EVT;
            }

#ifdef ZCL_EZMODE
            if(events & TEMPSENSOR_EZMODE_NEXTSTATE_EVT)
            {
                // going on to next state
                zcl_EZModeAction(EZMODE_ACTION_PROCESS, NULL);
                events &= ~TEMPSENSOR_EZMODE_NEXTSTATE_EVT;
            }

            if(events & TEMPSENSOR_EZMODE_TIMEOUT_EVT)
            {
                // EZ-Mode timed out
                zcl_EZModeAction(EZMODE_ACTION_TIMED_OUT, NULL);
                events &= ~TEMPSENSOR_EZMODE_TIMEOUT_EVT;
            }
#endif // ZLC_EZMODE
        }
    }
}

/******************************************************************************
 * @fn      TempSensor_processZStackMsgs
 *
 * @brief   Process event from Stack
 *
 * @param   pMsg - pointer to incoming ZStack message to process
 *
 * @return  void
 */
static void TempSensor_processZStackMsgs(zstackmsg_genericReq_t *pMsg)
{
    switch(pMsg->hdr.event)
    {
        case zstackmsg_CmdIDs_DEV_STATE_CHANGE_IND:
            {
                // The ZStack Thread is indicating a state change
                zstackmsg_devStateChangeInd_t *pInd
                    = (zstackmsg_devStateChangeInd_t *)pMsg;

                // Only process the state change if it actually changed.
                if(savedState != pInd->req.state)
                {
                    savedState = pInd->req.state;

                    if((pInd->req.state == zstack_DevState_DEV_ZB_COORD)
                        || (pInd->req.state == zstack_DevState_DEV_ROUTER)
                        || (pInd->req.state == zstack_DevState_DEV_END_DEVICE))
                    {
                        // The device is part of a network, get the device's
                        // network parameters.
                        pNwkInfo = zclport_getDeviceInfo(ztsEntity);

                        // Update the display with network information
                        giTsScreenMode = TEMPSENSOR_MAINMODE;
                        TempSensor_updateLcdDisplay();
                        Board_Led_control(board_led_type_LED1,
                                          board_led_state_OFF);

                        if(pInd->req.state != zstack_DevState_DEV_END_DEVICE)
                        {
                            // Don't turn on LED if Power saving end device
                            Board_Led_control(board_led_type_LED4,
                                              board_led_state_ON);
                        }
                        else
                        {
                            // Change the default poll rate from 1 second to
                            // the config setting in znwk_config.h
                            TempSensor_setPollRate(ZNWK_POLL_RATE);
                        }

  #if defined (ZCL_EZMODE)
                        zcl_EZModeAction(EZMODE_ACTION_NETWORK_STARTED, NULL);
  #endif
                    }
                }
            }
            break;

#if defined (ZCL_EZMODE)
        case zstackmsg_CmdIDs_ZDO_MATCH_DESC_RSP:
            {
                zstackmsg_zdoMatchDescRspInd_t *pInd
                    = (zstackmsg_zdoMatchDescRspInd_t *)pMsg;
                zclEZMode_ActionData_t actionData;
                ZDO_MatchDescRsp_t *pRsp;

                /*
                 * Parse the Match Descriptor Response and give it to
                 * the ZCL EZMode module to process
                 */
                pRsp = (ZDO_MatchDescRsp_t *)ICall_allocMsg(
                    sizeof(ZDO_MatchDescRsp_t) + pInd->rsp.n_matchList);
                if(pRsp)
                {
                    pRsp->status = pInd->rsp.status;
                    pRsp->nwkAddr = pInd->rsp.nwkAddrOfInterest;
                    pRsp->cnt = pInd->rsp.n_matchList;
                    memcpy(pRsp->epList, pInd->rsp.pMatchList,
                           pInd->rsp.n_matchList);

                    actionData.pMatchDescRsp = pRsp;
                    zcl_EZModeAction(EZMODE_ACTION_MATCH_DESC_RSP, &actionData);
                    ICall_freeMsg(pRsp);
                }
            }
            break;
#endif // ZCL_EZMODE

        case zstackmsg_CmdIDs_AF_INCOMING_MSG_IND:
            {
                // Process incoming data messages
                zstackmsg_afIncomingMsgInd_t *pInd
                    = (zstackmsg_afIncomingMsgInd_t *)pMsg;
                TempSensor_processAfIncomingMsgInd( &(pInd->req) );
            }
            break;

        /*
         * These are messages/indications from ZStack that this
         * application doesn't process.  These message can be
         * processed by your application, remove from this list and
         * process them here in this switch statement.
         */
         case zstackmsg_CmdIDs_AF_DATA_CONFIRM_IND:
        case zstackmsg_CmdIDs_ZDO_DEVICE_ANNOUNCE:
        case zstackmsg_CmdIDs_ZDO_NWK_ADDR_RSP:
        case zstackmsg_CmdIDs_ZDO_IEEE_ADDR_RSP:
        case zstackmsg_CmdIDs_ZDO_NODE_DESC_RSP:
        case zstackmsg_CmdIDs_ZDO_POWER_DESC_RSP:
        case zstackmsg_CmdIDs_ZDO_SIMPLE_DESC_RSP:
        case zstackmsg_CmdIDs_ZDO_ACTIVE_EP_RSP:
        case zstackmsg_CmdIDs_ZDO_COMPLEX_DESC_RSP:
        case zstackmsg_CmdIDs_ZDO_USER_DESC_RSP:
        case zstackmsg_CmdIDs_ZDO_USER_DESC_SET_RSP:
        case zstackmsg_CmdIDs_ZDO_SERVER_DISC_RSP:
        case zstackmsg_CmdIDs_ZDO_END_DEVICE_BIND_RSP:
        case zstackmsg_CmdIDs_ZDO_BIND_RSP:
        case zstackmsg_CmdIDs_ZDO_UNBIND_RSP:
        case zstackmsg_CmdIDs_ZDO_MGMT_NWK_DISC_RSP:
        case zstackmsg_CmdIDs_ZDO_MGMT_LQI_RSP:
        case zstackmsg_CmdIDs_ZDO_MGMT_RTG_RSP:
        case zstackmsg_CmdIDs_ZDO_MGMT_BIND_RSP:
        case zstackmsg_CmdIDs_ZDO_MGMT_LEAVE_RSP:
        case zstackmsg_CmdIDs_ZDO_MGMT_DIRECT_JOIN_RSP:
        case zstackmsg_CmdIDs_ZDO_MGMT_PERMIT_JOIN_RSP:
        case zstackmsg_CmdIDs_ZDO_MGMT_NWK_UPDATE_NOTIFY:
        case zstackmsg_CmdIDs_ZDO_SRC_RTG_IND:
        case zstackmsg_CmdIDs_ZDO_CONCENTRATOR_IND:
        case zstackmsg_CmdIDs_ZDO_NWK_DISC_CNF:
        case zstackmsg_CmdIDs_ZDO_BEACON_NOTIFY_IND:
        case zstackmsg_CmdIDs_ZDO_JOIN_CNF:
        case zstackmsg_CmdIDs_ZDO_LEAVE_CNF:
        case zstackmsg_CmdIDs_ZDO_LEAVE_IND:
        case zstackmsg_CmdIDs_SYS_RESET_IND:
        case zstackmsg_CmdIDs_AF_REFLECT_ERROR_IND:
        case zstackmsg_CmdIDs_ZDO_TC_DEVICE_IND:
        case zstackmsg_CmdIDs_DEV_PERMIT_JOIN_IND:
            break;

        default:
            break;
    }
}

/******************************************************************************
 *
 * @fn          TempSensor_processAfIncomingMsgInd
 *
 * @brief       Process AF Incoming Message Indication message
 *
 * @param       pInMsg - pointer to incoming message
 *
 * @return      none
 *
 */
static void TempSensor_processAfIncomingMsgInd(
    zstack_afIncomingMsgInd_t *pInMsg)
{
    afIncomingMSGPacket_t afMsg;

    /*
     * All incoming messages are passed to the ZCL message processor,
     * first convert to a structure that ZCL can process.
     */
    afMsg.groupId = pInMsg->groupID;
    afMsg.clusterId = pInMsg->clusterId;
    afMsg.srcAddr.endPoint = pInMsg->srcAddr.endpoint;
    afMsg.srcAddr.panId = pInMsg->srcAddr.panID;
    afMsg.srcAddr.addrMode = (afAddrMode_t)pInMsg->srcAddr.addrMode;
    if( (afMsg.srcAddr.addrMode == afAddr16Bit)
        || (afMsg.srcAddr.addrMode == afAddrGroup)
        || (afMsg.srcAddr.addrMode == afAddrBroadcast) )
    {
        afMsg.srcAddr.addr.shortAddr = pInMsg->srcAddr.addr.shortAddr;
    }
    else if(afMsg.srcAddr.addrMode == afAddr64Bit)
    {
        memcpy(afMsg.srcAddr.addr.extAddr, &(pInMsg->srcAddr.addr.extAddr), 8);
    }
    afMsg.macDestAddr = pInMsg->macDestAddr;
    afMsg.endPoint = pInMsg->endpoint;
    afMsg.wasBroadcast = pInMsg->wasBroadcast;
    afMsg.LinkQuality = pInMsg->linkQuality;
    afMsg.correlation = pInMsg->correlation;
    afMsg.rssi = pInMsg->rssi;
    afMsg.SecurityUse = pInMsg->securityUse;
    afMsg.timestamp = pInMsg->timestamp;
    afMsg.nwkSeqNum = pInMsg->nwkSeqNum;
    afMsg.macSrcAddr = pInMsg->macSrcAddr;
    afMsg.radius = pInMsg->radius;
    afMsg.cmd.TransSeqNumber = pInMsg->transSeqNum;
    afMsg.cmd.DataLength = pInMsg->n_payload;
    afMsg.cmd.Data = pInMsg->pPayload;

    zcl_ProcessMessageMSG(&afMsg);
}

/******************************************************************************
 * @fn      TempSensor_handleKeys
 *
 * @brief   Callback service for keys
 *
 * @param   keys  - keys that were pressed
 *
 * @return  void
 */
static void TempSensor_handleKeys(uint8_t keys)
{
    if(keys == KEY_UP)
    {
        // increase temperature
        giTsScreenMode = TEMPSENSOR_MAINMODE;

        TempSensor_changeTemp(true);
    }

    if(keys == KEY_RIGHT)
    {
        // Start EZMode Commissioning
        if( (giTsScreenMode == TEMPSENSOR_MAINMODE) ||
            (giTsScreenMode == TEMPSENSOR_HELPMODE) )
        {
            giTsScreenMode = TEMPSENSOR_MAINMODE;

            TempSensor_startEzMode();
        }
    }

    if(keys == KEY_DOWN)
    {
        giTsScreenMode = TEMPSENSOR_MAINMODE;

        // decrease the temperature
        TempSensor_changeTemp(false);
    }

    // toggle permit join
    if(keys == KEY_LEFT)
    {
        giTsScreenMode = TEMPSENSOR_MAINMODE; // remove help screen if there

        if( pNwkInfo && ( (savedState == zstack_DevState_DEV_ZB_COORD)
                          || (savedState == zstack_DevState_DEV_ROUTER) ) )
        {
            zstack_zdoMgmtPermitJoinReq_t req;

            // toggle permit join
            gPermitDuration = gPermitDuration ? 0 : 0xff;

            req.nwkAddr = pNwkInfo->nwkAddr;
            req.duration = gPermitDuration;
            req.tcSignificance = true;

            Zstackapi_ZdoMgmtPermitJoinReq(ztsEntity, &req);
        }
    }

    if(keys == KEY_SELECT)
    {
        // Switch between Help and Main screens
        if(giTsScreenMode == TEMPSENSOR_MAINMODE)
        {
            giTsScreenMode = TEMPSENSOR_HELPMODE;
        }
        else if(giTsScreenMode == TEMPSENSOR_HELPMODE)
        {
            LCD_WRITE_STRING( (char *)sClearLine, LCD_PAGE2 );
            giTsScreenMode = TEMPSENSOR_MAINMODE;
        }
    }

    // update the display
    TempSensor_updateLcdDisplay();
}

/*********************************************************************
 * @fn      TempSensor_updateLcdDisplay
 *
 * @brief   Called to update the LCD display.
 *
 * @param   none
 *
 * @return  none
 */
static void TempSensor_updateLcdDisplay(void)
{
    // turn on LED2 for temperatures >= 24.00C
    if(ztsMeasuredValue >= 2400)
    {
        Board_Led_control(board_led_type_LED1, board_led_state_OFF);
        Board_Led_control(board_led_type_LED2, board_led_state_ON);
    }
    // turn on LED1 for temperatures <= 20.00C
    else if(ztsMeasuredValue <= 2000)
    {
        Board_Led_control(board_led_type_LED1, board_led_state_ON);
        Board_Led_control(board_led_type_LED2, board_led_state_OFF);
    }
    // turn on both LEDs (1&2) for temperatures between 20.00C and
    // 24.00C
    else
    {
        Board_Led_control(board_led_type_LED1, board_led_state_ON);
        Board_Led_control(board_led_type_LED2, board_led_state_ON);
    }

    // Update depending on Screen Mode
    if(giTsScreenMode == TEMPSENSOR_HELPMODE)
    {
        TempSensor_updateLcdHelpScreen();
    }
    else
    {
        TempSensor_updateLcdMainScreen();
    }
}

/*********************************************************************
 * @fn      TempSensor_updateLcdLine1Status
 *
 * @brief   Display LCD line 1 with network status
 *          only call after on network
 *          ZC: PPPP CH ADDR
 *          ZR: PPPP CH ADDR
 *          ZE: PPPP CH ADDR
 *
 * @param   none
 *
 * @return  none
 */
static void TempSensor_updateLcdLine1Status(void)
{
    int idx;
    char szLine[TEMPSENSOR_MAX_LCD_LINE];

    // Determine the device type
    if(savedState == zstack_DevState_DEV_ZB_COORD)
    {
        idx = 0;
    }
    else if(savedState == zstack_DevState_DEV_ROUTER)
    {
        idx = 1;
    }
    else if(savedState == zstack_DevState_DEV_END_DEVICE)
    {
        idx = 2;
    }
    else
    {
        idx = 3;
    }

    // If we've collected the device info from the ZStack Thread
    // display the device information on the screen
    //  ZE: PANx CH ADDR
    if(pNwkInfo)
    {
        memcpy(szLine, devInfoStrs[idx], 4);
        Util_uint16toa(pNwkInfo->panId, &szLine[4]);
        szLine[8] = ' ';
        Util_ltoa(pNwkInfo->logicalChannel, (void *)(&szLine[9]), 10);
        szLine[11] = ' ';
        Util_uint16toa(pNwkInfo->nwkAddr, &szLine[12]);
        LCD_WRITE_STRING(szLine,  LCD_PAGE1);
    }
}

/*********************************************************************
 * @fn      TempSensor_updateLcdMainScreen
 *
 * @brief   Called to display the main screen on the LCD.
 *
 * @param   none
 *
 * @return  none
 */
static void TempSensor_updateLcdMainScreen(void)
{
    char sDisplayTemp[TEMPSENSOR_MAX_LCD_LINE];

    TempSensor_updateLcdLine1Status();

    memset(sDisplayTemp, 0, TEMPSENSOR_MAX_LCD_LINE);

    // display current temperature
    memcpy(sDisplayTemp, "TEMP: ", 6);
    // convert temperature to whole number
    Util_ltoa( (ztsMeasuredValue / 100), (void *)(&sDisplayTemp[6]), 10 );
    memcpy(&sDisplayTemp[8], "C", 2);
    LCD_WRITE_STRING( (char *)sDisplayTemp,  LCD_PAGE2 );

    if((savedState == zstack_DevState_DEV_ZB_COORD)
        || (savedState == zstack_DevState_DEV_ROUTER))
    {
        if(gPermitDuration)
        {
            // The '*' means that permit join is enabled
            memcpy(sDisplayTemp, "Select: Help   *", 16);
        }
        else
        {
            memcpy(sDisplayTemp, "Select: Help    ", 16);
        }
        // display help key with permit join status
        LCD_WRITE_STRING(sDisplayTemp,  LCD_PAGE3);
    }
    else
    {
        // display help key
        LCD_WRITE_STRING( (char *)sSwHelp,  LCD_PAGE3 );
    }
}

/*********************************************************************
 * @fn      TempSensor_updateLcdHelpScreen
 *
 * @brief   Called to update the LCD display with the help screen.
 *
 * @param   none
 *
 * @return  none
 */
static void TempSensor_updateLcdHelpScreen(void)
{
    // Display the 3 help screen lines
    LCD_WRITE_STRING((char *)sSwTempUp, LCD_PAGE1);
    LCD_WRITE_STRING((char *)sSwEZMode, LCD_PAGE2);
    LCD_WRITE_STRING((char *)sSwTempDown, LCD_PAGE3);
}

/*********************************************************************
 * @fn      TempSensor_sendTemp
 *
 * @brief   Called to send current temperature information to the thermostat
 *
 * @param   none
 *
 * @return  none
 */
static void TempSensor_sendTemp(void)
{
#ifdef ZCL_REPORT
    zclReportCmd_t *pReportCmd;

    // Build and send a ZCL temperature reading to the matched device
    pReportCmd = ICall_malloc( sizeof(zclReportCmd_t) + sizeof(zclReport_t) );
    if(pReportCmd != NULL)
    {
        afAddrType_t dstAddr;

        // Fill in the destination address
        dstAddr.addrMode = (afAddrMode_t)ztsDstAddr.addrMode;
        dstAddr.addr.shortAddr = ztsDstAddr.addr.shortAddr;
        dstAddr.endPoint = ztsDstAddr.endpoint;
        dstAddr.panId = ztsDstAddr.panID;

        // Fill in the single attribute information for the temperature reading
        pReportCmd->numAttr = 1;
        pReportCmd->attrList[0].attrID = ATTRID_MS_TEMPERATURE_MEASURED_VALUE;
        pReportCmd->attrList[0].dataType = ZCL_DATATYPE_INT16;
        pReportCmd->attrList[0].attrData = (void *)(&ztsMeasuredValue);

        // Call ZCL function to send the report
        zcl_SendReportCmd(TEMPSENSOR_EP, &dstAddr,
                          ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT,
                          pReportCmd,
                          ZCL_FRAME_SERVER_CLIENT_DIR,
                          true,
                          ztsTransID++);

        ICall_free(pReportCmd);
    }
#endif  // ZCL_REPORT
}

/*********************************************************************
 * @fn      TempSensor_processKeyChangeCallback
 *
 * @brief   Key event handler function
 *
 * @param   keysPressed - ignored
 *
 * @return  none
 */
static void TempSensor_processKeyChangeCallback(uint8_t keysPressed)
{
    // Save the key press information
    keys = keysPressed;

    // set the key press event
    events |= TEMPSENSOR_KEY_EVENT;

    // Wake up the application thread when it waits for clock event
    Semaphore_post(sem);
}

#if defined (ZCL_EZMODE)
/*********************************************************************
 * @fn      ezmodeCB
 *
 * @brief   The Application is informed of events. This can be used to
 *          show on the UI what is going on during EZ-Mode
 *          steering/finding/binding.
 *
 * @param   state - ignored
 * @param   pData - EZMode state information
 *
 * @return  none
 */
static void ezmodeCB(zlcEZMode_State_t state, zclEZMode_CBData_t *pData)
{
#if defined (TI_DRIVERS_LCD_INCLUDED)
    char szLine[TEMPSENSOR_MAX_LCD_LINE];
    char *pStr;
    uint8_t err;
#endif // TI_DRIVERS_LCD_INCLUDED

    // time to go into identify mode
    if(state == EZMODE_STATE_IDENTIFYING)
    {
        LCD_WRITE_STRING("EZMode",  LCD_PAGE2);
        ztsIdentifyTime = TEMPSENSOR_CONVERT_TO_SECONDS(EZMODE_TIME);
        TempSensor_processIdentifyTimeChange();
    }

    // autoclosing, show what happened (success, cancelled, etc...)
    if(state == EZMODE_STATE_AUTOCLOSE)
    {
#if defined (TI_DRIVERS_LCD_INCLUDED)
        pStr = NULL;
        err = pData->sAutoClose.err;
        if(err == EZMODE_ERR_SUCCESS)
        {
            pStr = "EZMode: Success";
        }
        else if(err == EZMODE_ERR_NOMATCH)
        {
            pStr = "EZMode: NoMatch"; // not a match made in heaven
        }
        if(pStr)
        {
            if(giTsScreenMode == TEMPSENSOR_MAINMODE)
            {
                LCD_WRITE_STRING(pStr,  LCD_PAGE2);
            }
        }
#endif // TI_DRIVERS_LCD_INCLUDED
    }

    // finished, either show DstAddr/EP, or nothing (depending on success or
    // not)
    if(state == EZMODE_STATE_FINISH)
    {
        // turn off identify mode
        ztsIdentifyTime = 0;
        TempSensor_processIdentifyTimeChange();

#if defined (TI_DRIVERS_LCD_INCLUDED)
        // if successful, inform user which nwkaddr/ep we bound to
        pStr = NULL;
        err = pData->sFinish.err;
        if(err == EZMODE_ERR_SUCCESS)
        {
            // "EZDst:1234 EP:34"
            memcpy(szLine, "EZDst:", 6);
            Util_uint16toa(pData->sFinish.nwkaddr, &szLine[6]);
            memcpy(&szLine[10], " EP:", 4);
            // Util_ltoa NULL terminates
            Util_ltoa(pData->sFinish.ep, (void *)(&szLine[14]), 16);
            pStr = szLine;
        }
        else if(err == EZMODE_ERR_BAD_PARAMETER)
        {
            pStr = "EZMode: BadParm";
        }
        else if(err == EZMODE_ERR_CANCELLED)
        {
            pStr = "EZMode: Cancel";
        }
        else
        {
            pStr = "EZMode: TimeOut";
        }
        if(pStr)
        {
            if(giTsScreenMode == TEMPSENSOR_MAINMODE)
            {
                LCD_WRITE_STRING(pStr,  LCD_PAGE2);
            }
        }
#endif // TI_DRIVERS_LCD_INCLUDED

        // show main UI screen 3 seconds after binding
        if(Util_isClockActive(&mainScreenClkStruct) == true)
        {
            Util_stopClock(&mainScreenClkStruct);
        }
        Clock_setTimeout( mainScreenClkHandle,
                          (TEMPSENSOR_MAINSCREEN_TIMEOUT * TIMER_MS_ADJUSTMENT) );
        Util_startClock(&mainScreenClkStruct);
    }
}
#endif  // ZCL_EZMODE

/*********************************************************************
 * @fn      TempSensor_processIdentifyTimeChange
 *
 * @brief   Called to process any change to the IdentifyTime attribute.
 *
 * @param   none
 *
 * @return  none
 */
static void TempSensor_processIdentifyTimeChange(void)
{
    // Stop the Identify timer
    if(Util_isClockActive(&identifyClkStruct) == true)
    {
        Util_stopClock(&identifyClkStruct);
    }

    // Are we still identifying?
    if(ztsIdentifyTime > 0)
    {
        // Continue with another timer
        Clock_setTimeout( identifyClkHandle,
            ((ztsIdentifyTime * TEMPSENSOR_1SEC_MSEC) * TIMER_MS_ADJUSTMENT));
        Util_startClock(&identifyClkStruct);

        Board_Led_control(board_led_type_LED4, board_led_state_ON);
    }
    else
    {
        // restore the LED status
        if(ztsOnOff)
        {
            Board_Led_control(board_led_type_LED4, board_led_state_ON);
        }
        else
        {
            Board_Led_control(board_led_type_LED4, board_led_state_OFF);
        }
    }
}

/*********************************************************************
 * @fn      TempSensor_processIdentifyCallback
 *
 * @brief   Callback from the ZCL General Cluster Library when
 *          it received an Identity Command for this application.
 *
 * @param   pCmd - pointer to ZCL command
 *
 * @return  none
 */
static void TempSensor_processIdentifyCallback(zclIdentify_t *pCmd)
{
    // Save the incoming time and setup a timer
    ztsIdentifyTime = pCmd->identifyTime;
    TempSensor_processIdentifyTimeChange();
}

/*********************************************************************
 * @fn      TempSensor_processIdentifyQueryResponseCallback
 *
 * @brief   Callback from the ZCL General Cluster Library when
 *          it received an Identity Query Response Command for this application.
 *
 * @param   pRsp - pointer to the response message
 *
 * @return  none
 */
static void TempSensor_processIdentifyQueryResponseCallback(
    zclIdentifyQueryRsp_t *pRsp)
{
#if defined (ZCL_EZMODE)
    {
        // ZCL EZMode will process this response message
        zclEZMode_ActionData_t data;
        data.pIdentifyQueryRsp = pRsp;
        zcl_EZModeAction(EZMODE_ACTION_IDENTIFY_QUERY_RSP, &data);
    }
#else
    // If you don't have EZMode enabled, add your own code to
    // Process this response message
    (void)pRsp;
#endif
}

#if defined (ZCL_EZMODE)
/*********************************************************************
 * @fn      TempSensor_processEzmodeTimerCallback
 *
 * @brief   Callback function to process the setup an EZMode timer.
 *
 * @param   start - true to start a timeer, false to stop a timer
 * @param   event_id - timer ID
 * @param   timeout_value - in milliseconds
 *
 * @return  none
 */
static void TempSensor_processEzmodeTimerCallback(bool start,
                                                  uint16_t event_id,
                                                  uint32_t timeout_value)
{
    if(event_id == TEMPSENSOR_EZMODE_TIMEOUT_EVT)
    {
        // Setup the EZMode Timeout timer
        if(Util_isClockActive(&ezmodeTimeoutClkStruct) == true)
        {
            Util_stopClock(&ezmodeTimeoutClkStruct);
        }

        if(start)
        {
            Clock_setTimeout( ezmodeTimeoutClkHandle,
                              (timeout_value * TIMER_MS_ADJUSTMENT) );
            Util_startClock(&ezmodeTimeoutClkStruct);
        }
    }
    else if(event_id == TEMPSENSOR_EZMODE_NEXTSTATE_EVT)
    {
        // Setup the EZMode Next State timer
        if(Util_isClockActive(&ezmodeStateClkStruct) == true)
        {
            Util_stopClock(&ezmodeStateClkStruct);
        }

        if(start)
        {
            Clock_setTimeout( ezmodeStateClkHandle,
                              (timeout_value * TIMER_MS_ADJUSTMENT) );
            Util_startClock(&ezmodeStateClkStruct);
        }
    }
}

/******************************************************************************
 * @fn      TempSensor_processEzmodeTimeoutCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void TempSensor_processEzmodeTimeoutCallback(UArg a0)
{
    (void)a0; // Parameter is not used

    events |= TEMPSENSOR_EZMODE_TIMEOUT_EVT;

    // Wake up the application thread when it waits for clock event
    Semaphore_post(sem);
}

/******************************************************************************
 * @fn      TempSensor_processEzmodeStateChangeCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void TempSensor_processEzmodeStateChangeCallback(UArg a0)
{
    (void)a0; // Parameter is not used

    events |= TEMPSENSOR_EZMODE_NEXTSTATE_EVT;

    // Wake up the application thread when it waits for clock event
    Semaphore_post(sem);
}
#endif // ZCL_EZMODE

/******************************************************************************
 * @fn      TempSensor_processIdentifyTimeoutCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void TempSensor_processIdentifyTimeoutCallback(UArg a0)
{
    (void)a0; // Parameter is not used

    events |= TEMPSENSOR_IDENTIFY_TIMEOUT_EVT;

    // Wake up the application thread when it waits for clock event
    Semaphore_post(sem);
}

/******************************************************************************
 * @fn      TempSensor_processMainScreenTimeoutCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void TempSensor_processMainScreenTimeoutCallback(UArg a0)
{
    (void)a0; // Parameter is not used

    events |= TEMPSENSOR_MAIN_SCREEN_EVT;

    // Wake up the application thread when it waits for clock event
    Semaphore_post(sem);
}

/******************************************************************************
 * @fn      TempSensor_setPollRate
 *
 * @brief   Set the ZStack Thread Poll Rate
 *
 * @param   newPollRate - new poll rate in milliseconds
 *
 * @return  none
 */
static void TempSensor_setPollRate(uint32_t newPollRate)
{
    zstack_sysConfigWriteReq_t writeReq = {0};

    // Set the new poll rate
    writeReq.has_pollRate = true;
    writeReq.pollRate = newPollRate;

    (void)Zstackapi_sysConfigWriteReq(ztsEntity, &writeReq);
}

/******************************************************************************
 * @fn      TempSensor_startEzMode
 *
 * @brief   Start the EZMode process
 *
 * @param   none
 *
 * @return  none
 */
static void TempSensor_startEzMode(void)
{
#if defined (ZCL_EZMODE)
    zclEZMode_InvokeData_t ezModeData;
    // only bind on temperature measurement
    static uint16_t clusterIDs[] = { ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT };

    // Invoke EZ-Mode
    ezModeData.endpoint = TEMPSENSOR_EP; // endpoint on which to invoke EZ-Mode
    if( (savedState == zstack_DevState_DEV_ZB_COORD)
        || (savedState == zstack_DevState_DEV_ROUTER)
        || (savedState == zstack_DevState_DEV_END_DEVICE) )
    {
        ezModeData.onNetwork = true;  // node is already on the network
    }
    else
    {
        ezModeData.onNetwork = false; // node is not yet on the network
    }
    ezModeData.initiator = true;      // Temperature Sensor is an initiator
    ezModeData.numActiveInClusters = 1;
    ezModeData.pActiveInClusterIDs = clusterIDs;
    ezModeData.numActiveOutClusters = 0; // active output cluster
    ezModeData.pActiveOutClusterIDs = NULL;
    zcl_InvokeEZMode(&ezModeData);

    LCD_WRITE_STRING("EZMode",  LCD_PAGE2);
#endif // ZCL_EZMODE
}

/******************************************************************************
 * @fn      TempSensor_changeTemp
 *
 * @brief   Change the current temperature and send the temperature
 *
 * @param   increment - true to increment, false to decrement
 *
 * @return  none
 */
static void TempSensor_changeTemp(bool increment)
{
    // Manually adjust the temperature, since aren't reading an actual
    // temperature
    if(increment)
    {
        // Increment the temperature
        if(ztsMeasuredValue < ztsMaxMeasuredValue)
        {
            // considering using whole number value
            ztsMeasuredValue = ztsMeasuredValue + 100;
        }
        else if(ztsMeasuredValue >= ztsMaxMeasuredValue)
        {
            ztsMeasuredValue = ztsMaxMeasuredValue;
        }
    }
    else
    {
        // decrease the temperature
        if(ztsMeasuredValue > ztsMinMeasuredValue)
        {
            // considering using whole number value
            ztsMeasuredValue = ztsMeasuredValue - 100;
        }
        else if(ztsMeasuredValue >= ztsMinMeasuredValue)
        {
            ztsMeasuredValue = ztsMinMeasuredValue;
        }
    }

    // Send temperature information
    TempSensor_sendTemp();
}

/******************************************************************************
 *****************************************************************************/
