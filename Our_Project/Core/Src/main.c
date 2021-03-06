/************* <<<<<<<<   Application code for our Graduation Project   >>>>>>>> *************
 * Embedded-Team members:
 * Abd El-Rahman Ramzy
 * Ahmed Noaman
 * Khaled Hagras
 * Omar El-Masry
 * Reem Muhammad
 * */

/**
 * What has been tested: running thw two motors and reading the angular velocity.
 * -So far, this code runs two motors in the start, update their PWM values if a command is received by
 * the UART interrupt.
 * -The command bytes sequence should be: 'r' , (RightMotor_PWM_value) , 'l' , (LeftMotor_PWM_value)
 * -The values from the two encoders are read every 1 second
 * -We get the angular velocities (radians per second) and save it in global variables
 */

#include "STD_TYPES.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "Timer_interface.h"
#include "USART_interface.h"

/*The declaration for the standard absolute function*/
s32 abs (s32 x);

/*Constant for conversion from rpm to */
const f64 rpm_to_radians = 0.10471975512;

/*Global variables for angular velocities (radians per second) for the two motors*/
f64 right_radian_per_second =0;
f64 left_radian_per_second  =0;

u8 PWM_right_motor= 10;
u8 PWM_left_motor= 10;

void readEncoder(void)
{
	static u32 last_local_u32_right_motor=0;
	static u32 last_local_u32_left_motor=0;
	u32 right_local_u32_motor=0;
	u32 left_local_u32_motor=0;

	right_local_u32_motor= TimerX_GetCount(TIMER_2_);
	left_local_u32_motor = TimerX_GetCount(TIMER_4_);

	/*Get rpm:
	 * get no. of revolutions per second by dividing the counter value by 1600
	 * get the rpm by multiplying by 60
	 * */
	right_radian_per_second = ((abs( (s32) right_local_u32_motor - (s32) last_local_u32_right_motor)/1600.0) *60);
	left_radian_per_second  = ((abs( (s32) left_local_u32_motor - (s32) last_local_u32_left_motor)/1600.0) *60);

	/*Convert from rpm to radians*/
	right_radian_per_second = right_radian_per_second * rpm_to_radians;
	left_radian_per_second  = left_radian_per_second  * rpm_to_radians;

	/*For proper operation clear the timers counters if they reached 64000 before the next revolution*/
	if(right_local_u32_motor >= 32000)
	{
		TimerX_ClearCounter(TIMER_2_);
		right_local_u32_motor = 0;
	}
	if(left_local_u32_motor >= 32000)
	{
		TimerX_ClearCounter(TIMER_4_);
		left_local_u32_motor = 0;
	}

	last_local_u32_right_motor = right_local_u32_motor;
	last_local_u32_left_motor  = left_local_u32_motor;

}


void getVelocity()
{
	static u8 last_byte_index= 0;
	u8 local_u8_data= MSUART_u8ReadDataRegister(2);

	switch(local_u8_data)
	{
		case 'r':
			last_byte_index = local_u8_data;
			break;
		case 'l':
			last_byte_index = local_u8_data;
			break;
		default:
			last_byte_index = 0;
			break;

	}

	if(local_u8_data != 'r' && local_u8_data != 'l')
	{
		if(last_byte_index == 'r'  )
		{
			PWM_right_motor = local_u8_data;
		}
		else if(last_byte_index == 'l' )
		{
			PWM_left_motor = local_u8_data;
		}
	}
}


int main(void)
{

	/*The initialization struct for UART 3*/
	USART_Init_struct Uart_t_Initialization;
	/*2 stands for USART 3 */
	Uart_t_Initialization.UartNo= 2;
	Uart_t_Initialization.Word_Length= Data_9_Bits;
	Uart_t_Initialization.Parity= Odd_Parity;
	Uart_t_Initialization.Baud_Rate= BaudRate_19200;
	Uart_t_Initialization.Stop_Bits= One_Stop_Bit;
	Uart_t_Initialization.Mode= Asynchronous;

	/*Initialize system clock*/
	RCC_voidInitSystemClock();

	/*Enable clock for the used peripheral*/
	/*Enable clock for GPIOA, GPIOB, GPIOC*/
	RCC_voidEnableCompClk(RCC_AHB1,RCC_AHB1_GPIOA);
	RCC_voidEnableCompClk(RCC_AHB1,RCC_AHB1_GPIOB);
	RCC_voidEnableCompClk(RCC_AHB1,RCC_AHB1_GPIOC);
	RCC_voidEnableCompClk(RCC_AHB1,RCC_AHB1_GPIOD);

	/*Enable clock for Timers from 2 to 5*/
	RCC_voidEnableCompClk(RCC_APB1,RCC_APB1_TIM2);
	RCC_voidEnableCompClk(RCC_APB1,RCC_APB1_TIM3);
	RCC_voidEnableCompClk(RCC_APB1,RCC_APB1_TIM4);
	RCC_voidEnableCompClk(RCC_APB1,RCC_APB1_TIM5);

	/*Enable clock for UART 3*/
	RCC_voidEnableCompClk(RCC_APB1,RCC_APB1_USART3);

	/*Direction pins*/
	/*Right motor */
	GPIO_voidSetPinDirection(GPIOC,PIN7,OUTPUT_PUSH_PULL_NO_PUPD_MEDIUM_SPEED);
	GPIO_voidSetPinDirection(GPIOB,PIN10,OUTPUT_PUSH_PULL_NO_PUPD_MEDIUM_SPEED);
    /*Left motor */
    GPIO_voidSetPinDirection(GPIOB,PIN3,OUTPUT_PUSH_PULL_NO_PUPD_MEDIUM_SPEED);
    GPIO_voidSetPinDirection(GPIOD,PIN2,OUTPUT_PUSH_PULL_NO_PUPD_MEDIUM_SPEED);

	/*Set alternating functions pins*/
	/*PWM Pins*/
    /*Right motor*/
    GPIO_voidSetPinDirection(GPIOB,PIN5,ALTERNATING_FUNCTION_PUSH_PULL_WITH_PU_MEDIUM_SPEED);
    /*Left motor*/
	GPIO_voidSetPinDirection(GPIOB,PIN4,ALTERNATING_FUNCTION_PUSH_PULL_WITH_PU_MEDIUM_SPEED);

	GPIO_voidSetAlternatingFunction(GPIOB,PIN5,AF2);
	GPIO_voidSetAlternatingFunction(GPIOB,PIN4,AF2);


	/*UART3 Pins*/
	GPIO_voidSetPinDirection(GPIOC,PIN10,ALTERNATING_FUNCTION_PUSH_PULL_WITH_PU_MEDIUM_SPEED);
	GPIO_voidSetPinDirection(GPIOC,PIN11,ALTERNATING_FUNCTION_PUSH_PULL_NO_PUPD_MEDIUM_SPEED);
	GPIO_voidSetAlternatingFunction(GPIOC,PIN10,AF7);
	GPIO_voidSetAlternatingFunction(GPIOC,PIN11,AF7);

	/*Encoder pins*/
	/*Right motor encoder pins*/
	GPIO_voidSetPinDirection(GPIOA,PIN0,ALTERNATING_FUNCTION_OPEN_DRAIN_NO_PUPD_MEDIUM_SPEED);
	GPIO_voidSetPinDirection(GPIOA,PIN1,ALTERNATING_FUNCTION_OPEN_DRAIN_NO_PUPD_MEDIUM_SPEED);
	GPIO_voidSetAlternatingFunction(GPIOA,PIN0,AF1);
	GPIO_voidSetAlternatingFunction(GPIOA,PIN1,AF1);

	/*Left motor encoder pins*/
	GPIO_voidSetPinDirection(GPIOB,PIN6,ALTERNATING_FUNCTION_OPEN_DRAIN_NO_PUPD_MEDIUM_SPEED);
	GPIO_voidSetPinDirection(GPIOB,PIN7,ALTERNATING_FUNCTION_OPEN_DRAIN_NO_PUPD_MEDIUM_SPEED);
	GPIO_voidSetAlternatingFunction(GPIOB,PIN6,AF2);
	GPIO_voidSetAlternatingFunction(GPIOB,PIN7,AF2);

	/*Initialize NVIC*/
	NVIC_Init();

	/*Initialize UART 3*/
	MUSART_voidInit(&Uart_t_Initialization);
	/*Enable UART receive interrupt*/
	MSUART_voidInterrupt(2,USART_RxDataNotEmptyInt,USART_Interrupt_Enable);
	/*Get the PWM value for the motors velocity from the received data from UART*/
	MUSART3_voidSetCallBack(getVelocity);

	/*Write direction*/
	/*Right motor*/
	GPIO_voidSetPinValue(GPIOC,PIN7,GPIO_HIGH);
	GPIO_voidSetPinValue(GPIOB,PIN10,GPIO_LOW);
	/*Left motor*/
	GPIO_voidSetPinValue(GPIOB,PIN3,GPIO_HIGH);
	GPIO_voidSetPinValue(GPIOD,PIN2,GPIO_LOW);

	/*Enable encoder mode on timer 2 for right motor */
	TimerX_EncoderMode(TIMER_2_);
	/*Enable encoder mode on timer 4 for left motor */
	TimerX_EncoderMode(TIMER_4_);

	/*Enable timer 3 to generate an interrupt every 1 sec*/
	TimerX_Count(TIMER_5_,UP_COUNTER,1000);
	/*Get the angular velocity from encoder every 1 sec*/
	Timer5_voidSetCallBack(readEncoder);

	/*Initialize PWM on right motor with duty cycle 20% as a start*/
	TimerX_PWM(TIMER_3_,CH2,20);
	/*Initialize PWM on left motor with duty cycle 20% as a start*/
	TimerX_PWM(TIMER_3_,CH1,20);

	while(1)
	{
		TimerXChangeDutyCycleOfPWM(TIMER_3_,CH2,PWM_right_motor);
		TimerXChangeDutyCycleOfPWM(TIMER_3_,CH1,PWM_left_motor);
	}

	return 1;
}
