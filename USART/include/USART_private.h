/*****************************************************************************/
/*
*Version: 1
*/
/****************************************************************************/
#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

typedef struct
{
	volatile u32 USART_SR;
	volatile u32 USART_DR;
	volatile u32 USART_BRR;
	volatile u32 USART_CR1;
	volatile u32 USART_CR2;
	volatile u32 USART_CR3;
	volatile u32 USART_GTPR;

}USART_Registers_Type;



#define USART1_BaseAddress 		  (0x40011000)
#define USART2_BaseAddress 		  (0x40004400)
#define USART3_BaseAddress 		  (0x40004800)
#define USART4_BaseAddress 		  (0x40004C00)
#define USART5_BaseAddress 		  (0x40005000)
#define USART6_BaseAddress 		  (0x40011400)






/*USART_Registers_Type (*Uart_Channels)[6]=
{
		((volatile USART_Registers_Type *)  0x40011000),
		((volatile USART_Registers_Type *)  0x40004400),
		((volatile USART_Registers_Type *)  0x40004800),
		((volatile USART_Registers_Type *)  0x40004C00),
		((volatile USART_Registers_Type *)  0x40005000),
		((volatile USART_Registers_Type *)  0x40011400),
};*/

enum {
	/*USART_CR1 register bits:*/
	USART_CR1_SBK,
	USART_CR1_RWU,
	USART_CR1_RE,
	USART_CR1_TE,
	USART_CR1_IDLEIE,
	USART_CR1_RXNEIE,
	USART_CR1_TCIE,
	USART_CR1_TXEIE ,
	USART_CR1_PEIE,
	USART_CR1_PS,
	USART_CR1_PCE,
	USART_CR1_WAKE,
	USART_CR1_M,
	USART_CR1_UE,
	USART_CR1_OVER8 =15,
	/****************************************************************************/
	/*USART_CR2 register bits:*/
	USART_CR2_CPHA  =9,
	USART_CR2_CPOL,
	USART_CR2_CLKEN,
	USART_CR2_STOP,
	/****************************************************************************/
	/*USART_CR3 register bits:*/
	USART_CR3_DMAR =6,
	USART_CR3_DMAT,
	/****************************************************************************/
	USART_SR_RXNE =5,
	USART_SR_TC,
	USART_SR_TXE,
	/****************************************************************************/
	/*Synchronous_SetUp Options*/
	Sample_At_Leading_Rising_Edge =0,
	Sample_At_Trailing_Falling_Edge,
	Sample_At_Leading_Falling_Edge,
	Sample_At_Trailing_Rising_Edge

}USART_Registers_Bits;

void (*USART1_CallBack) (void) = NULL ;
void (*USART2_CallBack) (void) = NULL ;
void (*USART3_CallBack) (void) = NULL ;
void (*UART4_CallBack) (void) = NULL ;
void (*UART5_CallBack) (void) = NULL ;
void (*USART6_CallBack) (void) = NULL ;


#endif
