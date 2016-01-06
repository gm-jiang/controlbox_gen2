//******************************************************************************
//! \file           stack_task.h
//! \brief          Stack Task interface function definition
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
#ifndef STACKTASK_H
#define STACKTASK_H

#ifdef __cplusplus
extern "C" {
#endif

// ****************************************************************************
// includes
// ****************************************************************************

// ****************************************************************************
// defines
// ****************************************************************************
    
// ****************************************************************************
// typedefs
// ****************************************************************************

// *****************************************************************************
// globals
// *****************************************************************************

// *****************************************************************************
// function prototypes
// *****************************************************************************

// -----------------------------------------------------------------------------
//! \brief      Initialize stack task.  This function is called when OSAL is 
//!             initialized.
//!
//! \param[in]  uint8 - taskId  OSAL Task ID.
//!
//! \return     void
// -----------------------------------------------------------------------------
void StackTask_init( uint8 taskId );


// -----------------------------------------------------------------------------
//! \brief      This function is the main event handling function of the Stack Thread executing
//!             in task context.  This function is called by OSAL when an event or message
//!             is pending for the Stack Thread.
//!
//! \param[in]  uint8 - OSAL task ID of this task.
//! \param[in]  uint16 - OSAL event mask.
//!
//! \return     void
// -----------------------------------------------------------------------------
extern uint16 StackTask_processEvent( uint8 taskId, uint16 events );

#ifdef __cplusplus
};
#endif

#endif /* STACKTASK_H */


