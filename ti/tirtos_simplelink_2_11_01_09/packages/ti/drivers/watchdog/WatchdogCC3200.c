/*
 * Copyright (c) 2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include <stdlib.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>

#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <ti/drivers/watchdog/WatchdogCC3200.h>

#include <driverlib/rom.h>
#include <driverlib/rom_map.h>

#include <ti/drivers/watchdog/WatchdogCC3200.h>

#include <inc/hw_types.h>
#include <driverlib/wdt.h>

/* Function prototypes */
void            WatchdogCC3200_clear(Watchdog_Handle handle);
void            WatchdogCC3200_close(Watchdog_Handle handle);
int             WatchdogCC3200_control(Watchdog_Handle handle, unsigned int cmd, void *arg);
void            WatchdogCC3200_init(Watchdog_Handle handle);
Watchdog_Handle WatchdogCC3200_open(Watchdog_Handle handle, Watchdog_Params *params);
void            WatchdogCC3200_setReload(Watchdog_Handle handle, uint32_t value);

/* Watchdog function table for CC3200 implementation */
const Watchdog_FxnTable WatchdogCC3200_fxnTable = {
    WatchdogCC3200_clear,
    WatchdogCC3200_close,
    WatchdogCC3200_control,
    WatchdogCC3200_init,
    WatchdogCC3200_open,
    WatchdogCC3200_setReload
};

/* Default Watchdog params */
extern const Watchdog_Params Watchdog_defaultParams;

/*
 *  ======== WatchdogCC3200_clear ========
 */
void WatchdogCC3200_clear(Watchdog_Handle handle)
{
    WatchdogCC3200_HWAttrs const *hwAttrs = handle->hwAttrs;

    MAP_WatchdogIntClear(hwAttrs->baseAddr);
}

/*
 *  ======== WatchdogCC3200_close ========
 */
void WatchdogCC3200_close(Watchdog_Handle handle)
{
    /*Not supported for CC3200 */
    Assert_isTrue(false, NULL);
}

/*
 *  ======== WatchdogCC3200_control ========
 *  @pre    Function assumes that the handle is not NULL
 */
int WatchdogCC3200_control(Watchdog_Handle handle, unsigned int cmd, void *arg)
{
	/* No implementation yet */
	return (WatchdogCC3200_CMD_UNDEFINED);
}

/*
 *  ======== Watchdog_init ========
 */
void WatchdogCC3200_init(Watchdog_Handle handle)
{
    WatchdogCC3200_Object *object = handle->object;

    object->isOpen = false;
}

/*
 *  ======== WatchdogCC3200_open ========
 */
Watchdog_Handle WatchdogCC3200_open(Watchdog_Handle handle, Watchdog_Params *params)
{
    unsigned int                  key;
    Hwi_Params                    hwiParams;
    WatchdogCC3200_HWAttrs const *hwAttrs = handle->hwAttrs;
    WatchdogCC3200_Object        *object  = handle->object;

    /* If params are NULL use defaults. */
    if (params == NULL) {
        params = (Watchdog_Params *) &Watchdog_defaultParams;
    }

    /* Don't allow preemption */
    key = Hwi_disable();

    /* Check if the Watchdog is open already with the HWAttrs */
    if (object->isOpen == true) {
        Hwi_restore(key);
        Log_warning1("Watchdog: Handle %x already in use.", (UArg)handle);
        return (NULL);
    }

    object->isOpen = true;
    Hwi_restore(key);

    /* Construct Hwi object for watchdog */
    Hwi_Params_init(&hwiParams);
    hwiParams.arg = (UArg)handle;

    if (params->callbackFxn != NULL) {
        Hwi_construct(&(object->hwi), hwAttrs->intNum, params->callbackFxn,
                      &hwiParams, NULL);
    }

    MAP_WatchdogUnlock(hwAttrs->baseAddr);
    MAP_WatchdogReloadSet(hwAttrs->baseAddr, hwAttrs->reloadValue);
    MAP_WatchdogIntClear(hwAttrs->baseAddr);

    /* Set debug stall mode */
    if (params->debugStallMode == Watchdog_DEBUG_STALL_ON) {
        MAP_WatchdogStallEnable(hwAttrs->baseAddr);
    }
    else {
        MAP_WatchdogStallDisable(hwAttrs->baseAddr);
    }

    MAP_WatchdogEnable(hwAttrs->baseAddr);

    MAP_WatchdogLock(hwAttrs->baseAddr);

    Log_print1(Diags_USER1, "Watchdog: handle %x opened" ,(UArg)handle);

    /* Return handle of the Watchdog object */
    return (handle);
}

/*
 *  ======== WatchdogCC3200_setReload ========
 */
void WatchdogCC3200_setReload(Watchdog_Handle handle, uint32_t value)
{
    WatchdogCC3200_HWAttrs const *hwAttrs = handle->hwAttrs;

    /* Set value */
    MAP_WatchdogUnlock(hwAttrs->baseAddr);
    MAP_WatchdogReloadSet(hwAttrs->baseAddr, value);
    MAP_WatchdogLock(hwAttrs->baseAddr);

    Log_print2(Diags_USER1, "Watchdog: WDT with handle 0x%x has been set to "
               "reload to 0x%x", (UArg)handle, value);
}
