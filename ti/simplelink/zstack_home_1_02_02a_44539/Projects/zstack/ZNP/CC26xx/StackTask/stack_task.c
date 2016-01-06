//******************************************************************************
//! \file           stack_task.c
//! \brief          Stack Task implementation
//
//   Revised        $Date: 2015-01-30 11:15:01 -0800 (Fri, 30 Jan 2015) $
//   Revision:      $Revision: 42161 $
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
#include <ICall.h>
#include "OSAL.h"

#include "MT_UART.h"
#include "MT_RPC.h"
#include "MT.h"

#include "inc/npi_client.h"
#include "zstackconfig.h"
#include "inc/npi_data.h"
#include "zstack.h"

// ****************************************************************************
// defines
// ****************************************************************************

// ****************************************************************************
// typedefs
// ****************************************************************************

// *****************************************************************************
// globals
// *****************************************************************************

//! \brief Copy of Stack Task OSAL Task ID.
//!
static uint8 stackTaskId;

//! \brief MT Task OSAL Task ID.
//!
extern uint8 MT_TaskID;

//! \brief ZStack Task Configuration Data Struct.
//!
extern zstack_Config_t *pZStackCfg;

//! \brief ICall Entity ID for the Stack Task.
//!
static ICall_EntityID stackEntity;

//! \brief ICall Semaphore for the Stack Task.
//!
static ICall_Semaphore stackSem;

//*****************************************************************************
// function prototypes
//*****************************************************************************

//! \brief Handler for incoming requests from NPI module.
//!
static void StackTask_handleNPIReq( ICall_EntityID srcEntityID, void *pMsg );

// -----------------------------------------------------------------------------
//! \brief      Initialize stack task.  This function is called when OSAL is 
//!             initialized.
//!
//! \param[in]  taskId - taskId  OSAL Task ID.
//!
//! \return     void
// -----------------------------------------------------------------------------
void StackTask_init( uint8 taskId )
{
    /* Enroll the service that this stack represents */
    ICall_enrollService( ICALL_SERVICE_CLASS_ZSTACK, NULL, &stackEntity, &stackSem );
    
    // Enroll the obtained dispatcher entity and task ID to OSAL
    // so that OSAL can route the dispatcher message into
    // the appropriate OSAL task.
    osal_enroll_dispatchid( taskId, stackEntity );
    
    // Enroll the obtained service entity. This is to ensure
    // that non-task (such as ISR) can route the dispatcher message 
    // into the appropriate alien task (application).
    osal_enroll_notasksender( stackEntity );
    
    stackTaskId = taskId;
    
    // Capture information for communication with NPI Task.
    NPIClient_saveLocalTaskInfo (stackEntity);
}

// -----------------------------------------------------------------------------
//! \brief      This function is the main event handling function of the Stack 
//!             Thread executing in task context.  This function is called by 
//!             OSAL when an event or message is pending for the Stack Thread.
//!
//! \param[in]  taskId - OSAL task ID of this task.
//! \param[in]  events - OSAL event mask.
//!
//! \return     void
// -----------------------------------------------------------------------------
uint16 StackTask_processEvent( uint8 taskId, uint16 events )
{
    uint8 *pMsg;
    
    (void)taskId;  // Intentionally unreferenced parameter
    
    if ( events & SYS_EVENT_MSG )
    {
        // Process system messages
        if ( (pMsg = (uint8 *)osal_msg_receive( stackTaskId )) != NULL )
        {
            ICall_EntityID srcEntityID;
                       
            // Assume it's a message from another thread
            osal_msg_hdr_t *pHdr;
            
            // Get the iCall message header
            pHdr = (osal_msg_hdr_t *)pMsg - 1;
            
            // Convert to the ICall entity ID
            srcEntityID = pHdr->srcentity;
            
            //handleICallMsg( srcEntityID, pMsg );
            StackTask_handleNPIReq( srcEntityID, pMsg );
                        
            // Release the memory
            ICall_freeMsg( (uint8 *)pMsg );
            
        }
        
        // Return unproccessed events
        return ( events ^ SYS_EVENT_MSG );
    }
    
    return 0;
}

// -----------------------------------------------------------------------------
//! \brief      Handle the incoming NPI Req. This is a Z-Stack Stack Task and
//!             as a result, the NPI Req is assumed to contain an MT message.
//!
//!             This function copies the MT message into a mtOSALSerialData_t
//!             buffer and passes it along to the MT task.
//!
//! \param[in]  srcEntityID - source thread ID
//! \param[in]  pMsg - pointer to the incoming message
//!
//! \return     void
// -----------------------------------------------------------------------------
static void StackTask_handleNPIReq( ICall_EntityID srcEntityID, void *pMsg )
{
    mtOSALSerialData_t  *pOsalMsg;
    
    uint8 *pReq = (uint8 *)pMsg;
    
    /* Allocate memory for the MT message */
    pOsalMsg = (mtOSALSerialData_t *)osal_msg_allocate( sizeof ( mtOSALSerialData_t ) );


    if (pOsalMsg)
    {
        /* Fill up what we can */
        pOsalMsg->hdr.event = CMD_SERIAL_MSG;

        pOsalMsg->msg = osal_mem_alloc ( MT_RPC_FRAME_HDR_SZ + pReq[MT_RPC_POS_LEN] );

        
        memcpy(pOsalMsg->msg, pReq, (MT_RPC_FRAME_HDR_SZ + pReq[MT_RPC_POS_LEN]) );
               
        osal_msg_send( MT_TaskID, (byte *)pOsalMsg );

    } 
}

