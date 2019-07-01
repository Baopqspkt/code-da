/**
 *
 *	@author 	Quoc Bao
 *	@email		baoqq.spkt@gmail.com
 *	@ide		Keil uVision 5
 */

#ifndef _UART_H
#define _UART_H
#define PORTUART2 	GPIOA
#define UART2_TX 		GPIO_Pin_2
#define UART2_RX 		GPIO_Pin_3
#define PORTuart3		GPIOB
#define TX3					GPIO_Pin_10
#define RX3					GPIO_Pin_11

#include "STM32F4XX_usart.h"
/////////////////////////
//UART2
void USART2_Config(void);
void USART2_PutChar(char c);
void USART2_PutString(char *s);
uint16_t USART2_GetChar(void);
////////////////////////////////
//UART1
void USART1_Config(void);
void USART1_PutChar(char c);
void USART1_PutString(char *s);
uint16_t USART1_GetChar(void);
uint16_t USART1_GetCharwhile(void);

//UART1
void USART3_Config(void);
void USART3_PutChar(char c);
void USART3_PutString(char *s);
uint16_t USART3_GetChar(void);
uint16_t USART3_GetCharwhile(void);

#endif
