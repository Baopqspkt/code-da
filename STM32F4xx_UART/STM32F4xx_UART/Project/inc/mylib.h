/**
 *	Define ahtlab for STM32F407VET6 kit
 *
 *	@author 	Phuoc Nguyen
 *	@email		phuocnguyen@ahtlab.com
 *	@website	ahtlab.com
 *	@ide		Keil uVision 5
 */

#ifndef _MYLIB_H
#define _MYLIB_H


void myprintf(char *,...);              //Our printf function
char* convert(unsigned int, int);       //Convert integer number into octal, hex, etc.

#endif
