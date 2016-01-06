//******************************************************************************
//! \file           main.c
//! \brief          main entry of the ZNP application
//
//   Revised        $Date: 2015-01-27 17:10:29 -0800 (Tue, 27 Jan 2015) $
//   Revision:      $Revision: 42069 $
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
#include <xdc/std.h>
#include <string.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/hal/Hwi.h>

#include <ioc.h>

#include "ICall.h"
#include "Board.h"
#include "TIMACBoard.h"
#include "CryptoBoard.h"
#include <ti/sysbios/family/arm/cc26xx/Power.h>
#include <ti/drivers/crypto/CryptoCC26XX.h>

/* Header files required for the temporary idle task function */
#include <ti/sysbios/family/arm/cc26xx/Power.h>
#include <ti/sysbios/family/arm/cc26xx/PowerCC2650.h>
#include <aon_rtc.h>
#include <prcm.h>

/* Header files required to enable instruction fetch cache */
#include <vims.h>
#include <hw_memmap.h>

#include "cpu.h"
#include "znpapp_task.h"
#include "inc/npi_task.h"
#include "pwrmon.h"


// ****************************************************************************
// defines
// ****************************************************************************

#define MY_TASK_STACK_SIZE 600

#define RFC_MODE_BLE                 PRCM_RFCMODESEL_CURR_MODE1
#define RFC_MODE_IEEE                PRCM_RFCMODESEL_CURR_MODE2
#define RFC_MODE_ANT                 PRCM_RFCMODESEL_CURR_MODE4
#define RFC_MODE_EVERYTHING_BUT_ANT  PRCM_RFCMODESEL_CURR_MODE5
#define RFC_MODE_EVERYTHING          PRCM_RFCMODESEL_CURR_MODE6

#define SET_RFC_MODE(mode) HWREG(PRCM_BASE + PRCM_O_RFCMODESEL) = (mode)

// Minimum voltage level need to run
#if !defined (MIN_VDD_RUN)
#define MIN_VDD_RUN         MIN_VDD_POLL
#endif

// ****************************************************************************
// typedefs
// ****************************************************************************

// ****************************************************************************
// globals
// ****************************************************************************

static Task_Struct myTask;
static Char myTaskStack[MY_TASK_STACK_SIZE];


//*****************************************************************************
// function prototypes
//*****************************************************************************

// -----------------------------------------------------------------------------
//! \brief      Entry function passed to TIRTOS
//!
//! \param[in]  a0   
//! \param[in]  a1   
//!
//! \return     Void
// -----------------------------------------------------------------------------
Void taskFxn(UArg a0, UArg a1)
{
    
    /* Disallow shutting down JTAG, VIMS, SYSBUS during idle state
    * since TIMAC requires SYSBUS during idle. */
    Power_setConstraint(Power_IDLE_PD_DISALLOW);
    
    /* Initialize the Power Monitor */
    PWRMON_init();
    
    // Make sure the voltage level is high enough to operate
    while ( PWRMON_check( MIN_VDD_RUN ) == false )
    {
      // Add your own code to do something here, flash LED, sleep, something
      // For now, we will loop and wait for power comes up to the
      // MIN_VDD_RUN level.
    }

    /* Initialize ICall module */
    ICall_init();
    
    {
        CryptoCC26XX_Params CryptoCC26XXParams;
        extern CryptoCC26XX_Handle CryptoCC26XXHandle;
        
        CryptoCC26XX_init();
        CryptoCC26XX_Params_init(&CryptoCC26XXParams);
        CryptoCC26XXHandle = CryptoCC26XX_open(Board_CRYPTO, false, &CryptoCC26XXParams);
        if (!CryptoCC26XXHandle)
        {
            Task_exit();
        }
        Crypto_init();
    }
    
    
    /* Kick off ZNP threads */
    ZNPAppTask_task();
    
}

// -----------------------------------------------------------------------------
//! \brief      TIRTOS exception handler
//!
//! \return     void
// -----------------------------------------------------------------------------
void exceptionHandler()
{
    while(1) {}
}

// -----------------------------------------------------------------------------
//! \brief      THE main function
//!
//! \return     void
// -----------------------------------------------------------------------------
Void main()
{
    Task_Params taskParams;
    
    memset(&myTaskStack, 0xDD, sizeof(myTaskStack));
    
    // set RFC mode to support IEEE802.15.4
    // Note: This must be done before the RF Core is released from reset!
    SET_RFC_MODE(RFC_MODE_IEEE);
    
    // enable iCache prefetching
    VIMSConfigure(VIMS_BASE, TRUE, TRUE);
    
    // Enable cache
    VIMSModeSet(VIMS_BASE, VIMS_MODE_ENABLED);
    
    /* Initialization for board related stuff such as LEDs
    * following TI-RTOS convention */
    PIN_init(BoardGpioInitTable);
    
    // Configure task.
    Task_Params_init(&taskParams);
    taskParams.stack = myTaskStack;
    taskParams.stackSize = MY_TASK_STACK_SIZE;
    taskParams.priority = 1;
    Task_construct(&myTask, taskFxn, &taskParams, NULL);
    
    BIOS_start();   /* enable interrupts and start SYS/BIOS */
}


// -----------------------------------------------------------------------------
//! \brief      Error handler to be hooked into TI-RTOS
//!
//! \param[in]  eb   Error_Block
//!
//! \return     Void
// -----------------------------------------------------------------------------
Void smallErrorHook(Error_Block *eb)
{
    while(1) {}
}
