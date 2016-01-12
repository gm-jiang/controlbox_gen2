
#ifndef SMARTLOCK2_PRINT_H
#define SMARTLOCK2_PRINT_H

void smartlock2_uart_init(void);
void log_print(char *str);
void log_printf(const char *fmt, ...);

#endif

