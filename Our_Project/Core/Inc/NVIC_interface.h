/*
 * NVIC_interface.h
 *
 *  Created on: Jan 11, 2022
 *      Author: Omar el Masry
 */

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_



#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_private.h"
#include "NVIC_config.h"


#define CPU_DISABLE_ALL_Interupts()		__asm ("CPSID i")
#define CPU_ENABLE_ALL_Interupts()		__asm ("CPSIE i")


#define NVIC_GROUPING_SYSTEM_XXX 				   4
#define	NVIC_GROUPING_SYSTEM_XXY 				   5
#define	NVIC_GROUPING_SYSTEM_XYY 				   6
#define	NVIC_GROUPING_SYSTEM_YYY 				   7



typedef enum            /*Represent All Interrupt Numbers */
{
		WWDG = 0 				,
		PVD 					,
		TAMPER	 				,
		RTC		 				,
		FLASH 					,
		RCC		 				,

		EXTI0		 			,
		EXTI1					,
		EXTI2		 			,
		EXTI3					,
		EXTI4		 			,

		DMA1_Channel0			,
		DMA1_Channel1			,
		DMA1_Channel2			,
		DMA1_Channel3			,
		DMA1_Channel4			,
		DMA1_Channel5			,
		DMA1_Channel6			,

		ADC1_2_3				,

		CAN1_TX					,
		CAN1_RX0				,

		CAN1_RX1				,
		CAN1_SCE				,

		EXTI9_5					,

		TIM1_BRK_TIM9			,
		TIM1_UP_TIM10			,
		TIM1_TRG_COM_TIM11		,
		TIM1_CC					,
		TIM2					,
		TIM3					,
		TIM4					,

		I2C1_EV					,
		I2C1_ER					,
		I2C2_EV					,
		I2C2_ER					,

		SPI1					,
		SPI2					,

		USART1					,
		USART2					,
		USART3					,

		EXTI15_10				,
		RTCAlarm				,
		USBWakeUp				,

		TIM8_BRK_TIM12			,
		TIM8_UP_TIM13			,
		TIM8_TRG_COM_TIM14		,
		TIM8_CC					,

		DMA1_Stream7			,

		FMC						,
		SDIO					,
		TIM5					,
		SPI3					,

		UART4					,
		UART5					,

		TIM6_DAC				,
		TIM7					,

		DMA2_Stream0			,
		DMA2_Stream1			,
		DMA2_Stream2			,
		DMA2_Stream3			,
		DMA2_Stream4			,

		/* reserved*/

		CAN2_TX=63				,
		CAN2_RX0				,
		CAN2_RX1				,
		CAN2_SCE				,

		OTG_FS					,

		DMA2_Stream5			,
		DMA2_Stream6			,
		DMA2_Stream7			,

		USART6					,

		I2C3_EV					,
		I2C3_ER					,

		OTG_HS_EP1_OUT			,
		OTG_HS_EP1_IN			,
		OTG_HS_WKUP				,
		OTG_HS					,
		DCMI					,

		/* reserved*/

		FPU=81					,

		/* reserved*/

		SPI4=84					,

		/* reserved*/

		SAI1=87					,

		/* reserved*/

		SAI2=91					,

		QuadSPI					,

		HDMI_CEC				,

		SPDIF_Rx				,

		FMPI2C1					,
		FMPI2C1_error

}NVIC_InterruptType;

typedef struct{
	NVIC_InterruptType	Interupt_Number;
	u8				Group_Priority;
	u8				SubGroup_Priority;
}NVIC_CfgType;

extern const NVIC_CfgType NVIC_Cfg[NVIC_ACTIVATED_INT_SIZE];

/****************************************************************************
* \Syntax : void IntCtrl_Init(void)
* \Description: Initilze NVIC/SCB Module
*
* \Sync\Async: Sync
* \Reentrancy: none
* \Parameters (in): none
* \Parameters (out): none
* \Return Value:    none
*
******************************************************************************/
void NVIC_Init(void);




#endif /* NVIC_INTERFACE_H_ */
