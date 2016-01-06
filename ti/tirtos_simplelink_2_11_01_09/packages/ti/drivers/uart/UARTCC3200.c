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
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Types.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <ti/drivers/uart/UARTCC3200.h>

/* driverlib header files */
#include <inc/hw_memmap.h>
#include <inc/hw_ints.h>
#include <inc/hw_types.h>
#include <driverlib/rom.h>
#include <driverlib/rom_map.h>
#include <driverlib/uart.h>

/* UARTCC3200 functions */
void        UARTCC3200_close(UART_Handle handle);
int         UARTCC3200_control(UART_Handle handle, unsigned int cmd, void *arg);
void        UARTCC3200_init(UART_Handle handle);
UART_Handle UARTCC3200_open(UART_Handle handle, UART_Params *params);
int         UARTCC3200_read(UART_Handle handle, void *buffer, size_t size);
void        UARTCC3200_readCancel(UART_Handle handle);
int         UARTCC3200_readPolling(UART_Handle handle, void *buffer, size_t size);
int         UARTCC3200_write(UART_Handle handle, const void *buffer, size_t size);
void        UARTCC3200_writeCancel(UART_Handle handle);
int         UARTCC3200_writePolling(UART_Handle handle, const void *buffer,
                                    size_t size);

/* UART function table for UARTCC3200 implementation */
const UART_FxnTable UARTCC3200_fxnTable = {
    UARTCC3200_close,
    UARTCC3200_control,
    UARTCC3200_init,
    UARTCC3200_open,
    UARTCC3200_read,
    UARTCC3200_readPolling,
    UARTCC3200_readCancel,
    UARTCC3200_write,
    UARTCC3200_writePolling,
    UARTCC3200_writeCancel
};

static const uint32_t dataLength[] = {
    UART_CONFIG_WLEN_5, /* UART_LEN_5 */
    UART_CONFIG_WLEN_6, /* UART_LEN_6 */
    UART_CONFIG_WLEN_7, /* UART_LEN_7 */
    UART_CONFIG_WLEN_8  /* UART_LEN_8 */
};

static const uint32_t stopBits[] = {
    UART_CONFIG_STOP_ONE,   /* UART_STOP_ONE */
    UART_CONFIG_STOP_TWO    /* UART_STOP_TWO */
};

static const uint32_t parityType[] = {
    UART_CONFIG_PAR_NONE,   /* UART_PAR_NONE */
    UART_CONFIG_PAR_EVEN,   /* UART_PAR_EVEN */
    UART_CONFIG_PAR_ODD,    /* UART_PAR_ODD */
    UART_CONFIG_PAR_ZERO,   /* UART_PAR_ZERO */
    UART_CONFIG_PAR_ONE     /* UART_PAR_ONE */
};

/* Default UART params */
extern const UART_Params UART_defaultParams;

/*
 *  ======== writeSemCallback ========
 *  Simple callback to post a semaphore for the blocking mode.
 */
static void writeSemCallback(UART_Handle handle, void *buffer, size_t count)
{
    UARTCC3200_Object *object = handle->object;

    Semaphore_post(Semaphore_handle(&(object->writeSem)));
}

/*
 *  ======== readSemCallback ========
 *  Simple callback to post a semaphore for the blocking mode.
 */
static void readSemCallback(UART_Handle handle, void *buffer, size_t count)
{
    UARTCC3200_Object *object = handle->object;

    Semaphore_post(Semaphore_handle(&(object->readSem)));
}

/*
 *  ======== writeData ========
 *  Write and process data to the UART.
 */
static int32_t writeData(UARTCC3200_Object        *object,
                         UARTCC3200_HWAttrs const *hwAttrs,
                         int32_t size)
{
    /* Send characters until FIFO is full or done. */
    while (size) {
        /* If mode is TEXT process the characters */
        if (object->writeDataMode == UART_DATA_TEXT) {
            if (object->writeCR) {
                if (!MAP_UARTCharPutNonBlocking(hwAttrs->baseAddr, '\r')) {
                    break;
                }
                size--;
                object->writeCR = false;

                Log_print2(Diags_USER2, "UART:(%p) Wrote character 0x%x",
                           hwAttrs->baseAddr, '\r');
            }
            else {
                /* Add a return if next character is a newline. */
               if (*(unsigned char *)object->writeBuf == '\n') {
                   size++;
                   object->writeCR = true;
               }

               /* Send the next character and increment counts. */
               if (!MAP_UARTCharPutNonBlocking(hwAttrs->baseAddr,
                                               *(unsigned char *)object->writeBuf)) {
                   /* Character was not sent */
                   if (object->writeCR) {
                       size--;
                       object->writeCR = false;
                   }
                   break;
               }

               Log_print2(Diags_USER2, "UART:(%p) Wrote character 0x%x",
                          hwAttrs->baseAddr, *(unsigned char *)object->writeBuf);
               size--;
               object->writeBuf = (unsigned char *)object->writeBuf + 1;
               object->writeCount++;
            }
        }
        else {
            /* Send the next character and increment counts. */
            if (!MAP_UARTCharPutNonBlocking(hwAttrs->baseAddr,
                                            *(unsigned char *)object->writeBuf)) {
                /* Character was not sent */
                break;
            }
            Log_print2(Diags_USER2, "UART:(%p) Wrote character 0x%x",
                       hwAttrs->baseAddr, *(unsigned char *)object->writeBuf);
            object->writeBuf = (unsigned char *)object->writeBuf + 1;
            size--;
            object->writeCount++;
        }
    }
    return (size);
}

/*
 *  ======== readData ========
 *  Read and process data from the UART.
 */
static int32_t readData(UARTCC3200_Object        *object,
                        UARTCC3200_HWAttrs const *hwAttrs,
                        int32_t                   size)
{
    int32_t readIn;

    /* Receive chars until empty or done. */
    while (size && (readIn = (int32_t)MAP_UARTCharGetNonBlocking(hwAttrs->baseAddr)) != -1) {
        /* If data mode is set to TEXT replace return with a newline. */
        if (object->readDataMode == UART_DATA_TEXT) {
            if ((uint8_t)readIn == '\r') {
                /* Echo character if enabled. */
                if (object->readEcho) {
                    MAP_UARTCharPut(hwAttrs->baseAddr, '\r');
                }
                readIn = (int32_t)'\n';
            }
        }

        Log_print2(Diags_USER2, "UART:(%p) Read character 0x%x",
                   hwAttrs->baseAddr, (uint8_t)readIn);

        *((unsigned char *)object->readBuf) = (uint8_t)readIn;
        object->readBuf = (unsigned char *)object->readBuf + 1;
        object->readCount++;
        size--;

        /* Echo character if enabled. */
        if (object->readEcho) {
            MAP_UARTCharPut(hwAttrs->baseAddr, (uint8_t)readIn);
        }

        /* If read return mode is newline, finish if a newline was received. */
        if (object->readReturnMode == UART_RETURN_NEWLINE && (uint8_t)readIn == '\n') {
            Log_print1(Diags_USER2, "UART:(%p) Newline character received, "
                       "returning", hwAttrs->baseAddr);
            size = 0;
            break;
        }
    }

    return (size);
}

/*
 *  ======== UARTCC3200_hwiIntFxn ========
 *  Hwi function that processes UART interrupts.
 *
 *  Three UART interrupts are enabled: Transmit FIFO is 7/8 empty,
 *  receive FIFO is 7/8 full and a receive timeout between the time
 *  the last character was received.
 *
 *  writeData and readData are in-lined functions that will read/write data
 *  with processing if enabled.  When the read or write is finished they will
 *  post the semaphore or make the callback and log the transfer.
 *
 *  @param(arg)         The UART_Handle for this Hwi.
 */
static void UARTCC3200_hwiIntFxn(UArg arg)
{
    uint32_t                    status;
    UARTCC3200_Object          *object = ((UART_Handle)arg)->object;
    UARTCC3200_HWAttrs const   *hwAttrs = ((UART_Handle)arg)->hwAttrs;

    /* Clear interrupts */
    status = MAP_UARTIntStatus(hwAttrs->baseAddr, true);
    MAP_UARTIntClear(hwAttrs->baseAddr, status);

    Log_print2(Diags_USER2, "UART:(%p) Interrupt with mask 0x%x",
               hwAttrs->baseAddr, status);

    /* Read data if characters are available. */
    if (object->readSize) {
        object->readSize = readData(object, hwAttrs, object->readSize);
        if (!object->readSize) {
            /* Reset the read buffer so we can pass it back */
            object->readBuf = (unsigned char *)object->readBuf - object->readCount;
            object->readCallback((UART_Handle)arg, object->readBuf,
                                 object->readCount);

            Log_print2(Diags_USER1, "UART:(%p) Read finished, %d bytes read",
                       hwAttrs->baseAddr, object->readCount);
        }
    }

    /* Write if there are characters to be written. */
    if (object->writeSize) {
        object->writeSize = writeData(object, hwAttrs, object->writeSize);
        if (!object->writeSize) {
            /* Reset the write buffer so we can pass it back */
            object->writeBuf = (unsigned char *)object->writeBuf - object->writeCount;
            object->writeCallback((UART_Handle)arg,
                                  (uint8_t*)object->writeBuf,
                                  object->writeCount);

            Log_print2(Diags_USER1, "UART:(%p) Write finished, %d bytes written",
                       hwAttrs->baseAddr, object->writeCount);
        }
    }
}

/*
 *  ======== UARTCC3200_init ========
 */
void UARTCC3200_init(UART_Handle handle)
{
    UARTCC3200_Object *object = handle->object;

    object->opened = false;
}

/*
 *  ======== UARTCC3200_open ========
 */
UART_Handle UARTCC3200_open(UART_Handle handle, UART_Params *params)
{
    unsigned int                 key;
    Types_FreqHz                 freq;
    UARTCC3200_Object           *object = handle->object;
    UARTCC3200_HWAttrs const    *hwAttrs = handle->hwAttrs;
    union {
        Hwi_Params               hwiParams;
        Semaphore_Params         semParams;
    } paramsUnion;

    /* If params are NULL use defaults. */
    if (params == NULL) {
        params = (UART_Params *) &UART_defaultParams;
    }

    /* Check that a callback is set */
    Assert_isTrue((params->readMode != UART_MODE_CALLBACK) ||
                  (params->readCallback != NULL), NULL);
    Assert_isTrue((params->writeMode != UART_MODE_CALLBACK) ||
                  (params->writeCallback != NULL), NULL);

    object->readMode       = params->readMode;
    object->writeMode      = params->writeMode;
    object->readTimeout    = params->readTimeout;
    object->writeTimeout   = params->writeTimeout;
    object->readCallback   = params->readCallback;
    object->writeCallback  = params->writeCallback;
    object->readReturnMode = params->readReturnMode;
    object->readDataMode   = params->readDataMode;
    object->writeDataMode  = params->writeDataMode;
    object->readEcho       = params->readEcho;

    /* Disable preemption while checking if the UART is open. */
    key = Hwi_disable();

    /* Check if the UART is open already with the base addr. */
    if (object->opened == true) {
        Hwi_restore(key);

        Log_warning1("UART:(%p) already in use.", hwAttrs->baseAddr);
        return (NULL);
    }

    object->opened = true;
    Hwi_restore(key);

    /* Set UART variables to defaults. */
    object->writeBuf = NULL;
    object->readBuf = NULL;
    object->writeCount = 0;
    object->readCount = 0;
    object->writeSize = 0;
    object->readSize = 0;
    object->writeCR = false;

    /* Create Hwi object for this UART peripheral. */
    Hwi_Params_init(&(paramsUnion.hwiParams));
    paramsUnion.hwiParams.arg = (UArg)handle;

    Hwi_construct(&(object->hwi), hwAttrs->intNum, UARTCC3200_hwiIntFxn,
                  &(paramsUnion.hwiParams), NULL);

    Semaphore_Params_init(&(paramsUnion.semParams));
    paramsUnion.semParams.mode = Semaphore_Mode_BINARY;

    /* If write mode is blocking create a semaphore and set callback. */
    if (object->writeMode == UART_MODE_BLOCKING) {
        Semaphore_construct(&(object->writeSem), 0, &(paramsUnion.semParams));
        object->writeCallback = &writeSemCallback;
    }

    /* If read mode is blocking create a semaphore and set callback. */
    if (object->readMode == UART_MODE_BLOCKING) {
        Semaphore_construct(&(object->readSem), 0, &(paramsUnion.semParams));
        object->readCallback = &readSemCallback;
    }

    /* Enable UART and its interrupt. */
    MAP_UARTIntClear(hwAttrs->baseAddr, (UART_INT_TX | UART_INT_RX | UART_INT_RT));
    MAP_UARTIntEnable(hwAttrs->baseAddr, (UART_INT_TX | UART_INT_RX | UART_INT_RT));
    MAP_UARTEnable(hwAttrs->baseAddr);

    /* Set the FIFO level to 7/8 empty and 7/8 full. */
    MAP_UARTFIFOLevelSet(hwAttrs->baseAddr, UART_FIFO_TX1_8, UART_FIFO_RX7_8);

    BIOS_getCpuFreq(&freq);
    MAP_UARTConfigSetExpClk(hwAttrs->baseAddr,
                            freq.lo,
                            params->baudRate,
                            dataLength[params->dataLength] |
                            stopBits[params->stopBits] |
                            parityType[params->parityType]);

    Log_print3(Diags_USER1, "UART:(%p) CPU freq: %d; UART baudrate to %d",
               hwAttrs->baseAddr, freq.lo, params->baudRate);

    Log_print1(Diags_USER1, "UART:(%p) opened", hwAttrs->baseAddr);

    /* Return the handle */
    return (handle);
}

/*
 *  ======== UARTCC3200_close ========
 */
void UARTCC3200_close(UART_Handle handle)
{
    UARTCC3200_Object           *object = handle->object;
    UARTCC3200_HWAttrs const    *hwAttrs = handle->hwAttrs;

    /* Disable UART and interrupts. */
    MAP_UARTIntDisable(hwAttrs->baseAddr, UART_INT_TX | UART_INT_RX | UART_INT_RT);
    MAP_UARTDisable(hwAttrs->baseAddr);

    /* Destruct the SYS/BIOS objects. */
    Hwi_destruct(&(object->hwi));
    Semaphore_destruct(&(object->writeSem));
    Semaphore_destruct(&(object->readSem));

    object->opened = false;

    Log_print1(Diags_USER1, "UART:(%p) closed", hwAttrs->baseAddr);
}

/*
 *  ======== UARTCC3200_control ========
 *  @pre    Function assumes that the handle is not NULL
 */
int UARTCC3200_control(UART_Handle handle, unsigned int cmd, void *arg)
{
	/* No implementation yet */
	return (UARTCC3200_CMD_UNDEFINED);
}

/*
 *  ======== UARTCC3200_write ========
 */
int UARTCC3200_write(UART_Handle handle, const void *buffer, size_t size)
{
    unsigned int        key;
    UARTCC3200_Object    *object = handle->object;

    /* Disable preemption while checking if the uart is in use. */
    key = Hwi_disable();
    if (object->writeSize) {
        Hwi_restore(key);
        Log_warning1("UART:(%p) Could not write data, uart in use.",
                     ((UARTCC3200_HWAttrs const *)(handle->hwAttrs))->baseAddr);

        return (UART_ERROR);
    }

    /* Save the data to be written and restore interrupts. */
    object->writeBuf = buffer;
    object->writeCount = 0;

    Hwi_restore(key);

    if (!(object->writeSize = writeData(object,
                                        (UARTCC3200_HWAttrs *) handle->hwAttrs,
                                        size))) {
        /* Write is finished. */
        Log_print2(Diags_USER1, "UART(%p): Write finished, %d bytes written",
                   ((UARTCC3200_HWAttrs const *)(handle->hwAttrs))->baseAddr,
                   object->writeCount);

        if (object->writeMode == UART_MODE_CALLBACK) {
            /* Reset the write buffer so we can pass it back */
            object->writeBuf = (unsigned char *)object->writeBuf - object->writeCount;
            object->writeCallback(handle, (uint8_t*)object->writeBuf,
                                  object->writeCount);

            /* Return 0 for UART_MODE_CALLBACK */
            return (0);
        }
        return (object->writeCount);
    }

    /* If writeMode is blocking, block and get the status. */
    if (object->writeMode == UART_MODE_BLOCKING) {
        /* Pend on semaphore and wait for Hwi to finish. */
        if (!Semaphore_pend(Semaphore_handle(&(object->writeSem)),
                            object->writeTimeout)) {
            /* Semaphore timed out, make the write empty and log the write. */
            object->writeSize = 0;

            Log_print2(Diags_USER1, "UART:(%p) Write timed out, %d bytes written",
                       ((UARTCC3200_HWAttrs const *)(handle->hwAttrs))->baseAddr,
                       object->writeCount);
        }
        return (object->writeCount);
    }

    return (0);
}

/*
 *  ======== UARTCC3200_writePolling ========
 */
int UARTCC3200_writePolling(UART_Handle handle, const void *buf, size_t size)
{
    int32_t                    count = 0;
    UARTCC3200_Object         *object = handle->object;
    UARTCC3200_HWAttrs const  *hwAttrs = handle->hwAttrs;
    unsigned char             *buffer = (unsigned char *)buf;

    /* Write characters. */
    while (size) {
        if (object->writeDataMode == UART_DATA_TEXT && *buffer == '\n') {
            MAP_UARTCharPut(hwAttrs->baseAddr, '\r');
            count++;
        }
        MAP_UARTCharPut(hwAttrs->baseAddr, *buffer);

        Log_print2(Diags_USER2, "UART:(%p) Wrote character 0x%x",
                   ((UARTCC3200_HWAttrs const *)(handle->hwAttrs))->baseAddr,
                   *buffer);
        buffer++;
        count++;
        size--;
    }

    Log_print2(Diags_USER1, "UART:(%p) Write polling finished, %d bytes written",
               ((UARTCC3200_HWAttrs const *)(handle->hwAttrs))->baseAddr,
               count);

    return (count);
}

/*
 *  ======== UARTCC3200_writeCancel ========
 */
void UARTCC3200_writeCancel(UART_Handle handle)
{
    unsigned int        key;
    UARTCC3200_Object  *object = handle->object;

    /* Disable interrupts to avoid writing data while changing state. */
    key = Hwi_disable();

    /* Return if there is no write. */
    if (!object->writeSize) {
        Hwi_restore(key);
        return;
    }

    /* Set size = 0 to prevent writing and restore interrupts. */
    object->writeSize = 0;
    Hwi_restore(key);

    /* Reset the write buffer so we can pass it back */
    object->writeBuf = (unsigned char *)object->writeBuf - object->writeCount;
    object->writeCallback(handle, (uint8_t*)object->writeBuf,
                          object->writeCount);

    Log_print2(Diags_USER1, "UART:(%p) Write canceled, %d bytes written",
               ((UARTCC3200_HWAttrs const *)(handle->hwAttrs))->baseAddr,
               object->writeCount);
}

/*
 *  ======== UARTCC3200_read ========
 */
int UARTCC3200_read(UART_Handle handle, void *buffer, size_t size)
{
    unsigned int        key;
    UARTCC3200_Object  *object = handle->object;

    /* Disable preemption while checking if the uart is in use. */
    key = Hwi_disable();
    if (object->readSize) {
        Hwi_restore(key);
        Log_warning1("UART:(%p) Could not read data, uart in use.",
                     ((UARTCC3200_HWAttrs const *)(handle->hwAttrs))->baseAddr);
        return (UART_ERROR);
    }

    /* Save the data to be read and restore interrupts. */
    object->readBuf = buffer;
    object->readCount = 0;

    Hwi_restore(key);

    if (!(object->readSize = readData(object, (UARTCC3200_HWAttrs *) handle->hwAttrs, size))) {
        /* Read is finished. */
        Log_print2(Diags_USER1, "UART:(%p) Read finished, %d bytes read",
                   ((UARTCC3200_HWAttrs const *)(handle->hwAttrs))->baseAddr,
                   object->readCount);

        if (object->readMode == UART_MODE_CALLBACK) {
            /* Reset the read buffer so we can pass it back */
            object->readBuf = (unsigned char *)object->readBuf - object->readCount;
            object->readCallback(handle, object->readBuf, object->readCount);

            /* Return 0 for UART_MODE_CALLBACK */
            return (0);
        }
        return (object->readCount);
    }

    /* If readMode is blocking, block and get the status. */
    if (object->readMode == UART_MODE_BLOCKING) {
        /* Pend on semaphore and wait for Hwi to finish. */
        if (!Semaphore_pend(Semaphore_handle(&(object->readSem)),
                            object->readTimeout)) {
            /* Semaphore timed out, make the read empty and log the read. */
            object->readSize = 0;

            Log_print2(Diags_USER1, "UART:(%p) Read timed out, %d bytes read",
                       ((UARTCC3200_HWAttrs const *)(handle->hwAttrs))->baseAddr,
                       object->readCount);

        }
        return (object->readCount);
    }

    return (0);
}

/*
 *  ======== UARTCC3200_readPolling ========
 */
int UARTCC3200_readPolling(UART_Handle handle, void *buf, size_t size)
{
    int32_t                    count = 0;
    UARTCC3200_Object         *object = handle->object;
    UARTCC3200_HWAttrs const  *hwAttrs = handle->hwAttrs;
    unsigned char             *buffer = (unsigned char *)buf;

    /* Read characters. */
    while (size) {
        *buffer = MAP_UARTCharGet(hwAttrs->baseAddr);
        Log_print2(Diags_USER2, "UART:(%p) Read character 0x%x",
                   hwAttrs->baseAddr, *buffer);
        count++;
        size--;

        if (object->readDataMode == UART_DATA_TEXT && *buffer == '\r') {
            /* Echo character if enabled. */
            if (object->readEcho) {
                MAP_UARTCharPut(hwAttrs->baseAddr, '\r');
            }
            *buffer = '\n';
        }

        /* Echo character if enabled. */
        if (object->readEcho) {
            MAP_UARTCharPut(hwAttrs->baseAddr, *buffer);
        }

        /* If read return mode is newline, finish if a newline was received. */
        if (object->readReturnMode == UART_RETURN_NEWLINE &&
            *buffer == '\n') {
            return (count);
        }

        buffer++;
    }

    Log_print2(Diags_USER1, "UART:(%p) Read polling finished, %d bytes read",
               hwAttrs->baseAddr, count);

    return (count);
}

/*
 *  ======== UARTCC3200_readCancel ========
 */
void UARTCC3200_readCancel(UART_Handle handle)
{
    unsigned int        key;
    UARTCC3200_Object    *object = handle->object;

    /* Disable interrupts to avoid reading data while changing state. */
    key = Hwi_disable();

    /* Return if there is no read. */
    if (!object->readSize) {
        Hwi_restore(key);
        return;
    }

    /* Set size = 0 to prevent reading and restore interrupts. */
    object->readSize = 0;
    Hwi_restore(key);

    /* Reset the read buffer so we can pass it back */
    object->readBuf = (unsigned char *)object->readBuf - object->readCount;
    object->readCallback(handle, object->readBuf, object->readCount);

    Log_print2(Diags_USER1, "UART:(%p) Read canceled, %d bytes read",
               ((UARTCC3200_HWAttrs const *)(handle->hwAttrs))->baseAddr,
               object->readCount);
}
