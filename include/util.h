#ifndef UTIL_H_
#define UTIL_H_

#include <hcs12.h>
#include <dbug12.h>


#ifdef DEBUG_PRINTB
#define CH2BINARY_F "0b %c%c%c%c %c%c%c%c\r\n"
#define CH2BINARY_I(n)  \
  (n & 0x80 ? '1' : '0'), \
  (n & 0x40 ? '1' : '0'), \
  (n & 0x20 ? '1' : '0'), \
  (n & 0x10 ? '1' : '0'), \
  (n & 0x08 ? '1' : '0'), \
  (n & 0x04 ? '1' : '0'), \
  (n & 0x02 ? '1' : '0'), \
  (n & 0x01 ? '1' : '0')
#define printb(s,n)  DB12FNP->DB12printf(s CH2BINARY_F, CH2BINARY_I((n)));
#endif

void busy_loop_delay(unsigned int times);

void set_clock_24mhz(void);

#endif /*UTIL_H_*/
