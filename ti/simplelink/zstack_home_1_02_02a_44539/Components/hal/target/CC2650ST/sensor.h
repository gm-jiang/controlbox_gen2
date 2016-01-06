/**************************************************************************************************
  Filename:       sensor.h
  Revised:        $Date: 2013-03-26 15:47:25 +0100 (ti, 26 mar 2013) $
  Revision:       $Revision: 33597 $

  Description:    Interface to sensor driver shared code.


  Copyright 2012-2013 Texas Instruments Incorporated. All rights reserved.

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

#ifndef HAL_SENSOR_H
#define HAL_SENSOR_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "stdbool.h"
#include "stdint.h"
  
/*********************************************************************
 * CONSTANTS and MACROS
 */

/* Sensor bit values for self-test */
#define ST_IRTEMP                             0x01
#define ST_HUMIDITY                           0x02
#define ST_LIGHT                              0x04
#define ST_PRESSURE                           0x08
#define ST_MPU                                0x10
  
#define ST_ALL                                ( ST_IRTEMP | ST_HUMIDITY | ST_LIGHT | ST_PRESSURE | ST_MPU )
  
/* Self test assertion; return FALSE (failed) if condition is not met */
#define ST_ASSERT(cond) st( if (!(cond)) {bspI2cRelease(); return false;} )

/* Data to when an error occurs */
#define ST_ERROR_DATA                         0xCC
  
/* Conversion macros */
#define st(x)      do { x } while (__LINE__ == -1)

#define HI_UINT16(a) (((a) >> 8) & 0xFF)
#define LO_UINT16(a) ((a) & 0xFF)


/*********************************************************************
 * FUNCTIONS
 */
uint16_t sensorTest(void);
bool     sensorReadReg(uint8_t addr, uint8_t *pBuf, uint8_t nBytes);
bool     sensorWriteReg(uint8_t addr, uint8_t *pBuf, uint8_t nBytes);
void     sensorSetErrorData(uint8_t *pBuf, uint8_t nBytes);

uint16_t floatToSfloat(float data);
float    sfloatToFloat(uint16_t rawData);
uint16_t intToSfloat(int data);
/*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* HAL_SENSOR_H */
