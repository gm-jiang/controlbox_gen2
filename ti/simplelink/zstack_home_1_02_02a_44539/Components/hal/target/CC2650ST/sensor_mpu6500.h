/**************************************************************************************************
  Filename:       sensor_mpu6500.h
  Revised:        $Date: 2013-12-11 19:32:18 +0100 (on, 11 des 2013) $
  Revision:       $Revision: 11547 $

  Description:    This file contains the declaration to the HAL Invensense MPU6500
                  abstraction layer.

  Copyright 2012 - 2013  Texas Instruments Incorporated. All rights reserved.

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
#ifndef SENSOR_MPU6500_H
#define SENSOR_MPU6500_H

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------------------------------
 *                                          Includes
 * ------------------------------------------------------------------------------------------------
 */
#include "stdint.h"
#include "stdbool.h"

/* ------------------------------------------------------------------------------------------------
 *                                          Constants
 * ------------------------------------------------------------------------------------------------
 */
#define ACC_RANGE_2G       1
#define ACC_RANGE_4G       2
#define ACC_RANGE_8G       3
#define ACC_RANGE_16G      4
  
  /* ------------------------------------------------------------------------------------------------
 *                                           Typedefs
 * ------------------------------------------------------------------------------------------------
 */


/* ------------------------------------------------------------------------------------------------
 *                                          Functions
 * ------------------------------------------------------------------------------------------------
 */
void sensorMpu6500Init(void);
bool sensorMpu6500Test(void);

void sensorMpu6500AccEnable(uint8_t config);
void sensorMpu6500AccSetRange(uint8_t range);
bool sensorMpu6500AccRead(uint16_t *rawData);
float sensorMpu6500AccelConvert(int16_t rawValue);

void sensorMpu6500GyroEnable(uint8_t config);
bool sensorMpu6500GyroRead(uint16_t *rawData);
float sensorMpu6500GyroConvert(int16_t rawValue);
/**************************************************************************************************
*/

#ifdef __cplusplus
};
#endif

#endif

/**************************************************************************************************
*/
