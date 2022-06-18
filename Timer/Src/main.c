/*
 * main.c
 *
 *  Created on: May 9, 2022
 *      Author: user
 */

#include "STD_TYPES.h"
#include "Timer_interface.h"

void main(void)
{
	while(1)
	{
		TimerX_Count(TIMER_2_,UP_COUNTER,500);
	}
}
