/*
 * EXTI_program.c
 *
 *  Created on: Oct 13, 2021
 *      Author: ahmed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

static void (*Global_pvEXTI0NotificationFunction)(void) = 0;


void MEXTI_Init(void)
{
		EXTI->PR=0x0000FFFF;
		//Select Trigger Mode
		SET_BIT(EXTI->RTSR,0);

		//Enable/Disable any EXTI line
		SET_BIT(EXTI->IMR,0);

}


void MEXTI_vidEnableLine(u8 LineNo)
{
	SET_BIT(EXTI->IMR,LineNo);
}


void MEXTI_vidSetLineTrig(u8 LineNo,u8 Trig)
{
if(LineNo<22)
{
	switch (Trig){
	case RISING_EDGE:
		SET_BIT(EXTI->RTSR,LineNo);
		CLR_BIT(EXTI->FSTR,LineNo);
		break;
	case FALLING_EDGE:
		SET_BIT(EXTI->FSTR,LineNo);
		CLR_BIT(EXTI->RTSR,LineNo);
		break;
	case ON_CHANGE:
		SET_BIT(EXTI->RTSR,LineNo);
		SET_BIT(EXTI->FSTR,LineNo);
		break;
	}

}

}




void MEXTI_vidDisableLine(u8 LineNo)
{
	CLR_BIT(EXTI->IMR,LineNo);
}


void MEXTI_SetSWInterrupt(u8 LineNo)
{
	if(LineNo <16)
	{
	SET_BIT(EXTI->SWIER, LineNo);
	}
}


void MEXTI_voidSetCallback(u8 Copy_u8ExternalLine, void (*Copy_pvNotificationFunction)(void))
{
	switch(Copy_u8ExternalLine)
	{
		case EXTI_LINE0:
			Global_pvEXTI0NotificationFunction = Copy_pvNotificationFunction;
			break;
	}

}


void EXTI0_IRQHandler(void)
{
	if(Global_pvEXTI0NotificationFunction != 0)
	{
		Global_pvEXTI0NotificationFunction();
	}
	else
	{
		/* Do Nothing*/
	}

}

