#include <hcs12.h>

#include "keypad.h"
#include "util.h"


#define  KEYPAD_COL_0                 0x01                  // Port A, Bit 0
#define  KEYPAD_COL_1                 0x02
#define  KEYPAD_COL_2                 0x04
#define  KEYPAD_COL_3                 0x08

#define  KEYPAD_ROW_0				  0x10                  // Port A, Bit 4
#define  KEYPAD_ROW_1                 0x20
#define  KEYPAD_ROW_2                 0x30
#define  KEYPAD_ROW_3                 0x40

#define  KEYPAD_IN_MASK               0x0f					// All Columns: Port A, Bit 0-3
#define  KEYPAD_OUT_MASK              0xf0					// All Rows: Port A, Bit 4-7

volatile INT8S KEYPAD_IGNORE = NO;							// Disable the keypad

const unsigned char keypad_layout[16] = { 	'1', '2', '3', 'A',
											'4', '5', '6', 'B',
											'7', '8', '9', 'C',
											'*', '0', '#', 'D'  };


void  EnableKeyboardAgain (void){
	KEYPAD_IGNORE = NO;
}

void  KeypadInitPort (void)
{
	DDRA  |=   KEYPAD_OUT_MASK;                             // Configure the ROWS as outputs
	DDRA  &=  ~KEYPAD_IN_MASK;                              // Configure the COLS as inputs
	PUCR  |=   PUCR_PUPAE_MASK;                             // Enable pull-up resistors for PORTA
}

/*
*********************************************************************************************************
*                                 Keypad Read Operation
*
* Description : KeypadReadPort() scans the keypad from left to right and top to bottom looking for
*               pressed keys. The first pressed key detected is returned.
*
* Arguments   : None
*
* Callers     : User Application
*
* Returns     : INT8U value 0 - 15 corresponding to which button is pressed and 0xFF NULL Event
*
* Notes       : 1) Columns are to be treated as inputs Rows are outputs.
*                 Rows are set HIGH to start and brougnt low, if a column on that
*                 row is found to be low, then that button value (0-15) is returned.
*
*                   C0  C1  C2  C3
*                   PA0 PA1 PA2 PA3
*                    |   |   |   |
*                -----------------
*                |   |   |   |   |
*                | 0 | 1 | 2 | 3 |
*                ------------------- PA4, R0
*                |   |   |   |   |
*                | 4 | 5 | 6 | 7 |
*                ------------------- PA5, R1
*                |   |   |   |   |
*                | 8 | 9 | 10| 11|
*                ------------------- PA6, R2
*                |   |   |   |   |
*                | 12| 13| 14| 15|
*                ------------------- PA7, R3
*********************************************************************************************************
*/
INT8U  KeypadReadPort (void)
{
	if (KEYPAD_IGNORE == YES) return KEYPAD_KEY_NONE;
    INT8S  row;
    INT8U  col;
    INT8U  input;
    INT8U  key_pressed = 0;										// Keep track of which key is  currently being scanned.

    key_pressed = 0;

    for (row = 0; row < 4; row++) {                             // Start scanning from row 0.
        PORTA   =   KEYPAD_OUT_MASK;                            // Initialize all rows to non-active (set HIGH).
        PORTA  &= ~(KEYPAD_ROW_0 << row);                       // Clear the pin of the desired row to scan.
        for (col = 0; col < 4; col++) {                         // Scan the columns from left to right.
            input = (PORTA & KEYPAD_IN_MASK);                   // Read PORTA and ignore the value of the output pins
            if ((input & (1 << col)) == 0) {                    // If a col bit is found low, then the key is pressed
                KEYPAD_IGNORE = YES;							// For de-bounce
            	return keypad_layout[key_pressed];              // Return the position of the key being pressed (0-15)
            }
            key_pressed++;                                      // If no key was pressed, increment the next key position
        }
    }
    key_pressed = KEYPAD_KEY_NONE;                              // If scan is complete and no keys are pressed, return 0xFF
    return (key_pressed);                                       // Return 0xFF indicating that no key was pressed
}

