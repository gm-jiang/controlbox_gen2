//******************************************************************************
//! \file           znpapp_task.c
//! \brief          ZNP is an TI RTOS Application Thread that instantiates a
//! \brief          Stack Task and an NPI Task to provide MT pass-thru
//! \brief          functionality.
//
//   Revised        $Date: 2015-02-04 15:24:24 -0800 (Wed, 04 Feb 2015) $
//   Revision:      $Revision: 42319 $
//
//  Copyright 2015 Texas Instruments Incorporated. All rights reserved.
//
// IMPORTANT: Your use of this Software is limited to those specific rights
// granted under the terms of a software license agreement between the user
// who downloaded the software, his/her employer (which must be your employer)
// and Texas Instruments Incorporated (the "License").  You may not use this
// Software unless you agree to abide by the terms of the License. The License
// limits your use, and you acknowledge, that the Software may not be modified,
// copied or distributed unless used solely and exclusively in conjunction with
// a Texas Instruments radio frequency device, which is integrated into
// your product.  Other than for the foregoing purpose, you may not use,
// reproduce, copy, prepare derivative works of, modify, distribute, perform,
// display or sell this Software and/or its documentation for any purpose.
//
//  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
//  PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,l
//  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
//  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
//  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
//  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
//  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
//  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
//  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
//  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
//  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
//
//  Should you have any questions regarding your right to use this Software,
//  contact Texas Instruments Incorporated at www.TI.com.
//******************************************************************************

// ****************************************************************************
// includes
// ****************************************************************************

#include <string.h>
#include <xdc/std.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Task.h>
#include "ICallAddrs.h"
#include <inc/hw_ccfg_simple_struct.h>

#include "zstackconfig.h"
#include "nvoctp.h"

#include "inc/npi_data.h"
#include "inc/npi_task.h"
#include "hal_defs.h"

// ****************************************************************************
// defines
// ****************************************************************************

// Exented Address Length
#define ZNPAPP_EXTADDR_LEN 8

// Extended Address offset in FCFG (LSB..MSB)
#define ZNPAPP_EXTADDR_OFFSET 0x2F0


// ****************************************************************************
// typedefs
// ****************************************************************************

//! \brief Queue record structure, used for RX and TX on serial side.
//!
typedef struct queueRec_t
{
    Queue_Elem _elem;
    void *ptr;
} queueRec;


//*****************************************************************************
// globals
//*****************************************************************************

//! \brief ZNP thread ICall Semaphore.
//!
static ICall_Semaphore appSem = NULL;

//! \brief ZNP ICall Application Entity ID.
//!
static ICall_EntityID appEntity = 0;

//! \brief Task pending events
//!
static uint16_t APP_events = 0;

//! \brief      Configuration structure used to pass parameters to the stack (ZNP)
//!             thread initilization.
//!
zstack_Config_t user0Cfg =
{
  {0,0,0,0,0,0,0,0},  // Extended Address
  {0,0,0,0,0,0,0,0},  // NV function pointers
  0,                  // ICall ZNP Task thread ID
  0,                  // stack image init fail flag
  MAC_USER_CFG
};

//! \brief Used to check for a valid extended address
static const uint8_t dummyExtAddr[] =
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

//! \brief NPI ICALL Thread Application ID.
//!
extern ICall_EntityID npiAppEntityID;

//! \brief Customer configuration area.
//!
extern const ccfg_t __ccfg;

//*****************************************************************************
// function prototypes
//*****************************************************************************

//! \brief      Process incoming ICall messages.
//!
static uint_least16_t ZNPAppTask_processICallMsgEvent(uint8_t *pMsg);

//! \brief      Main processing loop for ZNP App
//!
static void ZNPAppTask_process(void);

//! \brief      Initialization for the ZNP Application
static void ZNPAppTask_init(void);

// -----------------------------------------------------------------------------
//! \brief      Initialization for the ZNP Application
//!
//! \return     void
// -----------------------------------------------------------------------------
static void ZNPAppTask_init(void)
{
    // Not used so void'd to muffle compiler warning.
    (void)APP_events;

    // Register the current thread with ICall so that the application can
    // send and receive ICALL messages.
    ICall_registerApp(&appEntity, &appSem);

    // Capture the application's Entity ID.
    user0Cfg.applicationEntityID = appEntity;

    // Configure and create the NPI task.
    NPITask_createTask(ICALL_SERVICE_CLASS_ZSTACK);

    /*
     * Copy the extended address from the CCFG area
     * Assumption: the memory in CCFG_IEEE_MAC_0 and CCFG_IEEE_MAC_1
     * is contiguous and LSB first.
     */
    memcpy(user0Cfg.extendedAddress,
           (uint8_t *)&(__ccfg.CCFG_IEEE_MAC_0), ZNPAPP_EXTADDR_LEN);

    // Check to see if the CCFG IEEE is valid
    if(memcmp(user0Cfg.extendedAddress, dummyExtAddr, ZNPAPP_EXTADDR_LEN) == 0)
    {
        // No, it isn't valid.  Get the Primary IEEE Address
        memcpy(user0Cfg.extendedAddress,
               (uint8_t *)(FCFG1_BASE + ZNPAPP_EXTADDR_OFFSET),
               ZNPAPP_EXTADDR_LEN);
    }

    /* Setup the NV driver for the ZStack thread */
    NVOCTP_loadApiPtrs(&user0Cfg.nvFps);

    if (user0Cfg.nvFps.initNV)
    {
        user0Cfg.nvFps.initNV(NULL);
    }

    // Start tasks of external (stack) image
    ICall_createRemoteTasks();
}


// -----------------------------------------------------------------------------
//! \brief      ZNP main event processing loop.
//!
//! \return     void
// -----------------------------------------------------------------------------
static void ZNPAppTask_process(void)
{
    ICall_ServiceEnum stackid;
    ICall_EntityID dest;
    uint8_t *pMsg;

    /* Forever loop */
    for (;;)
    {
        /* Wait for response message */
        if (ICall_wait(ICALL_TIMEOUT_FOREVER) == ICALL_ERRNO_SUCCESS)
        {
            /* Retrieve the response message */
            if (ICall_fetchServiceMsg(&stackid, &dest, (void * *) &pMsg)
                == ICALL_ERRNO_SUCCESS)
            {
                if ((stackid == ICALL_SERVICE_CLASS_ZSTACK) &&
                    (dest == appEntity))
                {
                    ZNPAppTask_processICallMsgEvent(pMsg);
                }

                ICall_freeMsg(pMsg);
            }
        }
    }
}

// -----------------------------------------------------------------------------
//! \brief      ZNP task entry point.
//!
//! \return     void
// -----------------------------------------------------------------------------
void ZNPAppTask_task(void)
{
    // Initialize application
    ZNPAppTask_init();

    // Enter endless processing loop
    ZNPAppTask_process();
}

// -----------------------------------------------------------------------------
//! \brief      Process an ICall message from the Stack
//!
//! \param[in]  pMsg A pointer to a message buffer
//!
//! \return     void
// -----------------------------------------------------------------------------
static uint_least16_t ZNPAppTask_processICallMsgEvent(uint8_t *pMsg)
{
    // we don't expect to get anything
    return(0);
}





