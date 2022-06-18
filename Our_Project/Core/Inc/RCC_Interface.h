/*				******************************************

-------------------------------------------------------------------------------------------------------------------------------------------------------
		*/	
/* Author: Abdelrahman Ramzi Fahmi				  						*/
/* Date: 07-Nov. 2021													*/
/* Version: 0.1															*/
/*				******************************************		*/

#ifndef _RCC_INTERFACE_H_
#define _RCC_INTERFACE_H_


void RCC_voidInitSystemClock(void);
void RCC_voidEnableCompClk(u8 Copy_uint8Bus, u8 Copy_uint8PerID);
void RCC_voidDisableCompClk(u8 Copy_uint8Bus, u8 Copy_uint8PerID);


/********************************************/
/*				RCC Peripherals				*/
/*				Clock EN/DIS				*/
/********************************************/
/*Buses definitions for Peripheral CLK Selection Enable*/
#define RCC_AHB1			1 
#define RCC_AHB2			2 
#define RCC_AHB3			3 
#define RCC_APB1			4
#define RCC_APB2 			5

/*			RCC Registers Bits / Peripherals IDs				*/

/*************************************************************************************************************************
 * Peripherals Enable Configurations
 ************************************************************************************************************************/

/* 			AHB1			*/
#define RCC_AHB1_GPIOA		0
#define RCC_AHB1_GPIOB		1
#define RCC_AHB1_GPIOC		2
#define RCC_AHB1_GPIOD		3
#define RCC_AHB1_GPIOE		4
#define RCC_AHB1_GPIOF		5
#define RCC_AHB1_GPIOG		6
#define RCC_AHB1_GPIOH		7
#define RCC_AHB1_CRC		12
#define RCC_AHB1_BKP		18
#define RCC_AHB1_DMA1		21
#define RCC_AHB1_DMA2		22
#define RCC_AHB1_OTGHS		29
#define RCC_AHB1_OTGHSULPI	30


/* 			AHB2			*/

#define RCC_AHB2_DCMI		0
#define RCC_AHB2_OTGHFS		7


/* 			AHB3			*/

#define RCC_AHB3_FMC		0
#define RCC_AHB3_QSPI		1

/* 			APB1			*/

#define RCC_APB1_TIM2		0
#define RCC_APB1_TIM3		1
#define RCC_APB1_TIM4		2
#define RCC_APB1_TIM5		3
#define RCC_APB1_TIM6		4
#define RCC_APB1_TIM7		5
#define RCC_APB1_TIM12		6
#define RCC_APB1_TIM13		7
#define RCC_APB1_TIM14		8
#define RCC_APB1_WWDG		11
#define RCC_APB1_SPI2		14
#define RCC_APB1_SPI3		15
#define RCC_APB1_SPDIFRX	16
#define RCC_APB1_USART2		17
#define RCC_APB1_USART3		18
#define RCC_APB1_USART4		19
#define RCC_APB1_USART5		20
#define RCC_APB1_I2C1		21
#define RCC_APB1_I2C2		22
#define RCC_APB1_I2C3		23
#define RCC_APB1_FMPI2C1	24
#define RCC_APB1_CAN1		25
#define RCC_APB1_CAN2		26
#define RCC_APB1_CEC		27
#define RCC_APB1_PWR		28
#define RCC_APB1_DAC		29

/* 			APB2 			*/

#define RCC_APB2_TIM1		0
#define RCC_APB2_TIM8		1
#define RCC_APB2_USART1		4
#define RCC_APB2_USART6		5
#define RCC_APB2_ADC1		8
#define RCC_APB2_ADC2		9
#define RCC_APB2_ADC3		10
#define RCC_APB2_SDIO		11
#define RCC_APB2_SPI1		12
#define RCC_APB2_SPI4		13
#define RCC_APB2_SYSCFG		14
#define RCC_APB2_TIM9		16
#define RCC_APB2_TIM10		17
#define RCC_APB2_TIM11		18
#define RCC_APB2_SAL1		22
#define RCC_APB2_SAL2		23

















#endif
