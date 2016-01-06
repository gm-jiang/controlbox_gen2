/**************************************************************************************************'
  Filename:       sensor_sht21.c
  Revised:        $Date: 2013-12-12 12:57:52 +0100 (to, 12 des 2013) $
  Revision:       $Revision: 11562 $

  Description:    Driver for the Sensirion SHT21 Humidity sensor


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
#include "sensor_sht21.h"
#include "sensor.h"
#include "bsp_i2c.h"

/* ------------------------------------------------------------------------------------------------
*                                           Constants
* ------------------------------------------------------------------------------------------------
*/
// Sensor I2C address
#define SENSOR_I2C_ADDRESS         0x40

#define S_REG_LEN                  2
#define DATA_LEN                   3

// Internal commands
#define SHT21_CMD_TEMP_T_NH        0xF3 // command trig. temp meas. no hold master
#define SHT21_CMD_HUMI_T_NH        0xF5 // command trig. humidity meas. no hold master
#define SHT21_CMD_WRITE_U_R        0xE6 // command write user register
#define SHT21_CMD_READ_U_R         0xE7 // command read user register
#define SHT21_CMD_SOFT_RST         0xFE // command soft reset

#define HUMIDITY				           0x00
#define TEMPERATURE			           0x01

#define USR_REG_MASK               0x38  // Mask off reserved bits (3,4,5)
#define USR_REG_DEFAULT            0x02  // Disable OTP reload
#define USR_REG_RES_MASK           0x7E  // Only change bits 0 and 7 (meas. res.)
#define USR_REG_11BITRES           0x81  // 11-bit resolution

#define USR_REG_TEST_VAL           0x83

#define DATA_SIZE                  6

// Sensor selection/deselection
#define SENSOR_SELECT()                     bspI2cAcquire(BSP_I2C_INTERFACE_0,SENSOR_I2C_ADDRESS)
#define SENSOR_DESELECT()                   bspI2cRelease()

/* ------------------------------------------------------------------------------------------------
*                                           Type Definitions
* ------------------------------------------------------------------------------------------------
*/

/* ------------------------------------------------------------------------------------------------
*                                           Local Functions
* ------------------------------------------------------------------------------------------------
*/
static bool sensorSht21ReadData(uint8_t *pBuf,uint8_t nBytes);
static bool sensorSht21WriteCmd(uint8_t cmd);

/* ------------------------------------------------------------------------------------------------
*                                           Local Variables
* ------------------------------------------------------------------------------------------------
*/
static uint8_t usr;                         // Keeps user register value
static uint8_t buf[DATA_SIZE];              // Data buffer
static bool  success;

/**************************************************************************************************
* @fn          sensorSht21Init
*
* @brief       Initialise the humidity sensor driver
*
* @return      none
**************************************************************************************************/
void sensorSht21Init(void)
{
  SENSOR_SELECT();

  // Set 11 bit resolution
  sensorReadReg(SHT21_CMD_READ_U_R,&usr,1);
  usr &= USR_REG_RES_MASK;
  usr |= USR_REG_11BITRES;
  sensorWriteReg(SHT21_CMD_WRITE_U_R,&usr,1);
  success = true;
  
  SENSOR_DESELECT();
}

/**************************************************************************************************
* @fn          sensorSht21StartTempMeasure
*
* @brief       Execute measurement step
*
* @return      none
*/
void sensorSht21StartTempMeasure(void)
{
  if (success)
  {
    SENSOR_SELECT();
    success = sensorSht21WriteCmd(SHT21_CMD_TEMP_T_NH);
    SENSOR_DESELECT();
  }
}

/**************************************************************************************************
* @fn          sensorSht21LatchTempMeasure
*
* @brief       Execute measurement step
*
* @return      none
*/
void sensorSht21LatchTempMeasure(void)
{
  if (success)
  {
    SENSOR_SELECT();
    success = sensorSht21ReadData(buf, DATA_LEN);
    SENSOR_DESELECT();
  }
}

/**************************************************************************************************
* @fn          sensorSht21StartHumMeasure
*
* @brief       Execute measurement step
*
* @return      none
*/
void sensorSht21StartHumMeasure(void)
{
  if (success)
  {
    SENSOR_SELECT();
    success = sensorSht21WriteCmd(SHT21_CMD_HUMI_T_NH);
    SENSOR_DESELECT();
  }
}

/**************************************************************************************************
* @fn          sensorSht21LatchHumMeasure
*
* @brief       Latch humidity measurement
*
* @return      none
*/
void sensorSht21LatchHumMeasure(void)
{
  if (success)
  {
    SENSOR_SELECT();
    success = sensorSht21ReadData(buf+DATA_LEN, DATA_LEN);
    SENSOR_DESELECT();
  }
}



/**************************************************************************************************
* @fn          sensorSht21Read
*
* @brief       Get humidity sensor data
*
* @return      none
*/
bool sensorSht21Read(uint16_t *rawTemp, uint16_t *rawHum)
{
  bool valid;
  
  valid = success;
  if (!success)
  {
    sensorSetErrorData(buf,DATA_SIZE);
  }
  
  // Store temperature
  *rawTemp = buf[0]<<8 | buf[1];
  // [2] ignore CRC
  // Store humidity
  *rawHum = buf[3]<<8 | buf[4];
  // [5] ignore CRC
  
  success = true; // Ready for next cycle
  
  return valid;
}

/**************************************************************************************************
 * @fn          sensorSht21Convert
 *
 * @brief       Convert raw data to temperature and humidity
 *
 * @param       data - raw data from sensor (little endian)
 *
 * @param       temp - converted temperature
 *
 * @param       hum - converted humidity
 *
 * @return      none
 **************************************************************************************************/
void sensorSht21Convert(uint16_t rawTemp, uint16_t rawHum,  float *temp, float *hum)
{
  //-- calculate temperature [°C] --
  rawTemp &= ~0x0003; // clear bits [1..0] (status bits)
  *temp = -46.85 + 175.72/65536 *(double)(int16_t)rawTemp;    

  rawHum &= ~0x0003; // clear bits [1..0] (status bits)
  //-- calculate relative humidity [%RH] --
  *hum = -6.0 + 125.0/65536 * (double)rawHum; // RH= -6 + 125 * SRH/2^16
}


/**************************************************************************************************
* @fn          sensorSht21Test
*
* @brief       Humidity sensor self test
*
* @return      none
**************************************************************************************************/
bool sensorSht21Test(void)
{
  uint8_t val;

  SENSOR_SELECT();

  // Verify write and read
  val = USR_REG_TEST_VAL;
  ST_ASSERT(sensorWriteReg(SHT21_CMD_WRITE_U_R,&val,1));
  ST_ASSERT(sensorReadReg(SHT21_CMD_READ_U_R,&val,1));
  ST_ASSERT(val == USR_REG_TEST_VAL);
  
  SENSOR_DESELECT();
  
  return true;
}


/* ------------------------------------------------------------------------------------------------
*                                           Private functions
* -------------------------------------------------------------------------------------------------
*/

/**************************************************************************************************
* @fn          halHumiWriteCmd
*
* @brief       Write a command to the humidity sensor
*
* @param       cmd - command to write
*
* @return      TRUE if the command has been transmitted successfully
**************************************************************************************************/
static bool sensorSht21WriteCmd(uint8_t cmd)
{
  /* Send command */
  return bspI2cWriteSingle(cmd);
}


/**************************************************************************************************
* @fn          sensorSht21ReadData
*
* @brief       This function implements the I2C protocol to read from the SHT21.
*
* @param       pBuf - pointer to buffer to place data
*
* @param       nBytes - number of bytes to read
*
* @return      TRUE if the required number of bytes are received
**************************************************************************************************/
static bool sensorSht21ReadData(uint8_t *pBuf, uint8_t nBytes)
{
  /* Read data */
  return bspI2cRead(pBuf,nBytes);
}


/*********************************************************************
*********************************************************************/

