/*
 * STK_interface.h
 *
 *  Created on: Oct 25, 2021
 *      Author: Omar el Masry
 */

#ifndef STK_INTERFACE_H_
#define STK_INTERFACE_H_
#include "STD_TYPES.h"

void mSTK_vidInit(void);

void mSTK_StartTimer();
void mSTK_StopTimer();

void mSTK_EnableInterrupt();
void mSTK_DisableInterrupt();

void mSTK_SetInterval_Single(u32 ticks,void(*fptr)());
void mSTK_SetInterval_Periodic(u32 ticks,void(*fptr)());
void mSTK_SetBusyWait(u32 ticks);

u32 mSTK_GetRamainingTime(void);
u32 mSTK_GetElapsedTime(void);







#endif /* STK_INTERFACE_H_ */
