/***************************************************************************************************
  Filename:       log_print.c

***************************************************************************************************/

/***************************************************************************************************
 * INCLUDES
 ***************************************************************************************************/

#ifdef PRINT_DEBUG

#include "hal_uart.h"
#include "hal_types.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define BUF_SIZE 128
void log_print( char *str )
{
    HalUARTWrite( HAL_UART_PORT_1, (uint8 *)str, strlen((const char *)str));
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

#endif

/***************************************************************************************************
***************************************************************************************************/
