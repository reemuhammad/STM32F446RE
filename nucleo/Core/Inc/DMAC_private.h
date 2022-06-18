/*
 * DMAC_private.h
 *
 *  Created on: May 21, 2022
 *      Author: NO3M4N
 */

#ifndef INC_DMAC_PRIVATE_H_
#define INC_DMAC_PRIVATE_H_

typedef struct {

		volatile u32 CR;
		volatile u32 NDTR;
		volatile u32 PAR;
		volatile u32 M0AR;
		volatile u32 M1AR;
		volatile u32 FCR;
}Stream_Registers_t;

//*Stream_Registers_t Stream[8];

typedef struct {
	volatile u32 LISR;
	volatile u32 HISR;
	volatile u32 LIFCR;
	volatile u32 HIFCR;
	Stream_Registers_t *Stream[8];


}DMA_Registers_Types;






#define DMA1_BASE_ADDRESS		(0x40026000)
#define DMA2_BASE_ADDRESS		(0x40026400)

//#define DMA1	((volatile DMA_Registers_Types*)(DMA1_BASE_ADDRESS))
//#define DMA2	((volatile DMA_Registers_Types*)(DMA2_BASE_ADDRESS))



void (*DMA1_CallBack) (void) = NULL ;
void (*DMA2_CallBack) (void) = NULL ;
void (*DMA2_Stream5_CallBack) (void) = NULL ;





#endif /* INC_DMAC_PRIVATE_H_ */
