/**
 *
 *	@author 	Quoc Bao
 *	@email		baoqq.spkt@gmail.com
 *	@ide		Keil uVision 5
 */

#ifndef _TIMER_H
#define _TIMER_H

#include "stm32f4xx.h"


//////////////////
void Init_timer2(void);
void Init_timer3(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
#endif
