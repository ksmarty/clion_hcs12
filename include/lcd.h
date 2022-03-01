#ifndef LCD_H
#define LCD_H

#include "hcs12.h"

/*
*********************************************************************************************************
*                                               uC/LCD
*                                         LCD Module Driver
*
*                              (c) Copyright 2005; Micrium; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        LCD MODULE SOURCE FILE
*
* Filename      : lcd.h
* Programmer(s) : JJL
* Version       : V3.00
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

#define  DISP_MODULE_PRESENT        1
#define  DISP_BUS_WIDTH             4

#define  DISP_SEL_CMD_REG           0
#define  DISP_SEL_DATA_REG          1


#define  LCD_LOWEST_DATA_BIT                 (INT8U)(2)   		        /* Bit two is the lowest order data bit                     */
#define  LCD_BIT_RS                          (INT8U)(1 <<  0)		    /* LCD Screen bit RS maps to PORTK, bit 0                   */
#define  LCD_BIT_E                           (INT8U)(1 <<  1)           /* LCD Screen bit EN maps to PORTK, bit 1                   */
#define  LCD_BIT_DATA0                       (INT8U)(1 <<  2)           /* LCD Screen bit D4 maps to PORTK, bit 2                   */
#define  LCD_BIT_DATA1                       (INT8U)(1 <<  3)           /* LCD Screen bit D5 maps to PORTK, bit 3                   */
#define  LCD_BIT_DATA2                       (INT8U)(1 <<  4)			/* LCD Screen bit D6 maps to PORTK, bit 4                   */
#define  LCD_BIT_DATA3                       (INT8U)(1 <<  5)    	    /* LCD Screen bit D7 maps to PORTK, bit 5                   */

void  DispDataWr (INT8U data);
void  DispInitPort (void);
void  DispDataWrOneNibble (INT8U data);
void  DispSel (INT8U sel);
void  DispLock(void);
void  DispUnlock(void);
void  DispDly_uS (INT32U us);
void  DispChar (CPU_INT08U row, CPU_INT08U col, CPU_INT08U c);
void  DispClrLine (CPU_INT08U line);
void  DispClrScr (void);
void  DispCursorSet (CPU_INT08U row, CPU_INT08U col);
void  DispDefChar (CPU_INT08U id, CPU_INT08U *pat);
void  DispDummy (void);
void  DispHorBar (CPU_INT08U row, CPU_INT08U col, CPU_INT08U val);
void  DispHorBarInit (void);
void  DispVertBar (CPU_INT08U row, CPU_INT08U col, CPU_INT08U val);
void  DispVertBarInit (void);
void  DispInit (CPU_INT08U maxrows, CPU_INT08U maxcols);
void  DispStr (CPU_INT08U row, CPU_INT08U col, CPU_INT08U *s);


#if DISP_BUS_WIDTH == 4
void  DispDataWrOneNibble(CPU_INT08U data);
#endif


#endif

