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
 /** ============================================================================
 *  @file       EMAC.h
 *
 *  @brief      EMAC driver interface
 *
 *  The EMAC header file should be included in an application as follows:
 *  @code
 *  #include <ti/drivers/EMAC.h>
 *  @endcode
 *
 *  # Implementation #
 *
 *  The EMAC driver interface module is joined (at link time) to a
 *  NULL-terminated array of EMAC_Config data structures named *EMAC_config*.
 *  *EMAC_config* is implemented in the application with each entry being an
 *  instance of a EMAC peripheral. Each entry in *EMAC_config* contains a:
 *  - (EMAC_FxnTable *) to a set of functions that implement a EMAC peripheral
 *  - (void *) data object that is associated with the EMAC_FxnTable
 *  - (void *) hardware attributes that are associated to the EMAC_FxnTable
 *
 *  Currently the following EMAC peripheral implementations are supported:
 *  - @ref EMACTiva.h
 *
 *  # Instrumentation #
 *  The EMAC driver interface produces log statements if instrumentation is
 *  enabled.
 *
 *  Diagnostics Mask | Log details |
 *  ---------------- | ----------- |
 *  Diags_USER1      | basic EMAC operations |
 *  Diags_USER2      | detailed EMAC operations |
 *
 *  ============================================================================
 */

#ifndef ti_drivers_EMAC__include
#define ti_drivers_EMAC__include

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/* Prototypes of EMAC interface */
typedef void (*EMAC_InitFxn)(uint32_t);
typedef bool (*EMAC_isLinkUpFxn)(uint32_t);

/*!
 *  @brief      EMAC Function table structure
 */
typedef struct EMAC_FxnTable {
    EMAC_InitFxn           emacInit;
    EMAC_isLinkUpFxn       emacIsLinkUp;
} EMAC_FxnTable;

/*!
 *  @brief      EMAC Global configuration
 */
typedef struct EMAC_Config {
    EMAC_FxnTable const *fxnTablePtr;      /*!< Pointer to EMAC function table */
    void                *objects;          /*!< Pointer to EMAC object */
    void          const *hwAttrs;          /*!< Pointer to hardware attribute */
} EMAC_Config;

/*!
 *  @brief  This function initializes the EMAC driver
 *
 *  This function must be called by the application before the NDK stack
 *  thread is started.
 *
 *  The EMAC_config structure must be present and initialized before this
 *  function is called.
 */
extern void EMAC_init(void);

/*!
 *  @brief  This function returns if the link is up
 *
 *  @return true is the link is up. false if it is down.
 */
extern bool EMAC_isLinkUp(unsigned int index);

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_EMAC__include */
