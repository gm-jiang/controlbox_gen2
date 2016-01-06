/**************************************************************************************************
  Filename:       hal_bar.c
  Revised:        $Date: 2013-12-12 12:57:52 +0100 (to, 12 des 2013) $
  Revision:       $Revision: 11562 $

  Description:    Driver for the Bosch BMP280 Pressure Sensor


  Copyright 2012  Texas Instruments Incorporated. All rights reserved.

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
*************************************************************************************************/

/* -----------------------------------------------------------------------------------------------
*                                          Includes
* ------------------------------------------------------------------------------------------------
*/
#include "sensor_bmp280.h"
#include "sensor.h"
#include "bsp_i2c.h"
#include "stddef.h"

/* ------------------------------------------------------------------------------------------------
*                                           Constants and macros
* ------------------------------------------------------------------------------------------------
*/

// Sensor I2C address
#define SENSOR_I2C_ADDRESS                  0x77

// Registers
#define ADDR_CALIB                          0x88
#define ADDR_PROD_ID                        0xD0
#define ADDR_RESET                          0xE0
#define ADDR_STATUS                         0xF3
#define ADDR_CTRL_MEAS                      0xF4
#define ADDR_CONFIG                         0xF5
#define ADDR_PRESS_MSB                      0xF7
#define ADDR_PRESS_LSB                      0xF8
#define ADDR_PRESS_XLSB                     0xF9
#define ADDR_TEMP_MSB                       0xFA
#define ADDR_TEMP_LSB                       0xFB
#define ADDR_TEMP_XLSB                      0xFC

// Reset values
#define VAL_PROD_ID                         0x58
#define VAL_RESET                           0x00
#define VAL_STATUS                          0x00
#define VAL_CTRL_MEAS                       0x00
#define VAL_CONFIG                          0x00
#define VAL_PRESS_MSB                       0x80
#define VAL_PRESS_LSB                       0x00
#define VAL_TEMP_MSB                        0x80
#define VAL_TEMP_LSB                        0x00

// Test values
#define VAL_RESET_EXECUTE                   0xB6
#define VAL_CTRL_MEAS_TEST                  0x55

// Misc.
#define MEAS_DATA_SIZE                      6
#define CALIB_DATA_SIZE                     24

#define RES_OFF                             0
#define RES_ULTRA_LOW_POWER                 1
#define RES_LOW_POWER                       2
#define RES_STANDARD                        3
#define RES_HIGH                            5
#define RES_ULTRA_HIGH                      6

// Bit fields in CTRL_MEAS register
#define PM_OFF                              0
#define PM_FORCED                           1
#define PM_NORMAL                           3

#define OSRST(v)                            ((v) << 5)
#define OSRSP(v)                            ((v) << 2)

// Sensor selection/deselection
#define SENSOR_SELECT()                     bspI2cAcquire(BSP_I2C_INTERFACE_0,SENSOR_I2C_ADDRESS)
#define SENSOR_DESELECT()                   bspI2cRelease()

/* ------------------------------------------------------------------------------------------------
*                                           Type Definitions
* ------------------------------------------------------------------------------------------------
*/
typedef struct {
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;
	int32_t t_fine;
} Bmp280Calibration_t;

/* ------------------------------------------------------------------------------------------------
*                                           Local Functions
* ------------------------------------------------------------------------------------------------
*/

/* ------------------------------------------------------------------------------------------------
*                                           Local Variables
* ------------------------------------------------------------------------------------------------
*/
static uint8_t calData[CALIB_DATA_SIZE];

/**************************************************************************************************
 * @fn          sensorBmp280Init
 *
 * @brief       Initalise the sensor
 *
 * @return      none
 */
void sensorBmp280Init(void)
{
  uint8_t val;
  
  SENSOR_SELECT();

  // Read and store calibration data
  sensorReadReg( ADDR_CALIB, calData, CALIB_DATA_SIZE);

  // Reset the sensor
  val = VAL_RESET_EXECUTE;
  sensorWriteReg(ADDR_RESET, &val, sizeof(val));
  
  SENSOR_DESELECT();
}


/**************************************************************************************************
 * @fn          sensorBmp280Enable
 *
 * @brief       Enable/disable measurements
 *
 * @param       enable - flag to turn the snesor on/off
 *
 * @return      none
 */
void sensorBmp280Enable(bool enable)
{
  uint8_t val;
  
  SENSOR_SELECT();
  if (enable)
  {
    // Enable forced mode
    val = PM_NORMAL | OSRSP(1) | OSRST(1);
  }
  else
  {
    val = PM_OFF;
  }
  sensorWriteReg(ADDR_CTRL_MEAS, &val, sizeof(val));
  SENSOR_DESELECT();
}


/**************************************************************************************************
 * @fn          sensorBmp280Read
 *
 * @brief       Read temperature and pressure data
 *
 * @param       data - buffer for temperature and pressure (6 bytes)
 *
 * @return      TRUE if valid data
 */
bool sensorBmp280Read(uint8_t *data)
{
  bool success;
 
  SENSOR_SELECT();
  success = sensorReadReg( ADDR_PRESS_MSB, data, MEAS_DATA_SIZE);
  if (!success)
  {
    sensorSetErrorData(data,MEAS_DATA_SIZE);
  }
  SENSOR_DESELECT();
  
  return success;
}


/**************************************************************************************************
 * @fn          sensorBmp280Convert
 *
 * @brief       Convert raw data to object and ambience tempertaure
 *
 * @param       data - raw data from sensor
 *
 * @param       temp - converted temperature
 *
 * @param       press - converted pressure
 *
 * @return      none
 **************************************************************************************************/
void sensorBmp280Convert(uint8_t *data, int32_t *temp, uint32_t *press)
{
  int32_t utemp, upress;
  Bmp280Calibration_t *p = (Bmp280Calibration_t *)calData;
	int32_t v_x1_u32r;
	int32_t v_x2_u32r;
	int32_t temperature;
	uint32_t pressure;
  
  // Pressure
  upress = (int32_t)((((uint32_t)(data[0])) << 12) | (((uint32_t)(data[1])) << 4) | ((uint32_t)data[2] >> 4));
  
  // Temperature
  utemp = (int32_t)((( (uint32_t) (data[3])) << 12) |	(((uint32_t)(data[4])) << 4) | ((uint32_t)data[5] >> 4));
  
  // Compensate temperature
	v_x1_u32r  = ((((utemp >> 3) - ((int32_t)p->dig_T1 << 1))) * ((int32_t)p->dig_T2)) >> 11;
	v_x2_u32r  = (((((utemp >> 4) - ((int32_t)p->dig_T1)) * ((utemp >> 4) - ((int32_t)p->dig_T1))) >> 12) * ((int32_t)p->dig_T3)) >> 14;
	p->t_fine = v_x1_u32r + v_x2_u32r;
	temperature  = (p->t_fine * 5 + 128) >> 8;  
  *temp = temperature;

  // Compensate pressure
	v_x1_u32r = (((int32_t)p->t_fine) >> 1) - (int32_t)64000;
	v_x2_u32r = (((v_x1_u32r >> 2) * (v_x1_u32r >> 2)) >> 11) * ((int32_t)p->dig_P6);
	v_x2_u32r = v_x2_u32r + ((v_x1_u32r * ((int32_t)p->dig_P5)) << 1);
	v_x2_u32r = (v_x2_u32r >> 2) + (((int32_t)p->dig_P4) << 16);
	v_x1_u32r = (((p->dig_P3 * (((v_x1_u32r >> 2) * (v_x1_u32r >> 2)) >> 13)) >> 3) + 
      ((((int32_t)p->dig_P2) * v_x1_u32r) >> 1)) >> 18;
	v_x1_u32r = ((((32768+v_x1_u32r)) * ((int32_t)p->dig_P1))	>> 15);
  
	if (v_x1_u32r == 0)
		return; /* Avoid exception caused by division by zero */
  
	pressure = (((uint32_t)(((int32_t)1048576) - upress) - (v_x2_u32r >> 12))) * 3125;
	if (pressure < 0x80000000)
		pressure = (pressure << 1) / ((uint32_t)v_x1_u32r);
	else
		pressure = (pressure / (uint32_t)v_x1_u32r) * 2;
	v_x1_u32r = (((int32_t)p->dig_P9) * ((int32_t)(((pressure >> 3) * (pressure >> 3)) >> 13))) >> 12;
	v_x2_u32r = (((int32_t)(pressure >> 2)) * ((int32_t)p->dig_P8)) >> 13;
	pressure = (uint32_t)((int32_t)pressure + ((v_x1_u32r + v_x2_u32r + p->dig_P7) >> 4));
  
  *press = pressure;
}

/**************************************************************************************************
 * @fn          sensorBmp280Test
 *
 * @brief       Run a sensor self-test
 *
 * @return      TRUE if passed, FALSE if failed
 */
bool sensorBmp280Test(void)
{
  uint8_t val;

  // Select this sensor on the I2C bus
  SENSOR_SELECT();

  // Check reset values
  ST_ASSERT(sensorReadReg(ADDR_PROD_ID, &val, sizeof(val)));
  ST_ASSERT(val == VAL_PROD_ID);

  ST_ASSERT(sensorReadReg(ADDR_CONFIG, &val, sizeof(val)));
  ST_ASSERT(val == VAL_CONFIG);

  // Check that registers can be written
  val = VAL_CTRL_MEAS_TEST;
  ST_ASSERT(sensorWriteReg(ADDR_CTRL_MEAS, &val, sizeof(val)));
  ST_ASSERT(sensorReadReg(ADDR_CTRL_MEAS, &val, sizeof(val)));
  ST_ASSERT(val == VAL_CTRL_MEAS_TEST);

  // Reset the sensor
  val = VAL_RESET_EXECUTE;
  ST_ASSERT(sensorWriteReg(ADDR_RESET, &val, sizeof(val)));
  
  // Check that CTRL_MEAS register has reset value
  ST_ASSERT(sensorReadReg(ADDR_CTRL_MEAS, &val, sizeof(val)));
  ST_ASSERT(val == VAL_CTRL_MEAS);
  
  SENSOR_DESELECT();
  
  return true;
}

