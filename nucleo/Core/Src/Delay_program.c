/*
 * Delay_program.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Omar el Masry
 */

#include "STD_TYPES.h"

#include "STK_interface.h"

#include "Delay_interface.h"


void _delay_ms( u32 Copy_u32Time ){

	mSTK_vidInit();
	mSTK_SetBusyWait(1000*Copy_u32Time);
}


/* Suppose That The Clock System (AHB) = 8MHZ EXT & The Systick Clock Is = AHB/8 */
void _delay_us( u32 Copy_u32Time ){

	mSTK_vidInit();
	mSTK_SetBusyWait(Copy_u32Time);

}


