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
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Types.h>

#include <ti/drivers/spi/SPIUSCIADMA.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/family/msp430/ClockFreqs.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/hal/Hwi.h>

/* driverlib header files */
#include <usci_a_spi.h>
#include <dma.h>

/* SPIUSCIADMA functions */
void        SPIUSCIADMA_close(SPI_Handle handle);
int         SPIUSCIADMA_control(SPI_Handle handle, unsigned int cmd, void *arg);
void        SPIUSCIADMA_hwiIntFxn(SPI_Handle handle);
void        SPIUSCIADMA_init(SPI_Handle handle);
SPI_Handle  SPIUSCIADMA_open(SPI_Handle handle, SPI_Params *params);
bool        SPIUSCIADMA_transfer(SPI_Handle handle,
                                 SPI_Transaction *transaction);
void        SPIUSCIADMA_transferCancel(SPI_Handle handle);
static void SPIUSCIADMA_transferCallback(SPI_Handle handle,
                                         SPI_Transaction *transaction);

/* SPI function table for SPIUSCIADMA implementation */
const SPI_FxnTable SPIUSCIADMA_fxnTable = {
    SPIUSCIADMA_close,
    SPIUSCIADMA_control,
    SPIUSCIADMA_init,
    SPIUSCIADMA_open,
    SPIUSCIADMA_transfer,
    SPIUSCIADMA_transferCancel,
    SPIUSCIADMA_hwiIntFxn
};

static const uint8_t frameFormat[] = {
    /* SPI_POLO_PHA0 */
    USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW | \
    USCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,

    /* SPI_POLO_PHA1 */
    USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW | \
    USCI_A_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,

    /* SPI_POL1_PHA0 */
    USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH | \
    USCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,

    /* SPI_POL1_PHA1 */
    USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH | \
    USCI_A_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,

    (0),    /* SPI_TI - Not supported */
    (0)     /* SPI_MW - Not supported */
};

/* Default SPI params */
extern const SPI_Params SPI_defaultParams;

/*
 *  ======== SPIUSCIADMA_close ========
 *  @pre    Function assumes that the handle is not NULL
 */
void SPIUSCIADMA_close(SPI_Handle handle)
{
    unsigned int                key;
    SPIUSCIADMA_Object         *object = handle->object;
    SPIUSCIADMA_HWAttrs const  *hwAttrs = handle->hwAttrs;

    USCI_A_SPI_disable(hwAttrs->baseAddr);

    Semaphore_destruct(&(object->transferComplete));

    Log_print1(Diags_USER1, "SPI:(%p) closed", hwAttrs->baseAddr);

    key = Hwi_disable();
    object->isOpen = false;
    Hwi_restore(key);
}

/*
 *  ======== SPIUSCIADMA_control ========
 *  @pre    Function assumes that the handle is not NULL
 */
int SPIUSCIADMA_control(SPI_Handle handle, unsigned int cmd, void *arg)
{
	/* No implementation yet */
	return (SPIUSCIADMA_CMD_UNDEFINED);
}

/*
 *  ======== SPIUSCIADMA_configDMA ========
 *  This functions configures the transmit and receive DMA channels for a given
 *  SPI_Handle and SPI_Transaction
 *
 *  @pre    Function assumes that the handle and transaction is not NULL
 */
static void SPIUSCIADMA_configDMA(SPI_Handle handle,
                                  SPI_Transaction *transaction)
{
    unsigned int                key;
    SPIUSCIADMA_HWAttrs const  *hwAttrs = handle->hwAttrs;
    uint32_t                    bufferPtr;
    uint16_t                    direction;

    /*
     * Hwi protection is needed because DMA_init could be accessing registers
     * that are shared
     */
    key = Hwi_disable();

    /* Rx Channel */
    DMA_init(hwAttrs->rxDMAChannelIndex,
             DMA_TRANSFER_SINGLE,
             transaction->count,
             hwAttrs->rxDMASourceTrigger,
             DMA_SIZE_SRCBYTE_DSTBYTE,
             DMA_TRIGGER_HIGH);

    /* Tx Channel */
    DMA_init(hwAttrs->txDMAChannelIndex,
             DMA_TRANSFER_SINGLE,
             transaction->count,
             hwAttrs->txDMASourceTrigger,
             DMA_SIZE_SRCBYTE_DSTBYTE,
             DMA_TRIGGER_HIGH);

    Hwi_restore(key);

    /*
     * The following APIs only access the channel specific DMA registers, which
     * we assume that we own exclusively.
     */

    /* Rx Channel */
    if (transaction->rxBuf) {
        bufferPtr = (uint32_t)transaction->rxBuf;
        direction = DMA_DIRECTION_INCREMENT;
    }
    else {
        bufferPtr = (uint32_t)hwAttrs->scratchBufPtr;
        direction = DMA_DIRECTION_UNCHANGED;
    }

    DMA_setSrcAddress(hwAttrs->rxDMAChannelIndex,
                      USCI_A_SPI_getReceiveBufferAddressForDMA(hwAttrs->baseAddr),
                      DMA_DIRECTION_UNCHANGED);
    DMA_setDstAddress(hwAttrs->rxDMAChannelIndex,
                      bufferPtr,
                      direction);
    DMA_enableInterrupt(hwAttrs->rxDMAChannelIndex);

    /* Tx Channel */
    if (transaction->txBuf) {
        bufferPtr = (uint32_t)transaction->txBuf;
        direction = DMA_DIRECTION_INCREMENT;
    }
    else {
        *hwAttrs->scratchBufPtr = hwAttrs->defaultTxBufValue;
        bufferPtr = (uint32_t)hwAttrs->scratchBufPtr;
        direction = DMA_DIRECTION_UNCHANGED;
    }

    DMA_setSrcAddress(hwAttrs->txDMAChannelIndex,
                      bufferPtr,
                      direction);
    DMA_setDstAddress(hwAttrs->txDMAChannelIndex,
                      USCI_A_SPI_getTransmitBufferAddressForDMA(hwAttrs->baseAddr),
                      DMA_DIRECTION_UNCHANGED);
    DMA_enableInterrupt(hwAttrs->txDMAChannelIndex);

    Log_print1(Diags_USER1,"SPI:(%p) DMA transfer enabled", hwAttrs->baseAddr);

    Log_print5(Diags_USER2,"SPI:(%p) DMA transaction: %p, "
                           "rxBuf: %p; txBuf: %p; Count: %d",
                            hwAttrs->baseAddr,
                            (UArg)transaction,
                            (UArg)transaction->rxBuf,
                            (UArg)transaction->txBuf,
                            (UArg)transaction->count);

    /* Enable DMA Channels */
    DMA_enableTransfers(hwAttrs->rxDMAChannelIndex);
    DMA_enableTransfers(hwAttrs->txDMAChannelIndex);
}

/*
 *  ======== SPIUSCIADMA_hwiIntFxn ========
 *  Function to be called by the DMA ISR (Hwi context)
 */
void SPIUSCIADMA_hwiIntFxn(SPI_Handle handle)
{
    SPI_Transaction            *msg;
    SPIUSCIADMA_Object         *object = ((SPI_Handle)handle)->object;
    SPIUSCIADMA_HWAttrs const  *hwAttrs = ((SPI_Handle)handle)->hwAttrs;

    Log_print1(Diags_USER2, "SPI:(%p) interrupt context start",
                             hwAttrs->baseAddr);

    if (DMA_getInterruptStatus(hwAttrs->txDMAChannelIndex) == DMA_INT_ACTIVE) {
        DMA_clearInterrupt(hwAttrs->txDMAChannelIndex);
        DMA_disableInterrupt(hwAttrs->txDMAChannelIndex);
    }

    /* Determine if the TX and RX DMA channels have completed */
    if ((object->transaction) &&
        (DMA_getInterruptStatus(hwAttrs->rxDMAChannelIndex) == DMA_INT_ACTIVE)){

        DMA_clearInterrupt(hwAttrs->rxDMAChannelIndex);
        DMA_disableInterrupt(hwAttrs->rxDMAChannelIndex);

        /*
         * Use a temporary transaction pointer in case the callback function
         * attempts to perform another SPI_transfer call
         */
        msg = object->transaction;

        /* Indicate we are done with this transfer */
        object->transaction = NULL;

        Log_print2(Diags_USER1,"SPI:(%p) DMA transaction: %p complete",
                                hwAttrs->baseAddr, (UArg)msg);

        /* Perform callback */
        object->transferCallbackFxn(handle, msg);
    }

    Log_print1(Diags_USER2, "SPI:(%p) interrupt context end",
                             hwAttrs->baseAddr);
}

/*
 *  ======== SPIUSCIADMA_init ========
 *  @pre    Function assumes that the handle is not NULL
 */
void SPIUSCIADMA_init(SPI_Handle handle)
{
    /* Mark the object as available */
    ((SPIUSCIADMA_Object *)(handle->object))->isOpen = false;
}

/*
 *  ======== SPIUSCIADMA_open ========
 *  @pre    Function assumes that the handle is not NULL
 */
SPI_Handle SPIUSCIADMA_open(SPI_Handle handle, SPI_Params *params)
{
    unsigned int                key;
    uint32_t                    clockFreq;
    Semaphore_Params            semParams;
    SPIUSCIADMA_Object         *object = handle->object;
    SPIUSCIADMA_HWAttrs const  *hwAttrs = handle->hwAttrs;

    /* Determine if the device index was already opened */
    key = Hwi_disable();
    if (object->isOpen == true) {
        Hwi_restore(key);
        return (NULL);
    }

    /* Mark the handle as being used */
    object->isOpen = true;
    Hwi_restore(key);

    /* Store the SPI parameters */
    if (params == NULL) {
        /* No params passed in, so use the defaults */
        params = (SPI_Params *) &SPI_defaultParams;
    }

    USCI_A_SPI_disableInterrupt(hwAttrs->baseAddr,
                                USCI_A_SPI_RECEIVE_INTERRUPT |
                                USCI_A_SPI_TRANSMIT_INTERRUPT);
    USCI_A_SPI_clearInterruptFlag(hwAttrs->baseAddr,
                                  USCI_A_SPI_RECEIVE_INTERRUPT |
                                  USCI_A_SPI_TRANSMIT_INTERRUPT);

    /* Store the current mode */
    object->transferMode = params->transferMode;
    object->transaction = NULL;

    if (object->transferMode == SPI_MODE_BLOCKING) {
        Log_print1(Diags_USER2, "SPI:(%p) in SPI_MODE_BLOCKING mode",
                                 hwAttrs->baseAddr);
        /*
         * Create a semaphore to block task execution for the duration of the
         * SPI transfer
         */
        Semaphore_Params_init(&semParams);
        semParams.mode = Semaphore_Mode_BINARY;
        Semaphore_construct(&(object->transferComplete), 0, &semParams);

        /* Store internal callback function */
        object->transferCallbackFxn = SPIUSCIADMA_transferCallback;
    }
    else {
        Log_print1(Diags_USER2, "SPI:(%p) in SPI_MODE_CALLBACK mode",
                                 hwAttrs->baseAddr);

        /* Check to see if a callback function was defined for async mode */
        Assert_isTrue(params->transferCallbackFxn != NULL, NULL);

        /* Save the callback function pointer */
        object->transferCallbackFxn = params->transferCallbackFxn;
    }

    /* Get the SPI clock input frequency */
    switch (hwAttrs->clockSource) {
        case USCI_A_SPI_CLOCKSOURCE_ACLK:
            clockFreq = ClockFreqs_getFrequency(ClockFreqs_Clock_ACLK);
            Log_print1(Diags_USER1, "ClockFreqs_getFrequency ACLK: %d", clockFreq);
            break;

        case USCI_A_SPI_CLOCKSOURCE_SMCLK:
            clockFreq = ClockFreqs_getFrequency(ClockFreqs_Clock_SMCLK);
            Log_print1(Diags_USER1, "ClockFreqs_getFrequency SMCLK: %d", clockFreq);
            break;

        default:
            Log_error0("SPI: Error determining clock source");
            SPIUSCIADMA_close(handle);
            return (NULL);
    }

    if (params->mode == SPI_MASTER) {
        USCI_A_SPI_masterInit(hwAttrs->baseAddr,
                              hwAttrs->clockSource,
                              clockFreq,
                              params->bitRate,
                              hwAttrs->bitOrder,
                              frameFormat[params->frameFormat] & UCCKPH,
                              frameFormat[params->frameFormat] & UCCKPL);
    }
    else { /* SPI_SLAVE */
        USCI_A_SPI_slaveInit(hwAttrs->baseAddr,
                             hwAttrs->bitOrder,
                             frameFormat[params->frameFormat] & UCCKPH,
                             frameFormat[params->frameFormat] & UCCKPL);
    }

    Log_print3(Diags_USER1, "SPI:(%p) CPU freq: %d; SPI freq to %d",
                             hwAttrs->baseAddr, clockFreq, params->bitRate);

    USCI_A_SPI_enable(hwAttrs->baseAddr);

    Log_print1(Diags_USER1, "SPI:(%p) opened", hwAttrs->baseAddr);

    return (handle);
}

/*
 *  ======== SPIUSCIADMA_transfer ========
 *  @pre    Function assumes that handle and transaction is not NULL
 */
bool SPIUSCIADMA_transfer(SPI_Handle handle, SPI_Transaction *transaction)
{
    unsigned int                key;
    SPIUSCIADMA_Object         *object = handle->object;
    SPIUSCIADMA_HWAttrs const  *hwattrs = handle->hwAttrs;

    /* Check the transaction arguments */
    if ((transaction->count == 0) ||
       !(transaction->rxBuf || transaction->txBuf) ||
      (!(transaction->rxBuf && transaction->txBuf) && !hwattrs->scratchBufPtr)) {
        return (false);
    }

    /* Check if a transfer is in progress */
    key = Hwi_disable();
    if (object->transaction) {
        Hwi_restore(key);

        Log_error1("SPI:(%p) transaction still in progress",
                   hwattrs->baseAddr);

        /* Transfer is in progress */
        return (false);
    }
    else {
        /* Save the pointer to the transaction */
        object->transaction = transaction;
    }
    Hwi_restore(key);

    SPIUSCIADMA_configDMA(handle, transaction);

    if (object->transferMode == SPI_MODE_BLOCKING) {
        Log_print1(Diags_USER1,
                   "SPI:(%p) transfer pending on transferComplete semaphore",
                    hwattrs->baseAddr);

        Semaphore_pend(Semaphore_handle(&(object->transferComplete)),
                       BIOS_WAIT_FOREVER);
    }

    return (true);
}

/*
 *  ======== SPIUSCIADMA_transferCancel ========
 *  A function to cancel a transaction (if one is in progress) when the driver
 *  is in SPI_MODE_CALLBACK.
 *
 *  @pre    Function assumes that the handle is not NULL
 */
void SPIUSCIADMA_transferCancel(SPI_Handle handle)
{
	/* No implementation yet */
    Assert_isTrue(false, NULL);
}

/*
 *  ======== SPIUSCIADMA_transferCallback ========
 *  Callback function for when the SPI is in SPI_MODE_BLOCKING
 *
 *  @pre    Function assumes that the handle is not NULL
 */
static void SPIUSCIADMA_transferCallback(SPI_Handle handle,
                                         SPI_Transaction *transaction)
{
    SPIUSCIADMA_Object    *object = handle->object;

    Log_print1(Diags_USER1, "SPI:(%p) posting transferComplete semaphore",
                  ((SPIUSCIADMA_HWAttrs const *)(handle->hwAttrs))->baseAddr);

    Semaphore_post(Semaphore_handle(&(object->transferComplete)));
}
