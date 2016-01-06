/**
  @file  sensortagapp.c
  @brief TI RTOS ZCL Home Automation SensorTag sample application
         interfacing with ZStack.

         The application interacts with the ZStack Thread
         via both messaging interface and C function interface.

  <!--
  Copyright 2014 - 2015 Texas Instruments Incorporated. All rights reserved.

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

 On the SensorTag:

  Key Press Description:

    KEY LEFT
      - Send On/Off Command

    KEY RIGHT
      - Invoke EZMode for Switch Endpoint

    KEY_LEFT and KEY RIGHT together
      - Invoke EZMode for Temp Sensor Endpoint and Light Sensor Endpoint

  NOTE: To use MGMT_BIND_SUPPORTED for the SensorTag,
        ZDO_MGMT_BIND_REQUEST and ZDO_MGMT_BIND_RESPONSE should be added
        to the Core End Device project which may require modification on
        the boundary file and rebuilding both the core and the application.
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
#include "board_led.h"

#include "zcl.h"
#include "zcl_general.h"
#include "zcl_ha.h"
#include "zcl_ms.h"

#if defined(ZCL_EZMODE)
#include "zcl_ezmode.h"
#endif

#include "util.h"
#include "zcl_port.h"
#include "sensortagapp.h"
#include "znwk_config.h"

#include "bsp_i2c.h"
#include "ext_flash.h"
#include "ext_flash_layout.h"
#include "sensor.h"
#include "sensor_tmp007.h"
#include "sensor_opt3001.h"
#include "math.h"


//*****************************************************************************
// Constants
//*****************************************************************************

/* Event IDs */
#define SENSORTAGAPP_IDENTIFY_TIMEOUT_EVT        0x0001
#define SENSORTAGAPP_POLL_CONTROL_TIMEOUT_EVT    0x0002
#define SENSORTAGAPP_EZMODE_TIMEOUT_EVT          0x0004
#define SENSORTAGAPP_EZMODE_NEXTSTATE_EVT        0x0008
#define SENSORTAGAPP_EZMODE_FINISHED_EVT         0x0010
#define SENSORTAGAPP_KEY_EVENT                   0x0020
#define SENSORTAGAPP_TEMPSENSOR_MIN_TIMEOUT_EVT  0x0040
#define SENSORTAGAPP_TEMPSENSOR_MAX_TIMEOUT_EVT  0x0080
#define SENSORTAGAPP_LIGHTSENSOR_MIN_TIMEOUT_EVT 0x0100
#define SENSORTAGAPP_LIGHTSENSOR_MAX_TIMEOUT_EVT 0x0200
#define SENSORTAGAPP_ERASENV_TIMEOUT_EVT        0x0400

/* Debounce timeout in ticks */
#define SENSORTAGAPP_KEY_DEBOUNCE_TIMEOUT       200

#define SENSORTAGAPP_SW_MAX_ATTRIBUTES          15
#define SENSORTAGAPP_TS_MAX_ATTRIBUTES          17
#define SENSORTAGAPP_LS_MAX_ATTRIBUTES          17

#define SENSORTAGAPP_SW_EP                      8
#define SENSORTAGAPP_TS_EP                      9
#define SENSORTAGAPP_LS_EP                      10

#define SENSORTAGAPP_DEVICE_VERSION             0
#define SENSORTAGAPP_FLAGS                      0

#define SENSORTAGAPP_HWVERSION                  0
#define SENSORTAGAPP_ZCLVERSION                 0

#define SENSORTAGAPP_OFF                        0x00
#define SENSORTAGAPP_ON                         0x01

#define SENSORTAGAPP_SW_MAX_INCLUSTERS          2
#define SENSORTAGAPP_SW_MAX_OUTCLUSTERS         1

#define SENSORTAGAPP_TS_MAX_INCLUSTERS          3
#define SENSORTAGAPP_TS_MAX_OUTCLUSTERS         1

#define SENSORTAGAPP_LS_MAX_INCLUSTERS          3
#define SENSORTAGAPP_LS_MAX_OUTCLUSTERS         1

#if defined(LIGHTSENSOR_ENABLED)
#define SENSORTAGAPP_MAX_ENDPOINTS_DEFINED      3
#else
#define SENSORTAGAPP_MAX_ENDPOINTS_DEFINED      2
#endif

#define SENSORTAGAPP_SW_EP_IDX                  0
#define SENSORTAGAPP_TS_EP_IDX                  1
#define SENSORTAGAPP_LS_EP_IDX                  2

// Delay from temp sensor enable to reading measurememt
// (allow for 250 ms conversion time)
#define SENSORTAGAPP_TEMP_MEAS_DELAY            275

// Delay from light sensor enable to reading measurememt
// (allow for 100 ms conversion time)
#define SENSORTAGAPP_ILLUM_MEAS_DELAY           113

#define SENSORTAGAPP_EZMODE_POLL_RATE           1000

#define SENSORTAGAPP_INIT_TIMEOUT_VALUE         100

#define SENSORTAGAPP_1SEC_MSEC                  1000

#define SENSORTAGAPP_CONVERT_TO_SECONDS(a)      ((a)/SENSORTAGAPP_1SEC_MSEC)

#define SENSORTAGAPP_BL_OFFSET                   0x1F001

#if defined(ZCL_REPORT)
#define MIN_HA_MIN_REPORTING_INT         1     // Should be >= 1 by HA spec
#define MIN_HA_MAX_REPORTING_INT         0x3C  // Should be >= 0x3C by HA spec
#if defined(LIGHTSENSOR_ENABLED)
#define MAX_REPORT_ATTR                  2
#else // LIGHTSENSOR_ENABLED
#define MAX_REPORT_ATTR                  1
#endif  // LIGHTSENSOR_ENABLED

#define DEFAULT_TEMP_REPORTING_INTERVAL   10    // 10 secs
#define DEFAULT_ILLUM_REPORTING_INTERVAL  3     // 3 secs

// NVM IDs
#define SENSORTAGAPP_NV_REPORT_CFG_TBL        0x0020
#define SENSORTAGAPP_NV_REPORT_CFG_ENTRY_LEN       5
#endif  // ZCL_REPORT

//*****************************************************************************
// Typedefs
//*****************************************************************************

// Structure used to read the current Temperature from the TMP007
typedef union
{
  struct
  {
    uint16_t  tempTarget, tempLocal;
  } v;
  uint16_t  a[2];
} TempData_t;

#if defined(ZCL_REPORT)
// Function pointer definition to callback timer setting function
typedef void (*configReportTimer_t)
             (uint16_t minInterval, uint16_t maxInterval);

// Structure used to manage report attribute configuration
typedef struct
{
  uint8_t             dataType;
  void*               pAttr;
  void*               pAttrOld;
  uint16_t            minReportInt;
  uint16_t            maxReportInt;
  void*               pReportableChange;
  configReportTimer_t configTimer;
} reportConfig_t;

// Structure used to store report attribute configuration entry to the NV
typedef struct
{
  uint16_t minReportInt;
  uint16_t maxReportInt;
  uint8_t reportableChange[];
} reportConfigEntry_t;
#endif

//*****************************************************************************
// Global Variables
//*****************************************************************************

#if defined(EXTERNAL_IMAGE_CHECK)
/* SPI Pin Handle */
PIN_Handle hGpioPin;
#endif
//*****************************************************************************
// Local Variables
//*****************************************************************************

// Semaphore used to post events to the application thread
static ICall_Semaphore sem;
static ICall_EntityID staEntity;

// Passed in function pointers to the NV driver
static NVINTF_nvFuncts_t *pfnStaNV = NULL;

// Hold the device's Zstack state when recieved
static zstack_DevState savedState = zstack_DevState_HOLD;

// Task pending events
static uint16_t events = 0;

// Destination address to send the On/Off toggle
static zstack_AFAddr_t staSwDstAddr;

// Destination address to send the temperature reading
static zstack_AFAddr_t staTsDstAddr;

#if defined(LIGHTSENSOR_ENABLED)
// Destination address to send the illuminance reading
static zstack_AFAddr_t staLsDstAddr;
#endif

// Transaction ID used to send data messages
static uint8_t staTransID = 0;

// ZStack Thread network information
static zstack_sysNwkInfoReadRsp_t *pNwkInfo = NULL;

// Key press parameters
static uint8_t keys;

// Clock/timer resources
static Clock_Struct identifyClkStruct;
static Clock_Handle identifyClkHandle;

// Clock resources for NV erase
static Clock_Struct eraseNVClkStruct;
static Clock_Handle eraseNVClkHandle;

#if defined(ZCL_REPORT)
// Clock resources for temp/light sensors
static Clock_Struct tempSensorMinClkStruct;
static Clock_Struct tempSensorMaxClkStruct;
static Clock_Handle tempSensorMinClkHandle;
static Clock_Handle tempSensorMaxClkHandle;

#if defined(LIGHTSENSOR_ENABLED)
static Clock_Struct lightSensorMinClkStruct;
static Clock_Struct lightSensorMaxClkStruct;
static Clock_Handle lightSensorMinClkHandle;
static Clock_Handle lightSensorMaxClkHandle;
#endif
#endif

#if defined(ZCL_EZMODE)
// Clock resources
static Clock_Struct ezmodeTimeoutClkStruct;
static Clock_Struct ezmodeStateClkStruct;

// Clock object for Ezmode timeout
static Clock_Handle ezmodeTimeoutClkHandle;
static Clock_Handle ezmodeStateClkHandle;
#endif // ZCL_EZMODE

// Cluster lists for the simple descriptor
static uint_least16_t swInputClusters[SENSORTAGAPP_SW_MAX_INCLUSTERS] =
{
  ZCL_CLUSTER_ID_GEN_BASIC,
  ZCL_CLUSTER_ID_GEN_IDENTIFY
};
static uint_least16_t swOutputClusters[SENSORTAGAPP_SW_MAX_OUTCLUSTERS] =
{
  ZCL_CLUSTER_ID_GEN_ON_OFF
};

static uint16_t tsInputClusters[SENSORTAGAPP_TS_MAX_INCLUSTERS] =
{
  ZCL_CLUSTER_ID_GEN_BASIC,
  ZCL_CLUSTER_ID_GEN_IDENTIFY,
  ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT
};
static uint16_t tsOutputClusters[SENSORTAGAPP_TS_MAX_OUTCLUSTERS] =
{
  ZCL_CLUSTER_ID_GEN_IDENTIFY
};

#if defined(LIGHTSENSOR_ENABLED)
static uint16_t lsInputClusters[SENSORTAGAPP_LS_MAX_INCLUSTERS] =
{
  ZCL_CLUSTER_ID_GEN_BASIC,
  ZCL_CLUSTER_ID_GEN_IDENTIFY,
  ZCL_CLUSTER_ID_MS_ILLUMINANCE_MEASUREMENT,
};
static uint16_t lsOutputClusters[SENSORTAGAPP_LS_MAX_OUTCLUSTERS] =
{
  ZCL_CLUSTER_ID_GEN_IDENTIFY
};
#endif

// Endpoint descriptors
static endPointDesc_t staEpDesc[SENSORTAGAPP_MAX_ENDPOINTS_DEFINED] =
{
  0
};
static SimpleDescriptionFormat_t
  afSimpleDesc[SENSORTAGAPP_MAX_ENDPOINTS_DEFINED] =
{
  0
};

#if defined(ZCL_EZMODE)
// EZMode Commissioning control structure
static void SensorTagApp_processEzmodeCallback(zlcEZMode_State_t state,
                                              zclEZMode_CBData_t *pData);
static const zclEZMode_RegisterData_t ezmodeRegisterData =
{
  &(staEpDesc[SENSORTAGAPP_SW_EP_IDX].endPoint),
  SENSORTAGAPP_EZMODE_NEXTSTATE_EVT,
  SENSORTAGAPP_EZMODE_TIMEOUT_EVT,
  &staTransID,
  SensorTagApp_processEzmodeCallback
};

extern zclEZMode_InvokeData_t zclEZModeInvokeData;
#endif // ZCL_EZMODE

#if defined(EXTERNAL_IMAGE_CHECK)
// PIN table for the SPI
static PIN_Config spiPinTable[] =
{
  Board_SPI_FLASH_CS | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH |
  PIN_PUSHPULL | PIN_DRVSTR_MIN,  /* External flash chip select    */
  Board_SPI_DEVPK_CS | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH |
  PIN_PUSHPULL | PIN_DRVSTR_MIN,  /* DevPack chip select           */
  PIN_TERMINATE /* Terminate list */
};

/* SPI pin state */
static PIN_State spiPinState;
#endif // EXTERNAL_IMAGE_CHECK

#if defined(LIGHTSENSOR_ENABLED)
static uint8_t whichSensorEP = SENSORTAGAPP_TS_EP;
#endif

/**
 * @internal A semaphore used to wait on a clock event
 */
extern ti_sysbios_knl_Semaphore_Handle semaphore0;

//*****************************************************************************
// Attribute Variables
//*****************************************************************************

// Attributes that aren't writable
static const uint8_t staHWRevision = SENSORTAGAPP_HWVERSION;
static const uint8_t staZCLVersion = SENSORTAGAPP_ZCLVERSION;
static const uint8_t staManufacturerName[] =
{
  16,
  'T', 'e', 'x', 'a', 's', 'I', 'n', 's',
  't', 'r', 'u', 'm', 'e', 'n', 't', 's'
};
static const uint8_t staModelId[] =
{
  16,
  'T', 'I', '0', '0', '0', '1', ' ', ' ',
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
};
static const uint8_t staDateCode[] =
{
  16,
  '2', '0', '0', '6', '0', '8', '3', '1',
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
};
static const uint8_t staPowerSource = POWER_SOURCE_BATTERY;

// Device location - updatable over the air
static uint8_t staLocationDescription[17] =
{
  16,
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
};
static uint8_t staPhysicalEnvironment = PHY_UNSPECIFIED_ENV;

// Attribute to control the device
static uint8_t staSwDeviceEnable = DEVICE_ENABLED;
static uint8_t staTsDeviceEnable = DEVICE_ENABLED;
#if defined(LIGHTSENSOR_ENABLED)
static uint8_t staIlDeviceEnable = DEVICE_ENABLED;
#endif

// Identify Cluster
static uint16_t staIdentifyTime = 0;

// Temperature Sensor Cluster
static int16_t staTempMeasuredValue = 2200;  // 22.00C
static const int16_t staTempMinMeasuredValue = -2300;   // -23.00C
static const int16_t staTempMaxMeasuredValue = 12700;  // 127.00C
#if defined(ZCL_REPORT)
static int16_t staTempMeasuredValueOld;
static int16_t staTempReportableChange = 0;
#endif

#if defined(LIGHTSENSOR_ENABLED)
// Illuminance Measurement Cluster
static uint16_t staIllumMeasuredValue = 30001;  // 1000 Lux
static const uint16_t staIllumMinMeasuredValue = 0xFFFF;   // not defined
static const uint16_t staIllumMaxMeasuredValue = 0xFFFF;  // not defined
#if defined(ZCL_REPORT)
static uint16_t staIllumMeasuredValueOld;
static int16_t  staIllumReportableChange = 0;
#endif  // ZCL_REPORT
#endif  // LIGHTSENSOR_ENABLED

// On/Off Clusters
static uint8_t  staSwOnOff = SENSORTAGAPP_OFF;
static uint8_t  staTsOnOff = SENSORTAGAPP_ON;
#if defined(LIGHTSENSOR_ENABLED)
static uint8_t  staLsOnOff = SENSORTAGAPP_ON;
#endif

static uint8_t staOnOffSwitchType = ON_OFF_SWITCH_TYPE_TOGGLE;
static uint8_t staOnOffSwitchActions = ON_OFF_SWITCH_ACTIONS_2;


//*****************************************************************************
// Reportable Attribute Configuration Variables
//*****************************************************************************
#if defined(ZCL_REPORT)
static reportConfig_t staTempReportConfig;
#if defined(LIGHTSENSOR_ENABLED)
static reportConfig_t staIllumReportConfig;
#endif  // LIGHTSENSOR_ENABLED
#if !defined(FORCE_REPORT)
static reportConfig_t* staReportConfigList[MAX_REPORT_ATTR];
#endif  // FORCE_REPORT
#endif  // ZCL_REPORT

//*****************************************************************************
// Local Function Prototypes
//*****************************************************************************

static void SensorTagApp_initialization(void);
static void SensorTagApp_initializeClocks(void);
static void SensorTagApp_registerEndpoints(void);
static void SensorTagApp_setupZStackCallbacks(void);
static void SensorTagApp_writeZStackParameters(void);
static void SensorTagApp_initializeZStack(void);
static void SensorTagApp_process(void);
static void SensorTagApp_processZStackMsgs(zstackmsg_genericReq_t *pMsg);
static void SensorTagApp_processAfIncomingMsgInd(
    zstack_afIncomingMsgInd_t *pInMsg);
static void SensorTag_handleKeys(uint8_t keys);

static bool SensorTagApp_readConvertIRTemp(int16_t *pResult);
#if defined(LIGHTSENSOR_ENABLED)
static bool SensorTagApp_readConvertIllum(uint16_t *pResult);
#endif

static void SensorTagApp_processKeyChangeCallback(uint8_t keysPressed);

static void SensorTagApp_processEraseNVTimeChange(uint8_t keysPressed,ICall_EntityID dest);
static void SensorTagApp_resetNVErase(void);

static void SensorTagApp_processIdentifyTimeChange(void);
static void SensorTagApp_processIdentifyQueryResponseCallback(
    zclIdentifyQueryRsp_t *pRsp);
static void SensorTagApp_processIdentifyCallback(zclIdentify_t *pCmd);

#if defined(ZCL_EZMODE)
static void SensorTagApp_processEzmodeTimerCallback(bool start,
    uint16_t event_id, uint32_t timeout_value);
static void SensorTagApp_processEzmodeTimeoutCallback(UArg a0);
static void SensorTagApp_processEzmodeStateChangeCallback(UArg a0);
#endif // ZCL_EZMODE

static void SensorTagApp_processIdentifyTimeoutCallback(UArg a0);
static void SensorTagApp_processeraseNVTimeoutCallback(UArg a0);
static void SensorTagApp_setPollRate(uint32_t newPollRate);
static void SensorTagApp_startEzMode(uint8_t endpoint);
static void SensorTagApp_sendToggle(void);
static uint8_t SensorTagApp_processZCLMsg(zclIncoming_t *pInMsg);

#if defined(ZCL_REPORT)
static uint8_t SensorTagApp_ProcessInConfigReportCmd(zclIncoming_t *pInMsg);
static void SensorTagApp_processTempSensorMinTimeoutCallback(UArg a0);
static void SensorTagApp_processTempSensorMaxTimeoutCallback(UArg a0);
static void SensorTagApp_setTempSensorTimer(uint16_t minInterval,
                                              uint16_t maxInterval);
static void SensorTagApp_sendTemp(void);
#if defined(LIGHTSENSOR_ENABLED)
static void SensorTagApp_processLightSensorMinTimeoutCallback(UArg a0);
static void SensorTagApp_processLightSensorMaxTimeoutCallback(UArg a0);
static void SensorTagApp_setLightSensorTimer(uint16_t minInterval,
                                              uint16_t maxInterval);
static void SensorTagApp_sendIllum(void);
#endif  // LIGHTSENSOR_ENABLED
static void SensorTagApp_initReportConfig(void);
#if !defined(FORCE_REPORT)
static uint8_t SensorTagApp_getReportConfigIdx(zclAttribute_t* pAttr);
#endif // FORCE_REPORT
#endif  // ZCL_REPORT

static void SensorTagApp_applyFactoryImage(void);
static bool SensorTagApp_hasFactoryImage(void);

/*********************************************************************
 * ZCL General Profile Callback table
 */
static zclGeneral_AppCallbacks_t cmdCallbacks =
{
  NULL,                                   // Basic Cluster Reset command
  SensorTagApp_processIdentifyCallback,   // Identify command
#ifdef ZCL_EZMODE
  NULL,                                   // Identify EZ-Mode Invoke command
  NULL,                                   // Identify Update Commission State
#endif
  NULL,                                   // Identify Trigger Effect command
  SensorTagApp_processIdentifyQueryResponseCallback, // Identify Query Rsp
  NULL,        // On/Off cluster commands
  NULL,        // On/Off cluster enhanced command Off with Effect
  NULL,        // On/Off cluster enhanced command On with Recall Global Scene
  NULL,        // On/Off cluster enhanced command On with Timed Off
#ifdef ZCL_LEVEL_CTRL
  NULL,                                   // Level Control Move to Level cmd
  NULL,                                   // Level Control Move command
  NULL,                                   // Level Control Step command
  NULL,                                   // Level Control Stop command
#endif
#ifdef ZCL_GROUPS
  NULL,                                   // Group Response commands
#endif
#ifdef ZCL_SCENES
  NULL,                                   // Scene Store Request command
  NULL,                                   // Scene Recall Request command
  NULL,                                   // Scene Response command
#endif
#ifdef ZCL_ALARMS
  NULL,                                   // Alarm (Response) commands
#endif
#ifdef SE_UK_EXT
  NULL,                                   // Get Event Log command
  NULL,                                   // Publish Event Log command
#endif
  NULL,                                   // RSSI Location command
  NULL                                    // RSSI Location Response command
};

const zclAttrRec_t zswAttrs[SENSORTAGAPP_SW_MAX_ATTRIBUTES] =
{
  // *** General Basic Cluster Attributes ***
  {
    ZCL_CLUSTER_ID_GEN_BASIC,    // Cluster IDs - defined in the foundation
                                 //    (ie. zcl.h)
    {
      // Attribute record
      ATTRID_BASIC_HW_VERSION, // Attribute ID - Found in Cluster Library
                               //     header (ie. zcl_general.h)
      ZCL_DATATYPE_UINT8,      // Data Type - found in zcl.h
      ACCESS_CONTROL_READ,     // Variable access control - found in
                               // zcl.h
      (void *)&staHWRevision   // Pointer to attribute variable
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_ZCL_VERSION,
      ZCL_DATATYPE_UINT8,
      ACCESS_CONTROL_READ,
      (void *)&staZCLVersion
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_MANUFACTURER_NAME,
      ZCL_DATATYPE_CHAR_STR,
      ACCESS_CONTROL_READ,
      (void *)staManufacturerName
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_MODEL_ID,
      ZCL_DATATYPE_CHAR_STR,
      ACCESS_CONTROL_READ,
      (void *)staModelId
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_DATE_CODE,
      ZCL_DATATYPE_CHAR_STR,
      ACCESS_CONTROL_READ,
      (void *)staDateCode
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_POWER_SOURCE,
      ZCL_DATATYPE_UINT8,
      ACCESS_CONTROL_READ,
      (void *)&staPowerSource
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_LOCATION_DESC,
      ZCL_DATATYPE_CHAR_STR,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
      (void *)staLocationDescription
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_PHYSICAL_ENV,
      ZCL_DATATYPE_UINT8,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
      (void *)&staPhysicalEnvironment
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_DEVICE_ENABLED,
      ZCL_DATATYPE_UINT8,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
      (void *)&staSwDeviceEnable
    }
  },

  // *** Identify Cluster Attribute ***
  {
    ZCL_CLUSTER_ID_GEN_IDENTIFY,
    {
      // Attribute record
      ATTRID_IDENTIFY_TIME,
      ZCL_DATATYPE_UINT16,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
      (void *)&staIdentifyTime
    }
  },

  // *** On / Off Cluster Attributes ***
  {
    ZCL_CLUSTER_ID_GEN_ON_OFF,
    {
      // Attribute record
      ATTRID_ON_OFF,
      ZCL_DATATYPE_BOOLEAN,
      ACCESS_CONTROL_READ,
      (void *)&staSwOnOff
    }
  },

  // *** On / Off Switch Configuration Cluster *** //
  {
    ZCL_CLUSTER_ID_GEN_ON_OFF_SWITCH_CONFIG,
    {
      // Attribute record
      ATTRID_ON_OFF_SWITCH_TYPE,
      ZCL_DATATYPE_ENUM8,
      ACCESS_CONTROL_READ,
      (void *)&staOnOffSwitchType
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_ON_OFF_SWITCH_CONFIG,
    {
      // Attribute record
      ATTRID_ON_OFF_SWITCH_ACTIONS,
      ZCL_DATATYPE_ENUM8,
      ACCESS_CONTROL_READ
      | ACCESS_CONTROL_WRITE,
      (void *)&staOnOffSwitchActions
    }
  },
};

const zclAttrRec_t ztsAttrs[SENSORTAGAPP_TS_MAX_ATTRIBUTES] =
{
  // *** General Basic Cluster Attributes ***
  {
    ZCL_CLUSTER_ID_GEN_BASIC,      // Cluster IDs - defined in the
                                   //   foundation (ie. zcl.h)
    {
      // Attribute record
      ATTRID_BASIC_HW_VERSION,   // Attribute ID - Found in Cluster
                                 //  Library header (ie. zcl_general.h)
      ZCL_DATATYPE_UINT8,        // Data Type - found in zcl.h
      ACCESS_CONTROL_READ,       // Variable access control
                                 //  - found in zcl.h
      (void *)&staHWRevision     // Pointer to attribute variable
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_ZCL_VERSION,
      ZCL_DATATYPE_UINT8,
      ACCESS_CONTROL_READ,
      (void *)&staZCLVersion
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_MANUFACTURER_NAME,
      ZCL_DATATYPE_CHAR_STR,
      ACCESS_CONTROL_READ,
      (void *)staManufacturerName
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_MODEL_ID,
      ZCL_DATATYPE_CHAR_STR,
      ACCESS_CONTROL_READ,
      (void *)staModelId
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_DATE_CODE,
      ZCL_DATATYPE_CHAR_STR,
      ACCESS_CONTROL_READ,
      (void *)staDateCode
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_POWER_SOURCE,
      ZCL_DATATYPE_UINT8,
      ACCESS_CONTROL_READ,
      (void *)&staPowerSource
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_LOCATION_DESC,
      ZCL_DATATYPE_CHAR_STR,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
      (void *)staLocationDescription
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_PHYSICAL_ENV,
      ZCL_DATATYPE_UINT8,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
      (void *)&staPhysicalEnvironment
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_DEVICE_ENABLED,
      ZCL_DATATYPE_BOOLEAN,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
      (void *)&staTsDeviceEnable
    }
  },

  // *** Identify Cluster Attribute ***
  {
    ZCL_CLUSTER_ID_GEN_IDENTIFY,
    {
      // Attribute record
      ATTRID_IDENTIFY_TIME,
      ZCL_DATATYPE_UINT16,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
      (void *)&staIdentifyTime
    }
  },

  // *** On/Off Cluster Attributes ***
  {
    ZCL_CLUSTER_ID_GEN_ON_OFF,
    {
      // Attribute record
      ATTRID_ON_OFF,
      ZCL_DATATYPE_BOOLEAN,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
      (void *)&staTsOnOff
    }
  },

  // *** Temperature Measurement Attriubtes ***
  {
    ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT,
    {
      // Attribute record
      ATTRID_MS_TEMPERATURE_MEASURED_VALUE,
      ZCL_DATATYPE_INT16,
      ACCESS_CONTROL_READ,
      (void *)&staTempMeasuredValue
    }
  },
  {
    ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT,
    {
      // Attribute record
      ATTRID_MS_TEMPERATURE_MIN_MEASURED_VALUE,
      ZCL_DATATYPE_INT16,
      ACCESS_CONTROL_READ,
      (void *)&staTempMinMeasuredValue
    }
  },
  {
    ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT,
    {
      // Attribute record
      ATTRID_MS_TEMPERATURE_MAX_MEASURED_VALUE,
      ZCL_DATATYPE_UINT16,
      ACCESS_CONTROL_READ,
      (void *)&staTempMaxMeasuredValue
    }
  },
};

#if defined(LIGHTSENSOR_ENABLED)
const zclAttrRec_t zlsAttrs[SENSORTAGAPP_LS_MAX_ATTRIBUTES] =
{
  // *** General Basic Cluster Attributes ***
  {
    ZCL_CLUSTER_ID_GEN_BASIC,      // Cluster IDs - defined in the
                                   //   foundation (ie. zcl.h)
    {
      // Attribute record
      ATTRID_BASIC_HW_VERSION,   // Attribute ID - Found in Cluster
                                 //  Library header (ie. zcl_general.h)
      ZCL_DATATYPE_UINT8,        // Data Type - found in zcl.h
      ACCESS_CONTROL_READ,       // Variable access control
                                 //  - found in zcl.h
      (void *)&staHWRevision     // Pointer to attribute variable
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_ZCL_VERSION,
      ZCL_DATATYPE_UINT8,
      ACCESS_CONTROL_READ,
      (void *)&staZCLVersion
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_MANUFACTURER_NAME,
      ZCL_DATATYPE_CHAR_STR,
      ACCESS_CONTROL_READ,
      (void *)staManufacturerName
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_MODEL_ID,
      ZCL_DATATYPE_CHAR_STR,
      ACCESS_CONTROL_READ,
      (void *)staModelId
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_DATE_CODE,
      ZCL_DATATYPE_CHAR_STR,
      ACCESS_CONTROL_READ,
      (void *)staDateCode
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_POWER_SOURCE,
      ZCL_DATATYPE_UINT8,
      ACCESS_CONTROL_READ,
      (void *)&staPowerSource
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_LOCATION_DESC,
      ZCL_DATATYPE_CHAR_STR,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
      (void *)staLocationDescription
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_PHYSICAL_ENV,
      ZCL_DATATYPE_UINT8,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
      (void *)&staPhysicalEnvironment
    }
  },
  {
    ZCL_CLUSTER_ID_GEN_BASIC,
    {
      // Attribute record
      ATTRID_BASIC_DEVICE_ENABLED,
      ZCL_DATATYPE_BOOLEAN,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
      (void *)&staIlDeviceEnable
    }
  },

  // *** Identify Cluster Attribute ***
  {
    ZCL_CLUSTER_ID_GEN_IDENTIFY,
    {
      // Attribute record
      ATTRID_IDENTIFY_TIME,
      ZCL_DATATYPE_UINT16,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
      (void *)&staIdentifyTime
    }
  },

  // *** On/Off Cluster Attributes ***
  {
    ZCL_CLUSTER_ID_GEN_ON_OFF,
    {
      // Attribute record
      ATTRID_ON_OFF,
      ZCL_DATATYPE_BOOLEAN,
      (ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE),
      (void *)&staLsOnOff
    }
  },

  // *** Illuminance Measurement Attriubtes ***
  {
    ZCL_CLUSTER_ID_MS_ILLUMINANCE_MEASUREMENT,
    {
      // Attribute record
      ATTRID_MS_ILLUMINANCE_MEASURED_VALUE,
      ZCL_DATATYPE_UINT16,
      ACCESS_CONTROL_READ,
      (void *)&staIllumMeasuredValue
    }
  },
  {
    ZCL_CLUSTER_ID_MS_ILLUMINANCE_MEASUREMENT,
    {
      // Attribute record
      ATTRID_MS_ILLUMINANCE_MIN_MEASURED_VALUE,
      ZCL_DATATYPE_UINT16,
      ACCESS_CONTROL_READ,
      (void *)&staIllumMinMeasuredValue
    }
  },
  {
    ZCL_CLUSTER_ID_MS_ILLUMINANCE_MEASUREMENT,
    {
      // Attribute record
      ATTRID_MS_ILLUMINANCE_MAX_MEASURED_VALUE,
      ZCL_DATATYPE_UINT16,
      ACCESS_CONTROL_READ,
      (void *)&staIllumMaxMeasuredValue
    }
  },
};
#endif

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
 * @fn          SensorTagApp_task
 *
 * @brief       Application task entry point for the ZStack HA Temperature
 *              Sensor Application.
 *
 * @param       pfnNV - pointer to the NV functions
 *
 * @return      none
 */
void SensorTagApp_task(NVINTF_nvFuncts_t *pfnNV)
{
  // Save and register the function pointers to the NV drivers
  pfnStaNV = pfnNV;
  zclport_registerNV(pfnStaNV, ZCL_PORT_SCENE_TABLE_NV_ID);

  // Initialize application
  SensorTagApp_initialization();

  // No return from task process
  SensorTagApp_process();
}

/******************************************************************************
 * @fn          SensorTagApp_initialization
 *
 * @brief       Initialize the application
 *
 * @param       none
 *
 * @return      none
 */
static void SensorTagApp_initialization(void)
{
  /* Initialize variables */
  staSwDstAddr.addrMode = zstack_AFAddrMode_NONE;
  staSwDstAddr.addr.shortAddr = 0;
  staSwDstAddr.endpoint = 0;
  staSwDstAddr.panID = 0;
  staTsDstAddr.addrMode = zstack_AFAddrMode_NONE;
  staTsDstAddr.addr.shortAddr = 0;
  staTsDstAddr.endpoint = 0;
  staTsDstAddr.panID = 0;
#if defined(LIGHTSENSOR_ENABLED)
  staLsDstAddr.addrMode = zstack_AFAddrMode_NONE;
  staLsDstAddr.addr.shortAddr = 0;
  staLsDstAddr.endpoint = 0;
  staLsDstAddr.panID = 0;
#endif
  
#if defined(ZCL_EZMODE)
  zclport_registerEZModeTimerCB(SensorTagApp_processEzmodeTimerCallback);
#endif

  // Setup I2C for sensors
  bspI2cInit();

  // Initialise the Temperature Sensor driver
  sensorTmp007Init();

#if defined(LIGHTSENSOR_ENABLED)
  // Initialise the Light Sensor driver
  sensorOpt3001Init();
#endif

  SensorTagApp_initializeClocks();

  /* Initialize keys */
  Board_Key_initialize(SensorTagApp_processKeyChangeCallback);

  /* Initialize the LEDS */
  Board_Led_initialize();

#if defined(EXTERNAL_IMAGE_CHECK)
  /* Initialize the SPI pins */
  hGpioPin = PIN_open(&spiPinState, spiPinTable);
#endif // EXTERNAL_IMAGE_CHECK

#if defined(ZCL_REPORT)
  SensorTagApp_initReportConfig();
#endif

  // Register the current thread as an ICall dispatcher application
  // so that the application can send and receive messages.
  ICall_registerApp(&staEntity, &sem);

  // Initialize the ZStack
  SensorTagApp_initializeZStack();
}

/******************************************************************************
 * @fn      SensorTagApp_initializeClocks
 *
 * @brief   Initialize Clocks
 *
 * @param   none
 *
 * @return  none
 */
static void SensorTagApp_initializeClocks(void)
{
  // Initialize the timers needed for this application
  identifyClkHandle = Util_constructClock(
    &identifyClkStruct,
    SensorTagApp_processIdentifyTimeoutCallback,
    SENSORTAGAPP_INIT_TIMEOUT_VALUE,
    0,
    false,
    0);
  
  eraseNVClkHandle = Util_constructClock(
    &eraseNVClkStruct,
    SensorTagApp_processeraseNVTimeoutCallback,
    SENSORTAGAPP_INIT_TIMEOUT_VALUE,
    0,
    false,
    0);

#if defined(ZCL_REPORT)
  tempSensorMinClkHandle = Util_constructClock(
    &tempSensorMinClkStruct,
    SensorTagApp_processTempSensorMinTimeoutCallback,
    SENSORTAGAPP_INIT_TIMEOUT_VALUE,
    0,
    false,
    0);

  tempSensorMaxClkHandle = Util_constructClock(
    &tempSensorMaxClkStruct,
    SensorTagApp_processTempSensorMaxTimeoutCallback,
    SENSORTAGAPP_INIT_TIMEOUT_VALUE,
    0,
    false,
    0);

#if defined(LIGHTSENSOR_ENABLED)
  lightSensorMinClkHandle = Util_constructClock(
    &lightSensorMinClkStruct,
    SensorTagApp_processLightSensorMinTimeoutCallback,
    SENSORTAGAPP_INIT_TIMEOUT_VALUE,
    0,
    false,
    0);

  lightSensorMaxClkHandle = Util_constructClock(
    &lightSensorMaxClkStruct,
    SensorTagApp_processLightSensorMaxTimeoutCallback,
    SENSORTAGAPP_INIT_TIMEOUT_VALUE,
    0,
    false,
    0);
#endif
#endif

#if defined(ZCL_EZMODE)
  ezmodeTimeoutClkHandle = Util_constructClock(
    &ezmodeTimeoutClkStruct,
    SensorTagApp_processEzmodeTimeoutCallback,
    SENSORTAGAPP_INIT_TIMEOUT_VALUE,
    0,
    false,
    0);

  ezmodeStateClkHandle = Util_constructClock(
    &ezmodeStateClkStruct,
    SensorTagApp_processEzmodeStateChangeCallback,
    SENSORTAGAPP_INIT_TIMEOUT_VALUE,
    0,
    false,
    0);
#endif // ZCL_EZMODE
}

/******************************************************************************
 * @fn      SensorTagApp_registerEndpoints
 *
 * @brief   Setup a Zigbee HA Door Lock Controller Endpoint
 *
 * @param   none
 *
 * @return  none
 */
static void SensorTagApp_registerEndpoints(void)
{
  // Initialize the Switch Simple Descriptor
  staEpDesc[SENSORTAGAPP_SW_EP_IDX].endPoint = SENSORTAGAPP_SW_EP;
  afSimpleDesc[SENSORTAGAPP_SW_EP_IDX].EndPoint = SENSORTAGAPP_SW_EP;
  afSimpleDesc[SENSORTAGAPP_SW_EP_IDX].AppProfId = ZCL_HA_PROFILE_ID;
  afSimpleDesc[SENSORTAGAPP_SW_EP_IDX].AppDeviceId =
      ZCL_HA_DEVICEID_ON_OFF_SWITCH;
  afSimpleDesc[SENSORTAGAPP_SW_EP_IDX].AppDevVer =
      SENSORTAGAPP_DEVICE_VERSION;
  afSimpleDesc[SENSORTAGAPP_SW_EP_IDX].AppNumInClusters =
      sizeof(swInputClusters) / sizeof(uint_least16_t);
  afSimpleDesc[SENSORTAGAPP_SW_EP_IDX].pAppInClusterList = swInputClusters;
  afSimpleDesc[SENSORTAGAPP_SW_EP_IDX].AppNumOutClusters =
      sizeof(swOutputClusters) / sizeof(uint_least16_t);
  afSimpleDesc[SENSORTAGAPP_SW_EP_IDX].pAppOutClusterList = swOutputClusters;
  staEpDesc[SENSORTAGAPP_SW_EP_IDX].simpleDesc =
      &afSimpleDesc[SENSORTAGAPP_SW_EP_IDX];
  (void)zclport_registerEndpoint(staEntity,
                                 &staEpDesc[SENSORTAGAPP_SW_EP_IDX]);

  // Initialize the Temperature Sensor Simple Descriptor
  staEpDesc[SENSORTAGAPP_TS_EP_IDX].endPoint = SENSORTAGAPP_TS_EP;
  afSimpleDesc[SENSORTAGAPP_TS_EP_IDX].EndPoint = SENSORTAGAPP_TS_EP;
  afSimpleDesc[SENSORTAGAPP_TS_EP_IDX].AppProfId = ZCL_HA_PROFILE_ID;
  afSimpleDesc[SENSORTAGAPP_TS_EP_IDX].AppDeviceId =
      ZCL_HA_DEVICEID_TEMPERATURE_SENSOR;
  afSimpleDesc[SENSORTAGAPP_TS_EP_IDX].AppDevVer =
      SENSORTAGAPP_DEVICE_VERSION;
  afSimpleDesc[SENSORTAGAPP_TS_EP_IDX].AppNumInClusters =
      sizeof(tsInputClusters) / sizeof(uint_least16_t);
  afSimpleDesc[SENSORTAGAPP_TS_EP_IDX].pAppInClusterList = tsInputClusters;
  afSimpleDesc[SENSORTAGAPP_TS_EP_IDX].AppNumOutClusters =
      sizeof(tsOutputClusters) / sizeof(uint_least16_t);
  afSimpleDesc[SENSORTAGAPP_TS_EP_IDX].pAppOutClusterList = tsOutputClusters;
  staEpDesc[SENSORTAGAPP_TS_EP_IDX].simpleDesc =
      &afSimpleDesc[SENSORTAGAPP_TS_EP_IDX];
  (void)zclport_registerEndpoint(staEntity,
                                 &staEpDesc[SENSORTAGAPP_TS_EP_IDX]);

#if defined(LIGHTSENSOR_ENABLED)
  // Initialize the Light Sensor Simple Descriptor
  staEpDesc[SENSORTAGAPP_LS_EP_IDX].endPoint = SENSORTAGAPP_LS_EP;
  afSimpleDesc[SENSORTAGAPP_LS_EP_IDX].EndPoint = SENSORTAGAPP_LS_EP;
  afSimpleDesc[SENSORTAGAPP_LS_EP_IDX].AppProfId = ZCL_HA_PROFILE_ID;
  afSimpleDesc[SENSORTAGAPP_LS_EP_IDX].AppDeviceId =
      ZCL_HA_DEVICEID_LIGHT_SENSOR;
  afSimpleDesc[SENSORTAGAPP_LS_EP_IDX].AppDevVer =
      SENSORTAGAPP_DEVICE_VERSION;
  afSimpleDesc[SENSORTAGAPP_LS_EP_IDX].AppNumInClusters =
      sizeof(lsInputClusters) / sizeof(uint_least16_t);
  afSimpleDesc[SENSORTAGAPP_LS_EP_IDX].pAppInClusterList = lsInputClusters;
  afSimpleDesc[SENSORTAGAPP_LS_EP_IDX].AppNumOutClusters =
      sizeof(lsOutputClusters) / sizeof(uint_least16_t);
  afSimpleDesc[SENSORTAGAPP_LS_EP_IDX].pAppOutClusterList = lsOutputClusters;
  staEpDesc[SENSORTAGAPP_LS_EP_IDX].simpleDesc =
      &afSimpleDesc[SENSORTAGAPP_LS_EP_IDX];
  (void)zclport_registerEndpoint(staEntity,
                                 &staEpDesc[SENSORTAGAPP_LS_EP_IDX]);
#endif
}

/******************************************************************************
 * @fn      SensorTagApp_setupZStackCallbacks
 *
 * @brief   Setup the Zstack Callbacks wanted
 *
 * @param   none
 *
 * @return  none
 */
static void SensorTagApp_setupZStackCallbacks(void)
{
  zstack_devZDOCBReq_t zdoCBReq = {0};

  // Register for Callbacks, turn on:
  //  Device State Change,
  //  ZDO Match Descriptor Response,
  zdoCBReq.has_devStateChange = true;
  zdoCBReq.devStateChange = true;

#if defined(ZCL_EZMODE)
  zdoCBReq.has_matchDescRsp = true;
  zdoCBReq.matchDescRsp = true;
#endif

#if defined(ZCL_REPORT)
  zdoCBReq.has_mgmtBindRsp = true;
  zdoCBReq.mgmtBindRsp = true;
#endif

  (void)Zstackapi_DevZDOCBReq(staEntity, &zdoCBReq);
}

/******************************************************************************
 * @fn      SensorTagApp_writeZStackParameters
 *
 * @brief   Initialize ZStack Parameters
 *
 * @param   none
 *
 * @return  none
 */
static void SensorTagApp_writeZStackParameters(void)
{
  zstack_sysConfigWriteReq_t  writeReq = { 0 };
  uint8_t                     extendedPANID[] = ZNWK_CONFIG_EXTENDED_PAN_ID;

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
  (void) Zstackapi_sysConfigWriteReq(staEntity, &writeReq);
}

/******************************************************************************
 * @fn      SensorTagApp_initializeZStack
 *
 * @brief   Initialize ZStack
 *
 * @param   none
 *
 * @return  none
 */
static void SensorTagApp_initializeZStack(void)
{
  // Initialize the ZStack Thread
  bool  startDev = true;  // default to auto-start

  // Setup the endpoints
  SensorTagApp_registerEndpoints();

  // Setup indications from ZStack
  SensorTagApp_setupZStackCallbacks();

#if defined(ZCL_EZMODE)
  startDev = zclport_isAlreadyPartOfNetwork(staEntity);

  // Register EZ-Mode
  zcl_RegisterEZMode(&ezmodeRegisterData);
  Board_Led_control(board_led_type_LED1, board_led_state_BLINK);
#endif
  if(startDev)
  {
    zstack_devStartReq_t  startReq = { 0 };

    // Start the ZStack Thread
    startReq.startDelay = 0;
    (void) Zstackapi_DevStartReq(staEntity, &startReq);
  }

  // Register the ZCL General Cluster Library callback functions
  zclGeneral_RegisterCmdCallbacks(SENSORTAGAPP_SW_EP, &cmdCallbacks);
  zclGeneral_RegisterCmdCallbacks(SENSORTAGAPP_TS_EP, &cmdCallbacks);
#if defined(LIGHTSENSOR_ENABLED)
  zclGeneral_RegisterCmdCallbacks(SENSORTAGAPP_LS_EP, &cmdCallbacks);
#endif

  // Register the callback function for unprocessed ZCL Foundation commands
  zclport_registerZclHandleExternal(SensorTagApp_processZCLMsg);

  // Register the application's attribute list
  zcl_registerAttrList(SENSORTAGAPP_SW_EP,
                       SENSORTAGAPP_SW_MAX_ATTRIBUTES, zswAttrs);
  zcl_registerAttrList(SENSORTAGAPP_TS_EP,
                       SENSORTAGAPP_TS_MAX_ATTRIBUTES, ztsAttrs);
#if defined(LIGHTSENSOR_ENABLED)
  zcl_registerAttrList(SENSORTAGAPP_LS_EP,
                       SENSORTAGAPP_LS_MAX_ATTRIBUTES, zlsAttrs);
#endif

  // Update the ZStack Parameters
  SensorTagApp_writeZStackParameters();
}

/******************************************************************************
 * @fn      SensorTagApp_process
 *
 * @brief   Application task processing start.
 *
 * @param   none
 *
 * @return  void
 */
static void SensorTagApp_process(void)
{
  /* Forever loop */
  for (;;)
  {
    ICall_ServiceEnum       stackid;
    ICall_EntityID          dest;
    zstackmsg_genericReq_t  *pMsg;

    /* Wait for response message */
    if(ICall_wait(ICALL_TIMEOUT_FOREVER) == ICALL_ERRNO_SUCCESS)
    {
      /* Retrieve the response message */
      if(ICall_fetchServiceMsg(&stackid, &dest, (void **) &pMsg) ==
           ICALL_ERRNO_SUCCESS)
      {
        if((stackid == ICALL_SERVICE_CLASS_ZSTACK) && (dest == staEntity))
        {
          if(pMsg)
          {
            SensorTagApp_processZStackMsgs(pMsg);

            // Free any separately allocated memory
            Zstackapi_freeIndMsg(pMsg);
          }
        }

        if(pMsg)
        {
          ICall_freeMsg(pMsg);
        }
      }
      
      if(events & SENSORTAGAPP_ERASENV_TIMEOUT_EVT)
      {
        

        SensorTagApp_processEraseNVTimeChange(keys, dest);

        events &= ~SENSORTAGAPP_ERASENV_TIMEOUT_EVT;
      }

      if(events & SENSORTAGAPP_KEY_EVENT)
      {
        // Process Key Presses
        SensorTag_handleKeys(keys);
        keys = 0;
        events &= ~SENSORTAGAPP_KEY_EVENT;
      }

      if(events & SENSORTAGAPP_IDENTIFY_TIMEOUT_EVT)
      {
        // Process the Identify timer expiration
        if(staIdentifyTime > 0)
        {
          staIdentifyTime--;
        }

        SensorTagApp_processIdentifyTimeChange();

        events &= ~SENSORTAGAPP_IDENTIFY_TIMEOUT_EVT;
      }

#if defined(ZCL_REPORT)
      if(events & SENSORTAGAPP_TEMPSENSOR_MIN_TIMEOUT_EVT)
      {
        int16_t result;

        // Read the current temperature
        if(SensorTagApp_readConvertIRTemp(&result))
        {
          staTempMeasuredValue = result;
        }

        // Report if the current temperature is higher or lower than
		// the last reported value by the reportable change
        if(abs(staTempMeasuredValue - staTempMeasuredValueOld) >=
             abs(staTempReportableChange))
        {
          SensorTagApp_sendTemp();
          staTempMeasuredValueOld = staTempMeasuredValue;

          // Reset both min & max timers
          SensorTagApp_setTempSensorTimer(staTempReportConfig.minReportInt,
                                          staTempReportConfig.maxReportInt);
        }
        else
        {
          // Don't reset max timer
          SensorTagApp_setTempSensorTimer(staTempReportConfig.minReportInt,
                                          0);
        }

        events &= ~SENSORTAGAPP_TEMPSENSOR_MIN_TIMEOUT_EVT;
      }

      if(events & SENSORTAGAPP_TEMPSENSOR_MAX_TIMEOUT_EVT)
      {
        int16_t result;

        // Read the current temperature
        if(SensorTagApp_readConvertIRTemp(&result))
        {
          staTempMeasuredValue = result;
        }

        // Timed out. Report anyway.
        SensorTagApp_sendTemp();
        staTempMeasuredValueOld = staTempMeasuredValue;

        // Reset both min & max timers
        SensorTagApp_setTempSensorTimer(staTempReportConfig.minReportInt,
                                        staTempReportConfig.maxReportInt);

        events &= ~SENSORTAGAPP_TEMPSENSOR_MAX_TIMEOUT_EVT;
      }

#if defined(LIGHTSENSOR_ENABLED)
      if(events & SENSORTAGAPP_LIGHTSENSOR_MIN_TIMEOUT_EVT)
      {
        uint16_t  result;
        uint16_t  gapUnsigned;

        // Read the current illuminance
        if(SensorTagApp_readConvertIllum(&result))
        {
          staIllumMeasuredValue = result;
        }

        // Report if the current illuminance is higher or lower than
        // the last reported value by the reportable change
        gapUnsigned = (staIllumMeasuredValue > staIllumMeasuredValueOld) ?
                      (staIllumMeasuredValue - staIllumMeasuredValueOld) :
                      (staIllumMeasuredValueOld - staIllumMeasuredValue);
        if(gapUnsigned >= abs(staIllumReportableChange))
        {
          SensorTagApp_sendIllum();
          staIllumMeasuredValueOld = staIllumMeasuredValue;

          // Reset both min & max timers
          SensorTagApp_setLightSensorTimer(staIllumReportConfig.minReportInt,
                                           staIllumReportConfig.maxReportInt);
        }
        else
        {
          // Don't reset max timer
          SensorTagApp_setLightSensorTimer(staIllumReportConfig.minReportInt,
                                           0);
        }

        events &= ~SENSORTAGAPP_LIGHTSENSOR_MIN_TIMEOUT_EVT;
      }

      if(events & SENSORTAGAPP_LIGHTSENSOR_MAX_TIMEOUT_EVT)
      {
        uint16_t result;

        // Read the current illuminance
        if(SensorTagApp_readConvertIllum(&result))
        {
          staIllumMeasuredValue = result;
        }

        // Timed out. Report anyway.
        SensorTagApp_sendIllum();
        staIllumMeasuredValueOld = staIllumMeasuredValue;

        // Reset both min & max timers
        SensorTagApp_setLightSensorTimer(staIllumReportConfig.minReportInt,
                                          staIllumReportConfig.maxReportInt);

        events &= ~SENSORTAGAPP_LIGHTSENSOR_MAX_TIMEOUT_EVT;
      }
#endif  // LIGHTSENSOR_ENABLED
#endif  // ZCL_REPORT
#ifdef ZCL_EZMODE
      if(events & SENSORTAGAPP_EZMODE_NEXTSTATE_EVT)
      {
        // going on to next state
        zcl_EZModeAction(EZMODE_ACTION_PROCESS, NULL);
        events &= ~SENSORTAGAPP_EZMODE_NEXTSTATE_EVT;
      }

      if(events & SENSORTAGAPP_EZMODE_TIMEOUT_EVT)
      {
        // EZ-Mode timed out
        zcl_EZModeAction(EZMODE_ACTION_TIMED_OUT, NULL);
        events &= ~SENSORTAGAPP_EZMODE_TIMEOUT_EVT;
      }

      if(events & SENSORTAGAPP_EZMODE_FINISHED_EVT)
      {
        // Change the default poll rate from 1 second to
		// the config setting znwk_config.h
        SensorTagApp_setPollRate(ZNWK_POLL_RATE);

        // An EZMode cycle is complete
        events &= ~SENSORTAGAPP_EZMODE_FINISHED_EVT;
      }
#endif // ZLC_EZMODE
    }
  }
}

/******************************************************************************
 * @fn      SensorTagApp_processZStackMsgs
 *
 * @brief   Process event from Stack
 *
 * @param   pMsg - pointer to incoming ZStack message to process
 *
 * @return  void
 */
static void SensorTagApp_processZStackMsgs(zstackmsg_genericReq_t *pMsg)
{
  switch (pMsg->hdr.event)
  {
    case zstackmsg_CmdIDs_DEV_STATE_CHANGE_IND:
      {
        // The ZStack Thread is indicating a State change
        zstackmsg_devStateChangeInd_t *pInd =
                                       (zstackmsg_devStateChangeInd_t *) pMsg;

        // Only process the state change if it actually changed.
        if(savedState != pInd->req.state)
        {
          savedState = pInd->req.state;

          if((pInd->req.state == zstack_DevState_DEV_ZB_COORD) ||
             (pInd->req.state == zstack_DevState_DEV_ROUTER) ||
             (pInd->req.state == zstack_DevState_DEV_END_DEVICE))
          {
#if defined(ZCL_REPORT) && defined(MGMT_BIND_SUPPORTED)
            zstack_zdoMgmtBindReq_t mgmtBindReq;
#endif  // ZCL_REPORT && MGMT_BIND_SUPPORTED
            // The device is part of a network,
            // get the device's network parameters.
            pNwkInfo = zclport_getDeviceInfo(staEntity);
            if(pNwkInfo == NULL)
            {
              // Something didn't work properly
            }

            // Update the UI with network information
            Board_Led_control(board_led_type_LED1, board_led_state_BLINK);
            Board_Led_control(board_led_type_LED2, board_led_state_BLINK);

#if defined(ZCL_REPORT)
#if defined(MGMT_BIND_SUPPORTED)
            // Check if there is existing binding info
            mgmtBindReq.nwkAddr = pNwkInfo->nwkAddr;
            mgmtBindReq.startIndex = 0;
            Zstackapi_ZdoMgmtBindReq(staEntity, &mgmtBindReq);
#else // MGMT_BIND_SUPPORTED
            // Start timers anyway
            SensorTagApp_setTempSensorTimer(staTempReportConfig.minReportInt,
                                            staTempReportConfig.maxReportInt);
#if defined(LIGHTSENSOR_ENABLED)
            // Start timers anyway
            SensorTagApp_setLightSensorTimer(staIllumReportConfig.minReportInt,
                                            staIllumReportConfig.maxReportInt);
#endif  // LIGHTSENSOR_ENABLED
#endif  // MGMT_BIND_SUPPORTED
#endif  // ZCL_REPORT

            if(pInd->req.state == zstack_DevState_DEV_END_DEVICE)
            {
#if !defined(ZCL_EZMODE)
              // Change the default poll rate from 1 second to
              // the config setting in znwk_config.h
              SensorTagApp_setPollRate(ZNWK_POLL_RATE);
#endif
            }

#if defined(ZCL_EZMODE)
            zcl_EZModeAction(EZMODE_ACTION_NETWORK_STARTED, NULL);
#endif
          }
          else
          {
            Board_Led_control(board_led_type_LED1, board_led_state_BLINKING);
            Board_Led_control(board_led_type_LED2, board_led_state_OFF);
          }
        }
      }
      break;

    case zstackmsg_CmdIDs_ZDO_MATCH_DESC_RSP:
#if defined(ZCL_EZMODE)
      {
        zstackmsg_zdoMatchDescRspInd_t  *pInd =
		                              (zstackmsg_zdoMatchDescRspInd_t *) pMsg;
        zclEZMode_ActionData_t          actionData;
        ZDO_MatchDescRsp_t              *pRsp;

        /*
         * Parse the Match Descriptor Response and give it
         * to the ZCL EZMode module to process
         */
        pRsp = (ZDO_MatchDescRsp_t *) ICall_allocMsg(
		       sizeof(ZDO_MatchDescRsp_t) + pInd->rsp.n_matchList);
        if(pRsp)
        {
          pRsp->status = pInd->rsp.status;
          pRsp->nwkAddr = pInd->rsp.nwkAddrOfInterest;
          pRsp->cnt = pInd->rsp.n_matchList;
          memcpy(pRsp->epList, pInd->rsp.pMatchList, pInd->rsp.n_matchList);

          actionData.pMatchDescRsp = pRsp;
          zcl_EZModeAction(EZMODE_ACTION_MATCH_DESC_RSP, &actionData);
          ICall_freeMsg(pRsp);
        }
      }
#endif // ZCL_EZMODE
      break;

    case zstackmsg_CmdIDs_ZDO_MGMT_BIND_RSP:
#if defined(ZCL_REPORT) && defined(MGMT_BIND_SUPPORTED)
      {
        zstackmsg_zdoMgmtBindRspInd_t  *pInd =
                                  (zstackmsg_zdoMgmtBindRspInd_t *) pMsg;
        uint8_t i;

        if(pInd->rsp.srcAddr == pNwkInfo->nwkAddr)
        {
          for (i = 0; i < pInd->rsp.n_bindList; i++)
          {
            if ((pInd->rsp.pBindList[i].srcEndpoint == SENSORTAGAPP_TS_EP) &&
                (pInd->rsp.pBindList[i].clustedID ==
                 ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT))
            {
#if !defined(FORCE_REPORT)
              // Make staTempReportableChange work
              staTempMeasuredValueOld = 0x7FFF;
#endif  // FORCE_REPORT

              // Start both min & max timers
              SensorTagApp_setTempSensorTimer(staTempReportConfig.minReportInt,
                                              staTempReportConfig.maxReportInt);
            }
#if defined(LIGHTSENSOR_ENABLED)
            else
            if((pInd->rsp.pBindList[i].srcEndpoint == SENSORTAGAPP_LS_EP) &&
               (pInd->rsp.pBindList[i].clustedID ==
                ZCL_CLUSTER_ID_MS_ILLUMINANCE_MEASUREMENT))
            {
#if !defined(FORCE_REPORT)
              // Make staIllumReportableChange work
              staIllumMeasuredValueOld = 0xFFFF;
#endif  // FORCE_REPORT

              // Start both min & max timers
              SensorTagApp_setLightSensorTimer(staIllumReportConfig.minReportInt,
                                               staIllumReportConfig.maxReportInt);
            }
#endif  // LIGHTSENSOR_ENABLED
          }
        }
      }
#endif // ZCL_REPORT && MGMT_BIND_SUPPORTED
      break;
    
    case zstackmsg_CmdIDs_AF_INCOMING_MSG_IND:
      {
        // Process incoming data messages
        zstackmsg_afIncomingMsgInd_t *pInd =
                                     (zstackmsg_afIncomingMsgInd_t *) pMsg;
        SensorTagApp_processAfIncomingMsgInd(&(pInd->req));
      }
      break;

    case zstackmsg_CmdIDs_AF_DATA_CONFIRM_IND:
#if !defined(MGMT_BIND_SUPPORTED)
      {
        // Process data confirm messages
        zstack_afDataConfirmInd_t *pCnf = (zstack_afDataConfirmInd_t *)
                            &(((zstackmsg_afDataConfirmInd_t*) pMsg)->req);

        if(pCnf->status == zstack_ZStatusValues_ZApsNoBoundDevice)
        {
          if(pCnf->endpoint == SENSORTAGAPP_TS_EP)
          {
            // The temp sensor is not bound. Stop attempting to report.
            if(Util_isClockActive(&tempSensorMinClkStruct) == true)
            {
                Util_stopClock(&tempSensorMinClkStruct);
            }

            if(Util_isClockActive(&tempSensorMaxClkStruct) == true)
            {
                Util_stopClock(&tempSensorMaxClkStruct);
            }
          }
#if defined(LIGHTSENSOR_ENABLED)
          else if(pCnf->endpoint == SENSORTAGAPP_LS_EP)
          {
            // The light sensor is not bound. Stop attempting to report.
            if(Util_isClockActive(&lightSensorMinClkStruct) == true)
            {
              Util_stopClock(&lightSensorMinClkStruct);
            }
            
            if(Util_isClockActive(&lightSensorMaxClkStruct) == true)
            {
              Util_stopClock(&lightSensorMaxClkStruct);
            }
          }
#endif  // LIGHTSENSOR_ENABLED
        }
      }
#endif  // MGMT_BIND_SUPPORTED
      break;

    /*
     * These are messages/indications from ZStack that this
     * application doesn't process.  These message can be
     * processed by your application, remove from this list and
     * process them here in this switch statement.
     */

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
 * @fn          SensorTagApp_processAfIncomingMsgInd
 *
 * @brief       Process AF Incoming Message Indication message
 *
 * @param       pInMsg - pointer to the incoming message
 *
 * @return      none
 *
 */
static void SensorTagApp_processAfIncomingMsgInd(
    zstack_afIncomingMsgInd_t *pInMsg)
{
  afIncomingMSGPacket_t afMsg;

  // All incoming messages are passed to the ZCL message processor
  // Convert from ZStack API message to ZStack AF incoming data
  // Structure (ZCL needs this structure).
  afMsg.groupId = pInMsg->groupID;
  afMsg.clusterId = pInMsg->clusterId;
  afMsg.srcAddr.endPoint = pInMsg->srcAddr.endpoint;
  afMsg.srcAddr.panId = pInMsg->srcAddr.panID;
  afMsg.srcAddr.addrMode = (afAddrMode_t)pInMsg->srcAddr.addrMode;
  if((afMsg.srcAddr.addrMode == afAddr16Bit)
      || (afMsg.srcAddr.addrMode == afAddrGroup)
      || (afMsg.srcAddr.addrMode == afAddrBroadcast))
  {
    afMsg.srcAddr.addr.shortAddr = pInMsg->srcAddr.addr.shortAddr;
  }
  else if(afMsg.srcAddr.addrMode == afAddr64Bit)
  {
    memcpy(afMsg.srcAddr.addr.extAddr, &(pInMsg->srcAddr.addr.extAddr),
           Z_EXTADDR_LEN);
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
 *
 * @fn          SensorTagApp_processZCLMsg
 *
 * @brief       Process ZCL foundation commands
 *              not processed by zcl_ProcessMessageMSG()
 *
 * @param       pInMsg - pointer to the incoming message
 *
 * @return      TRUE
 *
 */
static uint8_t SensorTagApp_processZCLMsg(zclIncoming_t *pInMsg)
{
  switch (pInMsg->hdr.commandID)
  {
#if defined(ZCL_REPORT)
    case ZCL_CMD_CONFIG_REPORT:
      SensorTagApp_ProcessInConfigReportCmd(pInMsg);
      break;

    case ZCL_CMD_READ_REPORT_CFG:
      // SensorTagApp_ProcessInReadReportCfgCmd(pInMsg);
      break;
#endif // ZCL_REPORT

    default:
      break;
  }

  if(pInMsg->attrCmd != NULL)
  {
    // free the parsed command
    ICall_free(pInMsg->attrCmd);
    pInMsg->attrCmd = NULL;
  }

  return TRUE;
}

/******************************************************************************
 * @fn      SensorTag_handleKeys
 *
 * @brief   Callback service for keys
 *
 * @param   keys  - keys that were pressed
 *
 * @return  void
 */
static void SensorTag_handleKeys(uint8_t keys)
{
  if(keys == KEY_LEFT)
  {
    // Handle the switch part of the device and send a switch toggle cmd
    SensorTagApp_sendToggle();
  }
  else if(keys == KEY_RIGHT)
  {
    // Start EZMode for the Switch Endpoint
    SensorTagApp_startEzMode(SENSORTAGAPP_SW_EP);
    
  }
  else if(keys == (KEY_RIGHT | KEY_LEFT))
  {
#if defined(LIGHTSENSOR_ENABLED)
    if(whichSensorEP == SENSORTAGAPP_TS_EP)
    {
      // Start EZMode for the Temp Sensor Endpoint
      SensorTagApp_startEzMode(SENSORTAGAPP_TS_EP);
      whichSensorEP = SENSORTAGAPP_LS_EP;
    }
    else
    {
      // Start EZMode for the Light Sensor Endpoint
      SensorTagApp_startEzMode(SENSORTAGAPP_LS_EP);
      whichSensorEP = SENSORTAGAPP_TS_EP;
    }
#else
    // Start EZMode for the Temp Sensor Endpoint
    SensorTagApp_startEzMode(SENSORTAGAPP_TS_EP);
#endif
  }

  // Check for an indication that the Factory Reset is supposed to happen
  else if(keys == (KEY_SELECT | KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT))
  {
    SensorTagApp_applyFactoryImage();
  }
  else if(keys == (KEY_SELECT | KEY_UP | KEY_DOWN | KEY_RIGHT))
  {
    
    Board_Led_control(board_led_type_LED2, board_led_state_ON);
    SensorTagApp_resetNVErase();
  }
}

/*********************************************************************
 * @fn      SensorTagApp_processKeyChangeCallback
 *
 * @brief   Key event handler function
 *
 * @param   keysPressed - ignored
 *
 * @return  none
 */
static void SensorTagApp_processKeyChangeCallback(uint8_t keysPressed)
{
  // Save the key press information
  keys = keysPressed;

  // set the key press event
  events |= SENSORTAGAPP_KEY_EVENT;

  // Wake up the application thread when it waits for clock event
  Semaphore_post(sem);
}

#if defined(ZCL_EZMODE)
/*********************************************************************
 * @fn      SensorTagApp_processEzmodeCallback
 *
 * @brief   The Application is informed of events. This can be used to
 *          show on the UI what is going on during EZ-Mode
 *          steering/finding/binding.
 *
 * @param   state - ignored
 * @param   pData - pointer to the callback data
 *
 * @return  none
 */
static void SensorTagApp_processEzmodeCallback(zlcEZMode_State_t state,
                                               zclEZMode_CBData_t *pData)
{
  uint8_t err;

  // time to go into identify mode
  if(state == EZMODE_STATE_IDENTIFYING)
  {
    staIdentifyTime = SENSORTAGAPP_CONVERT_TO_SECONDS(EZMODE_TIME);
    SensorTagApp_processIdentifyTimeChange();
  }

  // autoclosing, show what happened (success, cancelled, etc...)
  if(state == EZMODE_STATE_AUTOCLOSE)
  {
    err = pData->sAutoClose.err;
    if(err == EZMODE_ERR_SUCCESS)
    {
      // EZMode: Success
    }
    else if(err == EZMODE_ERR_NOMATCH)
    {
      // EZMode: NoMatch
    }
  }

  // finished, either show DstAddr/EP,
  // or nothing (depending on success or not)
  if(state == EZMODE_STATE_FINISH)
  {
    // turn off identify mode
    staIdentifyTime = 0;
    SensorTagApp_processIdentifyTimeChange();

    // if successful, inform user which nwkaddr/ep we bound to
    err = pData->sFinish.err;
    if(err == EZMODE_ERR_SUCCESS)
    {
      // EZMode: Success
#if defined(FORCE_REPORT)
      // initiate periodic reporting based on default intervals
      if(zclEZModeInvokeData.endpoint == SENSORTAGAPP_TS_EP)
      {
        SensorTagApp_setTempSensorTimer(staTempReportConfig.minReportInt,
                                        staTempReportConfig.maxReportInt);
      }
#if defined(LIGHTSENSOR_ENABLED)
      else if(zclEZModeInvokeData.endpoint == SENSORTAGAPP_LS_EP)
      {
        SensorTagApp_setLightSensorTimer(staIllumReportConfig.minReportInt,
                                         staIllumReportConfig.maxReportInt);
      }
#endif  // LIGHTSENSOR_ENABLED
#endif  // FORCE_REPORT

      Board_Led_control(board_led_type_LED1, board_led_state_BLINK);
      Board_Led_control(board_led_type_LED2, board_led_state_BLINK);
    }
    else if(err == EZMODE_ERR_BAD_PARAMETER)
    {
      // EZMode: BadParm
    }
    else if(err == EZMODE_ERR_CANCELLED)
    {
      // EZMode: Cancel
    }
    else
    {
      // EZMode: TimeOut
    }

    // Finished, notify the app's event processing
    events |= SENSORTAGAPP_EZMODE_FINISHED_EVT;

    // Wake up the application
    Semaphore_post(sem);
  }
}
#endif // ZCL_EZMODE

/*********************************************************************
 * @fn      SensorTagApp_processIdentifyTimeChange
 *
 * @brief   Called to process any change to the IdentifyTime attribute.
 *
 * @param   none
 *
 * @return  none
 */
static void SensorTagApp_processIdentifyTimeChange(void)
{
  // Stop the Identify timer
  if(Util_isClockActive(&identifyClkStruct) == true)
  {
    Util_stopClock(&identifyClkStruct);
  }

  // Are we still identifying?
  if(staIdentifyTime > 0)
  {
    // Continue with another timer
    Clock_setTimeout(identifyClkHandle,
          ((staIdentifyTime * SENSORTAGAPP_1SEC_MSEC) * TIMER_MS_ADJUSTMENT));
    Util_startClock(&identifyClkStruct);

    Board_Led_control(board_led_type_LED2, board_led_state_BLINKING);
  }
  else
  {
    Board_Led_control(board_led_type_LED2, board_led_state_OFF);
  }
}

/*********************************************************************
 * @fn      SensorTagApp_processIdentifyCallback
 *
 * @brief   Callback from the ZCL General Cluster Library when
 *          it received an Identity Command for this application.
 *
 * @param   pCmd - pointer to Identify command
 *
 * @return  none
 */
static void SensorTagApp_processIdentifyCallback(zclIdentify_t *pCmd)
{
  // Save the incoming time and setup a timer
  staIdentifyTime = pCmd->identifyTime;
  SensorTagApp_processIdentifyTimeChange();
}

/*********************************************************************
 * @fn      SensorTagApp_processIdentifyQueryResponseCallback
 *
 * @brief   Callback from the ZCL General Cluster Library when
 *          it received an Identity Query Response Command
 *          for this application.
 *
 * @param   pRsp - pointer to the incoming ZCL Response
 *
 * @return  none
 */
static void SensorTagApp_processIdentifyQueryResponseCallback(
    zclIdentifyQueryRsp_t *pRsp)
{
#if defined(ZCL_EZMODE)
  {
    // ZCL EZMode will process this response message
    zclEZMode_ActionData_t  data;
    data.pIdentifyQueryRsp = pRsp;
    zcl_EZModeAction(EZMODE_ACTION_IDENTIFY_QUERY_RSP, &data);
  }

#else
  // If you don't have EZMode enabled, add your own code
  // to Process this response message
  (void) pRsp;
#endif
}

#if defined(ZCL_EZMODE)
/*********************************************************************
 * @fn      SensorTagApp_processEzmodeTimerCallback
 *
 * @param   start - true to start a timeer, false to stop a timer
 * @param   event_id - timer ID
 * @param   timeout_value - in milliseconds
 *
 * @return  none
 */
static void SensorTagApp_processEzmodeTimerCallback(bool start,
                                                    uint16_t event_id,
                                                    uint32_t timeout_value)
{
  if(event_id == SENSORTAGAPP_EZMODE_TIMEOUT_EVT)
  {
    // Setup the EZMode Timeout timer
    if(Util_isClockActive(&ezmodeTimeoutClkStruct) == true)
    {
      Util_stopClock(&ezmodeTimeoutClkStruct);
    }

    if(start)
    {
      Clock_setTimeout(ezmodeTimeoutClkHandle,
                       (timeout_value * TIMER_MS_ADJUSTMENT));
      Util_startClock(&ezmodeTimeoutClkStruct);
    }
  }
  else if(event_id == SENSORTAGAPP_EZMODE_NEXTSTATE_EVT)
  {
    // Setup the EZMode Next State timer
    if(Util_isClockActive(&ezmodeStateClkStruct) == true)
    {
      Util_stopClock(&ezmodeStateClkStruct);
    }

    if(start)
    {
      Clock_setTimeout(ezmodeStateClkHandle,
                       (timeout_value * TIMER_MS_ADJUSTMENT));
      Util_startClock(&ezmodeStateClkStruct);
    }
  }
}

/******************************************************************************
 * @fn      SensorTagApp_processEzmodeTimeoutCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void SensorTagApp_processEzmodeTimeoutCallback(UArg a0)
{
  (void) a0;  // Parameter is not used

  events |= SENSORTAGAPP_EZMODE_TIMEOUT_EVT;

  // Wake up the application thread when it waits for clock event
  Semaphore_post(sem);
}

/******************************************************************************
 * @fn      SensorTagApp_processEzmodeStateChangeCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void SensorTagApp_processEzmodeStateChangeCallback(UArg a0)
{
  (void) a0;  // Parameter is not used

  events |= SENSORTAGAPP_EZMODE_NEXTSTATE_EVT;

  // Wake up the application thread when it waits for clock event
  Semaphore_post(sem);
}
#endif // ZCL_EZMODE

/******************************************************************************
 * @fn      SensorTagApp_processIdentifyTimeoutCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void SensorTagApp_processIdentifyTimeoutCallback(UArg a0)
{
  (void) a0;  // Parameter is not used

  events |= SENSORTAGAPP_IDENTIFY_TIMEOUT_EVT;

  // Wake up the application thread when it waits for clock event
  Semaphore_post(sem);
}

/*********************************************************************
 * @fn      SensorTagApp_processEraseNVTimeChange
 *
 * @brief   Called to process any change to the IdentifyTime attribute.
 *
 * @param   none
 *
 * @return  none
 */
static void SensorTagApp_processEraseNVTimeChange(uint8_t keysPressed,ICall_EntityID dest)
{
  
  Board_Led_control(board_led_type_LED2, board_led_state_OFF);
  zstack_sysResetReq_t restReq;  
  restReq.newNwkState = true;
  (void)Zstackapi_sysResetReq(staEntity, &restReq);  
  
}

/******************************************************************************
 * @fn      SensorTagApp_processeraseNVTimeoutCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void SensorTagApp_processeraseNVTimeoutCallback(UArg a0)
{
  (void) a0;  // Parameter is not used

  events |= SENSORTAGAPP_ERASENV_TIMEOUT_EVT;

  // Wake up the application thread when it waits for clock event
  Semaphore_post(sem);
}

/******************************************************************************
 * @fn          SensorTagApp_setEraseNVTimer
 *
 * @brief       Call function to Setup the next Illuminance reading
 *
 * @param       none
 *
 * @return      none
 */
static void SensorTagApp_resetNVErase(void)
{
  zstack_zdoMgmtLeaveReq_t leaveReq;
  zstack_sysNwkInfoReadRsp_t *nwkInfo;
  nwkInfo = zclport_getDeviceInfo(staEntity);
  memcpy(leaveReq.deviceAddress, nwkInfo->ieeeAddr, EXTADDR_LEN);
  leaveReq.nwkAddr = nwkInfo->nwkAddr;
  leaveReq.options.rejoin = false;
  leaveReq.options.removeChildren = false;
  
  Zstackapi_ZdoMgmtLeaveReq( staEntity, &leaveReq);	
  
  // Reset after a couple of seconds (gives user a chance to see LED)
  // If the timer is running, stop it
  if(Util_isClockActive(&eraseNVClkStruct) == true)
  {
    Util_stopClock(&eraseNVClkStruct);
  }
  
  // Set the timeout
  Clock_setTimeout(eraseNVClkHandle,
                   ( 3000 * TIMER_MS_ADJUSTMENT));
  Board_Led_control(board_led_type_LED2, board_led_state_BLINKING);
  Util_startClock(&eraseNVClkStruct);
    
}


/******************************************************************************
 * @fn      SensorTagApp_setPollRate
 *
 * @brief   Set the ZStack Thread Poll Rate
 *
 * @param   newPollRate - new poll rate in milliseconds
 *
 * @return  none
 */
static void SensorTagApp_setPollRate(uint32_t newPollRate)
{
  zstack_sysConfigWriteReq_t  writeReq = { 0 };

  // Set the new poll rate
  writeReq.has_pollRate = true;
  writeReq.pollRate = newPollRate;
  (void) Zstackapi_sysConfigWriteReq(staEntity, &writeReq);
}

/******************************************************************************
 * @fn      SensorTagApp_startEzMode
 *
 * @brief   Start the EZMode process
 *
 * @param   none
 *
 * @return  none
 */
static void SensorTagApp_startEzMode(uint8_t endpoint)
{
#if defined(ZCL_EZMODE)
  zclEZMode_InvokeData_t  ezModeData;

  // Cluster list for a switch discovery
  static uint16_t swClusterIDs[] =
  {
    ZCL_CLUSTER_ID_GEN_ON_OFF,
  };
  // Cluster list for a temp sensor discovery
  static uint16_t tsClusterIDs[] =
  {
    ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT
  };
#if defined(LIGHTSENSOR_ENABLED)
  // Cluster list for a light sensor discovery
  static uint16_t lsClusterIDs[] =
  {
    ZCL_CLUSTER_ID_MS_ILLUMINANCE_MEASUREMENT
  };
#endif

  // Invoke EZ-Mode
  ezModeData.endpoint = endpoint;      // endpoint on which to invoke EZ-Mode
  if((savedState == zstack_DevState_DEV_ZB_COORD) ||
      (savedState == zstack_DevState_DEV_ROUTER) ||
      (savedState == zstack_DevState_DEV_END_DEVICE))
  {
    ezModeData.onNetwork = true;          // node is already on the network
  }
  else
  {
    ezModeData.onNetwork = false;         // node is not yet on the network
  }

  ezModeData.initiator = true;            // This device is an initiator

  // Which EZMode do we want to setup for Switch or Temp Sensor
  if(endpoint == SENSORTAGAPP_SW_EP)
  {
    // Setup for Switch discovery
    ezModeData.numActiveInClusters = 0;
    ezModeData.pActiveInClusterIDs = NULL;
    ezModeData.numActiveOutClusters = 1;  // active output cluster
    ezModeData.pActiveOutClusterIDs = swClusterIDs;
  }
#if defined(LIGHTSENSOR_ENABLED)
  else if(endpoint == SENSORTAGAPP_LS_EP)
  {
    // Setup for Light Sensor discovery
    ezModeData.numActiveInClusters = 1; // active input cluster
    ezModeData.pActiveInClusterIDs = lsClusterIDs;
    ezModeData.numActiveOutClusters = 0;
    ezModeData.pActiveOutClusterIDs = NULL;
  }
#endif
  else // SENSORTAGAPP_TS_EP
  {
    // Setup for Temp Sensor discovery
    ezModeData.numActiveInClusters = 1;   // active input cluster
    ezModeData.pActiveInClusterIDs = tsClusterIDs;
    ezModeData.numActiveOutClusters = 0;
    ezModeData.pActiveOutClusterIDs = NULL;
  }

  zcl_InvokeEZMode(&ezModeData);

  SensorTagApp_setPollRate(SENSORTAGAPP_EZMODE_POLL_RATE);
#endif // ZCL_EZMODE
}

/******************************************************************************
 * @fn      SensorTagApp_sendToggle
 *
 * @brief   Send an ON/OFF toggle command
 *
 * @param   none
 *
 * @return  none
 */
static void SensorTagApp_sendToggle(void)
{
  afAddrType_t  dstAddr;

  // Setup the destination address
  dstAddr.addrMode = (afAddrMode_t) staSwDstAddr.addrMode;
  dstAddr.addr.shortAddr = staSwDstAddr.addr.shortAddr;
  dstAddr.endPoint = staSwDstAddr.endpoint;
  dstAddr.panId = staSwDstAddr.panID;

  // Send a toggle command through ZCL
  zclGeneral_SendOnOff_CmdToggle(SENSORTAGAPP_SW_EP, &dstAddr, false, 0);
}

/******************************************************************************
 * @fn          SensorTagApp_readConvertIRTemp
 *
 * @brief       Call function to read temp sensor.
 *
 * @param       pResult - pointer to result
 *
 * @return      true if temp read
 */
static bool SensorTagApp_readConvertIRTemp(int16_t *pResult)
{
  bool        ret;
  TempData_t  tmpData;

  // Read data from the Tmp007 Temperature sensor
  sensorTmp007Enable(true);
  delay_ms(SENSORTAGAPP_TEMP_MEAS_DELAY);
  ret = sensorTmp007Read(&tmpData.v.tempLocal, &tmpData.v.tempTarget);
  sensorTmp007Enable(false);

  if(ret)
  {
    float tObj; // result - object temperature
    float tTgt; // result - ambience temperature

    // Convert from raw temp to Celcius
    sensorTmp007Convert(tmpData.v.tempTarget, tmpData.v.tempLocal,
                        &tObj, &tTgt);

    // We are using the ambience temperature from the chip.
    // If you want to use the object temperature, use tObj below.
    // Convert to pResult, multiply by 100,
    // use the 24.75 C will look like 2475
    *pResult = (int16_t) (tTgt * 100);
  }

  return ret;
}

#if defined(LIGHTSENSOR_ENABLED)
/******************************************************************************
 * @fn          SensorTagApp_readConvertIllum
 *
 * @brief       Call function to read light sensor.
 *
 * @param       pResult - pointer to result
 *
 * @return      true if illuminance read
 */
static bool SensorTagApp_readConvertIllum(uint16_t *pResult)
{
  bool      ret;
  uint16_t  illumData;

  // Read data from the OPT3001 light sensor
  sensorOpt3001Enable(true);
  delay_ms(SENSORTAGAPP_ILLUM_MEAS_DELAY);
  ret = sensorOpt3001Read(&illumData);
  sensorOpt3001Enable(false);

  if(ret)
  {
    float fLux, fResult;

    // Convert from raw illuminance to Lux and then
    // to Illuminance Measurement cluster value
    fLux = sensorOpt3001Convert(illumData);
    fResult = 10000. * log(fLux) + 1;

    if(fResult < 1.)
    {
      *pResult = 0;
    }
    else if(fResult > 65534.)
    {
      *pResult = 0xffff;
    }
    else
    {
      *pResult = (uint16_t) fResult;
    }
  }

  return ret;
}
#endif

#if defined(ZCL_REPORT)
/*********************************************************************
 * @fn      SensorTagApp_ProcessInConfigReportCmd
 *
 * @brief   Process the Configure Reporting Command
 *
 * @param   pInMsg - incoming message to process
 *
 * @return  TRUE if attribute was found in the Attribute list,
 *          FALSE if not
 */
static uint8_t SensorTagApp_ProcessInConfigReportCmd(zclIncoming_t *pInMsg)
{
  zclCfgReportCmd_t *cfgReportCmd;
  zclCfgReportRec_t *reportRec;
  zclCfgReportRspCmd_t *cfgReportRspCmd;
  uint8 status;
  uint8 i, j = 0;
#if !defined(FORCE_REPORT)
  zclAttrRec_t attrRec;
#endif

  cfgReportCmd = (zclCfgReportCmd_t *)pInMsg->attrCmd;

  // Allocate space for the response command
  cfgReportRspCmd = (zclCfgReportRspCmd_t *) ICall_malloc(
                     sizeof(zclCfgReportRspCmd_t) +
                     sizeof (zclCfgReportStatus_t) * cfgReportCmd->numAttr);
  if(cfgReportRspCmd == NULL)
  {
    return FALSE; // EMBEDDED RETURN
  }

  // Process each Attribute Reporting Configuration record
  for (i = 0; i < cfgReportCmd->numAttr; i++)
  {
#if defined(FORCE_REPORT)
    // Attribute is not supported for configuration
    status = ZCL_STATUS_UNSUPPORTED_ATTRIBUTE;
#else // FORCE_REPORT
    reportRec = &(cfgReportCmd->attrList[i]);

    status = ZCL_STATUS_SUCCESS;

    if(zclFindAttrRec(pInMsg->msg->endPoint, pInMsg->msg->clusterId,
                         reportRec->attrID, &attrRec))
    {
      if(reportRec->direction == ZCL_SEND_ATTR_REPORTS)
      {
        if(reportRec->dataType == attrRec.attr.dataType)
        {
          reportConfig_t* pReportConfig;
          uint8_t cfgIdx;

          cfgIdx = SensorTagApp_getReportConfigIdx(&(attrRec.attr));

          if(cfgIdx < MAX_REPORT_ATTR)
          {
            // This the attribute that is to be reported
            pReportConfig = staReportConfigList[cfgIdx];
            
            if(reportRec->minReportInt < MIN_HA_MIN_REPORTING_INT ||
                 (reportRec->maxReportInt != 0 &&
                   (reportRec->maxReportInt < reportRec->minReportInt ||
                     reportRec->maxReportInt < MIN_HA_MAX_REPORTING_INT)))
            {
              // Invalid fields
              status = ZCL_STATUS_INVALID_VALUE;
            }
            else
            {
              // Set the Min and Max Reporting Intervals and Reportable Change
              pReportConfig->minReportInt = reportRec->minReportInt;
              pReportConfig->maxReportInt = reportRec->maxReportInt;
              memcpy(pReportConfig->pReportableChange,
                     &(reportRec->reportableChange[0]),
                     zclGetDataTypeLength(reportRec->dataType));
              pReportConfig->configTimer(pReportConfig->minReportInt,
                                         pReportConfig->maxReportInt);

              // Save the paramaters to NV
              if(pfnStaNV && pfnStaNV->writeItem)
              {
                reportConfigEntry_t* pCfgEntry;
                uint8_t len;

                len = sizeof(reportConfigEntry_t) +
                      zclGetDataTypeLength(pReportConfig->dataType);
                
                pCfgEntry = ICall_malloc(len);
                
                if(pCfgEntry)
                {
                  NVINTF_itemID_t nvId;

                  // Fill in the NV ID header
                  nvId.systemID = NVINTF_SYSID_APP;
                  nvId.itemID = (uint16_t) SENSORTAGAPP_NV_REPORT_CFG_TBL;
                  nvId.subID = (uint16_t) cfgIdx;

                  pCfgEntry->minReportInt = pReportConfig->minReportInt;
                  pCfgEntry->maxReportInt = pReportConfig->maxReportInt;
                  memcpy(&(pCfgEntry->reportableChange[0]),
                         pReportConfig->pReportableChange,
                         zclGetDataTypeLength(pReportConfig->dataType));

                  pfnStaNV->writeItemEx(nvId, 0, len, pCfgEntry);
                  
                  ICall_free(pCfgEntry);
                }
              }

              status = ZCL_STATUS_SUCCESS;
            }
          }
          else
          {
            // Attribute cannot be reported
            status = ZCL_STATUS_UNREPORTABLE_ATTRIBUTE;
          }
        }
        else
        {
          // Attribute data type is incorrect
          status = ZCL_STATUS_INVALID_DATA_TYPE;
        }
      }
      else
      {
        // ZCL_EXPECT_ATTR_REPORTS direction is not supported
        status = ZCL_STATUS_UNSUPPORTED_ATTRIBUTE; // for now
      }
    }
    else
    {
      // Attribute is not supported
      status = ZCL_STATUS_UNSUPPORTED_ATTRIBUTE;
    }
#endif// FORCE_REPORT

    // If not successful then record the status
    if(status != ZCL_STATUS_SUCCESS)
    {
      cfgReportRspCmd->attrList[j].status = status;
      cfgReportRspCmd->attrList[j++].attrID = reportRec->attrID;
    }
  } // for loop

  if(j == 0)
  {
    // Since all attributes were configured successfully, include a single
    // attribute status record in the response command with the status field
    // set to SUCCESS and the attribute ID field omitted.
    cfgReportRspCmd->attrList[0].status = ZCL_STATUS_SUCCESS;
    cfgReportRspCmd->numAttr = 1;
  }
  else
  {
    cfgReportRspCmd->numAttr = j;
  }

  // Send the response back
  zcl_SendConfigReportRspCmd(pInMsg->msg->endPoint, &(pInMsg->msg->srcAddr),
                             pInMsg->msg->clusterId, cfgReportRspCmd,
                             ZCL_FRAME_SERVER_CLIENT_DIR,
                             TRUE, pInMsg->hdr.transSeqNum);
  ICall_free(cfgReportRspCmd);

  return TRUE ;
}

/******************************************************************************
 * @fn      SensorTagApp_processTempSensorMinTimeoutCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void SensorTagApp_processTempSensorMinTimeoutCallback(UArg a0)
{
  (void) a0;  // Parameter is not used

  events |= SENSORTAGAPP_TEMPSENSOR_MIN_TIMEOUT_EVT;

  // Wake up the application thread when it waits for clock event
  Semaphore_post(sem);
}

/******************************************************************************
 * @fn      SensorTagApp_processTempSensorMaxTimeoutCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void SensorTagApp_processTempSensorMaxTimeoutCallback(UArg a0)
{
  (void) a0;  // Parameter is not used

  events |= SENSORTAGAPP_TEMPSENSOR_MAX_TIMEOUT_EVT;

  // Wake up the application thread when it waits for clock event
  Semaphore_post(sem);
}

/******************************************************************************
 * @fn          SensorTagApp_setTempTimer
 *
 * @brief       Call function to Setup the next Temperature reading
 *
 * @param       none
 *
 * @return      none
 */
static void SensorTagApp_setTempSensorTimer(uint16_t minInterval,
                                            uint16_t maxInterval)
{
  // If the Temp timers are running, stop them
  if(Util_isClockActive(&tempSensorMinClkStruct) == true)
  {
      Util_stopClock(&tempSensorMinClkStruct);
  }

  // If maxInterval is 0, don't stop currently running max timer
  if((maxInterval != 0) &&
      (Util_isClockActive(&tempSensorMaxClkStruct) == true))
  {
      Util_stopClock(&tempSensorMaxClkStruct);
  }

  // Reconfigure Temp Sensor timers in 10 usec increments
  if(maxInterval != ZCL_REPORTING_OFF)
  {
    if(minInterval < maxInterval)
    {
      // Don't run min timer if min int is the same as max int
      Clock_setTimeout(tempSensorMinClkHandle,
                       (minInterval * 1000 * TIMER_MS_ADJUSTMENT));
      Util_startClock(&tempSensorMinClkStruct);
    }

    if(maxInterval != 0)
    {
      // Restart the max timer if maxInterval is not 0
      Clock_setTimeout(tempSensorMaxClkHandle,
                       (maxInterval * 1000 * TIMER_MS_ADJUSTMENT));
      Util_startClock(&tempSensorMaxClkStruct);
    }
  }
}

/*********************************************************************
 * @fn      SensorTagApp_sendTemp
 *
 * @brief   Called to send current temperature information to the thermostat
 *
 * @param   none
 *
 * @return  none
 */
static void SensorTagApp_sendTemp(void)
{
  zclReportCmd_t  *pReportCmd;

  // Build and send a ZCL temperature reading to the matched device
  pReportCmd = ICall_malloc(sizeof(zclReportCmd_t) + sizeof(zclReport_t));
  if(pReportCmd != NULL)
  {
    afAddrType_t  dstAddr;

    // Fill in the destination address
    dstAddr.addrMode = (afAddrMode_t) staTsDstAddr.addrMode;
    dstAddr.addr.shortAddr = staTsDstAddr.addr.shortAddr;
    dstAddr.endPoint = staTsDstAddr.endpoint;
    dstAddr.panId = staTsDstAddr.panID;

    // Fill in the single attribute information for the temperature reading
    pReportCmd->numAttr = 1;
    pReportCmd->attrList[0].attrID = ATTRID_MS_TEMPERATURE_MEASURED_VALUE;
    pReportCmd->attrList[0].dataType = ZCL_DATATYPE_INT16;
    pReportCmd->attrList[0].attrData = (void *) (&staTempMeasuredValue);

    // Call ZCL function to send the report
    zcl_SendReportCmd(SENSORTAGAPP_TS_EP, &dstAddr,
                      ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT, pReportCmd,
                      ZCL_FRAME_SERVER_CLIENT_DIR, true, staTransID++);

    ICall_free(pReportCmd);
  }
}

#if defined(LIGHTSENSOR_ENABLED)
/******************************************************************************
 * @fn      SensorTagApp_processLightSensorMinTimeoutCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void SensorTagApp_processLightSensorMinTimeoutCallback(UArg a0)
{
  (void) a0;  // Parameter is not used

  events |= SENSORTAGAPP_LIGHTSENSOR_MIN_TIMEOUT_EVT;

  // Wake up the application thread when it waits for clock event
  Semaphore_post(sem);
}

/******************************************************************************
 * @fn      SensorTagApp_processLightSensorMinTimeoutCallback
 *
 * @brief   Timeout handler function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void SensorTagApp_processLightSensorMaxTimeoutCallback(UArg a0)
{
  (void) a0;  // Parameter is not used

  events |= SENSORTAGAPP_LIGHTSENSOR_MAX_TIMEOUT_EVT;

  // Wake up the application thread when it waits for clock event
  Semaphore_post(sem);
}

/******************************************************************************
 * @fn          SensorTagApp_setIllumTimer
 *
 * @brief       Call function to Setup the next Illuminance reading
 *
 * @param       none
 *
 * @return      none
 */
static void SensorTagApp_setLightSensorTimer(uint16_t minInterval,
                                             uint16_t maxInterval)
{
  // If the Light timers are running, stop them
  if(Util_isClockActive(&lightSensorMinClkStruct) == true)
  {
    Util_stopClock(&lightSensorMinClkStruct);
  }
  
  // If maxInterval is 0, don't stop currently running max timer
  if((maxInterval != 0) &&
      (Util_isClockActive(&lightSensorMaxClkStruct) == true))
  {
    Util_stopClock(&lightSensorMaxClkStruct);
  }
  
  // Reconfigure Light Sensor timers in 10 usec increments
  if(maxInterval != ZCL_REPORTING_OFF)
  {
    if(minInterval < maxInterval)
    {
      // Don't run min timer if min int is the same as max int
      Clock_setTimeout(lightSensorMinClkHandle,
                       (minInterval * 1000 * TIMER_MS_ADJUSTMENT));
      Util_startClock(&lightSensorMinClkStruct);
    }
    
    if(maxInterval != 0)
    {
      // Restart the max timer if maxInterval is not 0
      Clock_setTimeout(lightSensorMaxClkHandle,
                       (maxInterval * 1000 * TIMER_MS_ADJUSTMENT));
      Util_startClock(&lightSensorMaxClkStruct);
    }
  }
}

/*********************************************************************
 * @fn      SensorTagApp_sendIllum
 *
 * @brief   Called to send current illuminance information to the gateway
 *
 * @param   none
 *
 * @return  none
 */
static void SensorTagApp_sendIllum(void)
{
  zclReportCmd_t *pReportCmd;

  // Build and send a ZCL illuminance reading to the matched device
  pReportCmd = ICall_malloc(sizeof(zclReportCmd_t) + sizeof(zclReport_t));
  if(pReportCmd != NULL)
  {
    afAddrType_t dstAddr;

    // Fill in the destination address
    dstAddr.addrMode = (afAddrMode_t)staLsDstAddr.addrMode;
    dstAddr.addr.shortAddr = staLsDstAddr.addr.shortAddr;
    dstAddr.endPoint = staLsDstAddr.endpoint;
    dstAddr.panId = staLsDstAddr.panID;

    // Fill in the single attribute information
    // for the temperature reading
    pReportCmd->numAttr = 1;
    pReportCmd->attrList[0].attrID = ATTRID_MS_ILLUMINANCE_MEASURED_VALUE;
    pReportCmd->attrList[0].dataType = ZCL_DATATYPE_UINT16;
    pReportCmd->attrList[0].attrData = (void *)(&staIllumMeasuredValue);

    // Call ZCL function to send the report
    zcl_SendReportCmd(SENSORTAGAPP_LS_EP, &dstAddr,
                      ZCL_CLUSTER_ID_MS_ILLUMINANCE_MEASUREMENT,
                      pReportCmd,
                      ZCL_FRAME_SERVER_CLIENT_DIR,
                      true,
                      staTransID++);

    ICall_free(pReportCmd);
  }
}
#endif  // LIGHTSENSOR_ENABLED

/******************************************************************************
 * @fn      SensorTagApp_initReportConfig
 *
 * @brief   report configurations initialization function
 *
 * @param   a0 - ignored
 *
 * @return  none
 */
static void SensorTagApp_initReportConfig(void)
{
  staTempMeasuredValueOld = 0;
  staTempReportConfig.dataType = ZCL_DATATYPE_INT16;
  staTempReportConfig.pAttr = &staTempMeasuredValue;
  staTempReportConfig.pAttrOld = &staTempMeasuredValueOld;
  staTempReportConfig.pReportableChange = &staTempReportableChange;
  staTempReportConfig.configTimer = SensorTagApp_setTempSensorTimer;
#if defined(FORCE_REPORT)
  staTempReportConfig.minReportInt = DEFAULT_TEMP_REPORTING_INTERVAL;
  staTempReportConfig.maxReportInt = DEFAULT_TEMP_REPORTING_INTERVAL;
#else // FORCE_REPORT
  staTempReportConfig.minReportInt = MIN_HA_MIN_REPORTING_INT;
  staTempReportConfig.maxReportInt = 0;

  staReportConfigList[0] = &staTempReportConfig;
#endif  // FORCE_REPORT

#if defined(LIGHTSENSOR_ENABLED)
  staIllumMeasuredValueOld = 0;
  staIllumReportConfig.dataType = ZCL_DATATYPE_UINT16;
  staIllumReportConfig.pAttr = &staIllumMeasuredValue;
  staIllumReportConfig.pAttrOld = &staIllumMeasuredValueOld;
  staIllumReportConfig.pReportableChange = &staIllumReportableChange;
  staIllumReportConfig.configTimer = SensorTagApp_setLightSensorTimer;
#if defined(FORCE_REPORT)
  staIllumReportConfig.minReportInt = DEFAULT_ILLUM_REPORTING_INTERVAL;
  staIllumReportConfig.maxReportInt = DEFAULT_ILLUM_REPORTING_INTERVAL;
#else // FORCE_REPORT
  staIllumReportConfig.minReportInt = MIN_HA_MIN_REPORTING_INT;
  staIllumReportConfig.maxReportInt = 0;

  staReportConfigList[1] = &staIllumReportConfig;
#endif  // FORCE_REPORT
#endif  // LIGHTSENSOR_ENABLED

#if !defined(FORCE_REPORT)
  // Initialize NVM for storing report configuration information
  if(pfnStaNV)
  {
    NVINTF_itemID_t nvId;
    uint32_t nvErr = NVINTF_NOTFOUND;
    uint8_t i;
    uint8_t len;
    reportConfigEntry_t* pCfgEntry;
 
    // Fill in the NV ID header
    nvId.systemID = NVINTF_SYSID_APP;
    nvId.itemID = (uint16_t) SENSORTAGAPP_NV_REPORT_CFG_TBL;

    for (i = 0; i < MAX_REPORT_ATTR; i++)
    {
      nvId.subID = (uint16_t) i;
      len = sizeof(reportConfigEntry_t) +
            zclGetDataTypeLength(staReportConfigList[i]->dataType);

      pCfgEntry = ICall_malloc(len);
      
      if (pCfgEntry)
      {
        // Read the PIN from NV
        if(pfnStaNV->readItem)
        {
          nvErr = pfnStaNV->readItem(nvId, 0, len, pCfgEntry);
        }

        // If the PIN doesn't exist in NV, create it
        if((nvErr == NVINTF_NOTFOUND) && pfnStaNV->createItem)
        {
          pfnStaNV->createItem(nvId, len, pCfgEntry);
        }
        else if(nvErr == SUCCESS)
        {
          staReportConfigList[i]->minReportInt = pCfgEntry->minReportInt;
          staReportConfigList[i]->maxReportInt = pCfgEntry->maxReportInt;
          memcpy(staReportConfigList[i]->pReportableChange,
                 &(pCfgEntry->reportableChange[0]),
                 zclGetDataTypeLength(staReportConfigList[i]->dataType));
        }

        ICall_free(pCfgEntry);
      }
    }
  }
#endif
}

#if !defined(FORCE_REPORT)
/******************************************************************************
 * @fn        SensorTagApp_getReportConfigIdx
 *
 * @brief     Call function to get the index of the matching reporting
 *            configuration entry
 *
 * @param     pAttr
 *
 * @return    reporting configuration entry
 */
static uint8_t SensorTagApp_getReportConfigIdx(zclAttribute_t* pAttr)
{
  uint8_t i;

  for (i = 0; i < MAX_REPORT_ATTR; i++)
  {
    if(pAttr->dataPtr == staReportConfigList[i]->pAttr)
    {
      break;
    }
  }

  return i;
}
#endif  // FORCE_REPORT
#endif  // ZCL_REPORT

/******************************************************************************
 * @fn          SensorTagApp_applyFactoryImage
 *
 * @brief       Load the factory image for the SensorTag from external flash
 *              and reboot.
 *
 * @param       none
 *
 * @return      none
 */
static void SensorTagApp_applyFactoryImage(void)
{
  Power_setConstraint(Power_SB_DISALLOW);

  if(SensorTagApp_hasFactoryImage())
  {
    // Launch factory image; page 31 must be ommitted
    ((void (*)(uint32_t, uint32_t, uint32_t))SENSORTAGAPP_BL_OFFSET)
                          (EFL_ADDR_RECOVERY,EFL_SIZE_RECOVERY-0x1000, 0);
  }

  Power_releaseConstraint(Power_SB_DISALLOW);
}

/******************************************************************************
 * @fn          SensorTagApp_hasFactoryImage
 *
 * @brief       Is the factory image available?
 *
 * @param       none
 *
 * @return      none
 */
static bool SensorTagApp_hasFactoryImage(void)
{
#if defined(EXTERNAL_IMAGE_CHECK)
  bool  valid;
  valid = extFlashOpen();

  if(valid)
  {
    uint16_t  buffer[2];

    // 1. Check reset vector
    valid = extFlashRead(EFL_ADDR_RECOVERY, sizeof(buffer),
                         (uint8_t *) buffer);
    if(valid)
    {
      valid = (buffer[0] != 0xFFFF && buffer[1] != 0xFFFF) &&
              (buffer[0] != 0x0000 && buffer[1] != 0x0000);
    }

    extFlashClose();
  }

  return valid;
#else
  return (true);
#endif
}

/******************************************************************************
 ******************************************************************************/
