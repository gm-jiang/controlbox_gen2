/**
  @file  znp.h
  @brief ZNP API structures

  <!--
  Copyright 2014 Texas Instruments Incorporated. All rights reserved.

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
  PROVIDED ``AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
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
#ifndef ZNP_H
#define ZNP_H

#include <stdbool.h>
#include <stdint.h>
#include <ICall.h>

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
// Constants and definitions
//*****************************************************************************

typedef enum  
{
  ZNP_CmdIDs_MT_REQ = 0x00,
  ZNP_CmdIDs_MT_RSP = 0x01,
  ZNP_CmdIDs_HEARTBEAT = 0x02
} ZNP_CmdIDs;

//*****************************************************************************
// Structures - Building blocks for the ZStack API structures
//*****************************************************************************



//*****************************************************************************
// System Interface Request Structures
//*****************************************************************************

/**
 * Header structure for ZNP iCall Message.
 */
typedef struct _znp_hdr_t
{
  /** event */
  uint_least8_t event;
  /** Will hold the default response status field. */
  uint_least8_t status;
} ZNP_Hdr_t;



/**
 * Structure to send an MT Buffer request to the ZNP thread.
 */
typedef struct _znp_mtbufreq_t
{
  
  ZNP_Hdr_t hdr;
  
  /**
   * MT message buffer size
   */
  uint8_t pBufSize;
  /**
   * MT message buffer 
   */
  uint8_t *pBuf;
} ZNP_mTBufReq_t;


typedef struct _znp_heartbeatreq_t
{
  
  ZNP_Hdr_t hdr;
  
} ZNP_HeartBeatReq_t;

/**
 * Structure to send an MT Buffer response to the APP thread.
 */
typedef struct _znp_mtbufrsp_t
{
  
  ZNP_Hdr_t hdr;
  
  uint8_t cmdType;
  uint8_t cmdId;
  uint8_t dataLen;
  uint8_t *pData;

} ZNP_mTBufRsp_t;


/**
 * Structure to register MT Pipe Task.
 */
typedef struct _znp_regmtpipe_t
{
  
  ZNP_Hdr_t hdr;
  
  ICall_MSGFormat format;
  ICall_EntityID entityID;
                       
} ZNP_registerMTPipe_t;
//*****************************************************************************
//*****************************************************************************

#ifdef __cplusplus
}
#endif

#endif /* ZNP_H */

