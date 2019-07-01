#include "delay.h"
#include "uart.h"
#include "mylib.h"


#define PORTLed			GPIOD
#define PORTButton		GPIOE
#define Led1			GPIO_Pin_12	
#define Led2			GPIO_Pin_13
#define Led3			GPIO_Pin_14
#define Led4			GPIO_Pin_15
#define BT0		GPIO_Pin_0	
#define BT1		GPIO_Pin_1	
#define BT2		GPIO_Pin_2	
#define BT3		GPIO_Pin_3	

uint16_t ADC3ConvertedValue[5]={0,0,0,0,0};
uint16_t data = 0, old_data = 0,check = 1;
short led1, led2, led3, led4;
short led1sta, led2sta, led3sta, led4sta;
uint8_t timesend;
/*Declare Struct*/
GPIO_InitTypeDef GPIO_InitStructure;
void init_Clock(void);

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
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_InitStructure.GPIO_Pin = Led1 | Led2 | Led3 | Led4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(PORTLed, &GPIO_InitStructure);
	
	/*setting PORT User Button*/
}

void Configure_PD0(void) {
    /* Set variables used */
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    /* Enable clock for GPIOD */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    /* Enable clock for SYSCFG */ // cap xung clock cho syscfg
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    /* Set pin as input */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = BT0;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
    /* Tell system that you will use PD0 for EXTI_Line0 */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0);   
    /* PD0 is connected to EXTI_Line0 */
    EXTI_InitStruct.EXTI_Line = EXTI_Line0;
    /* Enable interrupt */
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    /* Interrupt mode */
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    /* Triggers on rising and falling edge */
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    /* Add to EXTI */
    EXTI_Init(&EXTI_InitStruct);
 
    /* Add IRQ vector to NVIC */
    /* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    /* Set priority */
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    /* Set sub priority */
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
    /* Enable interrupt */
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    /* Add to NVIC */
    NVIC_Init(&NVIC_InitStruct);
}

void EXTI0_IRQHandler(void) {
    /* Make sure that interrupt flag is set */
    if (EXTI_GetITStatus(EXTI_Line0) == 0) {
        /* Do your stuff when PE2 is changed */
        led1 = ~led1;
        /* Clear interrupt flag */
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
void Configure_PD1(void) {
    /* Set variables used */
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    /* Enable clock for GPIOD */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    /* Enable clock for SYSCFG */ // cap xung clock cho syscfg
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    /* Set pin as input */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = BT1;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
    /* Tell system that you will use PD1 for EXTI_Line1 */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource1);   
    /* PA4 is connected to EXTI_Line1 */
    EXTI_InitStruct.EXTI_Line = EXTI_Line1;
    /* Enable interrupt */
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    /* Interrupt mode */
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    /* Triggers on rising and falling edge */
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    /* Add to EXTI */
    EXTI_Init(&EXTI_InitStruct);
 
    /* Add IRQ vector to NVIC */
    /* PD0 is connected to EXTI_Line1, which has EXTI1_IRQn vector */
    NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
    /* Set priority */
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    /* Set sub priority */
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
    /* Enable interrupt */
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    /* Add to NVIC */
    NVIC_Init(&NVIC_InitStruct);
}

void EXTI1_IRQHandler(void) {
    /* Make sure that interrupt flag is set */
    if (EXTI_GetITStatus(EXTI_Line1) == 0) {
        /* Do your stuff when PE2 is changed */
        led2 = ~led2;
        /* Clear interrupt flag */
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}
void Configure_PD2(void) {
    /* Set variables used */
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    /* Enable clock for GPIOD */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    /* Enable clock for SYSCFG */ // cap xung clock cho syscfg
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    /* Set pin as input */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = BT2;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
    /* Tell system that you will use PD2 for EXTI_Line2 */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource2);   
    /* PA4 is connected to EXTI_Line2 */
    EXTI_InitStruct.EXTI_Line = EXTI_Line2;
    /* Enable interrupt */
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    /* Interrupt mode */
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    /* Triggers on rising and falling edge */
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    /* Add to EXTI */
    EXTI_Init(&EXTI_InitStruct);
 
    /* Add IRQ vector to NVIC */
    /* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
    NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
    /* Set priority */
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    /* Set sub priority */
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x02;
    /* Enable interrupt */
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    /* Add to NVIC */
    NVIC_Init(&NVIC_InitStruct);
}

void EXTI2_IRQHandler(void) {
    /* Make sure that interrupt flag is set */
    if (EXTI_GetITStatus(EXTI_Line2) == 0) {
        /* Do your stuff when PD2 is changed */
        led3 = ~led3;
        /* Clear interrupt flag */
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}
void Configure_PD3(void) {
    /* Set variables used */
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    /* Enable clock for GPIOD */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    /* Enable clock for SYSCFG */ // cap xung clock cho syscfg
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    /* Set pin as input */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = BT3;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
    /* Tell system that you will use PD3 for EXTI_Line3 */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource3);   
    /* PA4 is connected to EXTI_Line3 */
    EXTI_InitStruct.EXTI_Line = EXTI_Line3;
    /* Enable interrupt */
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    /* Interrupt mode */
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    /* Triggers on rising and falling edge */
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    /* Add to EXTI */
    EXTI_Init(&EXTI_InitStruct);
 
    /* Add IRQ vector to NVIC */
    /* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
    NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;
    /* Set priority */
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    /* Set sub priority */
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x03;
    /* Enable interrupt */
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    /* Add to NVIC */
    NVIC_Init(&NVIC_InitStruct);
}

void EXTI3_IRQHandler(void) {
    /* Make sure that interrupt flag is set */
    if (EXTI_GetITStatus(EXTI_Line3) == 0) {
        /* Do your stuff when PD3 is changed */
        led4 =~ led4;
        /* Clear interrupt flag */
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}

void ADC_configure()
{
		ADC_InitTypeDef       ADC_InitStruct;
    ADC_CommonInitTypeDef ADC_CommonInitStruct;
    DMA_InitTypeDef       DMA_InitStruct;
    GPIO_InitTypeDef      GPIO_InitStruct;
    /* Enable ADC3, DMA2 and GPIO clocks ****************************************/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);//ADC3 is connected to the APB2 peripheral bus
    /* DMA2 Stream0 channel0 configuration **************************************/
    DMA_InitStruct.DMA_Channel = DMA_Channel_2;
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC3->DR;//ADC3's data register
    DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)&ADC3ConvertedValue;
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStruct.DMA_BufferSize = 5;
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//Reads 16 bit values
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//Stores 16 bit values
    DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStruct.DMA_Priority = DMA_Priority_High;
    DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream0, &DMA_InitStruct);
    DMA_Cmd(DMA2_Stream0, ENABLE);
    /* Configure GPIO pins ******************************************************/
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;// PC0, PC1, PC2, PC3
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;//The pins are configured in analog mode
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL ;//We don't need any pull up or pull down
    GPIO_Init(GPIOC, &GPIO_InitStruct);//Initialize GPIOC pins with the configuration
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;//PA1
    GPIO_Init(GPIOA, &GPIO_InitStruct);//Initialize GPIOA pins with the configuration
    /* ADC Common Init **********************************************************/
    ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStruct);
    /* ADC3 Init ****************************************************************/
    ADC_DeInit();
    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;//Input voltage is converted into a 12bit int (max 4095)
    ADC_InitStruct.ADC_ScanConvMode = ENABLE;//The scan is configured in multiple channels
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;//Continuous conversion: input signal is sampled more than once
    ADC_InitStruct.ADC_ExternalTrigConv = 0;
    ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//Data converted will be shifted to right
    ADC_InitStruct.ADC_NbrOfConversion = 5;
    ADC_Init(ADC3, &ADC_InitStruct);//Initialize ADC with the configuration
    /* Select the channels to be read from **************************************/
    ADC_RegularChannelConfig(ADC3, ADC_Channel_10, 1, ADC_SampleTime_144Cycles);//PC0
    ADC_RegularChannelConfig(ADC3, ADC_Channel_11, 2, ADC_SampleTime_144Cycles);//PC1
    ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 3, ADC_SampleTime_144Cycles);//PC2
    ADC_RegularChannelConfig(ADC3, ADC_Channel_13, 4, ADC_SampleTime_144Cycles);//PC3
    ADC_RegularChannelConfig(ADC3, ADC_Channel_1,  5, ADC_SampleTime_144Cycles);//PA1
    /* Enable DMA request after last transfer (Single-ADC mode) */
    ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);
    /* Enable ADC3 DMA */
    ADC_DMACmd(ADC3, ENABLE);
    /* Enable ADC3 */
    ADC_Cmd(ADC3, ENABLE);
    /* Start ADC3 Software Conversion */
    ADC_SoftwareStartConv(ADC3);
}

void ReceviceData()
{
	data = USART2_GetChar();
	switch(data)
	{
		case 49:{check = 1; led1 = 0; break;}
		case 66:{check = 1; led1 = 1; break;}
		case 50:{check = 1; led2 = 0; break;}
		case 67:{check = 1; led2 = 1; break;}
		case 51:{check = 1; led3 = 0; break;}
		case 68:{check = 1; led3 = 1;break;}
		case 52:{check = 1; led4 = 0; break;}
		case 69:{check = 1; led4 = 1; break;}
		default: {break;}
	}
	myprintf2("%d%d%d%d",led1,led2,led3,led4);
}

void turnled()
{
	if(led1 == 1)
		GPIO_SetBits(GPIOD,Led1);
	else
		GPIO_ResetBits(GPIOD,Led1);
	if(led2 == 1)
		GPIO_SetBits(GPIOD,Led2);
	else
		GPIO_ResetBits(GPIOD,Led2);
	if(led3 == 1)
		GPIO_SetBits(GPIOD,Led3);
	else
		GPIO_ResetBits(GPIOD,Led3);
	if(led4 == 1)
		GPIO_SetBits(GPIOD,Led4);
	else
		GPIO_ResetBits(GPIOD,Led4);
	//myprintf2("%d%d%d%d",led1sta,led2sta,led3sta,led4sta);
}

void readadc()
{
	if (ADC3ConvertedValue[0] > 255)
		led1sta = 1;
	else 
		led1sta = 0;
	if (ADC3ConvertedValue[1] > 255)
		led2sta = 1;
	else
		led2sta = 0;
	if (ADC3ConvertedValue[2] > 255)
		led3sta = 1;
	else 
		led3sta = 0;
	if (ADC3ConvertedValue[3] > 255)
		led4sta = 1;
	else 
		led4sta = 0;
	
}

int main(){
	
	/*--------------------------Initialise Clock------------------------------*/
	SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }
	init_GPIO();		
	USART2_Config();
	Configure_PD0();
	Configure_PD1();
	Configure_PD2();
	Configure_PD3();
	ADC_configure();
	while(1){
			ReceviceData();
			turnled();
			if(timesend > 5){	
				readadc();
				timesend = 0;
			}
	}
}
