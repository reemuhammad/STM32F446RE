/*
 * main.c
 *
 *  Created on: Mar 6, 2022
 *      Author: user
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "USART_interface.h"

USART_Init_struct Uart_Config =

		{
		0,
		Data_9_Bits,
		Odd_Parity,
		BaudRate_9600,
		One_Stop_Bit,
		Asynchronous
		};


void main()
{
	while(1)
	{
		;
	}
}
