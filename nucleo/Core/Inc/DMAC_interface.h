/*
 * DMAC_private.h
 *
 *  Created on: May 21, 2022
 *      Author: NO3M4N
 */

#ifndef INC_DMAC_INTERFACE_H_
#define INC_DMAC_INTERFACE_H_

typedef enum DMA_e{


	/*
	 *
	 *
	 *
	 * */

	DMA1=0,
	DMA2=1,

	Stream0,
	Stream1,
	Stream2,
	Stream3,
	Stream4,
	Stream5,
	Stream6,
	Stream7,

	Channel0=000,
	Channel1=001,
	Channel2=010,
	Channel3=011,
	Channel4=100,
	Channel5=101,
	Channel6=110,
	Channel7=111,

	FIFO1_4=00,
	FIFO1_2=01,
	FIFO3_4=10,
	FIFO_FULL=11,


	Direct_mode_INT_EN,
	Direct_mode_INT_DIS,

	Transfer_error_INT_EN,
	Transfer_error_INT_DIS,

	HalfTransfer_error_INT_EN,
	HalfTransfer_error_INT_DIS,

	Trans_Comp_INT_EN,
	Trans_Comp_INT_DIS,

	Flow_Control_Perph,
	Flow_Control_DMA,

	Perph_to_Memory=00,
	Memory_to_Perph=01,
	Memory_to_Memory=11,


	PERPHPOINTER_INCREMENT,
	PERPHPOINTER_FIXED,

	MEMORY_POINTER_INCREMENT,
	MEMORY_POINTER_FIXED,


	MEM_BYTE=00,
	MEM_HALFWORD=01,
	MEM_WORD=10,

	PER_BYTE=00,
	PER_HALFWORD=01,
	PER_WORD=10,

	INCREMENT_PSIZE,
	INCREMENT_4,

	/*********DMA MODES***********/

	DIRECT_MODE_EN,
	FIFO_MODE_EN,
/**************************************/

	NORMAL_MODE_EN,
	CIRCULAR_MODE_EN,
	PERPH_FLOW_CTRL_EN,



/**********************PRIORITY*******************************/

LOW=00,
MEDIUM=01,
HIGH=10,
VERYHIGH=11,


/**********************BURST*******************************/

SINGLE=00,
INC4=01,
INC8=10,
INCR16=11,


}DMA_enum;

typedef struct {
	/*USART1 RX IS
	 * DMA    	2
	 * STREAM 	2
	 * CHANNEL 	4*/


	DMA_enum 			DMA_no;
	DMA_enum			Stream_no;
	DMA_enum			Channel_no;
	DMA_enum			DMA_Transfer_Mode;
	DMA_enum			DMA_FIFO_MODE;
	DMA_enum			DMA_FIFO_THRESH;
	DMA_enum			DMA_Transfer_Direction;
	DMA_enum			DMA_Flow_Ctrl;
	DMA_enum			DMA_MEM_INC;
	DMA_enum			DMA_PERPH_INC;
	DMA_enum			DMA_PRIORITY;
	DMA_enum			DMA_MBURST;
	DMA_enum			DMA_PBURST;
	DMA_enum			DMA_MSIZE;
	DMA_enum			DMA_PSIZE;
	u16					Buffer_Size;
	u32					Perph_Addr;
	u32					Mem_Addr;




////DMA_enum			DMA_INT;



}DMA_Init_struct;



void HDMA_voidInit(DMA_Init_struct*  Cpy_HDMA_InitConf);


void DMA1_voidSetCallBack( void (* ptr) (void) );
void DMA2_voidSetCallBack( void (* ptr) (void) );
void DMA2_Stream5_voidSetCallBack( void (* ptr) (void) );








#endif /* INC_DMAC_PRIVATE_H_ */
