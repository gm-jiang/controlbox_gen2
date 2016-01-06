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
#include <stdbool.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Log.h>

#include <ti/drivers/GPIO.h>

#include <ti/sysbios/hal/Hwi.h>

#include <gpio.h>

static const uint8_t interruptType[] = {
    GPIO_HIGH_TO_LOW_TRANSITION,    /* Interrupt on falling edge */

    GPIO_LOW_TO_HIGH_TRANSITION,    /* Interrupt on rising edge */

    GPIO_HIGH_TO_LOW_TRANSITION |   /* Interrupt on both edges */
    GPIO_LOW_TO_HIGH_TRANSITION,

    GPIO_INPUT_PIN_LOW,             /* Interrupt on low level */

    GPIO_INPUT_PIN_HIGH             /* Interrupt on high level */
};

extern const GPIO_Config GPIO_config[];
static int GPIO_count = -1; /* Also used to check status for initialization */

/*
 *  ======== GPIO_clearInt ========
 */
void GPIO_clearInt(unsigned int index)
{
    GPIO_HWAttrs const *attrs;

    Assert_isTrue(GPIO_count >= 0 && (int)index < GPIO_count, NULL);

    attrs = GPIO_config[index].hwAttrs;

    /* Clear GPIO interrupt flag */
    GPIO_clearInterruptFlag(attrs->port, attrs->pin);

    Log_print2(Diags_USER1, "GPIO: port 0x%x, pin 0x%x interrupt flag cleared",
               attrs->port, attrs->pin);
}

/*
 *  ======== GPIO_disableInt ========
 */
void GPIO_disableInt(unsigned int index)
{
    unsigned int key;
    GPIO_HWAttrs const *attrs;

    Assert_isTrue(GPIO_count >= 0 && (int)index < GPIO_count, NULL);

    attrs = GPIO_config[index].hwAttrs;

    /* Make atomic update */
    key = Hwi_disable();

    GPIO_disableInterrupt(attrs->port, attrs->pin);

    Hwi_restore(key);

    Log_print2(Diags_USER1, "GPIO: port 0x%x, pin 0x%x interrupts disabled",
               attrs->port, attrs->pin);
}

/*
 *  ======== GPIO_enableInt ========
 */
void GPIO_enableInt(unsigned int index, GPIO_IntType intType)
{
    unsigned int key;
    GPIO_HWAttrs const *attrs;

    Assert_isTrue(GPIO_count >= 0 && (int)index < GPIO_count, NULL);

    attrs = GPIO_config[index].hwAttrs;

    /* Make atomic update */
    key = Hwi_disable();

    /* Set type of interrupt and then enable it */
	GPIO_interruptEdgeSelect(attrs->port, attrs->pin, interruptType[intType]);
    GPIO_clearInterruptFlag(attrs->port, attrs->pin);
	GPIO_enableInterrupt(attrs->port, attrs->pin);

    Hwi_restore(key);

    Log_print2(Diags_USER1, "GPIO: port 0x%x, pin 0x%x interrupts enabled",
               attrs->port, attrs->pin);
}

/*
 *  ======== GPIO_init ========
 */
void GPIO_init()
{
    /* Allow multiple calls for GPIO_init */
    if (GPIO_count >= 0) {
        return;
    }

    /* Determine the value for GPIO_count */
    for (GPIO_count = 0; GPIO_config[GPIO_count].hwAttrs != NULL; GPIO_count++) {
    }
}

/*
 *  ======== GPIO_read ========
 */
uint32_t GPIO_read(unsigned int index)
{
    unsigned int key;
    uint32_t value;
    GPIO_HWAttrs const *attrs;

    Assert_isTrue(GPIO_count >= 0 && (int)index < GPIO_count, NULL);

    attrs = GPIO_config[index].hwAttrs;

    /* Make atomic update */
    key = Hwi_disable();
	value = GPIO_getInputPinValue(attrs->port, attrs->pin);

    Hwi_restore(key);

    Log_print3(Diags_USER1, "GPIO: port 0x%x, pin 0x%x read 0x%x",
               attrs->port, attrs->pin, value);

    return (value);
}

/*
 *  ======== GPIO_setupCallbacks ========
 *  This function is not thread-safe.
 */
void GPIO_setupCallbacks(GPIO_Callbacks const *callbacks)
{
    Assert_isTrue(false, NULL);
}

/*
 *  ======== GPIO_toggle ========
 */
void GPIO_toggle(unsigned int index)
{
    unsigned int key;
    GPIO_HWAttrs const *attrs;

    Assert_isTrue(GPIO_count >= 0 && (int)index < GPIO_count, NULL);
    Assert_isTrue(GPIO_config[index].hwAttrs->direction == GPIO_OUTPUT, NULL);

    attrs = GPIO_config[index].hwAttrs;

    /* Make atomic update */
    key = Hwi_disable();

    GPIO_toggleOutputOnPin(attrs->port, attrs->pin);

    Hwi_restore(key);

    Log_print2(Diags_USER1, "GPIO: port 0x%x, pin 0x%x toggled",
               attrs->port, attrs->pin);
}

/*
 *  ======== GPIO_write ========
 */
void GPIO_write(unsigned int index, uint32_t value)
{
    unsigned int        key;
    GPIO_HWAttrs const *attrs;

    Assert_isTrue(GPIO_count >= 0 && (int)index < GPIO_count, NULL);
    Assert_isTrue(GPIO_config[index].hwAttrs->direction == GPIO_OUTPUT, NULL);

    attrs = GPIO_config[index].hwAttrs;

    key = Hwi_disable();

    if (value != 0) {
        GPIO_setOutputHighOnPin(attrs->port, attrs->pin);
    }
    else {
        GPIO_setOutputLowOnPin(attrs->port, attrs->pin);
    }

    Hwi_restore(key);

    Log_print3(Diags_USER1, "GPIO: port 0x%x, pin 0x%x wrote 0x%x",
               attrs->port, attrs->pin, value);
}
