
#include "STD_TYPES.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "CAN_interface.h"


int main()
{
	/*Initialize struct*/
	CAN_Init_t Initialize_struct;
	Initialize_struct.No_Of_Can1Filters = 1;
	Initialize_struct.Filter_Scale= Single_32_bit_scale;
	Initialize_struct.No_Of_Filters_For_FIFO_ZERO =1;
	Initialize_struct.No_Of_Filters_In_List_Mode =0;

	RCC_voidInitSystemClock();
	RCC_voidEnableCompClk(RCC_APB1,RCC_APB1_CAN1);
	RCC_voidEnableCompClk(RCC_AHB1,RCC_AHB1_GPIOA);
	NVIC_Init();

	/*LED test pin*/
	GPIO_voidSetPinDirection(GPIOA,0,OUTPUT_PUSH_PULL_NO_PUPD_FAST_SPEED);


	/*Enable CAN1 Rx pin*/
	GPIO_voidSetPinDirection(GPIOA,11,ALTERNATING_FUNCTION_OPEN_DRAIN_WITH_PU_MEDIUM_SPEED);
	/*Enable CAN1 Tx pin*/
	GPIO_voidSetPinDirection(GPIOA,12,ALTERNATING_FUNCTION_PUSH_PULL_WITH_PU_MEDIUM_SPEED);
	/*Set alternating function*/
	GPIO_voidSetAlternatingFunction(GPIOA,11,AF9);
	GPIO_voidSetAlternatingFunction(GPIOA,12,AF9);

	/*Initialize CAN1*/
	CAN_voidInitialize(&Initialize_struct);

	/*Transmit struct*/
	CAN_frame_t message;
	message.DataLength = Two_Bytes;
	message.FrameType=Data_frame;
	message.ID_Type=Standarad_ID;
	message.ID= 0x100;

	u8 message_arr[]= {'a','b'};

	/*Received data struct*/
	CAN_Receive_t received_data;
	CAN_voidTransmit(&message, message_arr);
	while(1)
	{

		CAN_voidReceive(&received_data);
        if( (u8)(received_data.Message[0]) ==  (u8) 'a' )
		{
        	if( (received_data.Message[1]) == (u8) 'b' )
			{
        		GPIO_voidSetPinValue(GPIOA,0,GPIO_HIGH);
			}

		}
	}

}


