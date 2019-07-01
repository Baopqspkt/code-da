#include "timer.h"
extern uint8_t timesend;

void Init_timer2()
{
    // Enable clock for TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // TIM2 initialization overflow every 1000ms
    // TIM2 by default has clock of 84MHz
    // Here, we must set value of prescaler and period,
    // so update event is 1Hz or 1000ms
    // Update Event (Hz) = timer_clock / ((TIM_Prescaler + 1) * 
    // (TIM_Period + 1))
    // Update Event (Hz) = 84MHz / ((8399 + 1) * (999 + 1)) = 10 Hz= 100ms
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 8399;
    TIM_TimeBaseInitStruct.TIM_Period = 999;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    // TIM2 initialize
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    // Enable TIM2 interrupt
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
		TIM_Cmd(TIM2, ENABLE);
    // Nested vectored interrupt settings
    // TIM2 interrupt is most important (PreemptionPriority and 
    // SubPriority = 0)
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

void Init_timer3()
{
    // Enable clock for TIM3
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    // TIM2 initialization overflow every 1000ms
    // TIM2 by default has clock of 84MHz
    // Here, we must set value of prescaler and period,
    // so update event is 1Hz or 1000ms
    // Update Event (Hz) = timer_clock / ((TIM_Prescaler + 1) * 
    // (TIM_Period + 1))
    // Update Event (Hz) = 84MHz / ((8399 + 1) * (9999 + 1)) = 1 Hz
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 8399;
    TIM_TimeBaseInitStruct.TIM_Period = 9999;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    // TIM2 initialize
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
    // Enable TIM2 interrupt
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
		TIM_Cmd(TIM3, ENABLE);
    // Nested vectored interrupt settings
    // TIM2 interrupt is most important (PreemptionPriority and 
    // SubPriority = 0)
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}
void TIM2_IRQHandler()
{

    // Checks whepresser presse TIM2 interrupt has occurred or not
    if (TIM_GetITStatus(TIM2, TIM_IT_Update))
    {

       TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
/*CONG GIA TRI SAU MOI 1 MS*/
void TIM3_IRQHandler()
{

    // Checks whepresser presse TIM2 interrupt has occurred or not
    if (TIM_GetITStatus(TIM3, TIM_IT_Update))
    {
			 timesend = timesend + 1;
       TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

