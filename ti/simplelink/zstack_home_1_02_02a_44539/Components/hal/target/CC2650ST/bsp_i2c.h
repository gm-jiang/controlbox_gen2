/**************************************************************************************************
  Filename:       bsp_i2c.h
  Revised:        $Date: 2012-08-16 01:58:46 +0200 (to, 16 aug 2012) $
  Revision:       $Revision: 31257 $

  Description:    Layer added on top of RTOS driver for backwards 
                  compatibility with CC2541ST

  Copyright 2013  Texas Instruments Incorporated. All rights reserved.

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
  PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
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
**************************************************************************************************/

#ifndef BSP_I2C_H
#define BSP_I2C_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
//#include "comdef.h"
#include "stdbool.h"
#include "stdint.h"
#include "hw_memmap.h"

/*********************************************************************
 * CONSTANTS
 */
#define BSP_I2C_INTERFACE_0     0
#define BSP_I2C_INTERFACE_1     1
   
/*********************************************************************
 * TYPEDEFS
 */
  
/*********************************************************************
 * FUNCTIONS
 */
void bspI2cInit(void);
void bspI2cAcquire(uint8_t interface, uint8_t slaveAddress);
bool bspI2cRead(uint8_t *pBuf, uint8_t len);
bool bspI2cWrite(uint8_t *pBuf, uint8_t len);
bool bspI2cWriteSingle(uint8_t data);
bool bspI2cWriteRead(uint8_t *wdata, uint8_t wlen, uint8_t *rdata, uint8_t rlen);
void bspI2cRelease(void);
void bspI2cDisable(void);

/////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#endif /* BSP_IRTEMP_H */
