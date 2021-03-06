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

typedef enum
{
	/*Options for interrupt*/
	Transmit_mailbox_empty_interrupt =0,
	FIFO_0_message_pending_interrupt,
	FIFO_0_full_interrupt,
	FIFO_0_overrun_interrupt,
	FIFO_1_message_pending_interrupt,
	FIFO_1_full_interrupt,
	FIFO_1_overrun_interrupt,
	Error_warning_interrupt =8,
	Error_passive_interrupt,
	Bus_off_interrupt,
	Last_error_code_interrupt,
	Error_interrupt =15,
	Wakeup_interrupt,
	Sleep_interrupt,

}CAN_Interrupts;

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
void CAN_InitInterrupt(CAN_Interrupts Copy_Can_Interrupt);

void CAN1_TX_voidSetCallBack( void (* ptr) (void) );
void CAN1_RX0_voidSetCallBack( void (* ptr) (void) );
void CAN1_RX1_voidSetCallBack( void (* ptr) (void) );
void CAN1_SCE_voidSetCallBack( void (* ptr) (void) );
/*******************************************************************************************/
/*Hagras*/

typedef enum
{
	StandardIdentifier,
	ExtendedIdentifier
}CAN_Identifier_Extension_TypeDef;

typedef enum
{
	DataFrame,
	RemoteFrame
}CAN_Remote_Transmission_Request_TypeDef;

typedef enum
{
	ByIdentifier,
	Chronologically
}CAN_Transmit_FIFO_Priority_TypeDef;

typedef enum
{
	Mask,
	Identifier
}CAN_Filter_Mode_TypeDef;

typedef enum
{
	Dual16Bit,
	Single32Bit
}CAN_Filter_Scale_TypeDef;

typedef enum
{
	FIFO0,
	FIFO1
}CAN_Filter_FIFO_Assignment_TypeDef;

typedef enum
{
	NotActive,
	Active
}CAN_Filter_Active_TypeDef;

typedef union
{
	u32 value;
	struct
	{
		u8 Def0	: 1;
		CAN_Remote_Transmission_Request_TypeDef RTR	: 1;
		CAN_Identifier_Extension_TypeDef IDE		: 1;
		u32 Blank	: 18;
		u32 STD_ID	: 11;
	}standardID_32Bit;

	struct
	{
		u8 Def0 	: 1;
		CAN_Remote_Transmission_Request_TypeDef RTR	: 1;
		CAN_Identifier_Extension_TypeDef IDE		: 1;
		u32 EXD_ID	: 29;
	}exd_ID;
}Filter_Bank_32_BIT_TypeDef;

typedef union
{
	u16 value;
	struct
	{
		u8 ExdID	: 3;
		CAN_Identifier_Extension_TypeDef IDE		: 1;
		CAN_Remote_Transmission_Request_TypeDef RTR	: 1;
		u32 StdID	: 11;
	}std_ID_16;
}Filter_Bank_16_BIT_TypeDef;

typedef struct
{
	Filter_Bank_16_BIT_TypeDef ID1_16bit;
	Filter_Bank_16_BIT_TypeDef Mask_OR_ID2_16bit;
}Dual_Filter_TypeDef;

typedef struct
{
	union
	{
		Filter_Bank_32_BIT_TypeDef SingleFilter;
		Dual_Filter_TypeDef DualFilter;
	}FxR1Value;

	union
	{
		Filter_Bank_32_BIT_TypeDef SingleFilter;
		Dual_Filter_TypeDef DualFilter;
	}FxR2Value;

}Filter_Bank_TypeDef;


typedef struct
{
	u8 filterNumber;
	CAN_Filter_Mode_TypeDef FilterMode;
	CAN_Filter_Scale_TypeDef FilterScale;
	CAN_Filter_FIFO_Assignment_TypeDef FIFOAssignment;
	CAN_Filter_Active_TypeDef FilterActivity;
	Filter_Bank_TypeDef FilterVal;

}CAN_Filter_Header_TypeDef;


typedef struct
{
	u32 ID;																	/*The LSBs of the extended identifier*/
	CAN_Identifier_Extension_TypeDef IdentifierExtension;					/*This bit defines the identifier type of message in the mailbox*/
	CAN_Remote_Transmission_Request_TypeDef  RemoteTransmissionRequest;		/*Remote transmission request*/
}CAN_Tx_Header_TypeDef;

u8 CAN_Filters_Init(CAN_Filter_Header_TypeDef* FiltersArray, u8 arraySize);

#endif /* CAN_INTERFACE_H_ */
