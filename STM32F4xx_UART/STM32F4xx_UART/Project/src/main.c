/**
 *	Define ahtlab for STM32F407VET6 kit
 *
 *	@author 	Phuoc Nguyen
 *	@email		hoangphuoc261@gmail.com
 *	@website	ahtlab.com
 *	@ide		Keil uVision 5
 */
 
#include "delay.h"
#include "ahtlab.h"
#include "uart.h"
#include "mylib.h"

/*Declare Struct*/
GPIO_InitTypeDef GPIO_InitStructure;

/*declare function*/
void init_GPIO(void);
void init_Clock(void);
void TIM_INT_Init(void);

void init_Clock()
{
		// Resets the clock configuration to the default reset state
    RCC_DeInit();

    // Enable external crystal (HSE)
    RCC_HSEConfig(RCC_HSE_ON);
    // Wait until HSE ready to use or not
    ErrorStatus errorStatus = RCC_WaitForHSEStartUp();

    if (errorStatus == SUCCESS)
    {
        // Configure the PLL for 168MHz SysClk and 48MHz for USB OTG, SDIO
        RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7);
        // Enable PLL
        RCC_PLLCmd(ENABLE);
        // Wait until main PLL clock ready
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

        // Set flash latency
        FLASH_SetLatency(FLASH_Latency_5);

        // AHB 168MHz
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        // APB1 42MHz
        RCC_PCLK1Config(RCC_HCLK_Div4);
        // APB2 84 MHz
        RCC_PCLK2Config(RCC_HCLK_Div2);

        // Set SysClk using PLL
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    }
    else
    {
        // Do something to indicate that error clock configuration
        while (1);
    }

    SystemCoreClockUpdate();
}

/*---------------------------Interrupt Systick-------------------------------*/
void SysTick_Handler()
{
	TimingDelay_Decrement();
}


void init_GPIO()
{
	/*setting PORT Led*/
	/* enable GPIOA */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = Led1 | Led2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(PORTLed, &GPIO_InitStructure);
	
	/*setting PORT User Button*/
	/* enable GPIOE */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin = UserButton | UserButton1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(PORTButton, &GPIO_InitStructure);
}

void TIM_INT_Init()
{
	
    // Enable clock for TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

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
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    // Enable TIM2 interrupt
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    // Start TIM2
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

void TIM2_IRQHandler()
{
    // Checks whether the TIM2 interrupt has occurred or not
    if (TIM_GetITStatus(TIM2, TIM_IT_Update))
    {
        // Toggle orange LED (GPIO13)
        GPIO_ToggleBits(PORTLed, Led1);

        // Clears the TIM2 interrupt pending bit
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}


int main(){
	
	/*--------------------------Initialise Clock------------------------------*/
	init_Clock(); 	                /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	
	init_GPIO();		
  USART_Config();

	 USART_PutString("Hello, Class!\n");
	int a=1234;
	char* c="Hello";
 
	
	while(1){
		        // Get a char from PC
        uint16_t data = USART_GetChar();

        if (data == 'H')
        {
            // If received char is 'H' then turn on orange LED
            GPIO_SetBits(GPIOA, GPIO_Pin_6);
        }
        else if (data == 'L')
        {
            // If received char is 'L' then turn off orange LED
            GPIO_ResetBits(GPIOA, GPIO_Pin_6);
        }
				else if (data == 'A')
        {
            // If received char is 'L' then turn off orange LED
            myprintf("\n file in %d %s ",a,c);
        }
				

	}
}
