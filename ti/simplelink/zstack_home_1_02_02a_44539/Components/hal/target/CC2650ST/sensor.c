/**************************************************************************************************
  Filename:       sensor.c
  Revised:        $Date: 2012-09-21 15:30:38 +0200 (fr, 21 sep 2012) $
  Revision:       $Revision: 31581 $

  Description:    This file contains code that is common to all sensor drivers.


  Copyright 2012 Texas Instruments Incorporated. All rights reserved.

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

/* ------------------------------------------------------------------------------------------------
*                                          Includes
* ------------------------------------------------------------------------------------------------
*/
#include "sensor.h"
#include "bsp_i2c.h"
#include "sensor_tmp006.h"
#include "sensor_sht21.h"
#include "sensor_bmp280.h"
#include "sensor_opt3001.h"
#include "sensor_mpu6500.h"

/* ------------------------------------------------------------------------------------------------
*                                           Macros and constants
* ------------------------------------------------------------------------------------------------
*/
#define N_TEST_RUNS                         5

/* ------------------------------------------------------------------------------------------------
*                                           Local Variables
* ------------------------------------------------------------------------------------------------
*/
static uint8_t buffer[24];

/**************************************************************************************************
 * @fn          sensorReadReg
 *
 * @brief       This function implements the I2C protocol to read from a sensor. The sensor must
 *              be selected before this routine is called.
 *
 * @param       addr - which register to read
 * @param       pBuf - pointer to buffer to place data
 * @param       nBytes - numbver of bytes to read
 *
 * @return      TRUE if the required number of bytes are reveived
 **************************************************************************************************/
bool sensorReadReg(uint8_t addr, uint8_t *pBuf, uint8_t nBytes)
{
  return bspI2cWriteRead(&addr,1,pBuf,nBytes);
}

/**************************************************************************************************
* @fn          sensorWriteReg
* @brief       This function implements the I2C protocol to write to a sensor. he sensor must
*              be selected before this routine is called.
*
* @param       addr - which register to write
* @param       pBuf - pointer to buffer containing data to be written
* @param       nBytes - number of bytes to write
*
* @return      TRUE if successful write
*/
bool sensorWriteReg(uint8_t addr, uint8_t *pBuf, uint8_t nBytes)
{
  uint8_t i;
  uint8_t *p = buffer;

  /* Copy address and data to local buffer for burst write */
  *p++ = addr;
  for (i = 0; i < nBytes; i++)
  {
    *p++ = *pBuf++;
  }
  nBytes++;

  /* Send data */
  return bspI2cWrite(buffer,nBytes);
}

/*********************************************************************
 * @fn      sensorTest
 *
 * @brief   Run a self-test on all the sensors
 *
 * @param   none
 *
 * @return  bitmask of error flags
 */
uint16_t sensorTest(void)
{
  uint16_t i;
  uint8_t selfTestResult;

  selfTestResult = ST_ALL;

  for  (i=0; i<N_TEST_RUNS; i++)
  {
    // 1. Temp sensor test
    if (!sensorTmp006Test())
      selfTestResult &= ~ST_IRTEMP;

    // 2. Humidity  sensor test
    if (!sensorSht21Test())
      selfTestResult &= ~ST_HUMIDITY;
    
    // 3. Barometer test
    if (!sensorBmp280Test())
      selfTestResult &= ~ST_PRESSURE;

    // 3. Optic sensor test
    if (!sensorOpt3001Test())
      selfTestResult &= ~ST_LIGHT;

    // 4. MPU test
    if (!sensorMpu6500Test())
      selfTestResult &= ~ST_MPU;
  }

  return selfTestResult;
}

/*********************************************************************
 * @fn      sensorSetErrorData
 *
 * @brief   Fill a result buffer with dummy error data
 *
 * @param   pBuf - pointer to buffer containing data to be written
 * @param   n - number of bytes to fill
 *
 * @return  bitmask of error flags
 */
void sensorSetErrorData(uint8_t *pBuf, uint8_t n)
{
  while (n > 0)
  {
    n--;
    pBuf[n] = ST_ERROR_DATA;
  }
}

#include "math.h"

#define PRECISION 100.0
#define IPRECISION 100

uint16_t floatToSfloat(float data)
{
    double sgn = data > 0 ? +1 : -1;
    double mantissa = fabs(data) * PRECISION;
    int exponent = 0; 
    bool scaled = false;
    
    // Scale if mantissa is too large
    while (!scaled)
    {
      if (mantissa <= (float)0xFFF)
      {
        scaled = true;
      }
      else
      {
        exponent++;
        mantissa /= 2.0;
      }
    }
    
    uint16_t int_mantissa = (int) round(sgn * mantissa);
    uint16_t sfloat = ((exponent & 0xF) << 12) | (int_mantissa & 0xFFF);
    
    return sfloat;
}

float sfloatToFloat(uint16_t rawData)
{
  uint16_t e, m;

  m = rawData & 0x0FFF;
  e = (rawData & 0xF000) >> 12;
  
  return m * exp2(e) * (1.0/PRECISION);
}

uint16_t intToSfloat(int data)
{
    int sgn = data > 0 ? +1 : -1;
    int mantissa = data * IPRECISION;
    int exponent = 0; 
    bool scaled = false;
    
    // Scale if mantissa is too large
    while (!scaled)
    {
      if (mantissa <= 0xFFF)
      {
        scaled = true;
      }
      else
      {
        exponent++;
        mantissa /= 2;
      }
    }
    
    uint16_t int_mantissa = sgn * mantissa;
    uint16_t sfloat = ((exponent & 0xF) << 12) | (int_mantissa & 0xFFF);
    
    return sfloat;
}

/*********************************************************************
*********************************************************************/
