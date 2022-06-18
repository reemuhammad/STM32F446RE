/*
 * EXTI_interface.h
 *
 *  Created on: Oct 13, 2021
 *      Author: ahmed
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

void MEXTI_Init(void);
void MEXTI_vidEnableLine(u8 LineNo);
void MEXTI_vidSetLineTrig(u8 LineNo,u8 Trig);
void MEXTI_voidDisableLine(u8 LineNo);
void MEXTI_SetSWInterrupt(u8 LineNo);
void MEXTI_voidSetCallback(u8 Copy_u8ExternalLine, void (*Copy_pvNotificationFunction)(void));




/* Interrupt Trigger Events --- Trig  */

#define FALLING_EDGE  	0
#define RISING_EDGE		1
#define ON_CHANGE		2

/* External Interrupt Lines ---  LineNo */

#define EXTI_LINE0 		0
#define EXTI_LINE1 		1
#define EXTI_LINE2 		2
#define EXTI_LINE3 		3
#define EXTI_LINE4 		4
#define EXTI_LINE5 		5
#define EXTI_LINE6	 	6
#define EXTI_LINE7 		7
#define EXTI_LINE8 		8
#define EXTI_LINE9 		9
#define EXTI_LINE10 	10
#define EXTI_LINE11		11
#define EXTI_LINE12		12
#define EXTI_LINE13		13
#define EXTI_LINE14		14
#define EXTI_LINE15		15
#define EXTI_LINE16		16
#define EXTI_LINE17		17
#define EXTI_LINE18		18
#define EXTI_LINE19		19
#define EXTI_LINE20		20
#define EXTI_LINE21		21
#define EXTI_LINE22		22


#endif /* EXTI_INTERFACE_H_ */
