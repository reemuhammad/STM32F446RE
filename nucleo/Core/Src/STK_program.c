/*
 * STK_program.c
 *
 *  Created on: Oct 25, 2021
 *      Author: Omar el Masry
 */
#include "BIT_Math.h"

#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"
#include "STD_TYPES.h"

static void (*Global_STK_Callback)(void);
volatile u8 single_flag=0;

void mSTK_vidInit(void)
{

#if 	STK_CLK_SOURCE	==	AHB_DIV_8
			CLR_BIT((STK->CTRL),CLKSOURCE);

#elif	STK_CLK_SOURCE	==	AHB
			SET_BIT((STK->CTRL),CLKSOURCE);
#endif


#if 	ENABLE_Interrupt	==	ENABLE
			SET_BIT((STK->CTRL),TICKINT);

#elif	ENABLE_Interrupt	==	DISABLE
			CLR_BIT((STK->CTRL),TICKINT);
#endif

}

void mSTK_StartTimer()
{
	SET_BIT((STK->CTRL),ENABLEB);

}
void mSTK_StopTimer()
{
	STK->VAL=0;
	STK->LOAD=0;
	CLR_BIT((STK->CTRL),ENABLEB);
}

void mSTK_EnableInterrupt()
{
	SET_BIT((STK->CTRL),TICKINT);
}
void mSTK_DisableInterrupt()
{
	CLR_BIT((STK->CTRL),TICKINT);
}


void mSTK_SetInterval_Single(u32 ticks,void(*fptr)())
{
	if(ticks	< (1UL<<24) )
	{
		single_flag=1;
		// 1- load ticks
		STK->LOAD=ticks;
		//2-set callback
		Global_STK_Callback=fptr;
		//3-start timer
		mSTK_StartTimer();
	}

}
void mSTK_SetInterval_Periodic(u32 ticks,void(*fptr)())
{
	if(ticks	< (1UL<<24) )
	{
		// 1- load ticks
		STK->LOAD=ticks;
		//2-set callback
		Global_STK_Callback=fptr;
		//3-start timer
		mSTK_StartTimer();
	}
}

void mSTK_SetBusyWait(u32 ticks)
{
	volatile u32 data=0;
	STK->LOAD=ticks;
	mSTK_StartTimer();
	data=GET_BIT(STK->CTRL,COUNTFLAG);
	while(!data) {
		data=GET_BIT(STK->CTRL,COUNTFLAG);
	}
	mSTK_StopTimer();

}

u32 mSTK_GetRamainingTime(void)
{
	return (STK->VAL);
}

u32 mSTK_GetElapsedTime(void)
{
	return ((STK->LOAD)-(STK->VAL));
}

void SysTick_Handler(void)
{

	Global_STK_Callback();
	if(single_flag==1)
	{
		single_flag=0;
		mSTK_StopTimer();
	}

}


