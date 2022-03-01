#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "hcs12.h"


#define KEYPAD_READ_ROWS 					(PORTA & 0xf0) 		// Only consider higher bits of port A
#define KEYPAD_ALL_COLUMNS_HIGH 			(PORTA |= 0x0f) 	// All lower bits of port A is set to 1
#define KEYPAD_ALL_COLUMNS_LOW_EXCEPT(c) 	(PORTA = 1 << c)	// All lower bits of port A is set to 0 except bit# c

#define  KEYPAD_KEY_NONE	0xff

void   KeypadInitPort(void);
INT8U  KeypadReadPort (void);
void  EnableKeyboardAgain (void);

#endif /*KEYPAD_H_*/
