/*
 * CAN_program.c
 *
 *  Created on: May 7, 2022
 *      Author: Reem
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "CAN_interface.h"
#include "CAN_private.h"
#include "CAN_config.h"


void CAN_voidInitialize(CAN_Init_t * Copy_t_Init)
{
	/*Reset the registers*/
	CAN_CONTROL_AND_STATUS->CAN_MCR =0x02;

	/*Stop the freeze while debug*/
	CLR_BIT(CAN_CONTROL_AND_STATUS->CAN_MCR,CAN_MCR_DBF);
	/*The default used values are:
	 * fifo priority driven by identifier of the message*/

	/*Automatic bus-off management:The Bus-Off state is left automatically by hardware once
	 * 128 occurrences of 11 recessive bits have been monitored.*/
	SET_BIT(CAN_CONTROL_AND_STATUS->CAN_MCR,CAN_MCR_ABOM);

	/*Automatic wakeup mode: The Sleep mode is left automatically by hardware on CAN message detection*/
	SET_BIT(CAN_CONTROL_AND_STATUS->CAN_MCR,CAN_MCR_AWUM);

	/*Request to enter Initialization mode*/
	SET_BIT(CAN_CONTROL_AND_STATUS->CAN_MCR,CAN_MCR_INRQ);

	/*Exit sleep mode*/
	CLR_BIT(CAN_CONTROL_AND_STATUS->CAN_MCR,CAN_MCR_SLEEP);

	while( (!GET_BIT(CAN_CONTROL_AND_STATUS->CAN_MSR,CAN_MSR_INAK)) || (GET_BIT(CAN_CONTROL_AND_STATUS->CAN_MSR,CAN_MSR_SLAK)) )
	{
		/*Do nothing until initialization mode is entered*/
	}

	/*For 1Mbps , and bus frequency of 16 MHz , total number of 8 quantas and SJW =1*/
	CAN_CONTROL_AND_STATUS->CAN_BTR = 0x00050001;

	/*enable message pending in FIFO0 interrupt if configured*/
	if(FIFO0_RECEIVE_INTERRUPT == ENABLE)
	{
		SET_BIT(CAN_CONTROL_AND_STATUS->CAN_IER,CAN_IER_FMPIE0);
	}
	/*enable message pending in FIFO1 interrupt if configured*/
	if(FIFO1_RECEIVE_INTERRUPT == ENABLE)
	{
		SET_BIT(CAN_CONTROL_AND_STATUS->CAN_IER,CAN_IER_FMPIE1);
	}
	/*Enable lock back mode if configured */
	if(LOCK_BACK_MODE == ENABLE)
	{
		SET_BIT(CAN_CONTROL_AND_STATUS->CAN_BTR,CAN_BTR_LBKM);
	}
	/*Enable lock back combined with silent mode if configured */
	if(LOCK_BACK_COMBINED_WITH_SILENT_MODE == ENABLE)
	{
		SET_BIT(CAN_CONTROL_AND_STATUS->CAN_BTR,CAN_BTR_LBKM);
		SET_BIT(CAN_CONTROL_AND_STATUS->CAN_BTR,CAN_BTR_SILM);
	}


	/*------------------------------------Filters Initialization------------------------------------*/
	/*Enter filters initialization mode*/
	SET_BIT(CAN_FMR,CAN_FMR_FINIT);

	/*Reset mode register*/
	CAN_FM1R=0x0000;

	/*Assign all filters to one CAN*/
	CAN_FMR &= ~(0b111111<< (CAN_FMR_CANSB));


	/*Choose scale mode*/
	if(Copy_t_Init->Filter_Scale == Dual_16_bit_scale)
	{
		CAN_FS1R = 0x0000;
	}
	else if(Copy_t_Init->Filter_Scale == Single_32_bit_scale)
	{
		CAN_FS1R = 0x7fffff;
	}

	/*Set the filters that are in List mode*/
	for(u8 filter_number=0; filter_number < (Copy_t_Init->No_Of_Filters_In_List_Mode) ; filter_number++)
	{
		SET_BIT(CAN_FM1R,filter_number);
	}

	/*Set the filters assigned to FIFO_0*/
	for(u8 filter_number=0; filter_number < (Copy_t_Init->No_Of_Can1Filters) ; filter_number++)
	{
		if( filter_number < (Copy_t_Init->No_Of_Filters_For_FIFO_ZERO) )
		{
			CLR_BIT(CAN_FFA1R,filter_number);
		}
		else if( filter_number >= (Copy_t_Init->No_Of_Filters_For_FIFO_ZERO) )
		{
			SET_BIT(CAN_FFA1R,filter_number);
		}
	}

	/*Write the ID or mask as configured in "CAN_config.h"*/
	for(u8 filter_number=0; filter_number < (Copy_t_Init->No_Of_Can1Filters) ; filter_number++)
	{
		*Filter_Bank[filter_number*2] = Filter_Banks_Config[filter_number*2];
		*Filter_Bank[(filter_number*2)+1] = Filter_Banks_Config[(filter_number*2)+1];
	}

	/*Activate all the needed filters*/
	for(u8 filter_number=0; filter_number < (Copy_t_Init->No_Of_Can1Filters) ; filter_number++)
	{
		SET_BIT(CAN_FA1R,filter_number);
	}

	/*Set normal mode for filters*/
	CLR_BIT(CAN_FMR,CAN_FMR_FINIT);
	/*------------------------------------------------------------------------------------------------*/

	/*Reset transmit data registers*/
	CAN_MAILBOX->CAN_TDL0R =0;
	CAN_MAILBOX->CAN_TDH0R =0;
	CAN_MAILBOX->CAN_TDL1R =0;
	CAN_MAILBOX->CAN_TDH1R =0;
	CAN_MAILBOX->CAN_TDL2R =0;
	CAN_MAILBOX->CAN_TDH2R =0;

	/*Enter Normal mode*/
	CLR_BIT(CAN_CONTROL_AND_STATUS->CAN_MCR,CAN_MCR_INRQ);
	/*Exit sleep mode*/
	CLR_BIT(CAN_CONTROL_AND_STATUS->CAN_MCR,CAN_MCR_SLEEP);

	while(GET_BIT(CAN_CONTROL_AND_STATUS->CAN_MSR,CAN_MSR_INAK))
	{
		/*Do nothing until normal mode is entered*/
	}
}

/*****************************************************************************************************************/
/*****************************************************************************************************************/

void CAN_voidTransmit(CAN_frame_t * Copy_t_frame, u8 * Copy_ptr_u8_Message)
{
	u8 Data_Length = Copy_t_frame->DataLength;

	/*If Transmit mailbox 0 is empty*/
	if( GET_BIT(CAN_CONTROL_AND_STATUS->CAN_TSR,CAN_TSR_TME0) == 1 )
		{
			/*Clear CAN mailbox data length control and time stamp register*/
			CAN_MAILBOX->CAN_TDT0R =0;
			/*Clear mailbox identifier register */
			CAN_MAILBOX->CAN_TI0R =0;

			/*Choose number of bytes*/
			CAN_MAILBOX->CAN_TDT0R |= Data_Length;

			if(Copy_t_frame->FrameType == Data_frame)
			{
				/*Choose RTR for data frame*/
				CLR_BIT(CAN_MAILBOX->CAN_TI0R,CAN_TIxR_RTR );

				/*Write Data bytes */
				if(Data_Length <= 4)
				{
					for(u8 counter=0; counter < Data_Length; counter++)
					{
						CAN_MAILBOX->CAN_TDL0R |= ( Copy_ptr_u8_Message[counter] << (counter*8) );
					}
				}
				else if(Data_Length >= 5)
				{
					/*Write Data bytes */
					for(u8 counter=0; counter < 4; counter++)
					{
						CAN_MAILBOX->CAN_TDL0R |= Copy_ptr_u8_Message[counter] << (counter*8);
					}

					for(u8 counter=0; counter < Data_Length-4; counter++)
					{
						CAN_MAILBOX->CAN_TDH0R |= Copy_ptr_u8_Message[counter+4] << (counter*8);
					}
				}


			}
			else if(Copy_t_frame->FrameType == Remote_frame )
			{
				/*Choose RTR for remote frame*/
				SET_BIT(CAN_MAILBOX->CAN_TI0R,CAN_TIxR_RTR );
			}

			/*Choose ID type*/
			if(Copy_t_frame->ID_Type == Standarad_ID)
			{
				CLR_BIT(CAN_MAILBOX->CAN_TI0R,CAN_TIxR_IDE );
				/*Write ID*/
				CAN_MAILBOX->CAN_TI0R |= (Copy_t_frame->ID) << CAN_TIxR_STID;

			}

			else if(Copy_t_frame->ID_Type == Extended_ID)
			{
				SET_BIT(CAN_MAILBOX->CAN_TI0R,CAN_TIxR_IDE );
				/*Write ID*/
				CAN_MAILBOX->CAN_TI0R |= (Copy_t_frame->ID) << CAN_TIxR_EXID;
			}

			/*Transmit mailbox request*/
			SET_BIT(CAN_MAILBOX->CAN_TI0R,CAN_TIxR_TXRQ);
		}
/*------------------------------------------------------------------------------------------------------*/
	/*Else if Transmit mailbox 1 is empty*/
	else if(GET_BIT(CAN_CONTROL_AND_STATUS->CAN_TSR,CAN_TSR_TME1) == 1)
		{
			/*Clear CAN mailbox data length control and time stamp register*/
			CAN_MAILBOX->CAN_TI1R =0;
			/*Clear mailbox identifier register */
			CAN_MAILBOX->CAN_TI1R =0;

			/*Choose number of bytes*/
			CAN_MAILBOX->CAN_TDT1R |= Data_Length;

			if(Copy_t_frame->FrameType == Data_frame)
			{
				/*Choose RTR for data frame*/
				CLR_BIT(CAN_MAILBOX->CAN_TI1R,CAN_TIxR_RTR );

				/*Write Data bytes */
				if(Data_Length <= 4)
				{
					for(u8 counter=0; counter < Data_Length; counter++)
					{
						CAN_MAILBOX->CAN_TDL1R |= ( Copy_ptr_u8_Message[counter] << (counter*8) );
					}
				}
				else if(Data_Length >= 5)
				{
					/*Write Data bytes */
					for(u8 counter=0; counter < 4; counter++)
					{
						CAN_MAILBOX->CAN_TDL1R |= Copy_ptr_u8_Message[counter] << (counter*8);
					}

					for(u8 counter=0; counter < Data_Length-4; counter++)
					{
						CAN_MAILBOX->CAN_TDH1R |= Copy_ptr_u8_Message[counter+4] << (counter*8);
					}
				}

			}
			else if(Copy_t_frame->FrameType == Remote_frame )
			{
				SET_BIT(CAN_MAILBOX->CAN_TI1R,CAN_TIxR_RTR );
			}

			/*Choose ID type*/
			if(Copy_t_frame->ID_Type == Standarad_ID)
			{
				CLR_BIT(CAN_MAILBOX->CAN_TI1R,CAN_TIxR_IDE );
				/*Write ID*/
				CAN_MAILBOX->CAN_TI1R |= (Copy_t_frame->ID) << CAN_TIxR_STID;
			}
			else if(Copy_t_frame->ID_Type == Extended_ID)
			{
				SET_BIT(CAN_MAILBOX->CAN_TI1R,CAN_TIxR_IDE );
				/*Write ID*/
				CAN_MAILBOX->CAN_TI1R |= (Copy_t_frame->ID) << CAN_TIxR_EXID;
			}

			/*Transmit mailbox request*/
			SET_BIT(CAN_MAILBOX->CAN_TI1R,CAN_TIxR_TXRQ);
		}
/*------------------------------------------------------------------------------------------------------*/
	/*Else if Transmit mailbox 2 is empty*/
	else if(GET_BIT(CAN_CONTROL_AND_STATUS->CAN_TSR,CAN_TSR_TME2) == 1)
		{
		/*Clear CAN mailbox data length control and time stamp register*/
		CAN_MAILBOX->CAN_TI2R =0;
		/*Clear mailbox identifier register */
		CAN_MAILBOX->CAN_TI2R=0;

		/*Choose number of bytes*/
		CAN_MAILBOX->CAN_TDT2R |= Data_Length;

			if(Copy_t_frame->FrameType == Data_frame)
			{
				/*Choose RTR for data frame*/
				CLR_BIT(CAN_MAILBOX->CAN_TI2R,CAN_TIxR_RTR );
				/*Write Data bytes */
				if(Data_Length <= 4)
				{
					for(u8 counter=0; counter < Data_Length; counter++)
					{
						CAN_MAILBOX->CAN_TDL2R |= ( Copy_ptr_u8_Message[counter] << (counter*8) );
					}
				}
				else if(Data_Length >= 5)
				{
				/*Write Data bytes */
					for(u8 counter=0; counter < 4; counter++)
					{
						CAN_MAILBOX->CAN_TDL2R |= Copy_ptr_u8_Message[counter] << (counter*8);
					}

					for(u8 counter=0; counter < Data_Length-4; counter++)
					{
						CAN_MAILBOX->CAN_TDH2R |= Copy_ptr_u8_Message[counter+4] << (counter*8);
				    }
				}
			}
			else if(Copy_t_frame->FrameType == Remote_frame )
			{
				/*Choose RTR for remote frame*/
				SET_BIT(CAN_MAILBOX->CAN_TI2R,CAN_TIxR_RTR );
			}

			/*Choose ID type*/
			if(Copy_t_frame->ID_Type == Standarad_ID)
			{
				CLR_BIT(CAN_MAILBOX->CAN_TI2R,CAN_TIxR_IDE );
				/*Write ID*/
				CAN_MAILBOX->CAN_TI2R |= (Copy_t_frame->ID) << CAN_TIxR_STID;
			}
			else if(Copy_t_frame->ID_Type == Extended_ID)
			{
				SET_BIT(CAN_MAILBOX->CAN_TI2R,CAN_TIxR_IDE );
				/*Write ID*/
				CAN_MAILBOX->CAN_TI2R |= (Copy_t_frame->ID) << CAN_TIxR_EXID;
			}

			/*Transmit mailbox request*/
			SET_BIT(CAN_MAILBOX->CAN_TI2R,CAN_TIxR_TXRQ);
		}
/*------------------------------------------------------------------------------------------------------*/
	else
		{
			/*Do nothing*/
		}
}

/*****************************************************************************************************************/
/*****************************************************************************************************************/

void CAN_voidReceive(CAN_Receive_t * Copy_t_ReceivedMessage)
{
	/*If at least a message is pending at FIF00*/
	if((CAN_CONTROL_AND_STATUS->CAN_RF0R & 0x03) != 0)
	{
		/*Get frame type*/
		Copy_t_ReceivedMessage->FrameType = GET_BIT(CAN_MAILBOX->CAN_RI0R,CAN_RIxR_RTR);
		/*Get number of received bytes*/
		Copy_t_ReceivedMessage->DataLength = (0x00fF & (CAN_MAILBOX->CAN_RDT0R));

		/*Read Data bytes */
		if(Copy_t_ReceivedMessage->DataLength <= 4)
		{
			for(u8 counter=0; counter < (Copy_t_ReceivedMessage->DataLength); counter++)
			{
				Copy_t_ReceivedMessage->Message[counter] = 0x00ff & (CAN_MAILBOX->CAN_RDL0R >> (counter*8));
			}
		}
		else if(Copy_t_ReceivedMessage->DataLength >= 5)
		{
		/*Read Data bytes */
			for(u8 counter=0; counter < 4; counter++)
			{
				Copy_t_ReceivedMessage->Message[counter] = 0x00ff & (CAN_MAILBOX->CAN_RDL0R >> (counter*8));
			}

			for(u8 counter=4; counter < (Copy_t_ReceivedMessage->DataLength); counter++)
			{
				Copy_t_ReceivedMessage->Message[counter] = 0x00ff & (CAN_MAILBOX->CAN_RDH0R >> ((counter-4)*8));
			}
		}

		/*Get filter index*/
		Copy_t_ReceivedMessage->FilterIndex = 0x00ff & (CAN_MAILBOX->CAN_RDT0R >>CAN_RDTxR_FMI);
		/*Release FIFO 0 output mailbox after receiving message*/
		SET_BIT(CAN_CONTROL_AND_STATUS->CAN_RF0R,CAN_RF0R_RFOM0);
	}

/*------------------------------------------------------------------------------------------------------*/
	/*Else if at least a message is pending at FIF01*/
	else if((CAN_CONTROL_AND_STATUS->CAN_RF1R & 0x03) != 0)
	{
		/*Get frame type*/
		Copy_t_ReceivedMessage->FrameType = GET_BIT(CAN_MAILBOX->CAN_RI1R,CAN_RIxR_RTR);
		/*Get number of received bytes*/
		Copy_t_ReceivedMessage->DataLength = (0x000F & (CAN_MAILBOX->CAN_RDT1R));
		/*Read Data bytes */
		if(Copy_t_ReceivedMessage->DataLength <= 4)
		{
			for(u8 counter=0; counter < (Copy_t_ReceivedMessage->DataLength); counter++)
			{
				Copy_t_ReceivedMessage->Message[counter] = (u8) (0x000f & (CAN_MAILBOX->CAN_RDL1R >> (counter*8)));
			}
		}
		else if(Copy_t_ReceivedMessage->DataLength >= 5)
		{
			/*Read Data bytes */
			for(u8 counter=0; counter < 4; counter++)
			{
				Copy_t_ReceivedMessage->Message[counter] = (u8) (0x000f & (CAN_MAILBOX->CAN_RDL1R >> (counter*8)));
			}

			for(u8 counter=4; counter < (Copy_t_ReceivedMessage->DataLength); counter++)
			{
				Copy_t_ReceivedMessage->Message[counter] = (u8) (0x000f & (CAN_MAILBOX->CAN_RDH1R >> ((counter-4)*8)));
			}
		}

		/*Get filter index*/
		Copy_t_ReceivedMessage->FilterIndex = (u8) ( 0x000f & (CAN_MAILBOX->CAN_RDT1R >>CAN_RDTxR_FMI) );
		/*Release FIFO 1 output mailbox after receiving message*/
		SET_BIT(CAN_CONTROL_AND_STATUS->CAN_RF1R,CAN_RF1R_RFOM1);
	}
}
/*****************************************************************************************************************/
/*****************************************************************************************************************/
void CAN1_TX_voidSetCallBack( void (* ptr) (void) )
{
	CAN1_TX_CallBack = ptr;
}

void CAN1_TX_IRQHandler(void)
{
	CAN1_TX_CallBack();
}

void CAN1_RX0_voidSetCallBack( void (* ptr) (void) )
{
	CAN1_RX0_CallBack = ptr;
}

void CAN1_RX0_IRQHandler(void)
{
	CAN1_RX0_CallBack();
}

void CAN1_RX1_voidSetCallBack( void (* ptr) (void) )
{
	CAN1_RX1_CallBack = ptr;
}

void CAN1_RX1_IRQHandler(void)
{
	CAN1_RX1_CallBack();
}

void CAN1_SCE_voidSetCallBack( void (* ptr) (void) )
{
	CAN1_SCE_CallBack = ptr;
}

void CAN1_SCE_IRQHandler(void)
{
	CAN1_SCE_CallBack();
}
