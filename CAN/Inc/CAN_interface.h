/*
 * CAN_interface.h
 *
 *  Created on: May 8, 2022
 *  Author: Reem
 *  This driver is only for CAN1 and has no implementation for using CAN2,
 *  with options to configure all the filters either in Dual or Single scale mode,
 *  and the filters in list mode are consecutive filters starting from 0 to a specified number
 *  and the rest are in mask mode
 */

#ifndef CAN_INTERFACE_H_
#define CAN_INTERFACE_H_

typedef enum
{
	/*Options for FrameType */
	Data_frame =0,
	Remote_frame =1,
	/*Options or DataLength*/
	One_Byte =1,
	Two_Bytes,
    Three_Bytes,
    Four_Bytes,
    Five_Bytes,
    Six_Bytes,
    Seven_Bytes,
    Eight_Bytes,
	/*Options For ID_Type */
	Standarad_ID =0,
	Extended_ID,
/*******************************************************************************************/

/*******************************************************************************************/
	/*Scale mode for filters*/
	Dual_16_bit_scale,
	Single_32_bit_scale,

}CAN_Options_e;

/*For the transmit function, use this struct to configure the frame*/
typedef struct
{
	CAN_Options_e FrameType;
	CAN_Options_e DataLength;
	CAN_Options_e ID_Type;
	u32 ID;

}CAN_frame_t;

/*Pass a pointer to struct of this type to the receive function */
typedef struct
{
	CAN_Options_e FrameType;
	CAN_Options_e DataLength;
	u8 FilterIndex;
	u8 Message[8];
}CAN_Receive_t;

/*To configure the options for the filters, use this struct*/
typedef struct
{
	/*Number of activated filters for CAN1*/
	u8 No_Of_Can1Filters;
	/*The filter scale for all filters either Dual or Single*/
	CAN_Options_e Filter_Scale;
	/*The no. of consecutive filters that are in list mode starting from filter 0*/
	u8 No_Of_Filters_In_List_Mode;
	/*Number of filters assigned to FIFO_0 starting from 0, the rest of activated filters will be for FIFO_1s*/
	u8 No_Of_Filters_For_FIFO_ZERO;

}CAN_Init_t;



void CAN_voidInitialize(CAN_Init_t * Copy_t_Init);
void CAN_voidTransmit(CAN_frame_t * Copy_t_frame, u8 * Copy_ptr_u8_Message);
void CAN_voidReceive(CAN_Receive_t * Copy_t_ReceivedMessage);


#endif /* CAN_INTERFACE_H_ */
