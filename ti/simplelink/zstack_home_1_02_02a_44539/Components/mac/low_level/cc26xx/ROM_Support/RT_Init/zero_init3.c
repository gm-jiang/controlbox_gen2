/**************************************************
 *
 * Code that performs zero initialization of global data.
 * New style init table.
 *
 * Copyright 2008 IAR Systems. All rights reserved.
 *
 * $Revision: 34575 $
 *
 **************************************************/

#include "data_init3.h"

#pragma language=extended
#pragma build_attribute vfpcc_compatible
#pragma build_attribute arm_thumb_compatible
#pragma build_attribute ropi_compatible
#pragma build_attribute rwpi_compatible

/* Format:
  Size1
  DestAddr1 (abs or SBrel)
  Size2
  DestAddr2 (abs or SBrel)
  ...
  0
*/

__no_init uint32_t __iar_SB @ r9;

init_fun_t __iar_zero_init2;

#pragma type_attribute=__thumb __interwork
uint32_t const *
__iar_zero_init3(uint32_t const * p);

#pragma type_attribute=__thumb __interwork
uint32_t const *
__iar_zero_init3(uint32_t const * p)
{
  uint32_t size;
  while ((size = *p++) != 0)
  {
    uint32_t d = *p++;
    uint32_t * dest;

    if( d & 1 )
    {
      d -= 1;
      d += __iar_SB;
    }

    dest = (uint32_t*)d;

    do
    {
      *dest++ = 0;
      size -= 4;
    } while (size != 0);
  }
  return p;
}
