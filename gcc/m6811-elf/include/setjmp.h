/*
	setjmp.h
	stubs for future use.
*/

#ifndef _SETJMP_H_
#define _SETJMP_H_

#include "_ansi.h"
#include <machine/setjmp.h>

_BEGIN_STD_C

#if defined(__mc68hc11__) || defined(__mc68hc12__) || defined(__mc68hc1x__)
void	_EXFUN(__attribute__((near)) longjmp,(jmp_buf __jmpb, int __retval));
int	_EXFUN(__attribute__((far)) setjmp,(jmp_buf __jmpb));
#else
void	_EXFUN(longjmp,(jmp_buf __jmpb, int __retval));
int	_EXFUN(setjmp,(jmp_buf __jmpb));
#endif

_END_STD_C

#endif /* _SETJMP_H_ */

