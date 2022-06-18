#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "USART_private.h"
#include "USART_interface.h"
#include "USART_config.h"

u8 RXDMABuffer[10] = {0};
u8 arr1[BufferMaxSize];

volatile USART_Registers_Type* Uart_Channels[6]=
{
		((volatile USART_Registers_Type *)  USART1_BaseAddress ),
		((volatile USART_Registers_Type *)  USART2_BaseAddress ),
		((volatile USART_Registers_Type *)  USART3_BaseAddress ),
		((volatile USART_Registers_Type *)  USART4_BaseAddress ),
		((volatile USART_Registers_Type *)  USART5_BaseAddress ),
		((volatile USART_Registers_Type *)  USART6_BaseAddress ),
};

void MUSART_voidInit(USART_Init_struct * Copy_structInitConfig)
{
	/* Get the USART channel */

	//volatile USART_Channels USARTx = Copy_structInitConfig->UartNo->USART_CR1

	/* Reset control registers settings */
	Uart_Channels[Copy_structInitConfig->UartNo]->USART_CR1=0 ;
	Uart_Channels[Copy_structInitConfig->UartNo]->USART_CR2= 0;
	Uart_Channels[Copy_structInitConfig->UartNo]->USART_CR3 =0;

	if(Copy_structInitConfig->Word_Length == Data_9_Bits)
	{
		SET_BIT(Uart_Channels[Copy_structInitConfig->UartNo]->USART_CR1 ,  USART_CR1_M);
	}
	/*else is the default Data_8_Bits */
	/****************************************************************************/
	if(Copy_structInitConfig->Parity == Even_Parity)
	{
		SET_BIT(Uart_Channels[Copy_structInitConfig->UartNo]->USART_CR1 ,USART_CR1_PCE);
	}
	else if (Copy_structInitConfig->Parity == Odd_Parity)
	{
		SET_BIT(Uart_Channels[Copy_structInitConfig->UartNo]->USART_CR1 ,USART_CR1_PCE);
		SET_BIT(Uart_Channels[Copy_structInitConfig->UartNo]->USART_CR1 ,USART_CR1_PS);
	}
	/*else is the default No_Parity */
	/****************************************************************************/
	/*Stop bits*/
	Uart_Channels[Copy_structInitConfig->UartNo]->USART_CR2 |= ((Copy_structInitConfig->Stop_Bits)<<USART_CR2_STOP);

	/****************************************************************************/
	//For manually calculated BRR values
	/*
	switch(Copy_structInitConfig->Baud_Rate)
	{
		case BaudRate_9600:
			if(USARTx == USART1)
				USARTx->USART_BRR = 0x1D4C;
			else
				USARTx->USART_BRR = 0xEA6;
			break;
		default:
			break;
	}
	*/
	/* To automatically calculate BRR value */
	f32 Local_f32IntegerDivider = ((PCLKx) / (8 * (OVR8+1) * (Copy_structInitConfig->Baud_Rate)));
	f32 Local_f32FractionalDivider = ((Local_f32IntegerDivider - ((u32) Local_f32IntegerDivider)) * 8 * (OVR8+1)) + 0.5;
	Uart_Channels[Copy_structInitConfig->UartNo]->USART_BRR = ( ((u32)Local_f32IntegerDivider<< 4) | ((u32)Local_f32FractionalDivider) );
	/****************************************************************************/
	switch (Copy_structInitConfig->Mode)
	{
		case UART_DMA_Receiver:
			SET_BIT(Uart_Channels[Copy_structInitConfig->UartNo]->USART_CR3,USART_CR3_DMAR);
			break;
		case UART_DMA_Transmitter:
			SET_BIT(Uart_Channels[Copy_structInitConfig->UartNo]->USART_CR3, USART_CR3_DMAT);
			break;
		case Synchronous:
			Uart_Channels[Copy_structInitConfig->UartNo]->USART_CR2 |= (Synchronous_SetUp<<USART_CR2_CPHA);
			SET_BIT(Uart_Channels[Copy_structInitConfig->UartNo]->USART_CR2,USART_CR2_CLKEN);
			break;
		default: 		/*Asynchronous*/
			break;
	}
	/****************************************************************************/
	/* Enable receiver and transmitter and UART peripheral : This is the default mode in this current driver */
	Uart_Channels[Copy_structInitConfig->UartNo]->USART_CR1 |= (1<<USART_CR1_RE) | (1<<USART_CR1_TE) | (1<<USART_CR1_UE);
	//Enable DMA Mode for Receiver and Transmitter
//	SET_BIT(Uart_Channels[Copy_structInitConfig->UartNo]->USART_CR3,6);
	//SET_BIT(Uart_Channels[Copy_structInitConfig->UartNo]->USART_CR3,7);
	//Clear all DMA Interrupt Flags
	//DMA2->DMA_HIFCR=0xffffffff;
	//Enable DMA stream 5 for RX
	//SET_BIT(DMA2->DMA_Streams[5].DMA_SCR,0);

}

void MSUART_voidInterrupt(u8 Copy_USART_Channel, USART_enum Copy_eInt, USART_enum Copy_eState)
{
	if(Copy_eState == USART_Interrupt_Enable)
	{
		SET_BIT(Uart_Channels[Copy_USART_Channel]->USART_CR1,Copy_eInt);
	}
	else if(Copy_eState == USART_Interrupt_Disable)
	{
		CLR_BIT(Uart_Channels[Copy_USART_Channel]->USART_CR1,Copy_eInt);
	}
}

/****************************************************************************************************************************************/
/*Use these functions in Interrupt Call Back to know which flag fired the global USART interrupt in case of several interrupts */
u8 MSUART_u8GetFlagTC(u8 Copy_USART_Channel)
{
	return (GET_BIT( Uart_Channels[Copy_USART_Channel]->USART_SR, USART_SR_TC));
}
u8 MSUART_u8GetFlagRxNE(u8 Copy_USART_Channel)
{
	return (GET_BIT( Uart_Channels[Copy_USART_Channel]->USART_SR, USART_CR1_RXNEIE));
}
u8 MSUART_u8GetFlagTxE(u8 Copy_USART_Channel)
{
	return (GET_BIT( Uart_Channels[Copy_USART_Channel]->USART_SR, USART_CR1_TXEIE));
}
u8 MSUART_u8GetFlagIdle(u8 Copy_USART_Channel)
{
	return (GET_BIT( Uart_Channels[Copy_USART_Channel]->USART_SR, USART_CR1_IDLEIE));
}



void MUSART_VidClearFlags(u8 Copy_USART_Channel  ){

	/* Clear all flags */
	Uart_Channels[Copy_USART_Channel]->USART_SR=0;

}




/****************************************************************************************************************************************/
u8 MSUART_u8ReadDataRegister(u8 Copy_USART_Channel)
{
	return Uart_Channels[Copy_USART_Channel]->USART_DR;
}
void MSUART_voidLoadDataRegister(u8 Copy_USART_Channel, u8 Copy_u8Character)
{
	Uart_Channels[Copy_USART_Channel]->USART_DR = Copy_u8Character;
}
/****************************************************************************************************************************************/

u8 MSUART_u8ReceiveWait(u8 Copy_USART_Channel)
{
	while( MSUART_u8GetFlagRxNE(Copy_USART_Channel) == 0 );
	return MSUART_u8ReadDataRegister(Copy_USART_Channel);
}
void MSUART_voidTransmitCharWait(u8 Copy_USART_Channel, u8 Copy_u8Character)
{
	MSUART_voidLoadDataRegister(Copy_USART_Channel,Copy_u8Character);
	while( MSUART_u8GetFlagTC(Copy_USART_Channel) == 0);
}
void MSUART_voidTransmitStringArrayWait(u8 Copy_USART_Channel, u8 Copy_u8StringArray[])
{
	u8 Local_u8CharCounter =0;
	while(Copy_u8StringArray[Local_u8CharCounter] != '\0')
	{
		MSUART_voidLoadDataRegister( Copy_USART_Channel, Copy_u8StringArray[Local_u8CharCounter]);
		while( MSUART_u8GetFlagTC(Copy_USART_Channel) == 0);
		Local_u8CharCounter++;
	}
}
/***************************************************************************************************************************************/

void MUSART1_voidSetCallBack( void (* ptr) (void) )
{
	USART1_CallBack = ptr;
}

void USART1_IRQHandler(void)
{
	USART1_CallBack();
}

void MUSART2_voidSetCallBack(void (* ptr) (void))
{
	USART2_CallBack = ptr;
}
void MUSART2_IRQHandler(void)
{
	USART2_CallBack();
}

void MUSART3_voidSetCallBack( void (* ptr) (void) )
{
	USART3_CallBack = ptr;
}

void USART3_IRQHandler(void)
{
	USART3_CallBack();
}

void MUART4_voidSetCallBack( void (* ptr) (void) )
{
	UART4_CallBack = ptr;
}

void UART4_IRQHandler(void)
{
	UART4_CallBack();
}

void MUART5_voidSetCallBack( void (* ptr) (void) )
{
	UART5_CallBack = ptr;
}

void UART5_IRQHandler(void)
{
	UART5_CallBack();
}

void MUSART6_voidSetCallBack( void (* ptr) (void) )
{
	USART6_CallBack = ptr;
}

void USART6_IRQHandler(void)
{
	USART6_CallBack();
}

void DMA2_Stream5_voidSetCallBack( void (* ptr) (void) )
{
	DMA2_Stream5_CallBack= ptr;
}
void DMA2_Stream5_IRQHandler()
{
	DMA2_Stream5_CallBack();

}
void DMA2_Stream7_voidSetCallBack( void (* ptr) (void) )
{
	DMA2_Stream7_CallBack= ptr;
}
void DMA2_Stream7_IRQHandler()
{
	DMA2_Stream7_CallBack();
}


void MSUART1_void_TX_DMA_Config()
{
	//Check if DMA2 Stream 7 Disabled
	if(GET_BIT(DMA2->DMA_Streams[7].DMA_SCR,0))
	{
		CLR_BIT(DMA2->DMA_Streams[7].DMA_SCR,0);

		while(GET_BIT(DMA2->DMA_Streams[7].DMA_SCR,0))
			;
	}
	//Select Channel 4 in CHSEL[0:2]
	CLR_BIT(DMA2->DMA_Streams[7].DMA_SCR,25);
	CLR_BIT(DMA2->DMA_Streams[7].DMA_SCR,26);
	SET_BIT(DMA2->DMA_Streams[7].DMA_SCR,27);
	//Select Stream Priority very high
	SET_BIT(DMA2->DMA_Streams[7].DMA_SCR,16);
	SET_BIT(DMA2->DMA_Streams[7].DMA_SCR,17);
	//Select stream Direction memory to peripheral
	SET_BIT(DMA2->DMA_Streams[7].DMA_SCR,6);
	CLR_BIT(DMA2->DMA_Streams[7].DMA_SCR,7);
	//Set Memory size to 8 bit
	CLR_BIT(DMA2->DMA_Streams[7].DMA_SCR,13);
	CLR_BIT(DMA2->DMA_Streams[7].DMA_SCR,14);
	//Set peripheral size to 8 bit
	CLR_BIT(DMA2->DMA_Streams[7].DMA_SCR,11);
	CLR_BIT(DMA2->DMA_Streams[7].DMA_SCR,12);
	//Select FIFO Mode
	SET_BIT(DMA2->DMA_Streams[7].DMA_SFCR,2);
	//Select FIFO Half Threshold
	SET_BIT(DMA2->DMA_Streams[7].DMA_SFCR,0);
	CLR_BIT(DMA2->DMA_Streams[7].DMA_SFCR,1);
	//Enable Memory Increment Mode ,peripheral have fixed address
	CLR_BIT(DMA2->DMA_Streams[7].DMA_SCR,10);
	//Enable DMA Transfer Complete Interrupt
	SET_BIT(DMA2->DMA_Streams[7].DMA_SCR,4);
	//Set peripheral address
	DMA2->DMA_Streams[7].DMA_SPAR= (u32)(0x40011004);

}




void MSUART1_void_RX_DMA_Config()
{
	//Check if DMA2 Stream 7 Disabled
	if(GET_BIT(DMA2->DMA_Streams[5].DMA_SCR,0))
	{
		CLR_BIT(DMA2->DMA_Streams[5].DMA_SCR,0);

		while(GET_BIT(DMA2->DMA_Streams[5].DMA_SCR,0))
			;
	}
	//Select Channel 4 in CHSEL[0:2]
	CLR_BIT(DMA2->DMA_Streams[5].DMA_SCR,25);
	CLR_BIT(DMA2->DMA_Streams[5].DMA_SCR,26);
	SET_BIT(DMA2->DMA_Streams[5].DMA_SCR,27);
	//Select Stream Priority very high
	SET_BIT(DMA2->DMA_Streams[5].DMA_SCR,16);
	SET_BIT(DMA2->DMA_Streams[5].DMA_SCR,17);
	//Select stream Direction peripheral to memory
	CLR_BIT(DMA2->DMA_Streams[5].DMA_SCR,6);
	CLR_BIT(DMA2->DMA_Streams[5].DMA_SCR,7);
	//Set Memory size to 8 bit
	CLR_BIT(DMA2->DMA_Streams[5].DMA_SCR,13);
	CLR_BIT(DMA2->DMA_Streams[5].DMA_SCR,14);
	//Set peripheral size to 8 bit
	CLR_BIT(DMA2->DMA_Streams[5].DMA_SCR,11);
	CLR_BIT(DMA2->DMA_Streams[5].DMA_SCR,12);
	//Select FIFO Mode
	SET_BIT(DMA2->DMA_Streams[5].DMA_SFCR,2);
	//Select FIFO Half Threshold
	SET_BIT(DMA2->DMA_Streams[5].DMA_SFCR,0);
	CLR_BIT(DMA2->DMA_Streams[5].DMA_SFCR,1);
	//Enable Memory Increment Mode ,peripheral have fixed address
	CLR_BIT(DMA2->DMA_Streams[5].DMA_SCR,10);
	//Enable DMA Transfer Complete Interrupt
	SET_BIT(DMA2->DMA_Streams[5].DMA_SCR,4);
	//Set peripheral address
	DMA2->DMA_Streams[5].DMA_SPAR= (u32)(0x40011004);
	//Set memory address
	DMA2->DMA_Streams[5].DMA_SM0AR= (u32)RXDMABuffer;
	//Set No of Data items
	DMA2->DMA_Streams[5].DMA_SNDTR=BufferMaxSize;

}


