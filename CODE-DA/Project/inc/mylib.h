/**
 *
 *	@author 	Quoc Bao
 *	@email		baopq.spkt@gmail.com
 *	@ide		Keil uVision 5
 */

#ifndef _MYLIB_H
#define _MYLIB_H


#include "STM32F4xx.h"
#include "delay.h"
#include "uart.h"
#include <stdio.h>
#include <stdarg.h>
//#include "clock.h"
//#include "timer.h"



void myprintf1(char *,...); 
void myprintf2(char *,...); 
void myprintf3(char *,...); 
char* convert(unsigned int, int);       //Convert integer number into octal, hex, etc.

#endif
