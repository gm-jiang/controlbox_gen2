/**************************************************************************************************
  Filename:       hal_irtemp.c
  Revised:        $Date: 2013-12-12 12:57:52 +0100 (to, 12 des 2013) $
  Revision:       $Revision: 11562 $

  Description:    Driver for the TI TMP06 infrared thermophile sensor.


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

/* ------------------------------------------------------------------------------------------------
*                                          Includes
* ------------------------------------------------------------------------------------------------
*/
#include "bsp_i2c.h"
#include "sensor.h"
#include "sensor_tmp006.h"
#include "math.h"
/* ------------------------------------------------------------------------------------------------
*                                           Constants
* ------------------------------------------------------------------------------------------------
*/

/* Slave address */
#define SENSOR_I2C_ADDRESS              0x44

/* TMP006 register addresses */
#define TMP006_REG_ADDR_VOLTAGE         0x00
#define TMP006_REG_ADDR_TEMPERATURE     0x01
#define TMP006_REG_ADDR_CONFIG          0x02
#define TMP006_REG_MANF_ID              0xFE
#define TMP006_REG_PROD_ID              0xFE

/* TMP006 register values */
#define TMP006_VAL_CONFIG_RESET         0x7400  // Sensor reset state
#define TMP006_VAL_CONFIG_ON            0x7000  // Sensor on state
#define TMP006_VAL_CONFIG_OFF           0x0000  // Sensor off state
#define TMP006_VAL_MANF_ID              0x5449  // Manufacturer ID
#define TMP006_VAL_PROD_ID              0x0067  // Product ID

/* Bit values */
#define DATA_RDY_BIT                    0x8000  // Data ready

/* Register length */
#define REGISTER_LENGTH                 2

/* Sensor data size */
#define DATA_SIZE                       4

// Sensor selection/deselection
#define SENSOR_SELECT()                     bspI2cAcquire(BSP_I2C_INTERFACE_0,SENSOR_I2C_ADDRESS)
#define SENSOR_DESELECT()                   bspI2cRelease()

/* ------------------------------------------------------------------------------------------------
*                                           Local Variables
* ------------------------------------------------------------------------------------------------
*/
static uint8_t configSensorReset[2] = {0x80, 0x00};  // Sensor reset
static uint8_t configSensorOff[2] = {0x00, 0x80};    // Sensor standby
static uint8_t configSensorOn[2] =  {0x70, 0x00};    // Conversion time 0.25 sec
static uint8_t buf[DATA_SIZE];

/* ------------------------------------------------------------------------------------------------
*                                           Public functions
* -------------------------------------------------------------------------------------------------
*/


/**************************************************************************************************
 * @fn          sensorTmp006Init
 *
 * @brief       Initialise the temperature sensor driver
 *
 * @return      none
 **************************************************************************************************/
void sensorTmp006Init(void)
{
  sensorTmp006Enable(false);
}


/**************************************************************************************************
 * @fn          sensorTmp006Enable
 *
 * @brief       Turn the sensor on/off
 *
 * @return      none
 **************************************************************************************************/
void sensorTmp006Enable(bool enable)
{
  SENSOR_SELECT();

  if (enable)
    sensorWriteReg(TMP006_REG_ADDR_CONFIG, configSensorOn, REGISTER_LENGTH);
  else
    sensorWriteReg(TMP006_REG_ADDR_CONFIG, configSensorOff, REGISTER_LENGTH);
  
  SENSOR_DESELECT();
}


/**************************************************************************************************
 * @fn          sensorTmp006Read
 *
 * @brief       Read the sensor voltage and sensor temperature registers
 *
 * @param       rawVolt - voltage in 16 bit format
 *
 * @param       rawtEMP - temperature in 16 bit format
 *
 * @return      TRUE if valid data
 **************************************************************************************************/
bool sensorTmp006Read(uint16_t *rawVolt, uint16_t *rawTemp)
{
  bool success;
  uint16_t v;
  
  SENSOR_SELECT();
  
  success = sensorReadReg(TMP006_REG_ADDR_CONFIG, (uint8_t *)&v,REGISTER_LENGTH );
  
  if (success)
    success = v & DATA_RDY_BIT;
  
  if (success)
  {
    // Read the sensor registers
    success = sensorReadReg(TMP006_REG_ADDR_VOLTAGE, &buf[0], REGISTER_LENGTH );
    if (success)
    {
      success = sensorReadReg(TMP006_REG_ADDR_TEMPERATURE, &buf[2], REGISTER_LENGTH );
    }
  }
  
  if (!success)
  {
    sensorSetErrorData(buf,4);
  }
  
  *rawVolt = buf[0]<<8 | buf[1];
  *rawTemp = buf[2]<<8 | buf[3];
  
  SENSOR_DESELECT();
  
  return success;
}


/**************************************************************************************************
 * @fn          sensorTmp006Test
 *
 * @brief       Run a sensor self-test
 *
 * @return      TRUE if passed, FALSE if failed
 **************************************************************************************************/
bool sensorTmp006Test(void)
{
  uint16_t val;

  // Select this sensor on the I2C bus
  SENSOR_SELECT();

  // Check manufacturer ID
  ST_ASSERT(sensorReadReg(TMP006_REG_MANF_ID, (uint8_t *)&val, REGISTER_LENGTH));
  val = (LO_UINT16(val) << 8) | HI_UINT16(val);
  ST_ASSERT(val == TMP006_VAL_MANF_ID);

  // Reset sensor
  ST_ASSERT(sensorWriteReg(TMP006_REG_ADDR_CONFIG, configSensorReset, REGISTER_LENGTH));

  // Check config register (reset)
  ST_ASSERT(sensorReadReg(TMP006_REG_ADDR_CONFIG, (uint8_t *)&val, REGISTER_LENGTH));
  val = ((LO_UINT16(val) << 8) | HI_UINT16(val));
  ST_ASSERT(val == TMP006_VAL_CONFIG_RESET);

  // Turn sensor off
  ST_ASSERT(sensorWriteReg(TMP006_REG_ADDR_CONFIG, configSensorOff,REGISTER_LENGTH));

  // Check config register (off)
  ST_ASSERT(sensorReadReg(TMP006_REG_ADDR_CONFIG, (uint8_t *)&val, REGISTER_LENGTH));
  val = ((LO_UINT16(val) << 8) | HI_UINT16(val));
  // ST_ASSERT(val == TMP006_VAL_CONFIG_OFF);
  
  // Turn sensor on
  ST_ASSERT(sensorWriteReg(TMP006_REG_ADDR_CONFIG, configSensorOn, REGISTER_LENGTH));

  // Check config register (on)
  ST_ASSERT(sensorReadReg(TMP006_REG_ADDR_CONFIG, (uint8_t *)&val, REGISTER_LENGTH));
  val = ((LO_UINT16(val) << 8) | HI_UINT16(val));
  ST_ASSERT(val == TMP006_VAL_CONFIG_ON);

  // Turn sensor off
  ST_ASSERT(sensorWriteReg(TMP006_REG_ADDR_CONFIG, configSensorOff, REGISTER_LENGTH));

  SENSOR_DESELECT();
  
  return true;
}

/**************************************************************************************************
 * @fn          sensorTmp006Convert
 *
 * @brief       Convert raw data to object and ambience tempertaure
 *
 * @param       rawVolt - raw voltage from sensor
 *
 * @param       rawTemp - raw temperature from sensor
 *
 * @param       tObj - converted object temperature
 *
 * @param       tAmb - converted ambience temperature
 *
 * @return      none
 **************************************************************************************************/
void sensorTmp006Convert(uint16_t rawVolt, uint16_t rawTemp, float *tObj, float *tAmb)
{
  //-- calculate die temperature [°C] --
  *tAmb = (double)((int16_t)rawTemp)/128.0;
  
  //-- calculate target temperature [°C] -
  double Vobj2 = (double)(int16_t)rawVolt;
  Vobj2 *= 0.00000015625;
  
  double Tdie2 = *tAmb + 273.15;
  const double S0 = 6.4E-14;            // Calibration factor
  
  const double a1 = 1.75E-3;
  const double a2 = -1.678E-5;
  const double b0 = -2.94E-5;
  const double b1 = -5.7E-7;
  const double b2 = 4.63E-9;
  const double c2 = 13.4;
  const double Tref = 298.15;
  double S = S0*(1+a1*(Tdie2 - Tref)+a2*pow((Tdie2 - Tref),2));
  double Vos = b0 + b1*(Tdie2 - Tref) + b2*pow((Tdie2 - Tref),2);
  double fObj = (Vobj2 - Vos) + c2*pow((Vobj2 - Vos),2);
  double t = pow(pow(Tdie2,4) + (fObj/S),.25);
  *tObj = (t - 273.15);
}

/*********************************************************************
*********************************************************************/

