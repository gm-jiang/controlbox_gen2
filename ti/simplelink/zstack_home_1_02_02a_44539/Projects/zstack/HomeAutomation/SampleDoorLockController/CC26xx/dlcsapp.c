/**
  @file  dlcsapp.c
  @brief TI RTOS ZCL Home Automation Door Lock Controller sample application
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
                                  - Send toggle door lock PIN code
                                 |
  KEY LEFT (or S4)               |      KEY RIGHT(or S2)
  - Enable/Disable Permit Join --+-----  - Invoke EZMode
                                 |
                                 |
                                KEY DOWN
                                 - Go to PIN Screen

  KEY_SELECT (or S5)
   -  Go to Help screen


  PIN Screen Description:

                                KEY UP (or S1)
                                  - Increase PIN Number
                                 |
  KEY LEFT (or S4)               |      KEY RIGHT(or S2)
   -                           --+-----  -
                                 |
                                 |
                                KEY DOWN
                                 - Decrease PIN Number

  KEY_SELECT (or S5)
   -  Enter PIN Number

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
#include "zcl_closures.h"

#if defined (ZCL_EZMODE)
#include "zcl_ezmode.h"
#endif

#include "util.h"
#include "zcl_port.h"
#include "dlcsapp.h"
#include "znwk_config.h"

//*****************************************************************************
// Constants
//*****************************************************************************

/* Event IDs */
#define DLCSAPP_IDENTIFY_TIMEOUT_EVT      0x0001
#define DLCSAPP_POLL_CONTROL_TIMEOUT_EVT  0x0002
#define DLCSAPP_EZMODE_TIMEOUT_EVT        0x0004
#define DLCSAPP_EZMODE_NEXTSTATE_EVT      0x0008
#define DLCSAPP_MAIN_SCREEN_EVT           0x0010
#define DLCSAPP_KEY_EVENT                 0x0020

/* Debounce timeout in ticks */
#define DLCSAPP_KEY_DEBOUNCE_TIMEOUT      200

#define DLCSAPP_MAX_ATTRIBUTES            20

#define DLCSAPP_EP                        8

#define DLCSAPP_DEVICE_VERSION            0
#define DLCSAPP_FLAGS                     0

#define DLCSAPP_HWVERSION                 0
#define DLCSAPP_ZCLVERSION                0

#define DLCSAPP_LIGHT_OFF                 0x00
#define DLCSAPP_LIGHT_ON                  0x01

#define DLCSAPP_MAX_INCLUSTERS            6
#define DLCSAPP_MAX_OUTCLUSTERS           6

// Application Display Modes
#define DLCSAPP_MAINMODE                  0x00
#define DLCSAPP_HELPMODE                  0x01
#define DLCSAPP_PINMODE                   0x02

// NVM IDs
#define DLCSAPP_NV_DOORLOCK_PIN           0x0010
#define DLCSAPP_NV_DOORLOCK_PIN_LEN       5

#define DLCSAPP_MAINSCREEN_TIMEOUT        3000         // 3 Seconds

#define DLCSAPP_INIT_TIMEOUT_VALUE        100

#define DLCSAPP_MAX_PIN_SIZE              4

#define DLCSAPP_MAX_LCD_LINE              20

#define DLCSAPP_1SEC_MSEC                 1000

#define DLCSAPP_CONVERT_TO_SECONDS(a)    ((a)/DLCSAPP_1SEC_MSEC)

//*****************************************************************************
// Global Variables
//*****************************************************************************

//*****************************************************************************
// Local Variables
//*****************************************************************************

// Semaphore used to post events to the application thread
static ICall_Semaphore sem;
static ICall_EntityID zdlcEntity;

// Passed in function pointers to the NV driver
static NVINTF_nvFuncts_t *pfnZdlcNV = NULL;

// Hold the device's Zstack state when recieved
static zstack_DevState savedState = zstack_DevState_HOLD;

// Task pending events
static uint16_t events = 0;

// Destination address to send the door lock commands
static zstack_AFAddr_t zdlcDstAddr;

// Transaction ID used to send data messages
static uint8_t zdlcTransID = 0;

// ZStack Thread network information
static zstack_sysNwkInfoReadRsp_t *pNwkInfo = NULL;

// Key press parameters
static uint8_t keys;

// Clock/timer resources
static Clock_Struct identifyClkStruct;
static Clock_Handle identifyClkHandle;
static Clock_Struct mainScreenClkStruct;
Clock_Handle mainScreenClkHandle;

#if defined (ZCL_EZMODE)
// Clock resources
static Clock_Struct ezmodeTimeoutClkStruct;
static Clock_Struct ezmodeStateClkStruct;

// Clock object for Ezmode timeout
static Clock_Handle ezmodeTimeoutClkHandle;
static Clock_Handle ezmodeStateClkHandle;
#endif // ZCL_EZMODE

// Display the main screen mode first
static uint8_t giDlcScreenMode = DLCSAPP_MAINMODE;

// Permit joining default to disabled
static uint8_t gPermitDuration = 0;

// Door lock status
static bool doorLocked = true;

// PIN Variables
static uint8_t giDoorLockPINCount = 0;
static uint8_t giDoorLockPINColumnCount = 0;

// Master PIN code for DoorLock
static uint8_t aiDoorLockPIN[] = {4, 0x31, 0x32, 0x33, 0x34};

// Cluster lists for the simple descriptor
static uint16_t inputClusters[DLCSAPP_MAX_INCLUSTERS] =
{
    ZCL_CLUSTER_ID_GEN_BASIC,
    ZCL_CLUSTER_ID_GEN_IDENTIFY,
    ZCL_CLUSTER_ID_GEN_SCENES,
    ZCL_CLUSTER_ID_GEN_GROUPS,
    ZCL_CLUSTER_ID_GEN_TIME,
    ZCL_CLUSTER_ID_CLOSURES_DOOR_LOCK
};
static uint16_t outputClusters[DLCSAPP_MAX_OUTCLUSTERS] =
{
    ZCL_CLUSTER_ID_GEN_BASIC,
    ZCL_CLUSTER_ID_GEN_IDENTIFY,
    ZCL_CLUSTER_ID_GEN_SCENES,
    ZCL_CLUSTER_ID_GEN_GROUPS,
    ZCL_CLUSTER_ID_GEN_TIME,
    ZCL_CLUSTER_ID_CLOSURES_DOOR_LOCK
};

// Endpoint descriptor
static endPointDesc_t zdlEpDesc = {0};
static SimpleDescriptionFormat_t afSimpleDesc = {0};

#if defined (ZCL_EZMODE)
// EZMode Commissioning control structure
static void DLCSApp_ezmodeCB(zlcEZMode_State_t state, zclEZMode_CBData_t *pData);
static const zclEZMode_RegisterData_t ezmodeRegisterData =
{
    &zdlEpDesc.endPoint,
    DLCSAPP_EZMODE_NEXTSTATE_EVT,
    DLCSAPP_EZMODE_TIMEOUT_EVT,
    &zdlcTransID,
    DLCSApp_ezmodeCB
};
#endif // ZCL_EZMODE

// Strings used to display on the LCD
static const char sClearLine[]    = " ";
static const char sDeviceName[]   = "DoorLock Remote";
static const char sSwDoorLock[]   = "Up: Lock/Unlock";
#if defined (ZCL_EZMODE)
static const char sSwEZMode[]     = "Rt: EZ-Mode";
#endif
static const char sSwPIN[]        = "Dn: Master PIN";
static const char sPINLine2[]     = "Up:+";
static const char sPINLine3[]     = "Dn:- Sel:Enter";
static const char sSwHelp[]       = "Select: Help";
static const char sStorePIN[]     = "   PIN SAVED";
static const char sFail[]         = "Lock/Unlock Fail";
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
static const uint8_t zdlcHWRevision = DLCSAPP_HWVERSION;
static const uint8_t zdlcZCLVersion = DLCSAPP_ZCLVERSION;
static const uint8_t zdlcManufacturerName[] =
{
    16,
    'T', 'e', 'x', 'a', 's', 'I', 'n', 's',
    't', 'r', 'u', 'm', 'e', 'n', 't', 's'
};
static const uint8_t zdlcModelId[] =
{
    16,
    'T', 'I', '0', '0', '0', '1', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
};
static const uint8_t zdlcDateCode[] =
{
    16,
    '2', '0', '0', '6', '0', '8', '3', '1',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
};
static const uint8_t zdlcPowerSource = POWER_SOURCE_BATTERY;

// Device location - updatable over the air
static uint8_t zdlcLocationDescription[17] =
{
    16,
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
};
static uint8_t zdlcPhysicalEnvironment = PHY_UNSPECIFIED_ENV;

// Attribute to control the device
static uint8_t zdlcDeviceEnable = DEVICE_ENABLED;

static uint8_t zdlcOnOff = DLCSAPP_LIGHT_ON;

// Closure Attributes
static uint8_t zdlcLockState = CLOSURES_LOCK_STATE_UNLOCKED;
static uint8_t zdlcLockType = CLOSURES_LOCK_TYPE_DEADBOLT;
static bool zdlcActuatorEnabled = true;

// Identify Cluster
static uint16_t zdlcIdentifyTime = 0;

//*****************************************************************************
// Local Function Prototypes
//*****************************************************************************

static void DLCSApp_initialization(void);
static void DLCSApp_initializeClocks(void);
static void DLCSApp_registerEndpoints(void);
static void DLCSApp_setupZStackCallbacks(void);
static void DLCSApp_writeZStackParameters(void);
static void DLCSApp_initializeZStack(void);
static void DLCSApp_process(void);
static void DLCSApp_processZStackMsgs(zstackmsg_genericReq_t *pMsg);
static void DLCSApp_processAfIncomingMsgInd(zstack_afIncomingMsgInd_t *pInMsg);
static void DLCSApp_handleKeys(uint8_t keys);

static void DLCSApp_updateLcdDisplay(void);
static void DLCSApp_updateLcdLine1Status(void);
static void DLCSApp_updateLcdMainScreen(void);
static void DLCSApp_updateLcdHelpScreen(void);
static void DLCSApp_updateLcdPinScreen(void);

static void DLCSApp_processKeyChangeCallback(uint8_t keysPressed);

static void DLCSApp_processIdentifyQueryResponseCallback(
    zclIdentifyQueryRsp_t *pRsp);

static void DLCSApp_processIdentifyTimeChange(void);
static void DLCSApp_processIdentifyCallback(zclIdentify_t *pCmd);
static void DLCSApp_processIdentifyQueryResponseCallback(
    zclIdentifyQueryRsp_t *pRsp);
static ZStatus_t DLCSApp_processDoorLockResponseCallback(zclIncoming_t *pInMsg,
                                                         uint8_t status);

#if defined (ZCL_EZMODE)
static void DLCSApp_processEZModeTimerCallback(bool start, uint16_t event_id,
                                               uint32_t timeout_value);
static void DLCSApp_processEZModeTimeoutCallback(UArg a0);
static void DLCSApp_processEZModeStateChangeCallback(UArg a0);
#endif // ZCL_EZMODE

static void DLCSApp_processIdentifyTimeoutCallback(UArg a0);
static void DLCSApp_processMainScreenTimeoutCallback(UArg a0);
static void DLCSApp_setPollRate(uint32_t newPollRate);
static void DLCSApp_sendDoorLock(void);
static void DLCSApp_startEzMode(void);

/*********************************************************************
 * ZCL General Profile Callback table
 */
static zclGeneral_AppCallbacks_t cmdCallbacks =
{
    NULL,                                 // Basic Cluster Reset command
    DLCSApp_processIdentifyCallback,      // Identify command
#ifdef ZCL_EZMODE
    NULL,                          // Identify EZ-Mode Invoke command
    NULL,                          // Identify Update Commission State command
#endif
    NULL,                                 // Identify Trigger Effect command
    DLCSApp_processIdentifyQueryResponseCallback, // Identify Query Response
                                                  // cmd
    NULL,        // On/Off cluster commands
    NULL,        // On/Off cluster enhanced command Off with Effect
    NULL,        // On/Off cluster enhanced command On with Recall Global Scene
    NULL,        // On/Off cluster enhanced command On with Timed Off
#ifdef ZCL_LEVEL_CTRL
    NULL,                               // Level Control Move to Level command
    NULL,                               // Level Control Move command
    NULL,                               // Level Control Step command
    NULL,                               // Level Control Stop command
#endif
#ifdef ZCL_GROUPS
    NULL,                                 // Group Response commands
#endif
#ifdef ZCL_SCENES
    NULL,                                 // Scene Store Request command
    NULL,                                 // Scene Recall Request command
    NULL,                                 // Scene Response command
#endif
#ifdef ZCL_ALARMS
    NULL,                                 // Alarm (Response) commands
#endif
#ifdef SE_UK_EXT
    NULL,                                 // Get Event Log command
    NULL,                                 // Publish Event Log command
#endif
    NULL,                                 // RSSI Location command
    NULL                                  // RSSI Location Response command
};

/*********************************************************************
 * ZCL Closure cluster Callback table
 */
static zclClosures_DoorLockAppCallbacks_t doorLockControllerCmdCallbacks =
{
    NULL,                                  // DoorLock cluster command
    DLCSApp_processDoorLockResponseCallback, // DoorLock Response
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

const zclAttrRec_t zdlcAttrs[DLCSAPP_MAX_ATTRIBUTES] =
{
    // *** General Basic Cluster Attributes ***
    {
        ZCL_CLUSTER_ID_GEN_BASIC,  // Cluster IDs - defined in the foundation
                                   //  (ie. zcl.h)
        { // Attribute record
            ATTRID_BASIC_HW_VERSION, // Attribute ID - Found in Cluster Library
                                     //   header (ie. zcl_general.h)
            ZCL_DATATYPE_UINT8,    // Data Type - found in zcl.h
            ACCESS_CONTROL_READ,   // Variable access control - found in zcl.h
            (void *)&zdlcHWRevision // Pointer to attribute variable
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_ZCL_VERSION,
            ZCL_DATATYPE_UINT8,
            ACCESS_CONTROL_READ,
            (void *)&zdlcZCLVersion
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_MANUFACTURER_NAME,
            ZCL_DATATYPE_CHAR_STR,
            ACCESS_CONTROL_READ,
            (void *)zdlcManufacturerName
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_MODEL_ID,
            ZCL_DATATYPE_CHAR_STR,
            ACCESS_CONTROL_READ,
            (void *)zdlcModelId
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_DATE_CODE,
            ZCL_DATATYPE_CHAR_STR,
            ACCESS_CONTROL_READ,
            (void *)zdlcDateCode
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_POWER_SOURCE,
            ZCL_DATATYPE_UINT8,
            ACCESS_CONTROL_READ,
            (void *)&zdlcPowerSource
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_LOCATION_DESC,
            ZCL_DATATYPE_CHAR_STR,
            (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
            (void *)zdlcLocationDescription
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_PHYSICAL_ENV,
            ZCL_DATATYPE_UINT8,
            (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
            (void *)&zdlcPhysicalEnvironment
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_BASIC,
        { // Attribute record
            ATTRID_BASIC_DEVICE_ENABLED,
            ZCL_DATATYPE_BOOLEAN,
            (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
            (void *)&zdlcDeviceEnable
        }
    },

    // *** Identify Cluster Attribute ***
    {
        ZCL_CLUSTER_ID_GEN_IDENTIFY,
        { // Attribute record
            ATTRID_IDENTIFY_TIME,
            ZCL_DATATYPE_UINT16,
            (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
            (void *)&zdlcIdentifyTime
        }
    },

    // *** On/Off Cluster Attributes ***
    {
        ZCL_CLUSTER_ID_GEN_ON_OFF,
        { // Attribute record
            ATTRID_ON_OFF,
            ZCL_DATATYPE_BOOLEAN,
            ACCESS_CONTROL_READ,
            (void *)&zdlcOnOff
        }
    },

    // *** Scene Cluster Attributes ***
    {
        ZCL_CLUSTER_ID_GEN_SCENES,
        { // Attribute record
            ATTRID_SCENES_COUNT,
            ZCL_DATATYPE_UINT8,
            ACCESS_CONTROL_READ,
            NULL // Use application's callback to Read this attribute
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_SCENES,
        { // Attribute record
            ATTRID_SCENES_CURRENT_SCENE,
            ZCL_DATATYPE_UINT8,
            ACCESS_CONTROL_READ,
            NULL
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_SCENES,
        { // Attribute record
            ATTRID_SCENES_CURRENT_GROUP,
            ZCL_DATATYPE_UINT16,
            ACCESS_CONTROL_READ,
            NULL
        }
    },
    {
        ZCL_CLUSTER_ID_GEN_SCENES,
        { // Attribute record
            ATTRID_SCENES_SCENE_VALID,
            ZCL_DATATYPE_BOOLEAN,
            ACCESS_CONTROL_READ,
            NULL
        }
    },
    {
        ZCL_CLUSTER_ID_CLOSURES_DOOR_LOCK,
        { // Attribute record
            ATTRID_CLOSURES_LOCK_STATE,
            ZCL_DATATYPE_ENUM8,
            (ACCESS_CONTROL_READ | ACCESS_REPORTABLE),
            (void *)&zdlcLockState
        }
    },
    {
        ZCL_CLUSTER_ID_CLOSURES_DOOR_LOCK,
        { // Attribute record
            ATTRID_CLOSURES_LOCK_TYPE,
            ZCL_DATATYPE_ENUM8,
            ACCESS_CONTROL_READ,
            (void *)&zdlcLockType
        }
    },
    {
        ZCL_CLUSTER_ID_CLOSURES_DOOR_LOCK,
        { // Attribute record
            ATTRID_CLOSURES_ACTUATOR_ENABLED,
            ZCL_DATATYPE_BOOLEAN,
            ACCESS_CONTROL_READ,
            (void *)&zdlcActuatorEnabled
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
 * @fn          DLCSApp_task
 *
 * @brief       Application task entry point for the ZStack HA Sample Door
 *              Lock Controller Appication.
 *
 * @param       pfnNV - pointer to the NV functions
 *
 * @return      none
 */
void DLCSApp_task(NVINTF_nvFuncts_t *pfnNV)
{
    // Save and register the function pointers to the NV drivers
    pfnZdlcNV = pfnNV;
    zclport_registerNV(pfnZdlcNV, ZCL_PORT_SCENE_TABLE_NV_ID);

    // Initialize application
    DLCSApp_initialization();

    // No return from task process
    DLCSApp_process();
}

/******************************************************************************
 * @fn          DLCSApp_initialization
 *
 * @brief       Initialize the application
 *
 * @param       none
 *
 * @return      none
 */
static void DLCSApp_initialization(void)
{
    /* Initialize variables */
    zdlcDstAddr.addrMode = zstack_AFAddrMode_NONE;
    zdlcDstAddr.addr.shortAddr = 0;
    zdlcDstAddr.endpoint = 0;
    zdlcDstAddr.panID = 0;

#if defined (ZCL_EZMODE)
    zclport_registerEZModeTimerCB(DLCSApp_processEZModeTimerCallback);
#endif

    DLCSApp_initializeClocks();

    /* Initialize keys */
    Board_Key_initialize(DLCSApp_processKeyChangeCallback);

    /* Initialize the LCD */
    Board_LCD_open();
    LCD_WRITE_STRING( (char *)sDeviceName,  LCD_PAGE1 );
#if defined (ZCL_EZMODE)
    LCD_WRITE_STRING( (char *)sSwEZMode,  LCD_PAGE2 );
#endif
    LCD_WRITE_STRING( (char *)sSwHelp,  LCD_PAGE3 );

    /* Initialize the LEDS */
    Board_Led_initialize();

    // Register the current thread as an ICall dispatcher application
    // so that the application can send and receive messages.
    ICall_registerApp(&zdlcEntity, &sem);

    // Initialize NVM for storing PIN information
    if(pfnZdlcNV)
    {
        NVINTF_itemID_t nvId;
        uint32_t nvErr = NVINTF_NOTFOUND;

        // Fill in the NV ID header
        nvId.systemID = NVINTF_SYSID_APP;
        nvId.itemID = (uint16_t)DLCSAPP_NV_DOORLOCK_PIN;
        nvId.subID = (uint16_t)0;

        // Read the PIN from NV
        if(pfnZdlcNV->readItem)
        {
            nvErr = pfnZdlcNV->readItem(nvId, 0, DLCSAPP_NV_DOORLOCK_PIN_LEN,
                                        aiDoorLockPIN);
        }

        // If the PIN doesn't exist in NV, create it
        if((nvErr == NVINTF_NOTFOUND) && pfnZdlcNV->createItem)
        {
            pfnZdlcNV->createItem(nvId, DLCSAPP_NV_DOORLOCK_PIN_LEN,
                                  aiDoorLockPIN);
        }
    }

    // Initialize the ZStack
    DLCSApp_initializeZStack();
}

/******************************************************************************
 * @fn      DLCSApp_initializeClocks
 *
 * @brief   Initialize Clocks
 *
 * @param   none
 *
 * @return  none
 */
static void DLCSApp_initializeClocks(void)
{
    // Construct the Identify Timer
    identifyClkHandle = Util_constructClock(
        &identifyClkStruct,
        DLCSApp_processIdentifyTimeoutCallback,
        DLCSAPP_INIT_TIMEOUT_VALUE,
        0,
        false,
        0);

    // Construct the timer used to switch back to the main screen
    mainScreenClkHandle = Util_constructClock(
        &mainScreenClkStruct,
        DLCSApp_processMainScreenTimeoutCallback,
        DLCSAPP_MAINSCREEN_TIMEOUT,
        0,
        false,
        0);

#if defined (ZCL_EZMODE)
    // Construct the EZMode Timeout timer
    ezmodeTimeoutClkHandle = Util_constructClock(
        &ezmodeTimeoutClkStruct,
        DLCSApp_processEZModeTimeoutCallback,
        DLCSAPP_INIT_TIMEOUT_VALUE,
        0,
        false,
        0);

    // Construct the EZMode State Timer
    ezmodeStateClkHandle = Util_constructClock(
        &ezmodeStateClkStruct,
        DLCSApp_processEZModeStateChangeCallback,
        DLCSAPP_INIT_TIMEOUT_VALUE,
        0,
        false,
        0);
#endif // ZCL_EZMODE
}

/******************************************************************************
 * @fn      DLCSApp_registerEndpoints
 *
 * @brief   Setup a Zigbee HA Door Lock Controller Endpoint
 *
 * @param   none
 *
 * @return  none
 */
static void DLCSApp_registerEndpoints(void)
{
    // Initialize the Door Lock Controller Simple Descriptor
    zdlEpDesc.endPoint = DLCSAPP_EP;
    afSimpleDesc.EndPoint = DLCSAPP_EP;
    afSimpleDesc.AppProfId = ZCL_HA_PROFILE_ID;
    afSimpleDesc.AppDeviceId = ZCL_HA_DEVICEID_DOOR_LOCK_CONTROLLER;
    afSimpleDesc.AppDevVer = DLCSAPP_DEVICE_VERSION;
    afSimpleDesc.AppNumInClusters = sizeof(inputClusters) / sizeof(uint16_t);
    afSimpleDesc.pAppInClusterList = inputClusters;
    afSimpleDesc.AppNumOutClusters = sizeof(outputClusters) / sizeof(uint16_t);
    afSimpleDesc.pAppOutClusterList = outputClusters;
    zdlEpDesc.simpleDesc = &afSimpleDesc;
    (void)zclport_registerEndpoint(zdlcEntity, &zdlEpDesc);
}

/******************************************************************************
 * @fn      DLCSApp_setupZStackCallbacks
 *
 * @brief   Setup the Zstack Callbacks wanted
 *
 * @param   none
 *
 * @return  none
 */
static void DLCSApp_setupZStackCallbacks(void)
{
    zstack_devZDOCBReq_t zdoCBReq = {0};

    // Register for Callbacks, turn on:
    //  Device State Change,
    //  ZDO Match Descriptor Response,
    //  End Device Bind Response
    zdoCBReq.has_devStateChange = true;
    zdoCBReq.devStateChange = true;

#if defined (ZCL_EZMODE)
    // EZMode uses the Match Descriptor Request/Response
    zdoCBReq.has_matchDescRsp = true;
    zdoCBReq.matchDescRsp = true;
#endif

    // Send the Device ZDO Callback Request
    (void)Zstackapi_DevZDOCBReq(zdlcEntity, &zdoCBReq);
}

/******************************************************************************
 * @fn      DLCSApp_writeZStackParameters
 *
 * @brief   Initialize ZStack Parameters
 *
 * @param   none
 *
 * @return  none
 */
static void DLCSApp_writeZStackParameters(void)
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
    memcpy(&(writeReq.extendedPANID), extendedPANID, EXTADDR_LEN);

    // Update the config PAN ID, defined in znwk_config.h
    writeReq.has_panID = true;
    writeReq.panID = ZNWK_CONFIG_PAN_ID;

    // Send the System Configuration Write Request
    (void)Zstackapi_sysConfigWriteReq(zdlcEntity, &writeReq);
}

/******************************************************************************
 * @fn      DLCSApp_initializeZStack
 *
 * @brief   Initialize ZStack
 *
 * @param   none
 *
 * @return  none
 */
static void DLCSApp_initializeZStack(void)
{
    // Initialize the ZStack Thread
    bool startDev = true; // default to auto-start

    // Setup the endpoints
    DLCSApp_registerEndpoints();

    // Setup indications from ZStack
    DLCSApp_setupZStackCallbacks();

#if defined (ZCL_EZMODE)
    startDev = zclport_isAlreadyPartOfNetwork(zdlcEntity);

    // Register EZ-Mode
    zcl_RegisterEZMode(&ezmodeRegisterData);
    Board_Led_control(board_led_type_LED1, board_led_state_BLINK);
#endif

    // Start the device now?
    if(startDev)
    {
        zstack_devStartReq_t startReq = {0};

        // Start the ZStack Thread
        startReq.startDelay = 0;
        (void)Zstackapi_DevStartReq(zdlcEntity, &startReq);

#if defined (ZCL_EZMODE)
        LCD_WRITE_STRING( (char *)sClearLine, LCD_PAGE2 );
#endif
    }

    // Register the ZCL General Cluster Library callback functions
    zclGeneral_RegisterCmdCallbacks(DLCSAPP_EP, &cmdCallbacks);

    //Register the ZCL DoorLock Cluster Library callback function
    zclClosures_RegisterDoorLockCmdCallbacks(DLCSAPP_EP,
                                             &doorLockControllerCmdCallbacks);

    // Register the application's attribute list
    zcl_registerAttrList(DLCSAPP_EP, DLCSAPP_MAX_ATTRIBUTES, zdlcAttrs);

    // Update the ZStack Parameters
    DLCSApp_writeZStackParameters();
}

/******************************************************************************
 * @fn      DLCSApp_process
 *
 * @brief   Application task processing loop.
 *
 * @param   none
 *
 * @return  void - Doesn't return from this function
 */
static void DLCSApp_process(void)
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
                    (dest == zdlcEntity) )
                {
                    if(pMsg)
                    {
                        DLCSApp_processZStackMsgs(pMsg);

                        // Free any seperately allocated memory
                        Zstackapi_freeIndMsg(pMsg);
                    }
                }

                if(pMsg)
                {
                    ICall_freeMsg(pMsg);
                }
            }

            if(events & DLCSAPP_KEY_EVENT)
            {
                // Process Key Presses
                DLCSApp_handleKeys(keys);
                keys = 0;

                // Clear the event, until next time
                events &= ~DLCSAPP_KEY_EVENT;
            }

            if(events & DLCSAPP_IDENTIFY_TIMEOUT_EVT)
            {
                // Count down the Identify Timer
                if(zdlcIdentifyTime > 0)
                {
                    zdlcIdentifyTime--;
                }

                // Identify Timeout value has changed - process it
                DLCSApp_processIdentifyTimeChange();

                // Clear the event, until next time
                events &= ~DLCSAPP_IDENTIFY_TIMEOUT_EVT;
            }

            if(events & DLCSAPP_MAIN_SCREEN_EVT)
            {
                // Update the display
                giDlcScreenMode = DLCSAPP_MAINMODE;
                DLCSApp_updateLcdMainScreen();

                // Clear the event, until next time
                events &= ~DLCSAPP_MAIN_SCREEN_EVT;
            }

#ifdef ZCL_EZMODE
            if(events & DLCSAPP_EZMODE_NEXTSTATE_EVT)
            {
                // going on to next state
                zcl_EZModeAction(EZMODE_ACTION_PROCESS, NULL);

                // Clear the event, until next time
                events &= ~DLCSAPP_EZMODE_NEXTSTATE_EVT;
            }

            if(events & DLCSAPP_EZMODE_TIMEOUT_EVT)
            {
                // EZ-Mode timed out
                zcl_EZModeAction(EZMODE_ACTION_TIMED_OUT, NULL);

                // Clear the event, until next time
                events &= ~DLCSAPP_EZMODE_TIMEOUT_EVT;
            }
#endif // ZLC_EZMODE
        }
    }
}

/******************************************************************************
 * @fn      DLCSApp_processZStackMsgs
 *
 * @brief   Process event from Stack
 *
 * @param   pMsg - pointer to incoming ZStack message to process
 *
 * @return  void
 */
static void DLCSApp_processZStackMsgs(zstackmsg_genericReq_t *pMsg)
{
    switch(pMsg->hdr.event)
    {
        case zstackmsg_CmdIDs_DEV_STATE_CHANGE_IND:
            {
                // The ZStack Thread is indicating a State change
                zstackmsg_devStateChangeInd_t *pInd
                    = (zstackmsg_devStateChangeInd_t *)pMsg;

                // Only process the state change if it actually changed.
                if(savedState != pInd->req.state)
                {
                    savedState = pInd->req.state;

                    if( (pInd->req.state == zstack_DevState_DEV_ZB_COORD)
                        || (pInd->req.state == zstack_DevState_DEV_ROUTER)
                        || (pInd->req.state == zstack_DevState_DEV_END_DEVICE) )
                    {
                        // The device is part of a network, get the device's
                        // network parameters.
                        pNwkInfo = zclport_getDeviceInfo(zdlcEntity);

                        // Update the display with network information
                        giDlcScreenMode = DLCSAPP_MAINMODE;
                        DLCSApp_updateLcdDisplay();
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
                            DLCSApp_setPollRate(ZNWK_POLL_RATE);
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
                DLCSApp_processAfIncomingMsgInd( &(pInd->req) );
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
 * @fn          DLCSApp_processAfIncomingMsgInd
 *
 * @brief       Process AF Incoming Message Indication message
 *
 * @param       pInMsg - pointer to incoming message
 *
 * @return      none
 *
 */
static void DLCSApp_processAfIncomingMsgInd(zstack_afIncomingMsgInd_t *pInMsg)
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
        memcpy(afMsg.srcAddr.addr.extAddr, &(pInMsg->srcAddr.addr.extAddr),
               EXTADDR_LEN);
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
 * @fn      DLCSApp_handleKeys
 *
 * @brief   Callback service for keys
 *
 * @param   keys  - keys that were pressed
 *
 * @return  void
 */
static void DLCSApp_handleKeys(uint8_t keys)
{
    if(keys == KEY_UP)
    {
        // Dual purpose key depending on screen mode
        if(giDlcScreenMode == DLCSAPP_PINMODE)
        {
            // increase PIN number
            if(giDoorLockPINColumnCount < DLCSAPP_MAX_PIN_SIZE)
            {
                if(giDoorLockPINCount > 8)
                {
                    giDoorLockPINCount = 0;
                }
                else
                {
                    giDoorLockPINCount++;
                }
            }
        }
        else
        {
            // Not in PIN Mode, toggle door lock
            DLCSApp_sendDoorLock();
        }
    }

    if(keys == KEY_RIGHT)
    {
        // If not in PIN mode, start EZMode
        if( (giDlcScreenMode == DLCSAPP_MAINMODE) ||
            (giDlcScreenMode == DLCSAPP_HELPMODE) )
        {
            giDlcScreenMode = DLCSAPP_MAINMODE;

            DLCSApp_startEzMode();
        }
    }

    if(keys == KEY_DOWN)
    {
        if(giDlcScreenMode == DLCSAPP_PINMODE)
        {
            // decrease PIN number
            if(giDoorLockPINColumnCount < DLCSAPP_MAX_PIN_SIZE)
            {
                if(giDoorLockPINCount < 1)
                {
                    giDoorLockPINCount = 9;
                }
                else
                {
                    giDoorLockPINCount--;
                }
            }
        }
        else
        {
            giDoorLockPINColumnCount = 0;
            giDlcScreenMode = DLCSAPP_PINMODE; // set to PIN screen
        }
    }

    // toggle permit join
    if(keys == KEY_LEFT)
    {
        giDlcScreenMode = DLCSAPP_MAINMODE; // remove help screen if there

        if( pNwkInfo && ( (savedState == zstack_DevState_DEV_ZB_COORD)
                          || (savedState == zstack_DevState_DEV_ROUTER) ) )
        {
            zstack_zdoMgmtPermitJoinReq_t req;

            // toggle permit join
            gPermitDuration = gPermitDuration ? 0 : 0xff;

            req.nwkAddr = pNwkInfo->nwkAddr;
            req.duration = gPermitDuration;
            req.tcSignificance = true;

            Zstackapi_ZdoMgmtPermitJoinReq(zdlcEntity, &req);
        }
    }

    if(keys & KEY_SELECT)
    {
        // for Master PIN screen
        if(giDlcScreenMode == DLCSAPP_PINMODE)
        {
            if(giDoorLockPINCount > 0)
            {
                char numBuff;

                // convert number to ASCII
                Util_itoa(giDoorLockPINCount, (uint8_t *)&numBuff, 10);

                // copy current PIN number
                aiDoorLockPIN[giDoorLockPINColumnCount + 1] = numBuff;
            }
            else
            {
                // make sure '0' is copied into PIN variable
                aiDoorLockPIN[giDoorLockPINColumnCount + 1] = '0';
            }

            if(giDoorLockPINColumnCount < (DLCSAPP_MAX_PIN_SIZE-1))
            {
                giDoorLockPINColumnCount++; // adjust PIN column
            }
            else
            {
                // hold here until PIN screen reset
                giDoorLockPINColumnCount = DLCSAPP_MAX_PIN_SIZE;
                giDoorLockPINCount = 0; // reset PIN count

                // insert the size of the PIN (always 4 for
                // sampledoorlockcontroller)
                aiDoorLockPIN[0] = DLCSAPP_MAX_PIN_SIZE;

                // store PIN to NVM
                if(pfnZdlcNV && pfnZdlcNV->writeItem)
                {
                    NVINTF_itemID_t nvId;

                    nvId.systemID = NVINTF_SYSID_APP;
                    nvId.itemID = (uint16_t)DLCSAPP_NV_DOORLOCK_PIN;
                    nvId.subID = (uint16_t)0;

                    pfnZdlcNV->writeItemEx(nvId, 0,
                                           DLCSAPP_NV_DOORLOCK_PIN_LEN,
                                           aiDoorLockPIN);
                }

                LCD_WRITE_STRING( (char *)sStorePIN,  LCD_PAGE2 );
                LCD_WRITE_STRING( (char *)sClearLine,  LCD_PAGE3 );
                giDlcScreenMode = DLCSAPP_MAINMODE;
            }
        }
        else if(giDlcScreenMode == DLCSAPP_MAINMODE)
        {
            giDlcScreenMode = DLCSAPP_HELPMODE;
        }
        else
        {
            giDlcScreenMode = DLCSAPP_MAINMODE;
            LCD_WRITE_STRING( (char *)sClearLine,  LCD_PAGE2 );
        }
    }

    // update the display
    DLCSApp_updateLcdDisplay();
}

/*********************************************************************
 * @fn      DLCSApp_updateLcdDisplay
 *
 * @brief   Called to update the LCD display.
 *
 * @param   none
 *
 * @return  none
 */
static void DLCSApp_updateLcdDisplay(void)
{
    // Update depending on Screen Mode
    if(giDlcScreenMode == DLCSAPP_PINMODE)
    {
        DLCSApp_updateLcdPinScreen();
    }
    else if(giDlcScreenMode == DLCSAPP_HELPMODE)
    {
        DLCSApp_updateLcdHelpScreen();
    }
    else
    {
        DLCSApp_updateLcdMainScreen();
    }
}

/*********************************************************************
 * @fn      DLCSApp_updateLcdLine1Status
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
static void DLCSApp_updateLcdLine1Status(void)
{
    int idx;
    char szLine[DLCSAPP_MAX_LCD_LINE];

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
 * @fn      DLCSApp_updateLcdMainScreen
 *
 * @brief   Called to display the main screen on the LCD.
 *
 * @param   none
 *
 * @return  none
 */
static void DLCSApp_updateLcdMainScreen(void)
{
    char sPermitJoinStatus[16];

    DLCSApp_updateLcdLine1Status();

    if( (savedState == zstack_DevState_DEV_ZB_COORD)
        || (savedState == zstack_DevState_DEV_ROUTER) )
    {
        // Update the permit join status
        memcpy(sPermitJoinStatus, "Select: Help    ", 16);
        if(gPermitDuration)
        {
            // The '*' means that permit join is enabled
            sPermitJoinStatus[15] = '*';
        }
        // display help key with permit join status
        LCD_WRITE_STRING( (char *)sPermitJoinStatus,  LCD_PAGE3 );
    }
    else
    {
        // display help key
        LCD_WRITE_STRING( (char *)sSwHelp,  LCD_PAGE3 );
    }
}

/*********************************************************************
 * @fn      DLCSApp_updateLcdHelpScreen
 *
 * @brief   Called to update the LCD display with permit join information.
 *
 * @param   none
 *
 * @return  none
 */
static void DLCSApp_updateLcdHelpScreen(void)
{
    LCD_WRITE_STRING( (char *)sSwDoorLock, LCD_PAGE1 );
#if defined (ZCL_EZMODE)
    LCD_WRITE_STRING( (char *)sSwEZMode, LCD_PAGE2 );
#endif
    LCD_WRITE_STRING( (char *)sSwPIN, LCD_PAGE3 );
}

/*********************************************************************
 * @fn      DLCSApp_updateLcdPinScreen
 *
 * @brief   Called to display the PIN screen on the LCD.
 *
 * @param   none
 *
 * @return  none
 */
static void DLCSApp_updateLcdPinScreen(void)
{
    char sDisplayPIN[16];

    memcpy(sDisplayPIN, "Enter PIN:       ", 16);

    // cover appropriate columns with security '*'
    if(giDoorLockPINColumnCount == 0)
    {
        Util_ltoa(giDoorLockPINCount,
                  (void *)(&sDisplayPIN[11 + giDoorLockPINColumnCount]), 10);
    }
    else if(giDoorLockPINColumnCount == 1)
    {
        sDisplayPIN[11] = '*';
        Util_ltoa(giDoorLockPINCount,
                  (void *)(&sDisplayPIN[11 + giDoorLockPINColumnCount]), 10);
    }
    else if(giDoorLockPINColumnCount == 2)
    {
        sDisplayPIN[11] = '*';
        sDisplayPIN[12] = '*';
        Util_ltoa(giDoorLockPINCount,
                  (void *)(&sDisplayPIN[11 + giDoorLockPINColumnCount]), 10);
    }
    else if(giDoorLockPINColumnCount == 3)
    {
        sDisplayPIN[11] = '*';
        sDisplayPIN[12] = '*';
        sDisplayPIN[13] = '*';
        Util_ltoa(giDoorLockPINCount,
                  (void *)(&sDisplayPIN[11 + giDoorLockPINColumnCount]), 10);
    }
    else if(giDoorLockPINColumnCount > 3)
    {
        sDisplayPIN[11] = '*';
        sDisplayPIN[12] = '*';
        sDisplayPIN[13] = '*';
        sDisplayPIN[14] = '*';
    }
    LCD_WRITE_STRING( (char *)sDisplayPIN, LCD_PAGE1 );
    LCD_WRITE_STRING( (char *)sPINLine2, LCD_PAGE2 );
    LCD_WRITE_STRING( (char *)sPINLine3, LCD_PAGE3 );
}

/*********************************************************************
 * @fn      DLCSApp_processKeyChangeCallback
 *
 * @brief   Key event handler function
 *
 * @param   keysPressed - ignored
 *
 * @return  none
 */
static void DLCSApp_processKeyChangeCallback(uint8_t keysPressed)
{
    // Save the key press information
    keys = keysPressed;

    // set the key press event
    events |= DLCSAPP_KEY_EVENT;

    // Wake up the application thread when it waits for clock event
    Semaphore_post(sem);
}

#if defined (ZCL_EZMODE)
/*********************************************************************
 * @fn      DLCSApp_ezmodeCB
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
static void DLCSApp_ezmodeCB(zlcEZMode_State_t state, zclEZMode_CBData_t *pData)
{
#if defined (TI_DRIVERS_LCD_INCLUDED)
    char szLine[DLCSAPP_MAX_LCD_LINE];
    char *pStr;
    uint8_t err;
#endif // TI_DRIVERS_LCD_INCLUDED

    // time to go into identify mode
    if(state == EZMODE_STATE_IDENTIFYING)
    {
        LCD_WRITE_STRING("EZMode",  LCD_PAGE2);
        zdlcIdentifyTime = DLCSAPP_CONVERT_TO_SECONDS(EZMODE_TIME);
        DLCSApp_processIdentifyTimeChange();
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
            if(giDlcScreenMode == DLCSAPP_MAINMODE)
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
        zdlcIdentifyTime = 0;
        DLCSApp_processIdentifyTimeChange();

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
            if(giDlcScreenMode == DLCSAPP_MAINMODE)
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
                          (DLCSAPP_MAINSCREEN_TIMEOUT * TIMER_MS_ADJUSTMENT) );
        Util_startClock(&mainScreenClkStruct);
    }
}
#endif  // ZCL_EZMODE

/*********************************************************************
 * @fn      DLCSApp_processIdentifyTimeChange
 *
 * @brief   Called to process any change to the IdentifyTime attribute.
 *
 * @param   none
 *
 * @return  none
 */
static void DLCSApp_processIdentifyTimeChange(void)
{
    // Stop the Identify timer
    if(Util_isClockActive(&identifyClkStruct) == true)
    {
        Util_stopClock(&identifyClkStruct);
    }

    // Are we still identifying?
     if(zdlcIdentifyTime > 0)
    {
        // Continue with another timer
        Clock_setTimeout( identifyClkHandle,
            ( (zdlcIdentifyTime * DLCSAPP_1SEC_MSEC) * TIMER_MS_ADJUSTMENT ) );
        Util_startClock(&identifyClkStruct);

        Board_Led_control(board_led_type_LED4, board_led_state_ON);
    }
    else
    {
        // restore the LED status
        if(zdlcOnOff)
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
 * @fn      DLCSApp_processIdentifyCallback
 *
 * @brief   Callback from the ZCL General Cluster Library when
 *          it received an Identity Command for this application.
 *
 * @param   pCmd - pointer to the ZCL command
 *
 * @return  none
 */
static void DLCSApp_processIdentifyCallback(zclIdentify_t *pCmd)
{
    // Save the incoming time and setup a timer
    zdlcIdentifyTime = pCmd->identifyTime;
    DLCSApp_processIdentifyTimeChange();
}

/*********************************************************************
 * @fn      DLCSApp_processIdentifyQueryResponseCallback
 *
 * @brief   Callback from the ZCL General Cluster Library when
 *          it received an Identity Query Response Command for this
 *          application.
 *
 * @param   pRsp - pointer to the incoming ZCL Response
 *
 * @return  none
 */
static void DLCSApp_processIdentifyQueryResponseCallback(
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

/*********************************************************************
 * @fn      DLCSApp_processDoorLockResponseCallback
 *
 * @brief   Callback from the ZCL General Cluster Library when
 *          it received an Door Lock response for this application.
 *
 * @param   pInMsg - pointer to ZCL Response message
 * @param   status - status response from server's door lock cmd
 *
 * @return  ZStatus_t
 */
static ZStatus_t DLCSApp_processDoorLockResponseCallback(zclIncoming_t *pInMsg,
                                                         uint8_t status)
{
    // Check the status of the response message
    if(status == ZSuccess)
    {
        zclReadCmd_t readCmd;

        // Successful - ZCL read the attribute from the door lock
        readCmd.numAttr = 1;
        readCmd.attrID[0] = ATTRID_CLOSURES_LOCK_STATE;
        pInMsg->hdr.transSeqNum += 1;
        zcl_SendRead(pInMsg->msg->endPoint, &pInMsg->msg->srcAddr,
                     ZCL_CLUSTER_ID_CLOSURES_DOOR_LOCK, &readCmd,
                     ZCL_FRAME_CLIENT_SERVER_DIR, true,
                     pInMsg->hdr.transSeqNum);
    }
    // ZFailure
    else
    {
        LCD_WRITE_STRING( (char *)sFail,  LCD_PAGE2 );
    }

    return(ZCL_STATUS_SUCCESS);
}

#if defined (ZCL_EZMODE)
/*********************************************************************
 * @fn      DLCSApp_processEZModeTimerCallback
 *
 * @param   start - true to start a timeer, false to stop a timer
 * @param   event_id - timer ID
 * @param   timeout_value - in milliseconds
 *
 * @return  none
 */
static void DLCSApp_processEZModeTimerCallback(bool start, uint16_t event_id,
                                               uint32_t timeout_value)
{
    if(event_id == DLCSAPP_EZMODE_TIMEOUT_EVT)
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
    else if(event_id == DLCSAPP_EZMODE_NEXTSTATE_EVT)
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
 * @fn      DLCSApp_processEZModeTimeoutCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void DLCSApp_processEZModeTimeoutCallback(UArg a0)
{
    (void)a0; // Parameter is not used

    events |= DLCSAPP_EZMODE_TIMEOUT_EVT;

    // Wake up the application thread when it waits for clock event
    Semaphore_post(sem);
}

/******************************************************************************
 * @fn      DLCSApp_processEZModeStateChangeCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void DLCSApp_processEZModeStateChangeCallback(UArg a0)
{
    (void)a0; // Parameter is not used

    events |= DLCSAPP_EZMODE_NEXTSTATE_EVT;

    // Wake up the application thread when it waits for clock event
    Semaphore_post(sem);
}
#endif // ZCL_EZMODE

/******************************************************************************
 * @fn      DLCSApp_processIdentifyTimeoutCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void DLCSApp_processIdentifyTimeoutCallback(UArg a0)
{
    (void)a0; // Parameter is not used

    events |= DLCSAPP_IDENTIFY_TIMEOUT_EVT;

    // Wake up the application thread when it waits for clock event
    Semaphore_post(sem);
}

/******************************************************************************
 * @fn      DLCSApp_processMainScreenTimeoutCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void DLCSApp_processMainScreenTimeoutCallback(UArg a0)
{
    (void)a0; // Parameter is not used

    events |= DLCSAPP_MAIN_SCREEN_EVT;

    // Wake up the application thread when it waits for clock event
    Semaphore_post(sem);
}

/******************************************************************************
 * @fn      DLCSApp_setPollRate
 *
 * @brief   Set the ZStack Thread Poll Rate
 *
 * @param   newPollRate - new poll rate in milliseconds
 *
 * @return  none
 */
static void DLCSApp_setPollRate(uint32_t newPollRate)
{
    zstack_sysConfigWriteReq_t writeReq = {0};

    // Set the new poll rate
    writeReq.has_pollRate = true;
    writeReq.pollRate = newPollRate;

    (void)Zstackapi_sysConfigWriteReq(zdlcEntity, &writeReq);
}

/******************************************************************************
 * @fn      DLCSApp_sendDoorLock
 *
 * @brief   Send the door lock command
 *
 * @param   none
 *
 * @return  none
 */
static void DLCSApp_sendDoorLock(void)
{
    zclDoorLock_t cmd;
    afAddrType_t dstAddr;

    // Update the PIN for the door lock command
    cmd.pPinRfidCode = aiDoorLockPIN;

    // Switch to the main scren
    giDlcScreenMode = DLCSAPP_MAINMODE;

    // Setup the destination address
    dstAddr.addrMode = (afAddrMode_t)zdlcDstAddr.addrMode;
    dstAddr.addr.shortAddr = zdlcDstAddr.addr.shortAddr;
    dstAddr.endPoint = zdlcDstAddr.endpoint;
    dstAddr.panId = zdlcDstAddr.panID;

    if(doorLocked)
    {
        // ZCL send the unlock command
        zclClosures_SendDoorLockUnlockDoor(DLCSAPP_EP, &dstAddr, &cmd, true,
                                           zdlcTransID++);
        doorLocked = false;
    }
    else
    {
        // ZCL send the lock command
        zclClosures_SendDoorLockLockDoor(DLCSAPP_EP, &dstAddr, &cmd, true,
                                         zdlcTransID++);
        doorLocked = true;
    }
}

/******************************************************************************
 * @fn      DLCSApp_startEzMode
 *
 * @brief   Start the EZMode process
 *
 * @param   none
 *
 * @return  none
 */
static void DLCSApp_startEzMode(void)
{
#if defined (ZCL_EZMODE)
    zclEZMode_InvokeData_t ezModeData;
    // only bind on door lock
    static uint16_t clusterIDs[] = { ZCL_CLUSTER_ID_CLOSURES_DOOR_LOCK };

    // Invoke EZ-Mode
    ezModeData.endpoint = DLCSAPP_EP; // endpoint on which to invoke EZ-Mode
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
    // Door Lock Controller (remote) is an initiator
    ezModeData.initiator = true;
    ezModeData.numActiveOutClusters = 1; // active output cluster
    ezModeData.pActiveOutClusterIDs = clusterIDs;
    ezModeData.numActiveInClusters = 0; // no active input clusters
    ezModeData.pActiveInClusterIDs = NULL;
    zcl_InvokeEZMode(&ezModeData);

    LCD_WRITE_STRING("EZMode",  LCD_PAGE2);
#endif // ZCL_EZMODE
}

/******************************************************************************
 *****************************************************************************/
