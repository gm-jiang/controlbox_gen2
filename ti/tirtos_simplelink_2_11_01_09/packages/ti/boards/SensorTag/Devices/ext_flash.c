/*******************************************************************************
*  Filename:       ext_flash.h
*  Revised:        $Date: $
*  Revision:       $Revision: $
*
*  Description:    External flash storage implementation
*
*  Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************/
#ifndef TI_DRIVERS_SPI_INCLUDED
#include <driverlib/gpio.h>
#include "bsp.h"
#endif
#include "Board.h"
#include "bsp_spi.h"
#include "ext_flash.h"

#define IO_PARKING

/*
 * Implementation for WinBond W25X20CL Flash
 *
 */

/* Instruction codes */

#define BLS_CODE_PROGRAM          0x02 /**< Page Program */
#define BLS_CODE_READ             0x03 /**< Read Data */
#define BLS_CODE_READ_STATUS      0x05 /**< Read Status Register */
#define BLS_CODE_WRITE_ENABLE     0x06 /**< Write Enable */
#define BLS_CODE_SECTOR_ERASE     0x20 /**< Sector Erase */
#define BLS_CODE_MDID             0x90 /**< Manufacturer Device ID */

#define BLS_CODE_DP               0xB9 /**< Power down */
#define BLS_CODE_RDP              0xAB /**< Power standby */

/* Erase instructions */

#define BLS_CODE_ERASE_4K         0x20 /**< Sector Erase */
#define BLS_CODE_ERASE_32K        0x52
#define BLS_CODE_ERASE_64K        0xD8
#define BLS_CODE_ERASE_ALL        0xC7 /**< Mass Erase */

/* Bitmasks of the status register */

#define BLS_STATUS_SRWD_BM        0x80
#define BLS_STATUS_BP_BM          0x0C
#define BLS_STATUS_WEL_BM         0x02
#define BLS_STATUS_WIP_BM         0x01

#define BLS_STATUS_BIT_BUSY       0x01 /**< Busy bit of the status register */

/* Part specific constants */

#define BLS_MANUFACTURER_ID       0xEF
#define BLS_DEVICE_ID             0x11

#define BLS_PROGRAM_PAGE_SIZE     256
#define BLS_ERASE_SECTOR_SIZE     4096

// Private functions
static int extFlashWaitReady(void);
static int extFlashWaitPowerDown(void);

#ifdef IO_PARKING
// Table of pins to be "parked" in when no device is selected. Leaving the pin
// floating causes increased power consumption in WinBind W25XC10.
static PIN_Config BoardSpiInitTable[] = {
    Board_SPI0_MOSI | PIN_PULLDOWN,
    PIN_TERMINATE
};

static PIN_Handle hSpiPin = NULL;
static PIN_State pinState;
#endif

/**
 * Clear external flash CSN line
 */
static void extFlashSelect(void)
{
#ifndef TI_DRIVERS_SPI_INCLUDED
  GPIOPinWrite(BSP_FLASH_CS, 0);
#else
  bspSpiFlashSelect(true);
#endif
}

/**
 * Set external flash CSN line
 */
static void extFlashDeselect(void)
{
#ifndef TI_DRIVERS_SPI_INCLUDED
  GPIOPinWrite(BSP_FLASH_CS, 1);
#else
  bspSpiFlashSelect(false);
#endif
}

/*******************************************************************************
* @fn       extFlashPowerDown
*
* @brief    Put the device in power save mode. No access to data; only
*           the status register is accessible.
*
* @param    none
*
* @return   Returns true if transactions succeed
*******************************************************************************/
static bool bspFlashExtPowerDown(void)
{
  uint8_t cmd;
  bool success;

  cmd = BLS_CODE_DP;
  extFlashSelect();
  success = bspSpiWrite(&cmd,sizeof(cmd)) == 0;
  extFlashDeselect();

  return success;
}

/*******************************************************************************
* @fn       extFlashPowerStandby
*
* @brief    Take device out of power save mode and prepare it for normal operation
*
* @param    none
*
* @return   Returns true if command successfully written
*******************************************************************************/
static bool extFlashPowerStandby(void)
{
  uint8_t cmd;
  bool success;

  cmd = BLS_CODE_RDP;
  extFlashSelect();
  success = bspSpiWrite(&cmd,sizeof(cmd)) == 0;
  extFlashDeselect();

  if (success)
    success = extFlashWaitReady() == 0;

  return success;
}

/**
 * Verify the flash part.
 * @return True when successful.
 */
static bool extFlashVerifyPart(void)
{
  const uint8_t wbuf[] = { BLS_CODE_MDID, 0xFF, 0xFF, 0x00 };
  uint8_t rbuf[2];

  extFlashSelect();

  int ret = bspSpiWrite(wbuf, sizeof(wbuf));
  if (ret)
  {
    extFlashDeselect();
    return false;
  }

  ret = bspSpiRead(rbuf, sizeof(rbuf));
  extFlashDeselect();

  if (ret || rbuf[0] != BLS_MANUFACTURER_ID || rbuf[1] != BLS_DEVICE_ID)
  {
    return false;
  }
  return true;
}

/**
 * Wait till previous erase/program operation completes.
 * @return Zero when successful.
 */
static int extFlashWaitReady(void)
{
  const uint8_t wbuf[1] = { BLS_CODE_READ_STATUS };
  int ret;

  /* Throw away all garbages */
  extFlashSelect();
  bspSpiFlush();
  extFlashDeselect();

  for (;;)
  {
    uint8_t buf;

    extFlashSelect();
    bspSpiWrite(wbuf, sizeof(wbuf));
    ret = bspSpiRead(&buf,sizeof(buf));
    extFlashDeselect();

    if (ret)
    {
      /* Error */
      return -2;
    }
    if (!(buf & BLS_STATUS_BIT_BUSY))
    {
      /* Now ready */
      break;
    }
  }

  return 0;
}

/**
 * Wait until the part has entered power down (JDEC readout fails)
 * @return Zero when successful.
 */
static int extFlashWaitPowerDown(void)
{
  uint8_t i;

  i = 0;
  while (i<10)
  {
    if (!extFlashVerifyPart())
    {
      return 0;
    }
    i++;
  }

  return -1;
}

/**
 * Enable write.
 * @return Zero when successful.
 */
static int extFlashWriteEnable(void)
{
  const uint8_t wbuf[] = { BLS_CODE_WRITE_ENABLE };

  extFlashSelect();
  int ret = bspSpiWrite(wbuf,sizeof(wbuf));
  extFlashDeselect();

  if (ret)
  {
    return -3;
  }
  return 0;
}

#ifdef IO_PARKING
/*******************************************************************************
 * @fn          extFlashIoPark
 *
 * @brief       Park the IO's connected to the flash to avoid floating
 *              lines during standy. This leads to leakage through the flash
*               device. NB! This is a workaround for bug #6424.
 *
 * @return      none
 */
static void extFlashIoPark(void)
{
  // Make the SPI lines available for reconfiuration
  bspSpiClose();

  // Configure SPI lines as IO and set them according to BoardSpiInitTable
  hSpiPin = PIN_open(&pinState, BoardSpiInitTable);
}

/*******************************************************************************
 * @fn          extFlashIoRelease
 *
 * @brief       Reconfigure SPI lines to the flash for normal opertion
 *
 * @return      none
 */
static void extFlashIoRelease(void)
{
  if (hSpiPin != NULL)
  {
    // Remove IO-confiuration of SPI lines
    PIN_close(hSpiPin);

    // Configure SPI-bus as SPI
    bspSpiOpen();

    hSpiPin = NULL;
  }
}
#endif

/* See ext_flash.h file for description */
bool extFlashOpen(void)
{
#ifndef TI_DRIVERS_SPI_INCLUDED
  bspSpiOpen();
  /* GPIO pin configuration */
  IOCPinTypeGpioOutput(BSP_IOID_FLASH_CS);
#endif
#ifdef IO_PARKING
  /* Make sure SPI is available */
  extFlashIoRelease();
#endif
  /* Put the part is standby mode */
  extFlashPowerStandby();

  return extFlashVerifyPart();
}

/* See ext_flash.h file for description */
void extFlashClose(void)
{
  // Put the part in low power mode
  bspFlashExtPowerDown();
#ifdef IO_PARKING
  /* Make sure SPI lines have a defined state */
  extFlashIoPark();
#endif

#ifndef TI_DRIVERS_SPI_INCLUDED
  bspSpiClose();
#endif
}

/* See ext_flash.h file for description */
bool extFlashRead(size_t offset, size_t length, uint8_t *buf)
{
  uint8_t wbuf[4];

  /* Wait till previous erase/program operation completes */
  int ret = extFlashWaitReady();
  if (ret)
  {
    return false;
  }

  /* SPI is driven with very low frequency (1MHz < 33MHz fR spec)
   * in this temporary implementation.
   * and hence it is not necessary to use fast read. */
  wbuf[0] = BLS_CODE_READ;
  wbuf[1] = (offset >> 16) & 0xff;
  wbuf[2] = (offset >> 8) & 0xff;
  wbuf[3] = offset & 0xff;

  extFlashSelect();

  if (bspSpiWrite(wbuf, sizeof(wbuf)))
  {
    /* failure */
    extFlashDeselect();
    return false;
  }

  ret = bspSpiRead(buf, length);

  extFlashDeselect();

  return ret == 0;
}

/* See ext_flash.h file for description */
bool extFlashWrite(size_t offset, size_t length, const uint8_t *buf)
{
  uint8_t wbuf[4];

  while (length > 0)
  {
    /* Wait till previous erase/program operation completes */
    int ret = extFlashWaitReady();
    if (ret)
    {
      return false;
    }

    ret = extFlashWriteEnable();
    if (ret)
    {
      return false;
    }

    size_t ilen; /* interim length per instruction */

    ilen = BLS_PROGRAM_PAGE_SIZE - (offset % BLS_PROGRAM_PAGE_SIZE);
    if (length < ilen)
    {
      ilen = length;
    }

    wbuf[0] = BLS_CODE_PROGRAM;
    wbuf[1] = (offset >> 16) & 0xff;
    wbuf[2] = (offset >> 8) & 0xff;
    wbuf[3] = offset & 0xff;

    offset += ilen;
    length -= ilen;

    /* Upto 100ns CS hold time (which is not clear
     * whether it's application only inbetween reads)
     * is not imposed here since above instructions
     * should be enough to delay
     * as much. */
    extFlashSelect();

    if (bspSpiWrite(wbuf, sizeof(wbuf)))
    {
      /* failure */
      extFlashDeselect();
      return false;
    }

    if (bspSpiWrite(buf,ilen))
    {
      /* failure */
      extFlashDeselect();
      return false;
    }
    buf += ilen;
    extFlashDeselect();
  }

  return true;
}

/* See ext_flash.h file for description */
bool extFlashErase(size_t offset, size_t length)
{
  /* Note that Block erase might be more efficient when the floor map
   * is well planned for OTA but to simplify for the temporary implemetation,
   * sector erase is used blindly. */
  uint8_t wbuf[4];
  size_t i, numsectors;

  wbuf[0] = BLS_CODE_SECTOR_ERASE;

  {
    size_t endoffset = offset + length - 1;
    offset = (offset / BLS_ERASE_SECTOR_SIZE) * BLS_ERASE_SECTOR_SIZE;
    numsectors = (endoffset - offset + BLS_ERASE_SECTOR_SIZE - 1) /
      BLS_ERASE_SECTOR_SIZE;
  }

  for (i = 0; i < numsectors; i++)
  {
    /* Wait till previous erase/program operation completes */
    int ret = extFlashWaitReady();
    if (ret)
    {
      return false;
    }

    ret = extFlashWriteEnable();
    if (ret)
    {
      return false;
    }

    wbuf[1] = (offset >> 16) & 0xff;
    wbuf[2] = (offset >> 8) & 0xff;
    wbuf[3] = offset & 0xff;

    extFlashSelect();

    if (bspSpiWrite(wbuf, sizeof(wbuf)))
    {
      /* failure */
      extFlashDeselect();
      return false;
    }
    extFlashDeselect();

    offset += BLS_ERASE_SECTOR_SIZE;
  }

  return true;
}

/* See ext_flash.h file for description */
bool extFlashTest(void)
{
  bool ret;

  ret = extFlashOpen();
  if (ret)
  {
    /* Put the part in low power mode */
    bspFlashExtPowerDown();

    /* Wait for device to enter lowe power mode */
    ret = extFlashWaitPowerDown() == 0;
#ifdef IO_PARKING
    /* Make sure SPI lines have a defined state */
    extFlashIoPark();
#endif
  }

  return ret;
}
