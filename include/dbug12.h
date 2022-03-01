#ifndef DBUG12_H
#define DBUG12_H

/* This file may be included with any C file that uses the D-Bug12 user callable      */
/* routines. It provides a simple, portable way to access the routines from C without */
/* having to use any assembly language "glue code" 				                      */
/* Some defaults used by D-Bug12 						                              */
/* Modified by Navid Mohaghegh (MC9S912DP256 - 2006/12/13)		   	                  */

typedef  void * Address;
typedef  int Boolean;
typedef  unsigned char Byte;

#define Version 400


/* Structure that defines the functions in D-Bug12's user accessible 		*/
/* function table. Also provides a function prototype for each function 	*/
/* Documentation for each of these functions can be found in Application 	*/

typedef struct {

		void 	(*dummy0)(void);
		void 	(*dummy1)(void);
		int 	(*DB12getchar)(void);
		int 	(*DB12putchar)(int);
		int 	(*DB12printf)(const char *,...);
		void 	(*dummy2)(void);
		void 	(*dummy3)(void);
		void 	(*dummy4)(void);
		void 	(*dummy5)(void);
		int 	(*DB12isxdigit)(int c);
		int 	(*DB12toupper)(int c);
		int 	(*DB12isalpha)(int c);
		unsigned int (*DB12strlen)(const char *cs);
		char * (*DB12strcpy)(char *s1, char *s2);
		void 	(*dummy6)(void);
		void 	(*dummy7)(void);
		void 	(*dummy8)(void);
		void 	(*dummy9)(void);
		int 	(*SetUserVector)(int VectNum, Address UserAddress);

}UserFN, *UserFNP;

/* Defines a pointer to the start of D-Bug12's user accessible functable 	*/
/* in D-Bug12 version 4.x.x the user accessible table begins at $ee80 		*/
#define DB12FNP ((UserFNP)0xee80) 


/* The following #defines are used to provide for portability and avoid a linker */
/* conflict with the standard library functions of the same name. No #define is  */
/* included for DB12main() since all C programs contain a main() function 	 */

#define printf DB12FNP->DB12printf
#define getchar DB12FNP->DB12getchar
#define putchar DB12FNP->DB12putchar
#define isxdigit DB12FNP->DB12isxdigit
#define toupper DB12FNP->DB12toupper
#define isalpha DB12FNP->DB12isalpha
#define strlen DB12FNP->DB12strlen
#define strcpy DB12FNP->DB12strcpy

#endif
