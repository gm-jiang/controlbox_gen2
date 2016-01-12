/***************************************************************************************************
  Filename:       log_print.c

***************************************************************************************************/

/***************************************************************************************************
 * INCLUDES
 ***************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ti/drivers/UART.h>
#include "board.h"
#include "smartlock2.h"

#define BUF_SIZE 128

static UART_Handle SbpUartHandle;
static UART_Params SbpUartParams;

void smartlock2_uart_init()
{
    UART_Params_init(&SbpUartParams);
    SbpUartParams.baudRate      = 115200;
    SbpUartParams.writeDataMode = UART_DATA_BINARY;
    SbpUartParams.dataLength    = UART_LEN_8;
    SbpUartParams.stopBits      = UART_STOP_ONE;
    SbpUartHandle = UART_open(CC2650_UART0,&SbpUartParams);
}

void log_print( char *str )
{
    UART_write(SbpUartHandle, (const void *)str, strlen((const char *)str));
}

void log_printf(const char *fmt, ...)
{
    va_list args;
    char log_buf[BUF_SIZE];

    va_start(args, fmt);
    vsprintf(log_buf,fmt,args);
    log_print(log_buf);
    va_end(args);
}

/***************************************************************************************************
***************************************************************************************************/
