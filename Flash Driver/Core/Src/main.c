/*
 */
#include "STD_TYPES.h"

#include "USART_config.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "USART_interface.h"
#include "NVIC_interface.h"
#include "GPIO_private.h"
#include "Flash_Interface.h"
//#include "USART_private.h"


extern u8 RXDMABuffer[BufferMaxSize];




USART_Init_struct uart1 = {0,Data_9_Bits,No_Parity,BaudRate_9600,One_Stop_Bit,Synchronous};

int main()
{
	//u32 val =0;
	RCC_voidInitSystemClock();
	RCC_voidEnableCompClk(RCC_APB2,RCC_APB2_USART1);
	RCC_voidEnableCompClk(RCC_AHB1,RCC_AHB1_GPIOA);
	RCC_voidEnableCompClk(RCC_AHB3,RCC_AHB3_FMC);
	RCC_voidEnableCompClk(RCC_AHB1,RCC_AHB1_DMA2);


	NVIC_Init();
	//MFLASH_voidINIT();
	GPIO_voidSetPinDirection(GPIOA,10,ALTERNATING_FUNCTION_PUSH_PULL_NO_PUPD_VERY_FAST_SPEED);
	GPIO_voidSetPinDirection(GPIOA,9,ALTERNATING_FUNCTION_PUSH_PULL_NO_PUPD_VERY_FAST_SPEED);


	GPIO_voidSetAlternatingFunction(GPIOA,9,AF7);
	GPIO_voidSetAlternatingFunction(GPIOA,10,AF7);
	MSUART1_void_TX_DMA_Config();
	MSUART1_void_RX_DMA_Config();
	MUSART_voidInit(&uart1);
	MSUART_voidTransmitCharWait(0,'a');
	DMA2_Stream5_voidSetCallBack(UART1_RX_DMA_CALLBACK);
	while(1)
	{
		// MFLASH_voidMAIN();
		MSUART_voidTransmitCharWait(0,'a');

	}

}


// ----------------------------------------------------------------------------
