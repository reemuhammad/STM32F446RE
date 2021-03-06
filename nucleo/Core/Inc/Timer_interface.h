/*
 * Timer_interface.h
 *
 *  Created on: May 6, 2022
 *      Author: Reem
 *      version: 1
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

typedef enum {
	/* Choose general purpose timer number (from 2 to 5) from here */
	TIMER_2_,
	TIMER_3_,
	TIMER_4_,
	TIMER_5_

}Timer_No_e;

typedef enum{
	/* Choose timer channel from here*/
	CH1,
	CH2,
	CH3,
	CH4

}Timer_Channl_e;

typedef enum{
	/* Choose Alignment Mode [Edge-aligned (Up/Down) / Center-aligned (mode 1/2/3)] */


	UP_COUNTER,
	/* 1) the counter counts from 0 to the auto-reload value */

	DOWN_COUNTER,
	/* 2) the counter counts from the auto-reload value down to 0 */

	CENTER_ALIGNED_MODE_1,
	/* 3) The counter counts up and down alternatively.Output compare interrupt
	 * flags of channels configured in output set only when the counter is counting down.*/

	CENTER_ALIGNED_MODE_2,
	/* 4) The counter counts up and down alternatively.Output compare interrupt
	 * flags of channels configured in output set only when the counter is counting up.*/

	CENTER_ALIGNED_MODE_3
	/* 5) The counter counts up and down alternatively.Output compare interrupt
	 * flags of channels configured in output set both when the counter is counting up or down.*/

}Timer_AlignmentMode_e;

void TimerX_Count(Timer_No_e Copy_e_Timer,Timer_AlignmentMode_e Copy_e_Mode, u32 Copy_u32_MilliSeconds );
/* @function: counts for a time of Milli-Seconds using a timer from 2 to 5.
 * @parameters:
 * 		1- Timer Number (from 2 to 5): choose from  ( Timer_No_e ) enum.
 * 		2- Alignment Mode [Edge-aligned (Up/Down) / Center-aligned (mode 1/2/3)]: choose from  ( Timer_AlignmentMode_e ) enum.
 * 		3- Time of update event in milli-seconds.
 * @return: None.
 * */
u32 TimerX_GetCount(Timer_No_e Copy_e_Timer);
/* @function: Get counts for a time of Ticks using a timer from 2 to 5.
 * @parameters:
 * 		1- Timer Number (from 2 to 5): choose from  ( Timer_No_e ) enum.
 * @return: None.
 * */

void TimerX_ExternalCounterOnETR(Timer_No_e Copy_e_Timer, u16 Copy_u16_Counts);
/* @function: use ETR pin as external input to the counter and generate an interrupt after certain
 * number of counts.
 * @parameters:
 * 		1- Timer Number (from 2 to 5): choose from  ( Timer_No_e ) enum.
 * 		2- Number of counts needed to generate an interrupt.
 * 	@return: None.
 * 	NOTE: extra configurations for the function are in <Timer_config.h> file.
 */

void TimerX_PWM(Timer_No_e Copy_e_Timer, Timer_Channl_e Copy_e_Channel,u8 Copy_u8_DutyCycle);
/*@function:Choose a channel in a selected timer to work in PWM mode given its duty cycle, under a time period
 * determined by the chosen frequency in <Timer_config.h> file.
 *@parameters:
 *		1- Timer Number (from 2 to 5): choose from  ( Timer_No_e ) enum.
 *		2- Channel for the timer: choose from  ( Timer_Channl_e ) enum.
 *		3- Duty cycle in Percentage %.
 *@return: None
 */

void TimerX_EncoderMode(Timer_No_e Copy_e_Timer);
/*@function: Enable the timer in encoder hardware mode.
 *@parameters: Timer Number (from 2 to 5): choose from  ( Timer_No_e ) enum.
 *@return: None
 */

//void TimerX_ExternalCounterOnTIxPin(Timer_No_e Copy_e_Timer, u16 Copy_u16_Counts);
void Timer3_voidSetCallBack( void (* ptr) (void) );
void TimerX_Clearflag(Timer_No_e Copy_e_Timer);

#endif /* TIMER_INTERFACE_H_ */
