/*
 * EXTI_private.h
 *
 *  Created on: Oct 13, 2021
 *      Author: ahmed
 */

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_
#include "STD_TYPES.h"


#define EXTI_BASE_ADDR 0x40013C00
typedef struct
{
	u32 IMR;
	u32 EMR;
	u32	RTSR;
	u32	FSTR;
	u32 SWIER;
	u32 PR;
}EXTI_t;

#define EXTI 		((volatile EXTI_t*) (EXTI_BASE_ADDR))





/*#define EXTI_EMR			*((volatile u32*) (EXTI_BASE_ADDR+0x04))
#define EXTI_RTSR 			*((volatile u32*) (EXTI_BASE_ADDR+0x08))
#define EXTI_FTSR 			*((volatile u32*) (EXTI_BASE_ADDR+0x0C))
#define EXTI_SWIER 			*((volatile u32*) (EXTI_BASE_ADDR+0x10))
#define EXTI_PR				*((volatile u32*) (EXTI_BASE_ADDR+0x14))


*/

#endif /* EXTI_PRIVATE_H_ */
