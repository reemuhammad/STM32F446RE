/*
 * Timer_program.c
 *
 *  Created on: May 6, 2022
 *      Author: Reem
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "Timer_interface.h"
#include "Timer_private.h"
#include "Timer_config.h"



void TimerX_Count(Timer_No_e Copy_e_Timer,Timer_AlignmentMode_e Copy_e_Mode, u32 Copy_u32_MilliSeconds )
{
	/*Reset Timer Registers */
	TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1 = 0x0000;

	/*Choose Edge-Aligned or Center-Aligned mode */
	switch(Copy_e_Mode)
	{
	case UP_COUNTER:
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_DIR);
		break;
	case DOWN_COUNTER:
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_DIR);
		break;
	case CENTER_ALIGNED_MODE_1:
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_CMS_0);
		break;
	case CENTER_ALIGNED_MODE_2:
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_CMS_1);
		break;
	case CENTER_ALIGNED_MODE_3:
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_CMS_0);
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_CMS_1);
		break;
	default:
		break;
	}

	/*Set timer prescaler*/
	TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_PSC = ((BUS_FREQUENCY/TICKS_FREQUENCY) -1) ;
	/*Set Auto-Reload value*/
	TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_ARR = ((Copy_u32_MilliSeconds /1000) * TICKS_FREQUENCY);

	/*Enable Timer */
	Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_CEN);
}


void TimerX_ExternalCounterOnETR(Timer_No_e Copy_e_Timer, u16 Copy_u16_Counts)
{
	/***This funtion uses ETR pin as external input for the timer in both external modes***/

	/*Reset timer slave mode control register to the default values
	 * NO External trigger prescaler and NO External trigger filter*/
	TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_SMCR = 0x0000;

	/*Set counter direction to UP counter*/
	Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_DIR);

	/*Set Auto-Reload value : Number of counts needed to generate overflow*/
	TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_ARR = Copy_u16_Counts;

	/*Choose external trigger polarity to be rising edge*/
	Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_SMCR, TIMx_SMCR_ETP);

	/*Set external trigger filter*/
	TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_SMCR |= EXTERNAL_TRIGGER_FILTER <<TIMx_SMCR_ETF_0 ;

	/*Enable update interrupt*/
	Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_DIER, TIMx_DIER_UIE);

	#if EXTERNAL_MODE == External_Mode_One
	/*Select external trigger input (ETRF) pin as trigger selection */
	TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_SMCR |= 0b111 << TIMx_SMCR_TS_0;
	/*Enable external clock mode 1 */
	TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_SMCR |= 0b111 << TIMx_SMCR_SMS_0;

	#elif EXTERNAL_MODE == External_Mode_Two
	/*Enable external clock mode 2 */
	Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_SMCR, TIMx_SMCR_ECE);
    #endif

	/*Enable Timer */
	Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_CEN);
}

void TimerX_PWM(Timer_No_e Copy_e_Timer, Timer_Channl_e Copy_e_Channel, u8 Copy_u8_DutyCycle)
{
	/* The polarity of the pwm signal is remained at the default of active high
	 * The pwm mode is working at the default UP counting (channel is active as long as TIMx_CNT<TIMx_CCR1 )
	 * PWM mode 1 */

	/*Set the timer on UP counting, edge-aligned mode*/
	Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_DIR);
	Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_CMS_0);
	Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_CMS_1);

	/*Set the auto-reload preload bit for ARR*/
	Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_ARPE);

	/*Set the ARR value to maximum*/
	TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_ARR = 0xffff;

	/*Set timer prescaler: for a pwm frequency of 100 Hz */
	TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_PSC = ((BUS_FREQUENCY/ (0xffff * PWM_FREQUENCY)) -1) ;

	switch(Copy_e_Channel)
	{
	case CH1:
		/*Select output mode for channel 1*/
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_CC1S_0);
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_CC1S_1);
		/*Select the polarity to active high*/
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC1P);
		/*Choose PWM mode 1*/
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_OC1M_0);
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_OC1M_1);
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_OC1M_2);
		/*Set the duty cycle*/
		TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCR1 = ( (0xffff * Copy_u8_DutyCycle) /100 );
		/*Set the preload bit*/
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_OC1PE);
		/*Enable capture compare*/
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC1E);
		break;
	case CH2:
		/*Select output mode for channel 2*/
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_CC2S_0);
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_CC2S_1);
		/*Select the polarity to active high*/
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC2P);
		/*Choose PWM mode 1*/
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_OC2M_0);
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_OC2M_1);
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_OC2M_2);
		/*Set the duty cycle*/
		TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCR2 = ( (0xffff * Copy_u8_DutyCycle) /100 );
		/*Set the preload bit*/
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_OC2PE);
		/*Enable capture compare*/
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC2E);
		break;
	case CH3:
		/*Select output mode for channel 3*/
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR2, TIMx_CCMR2_CC3S_0);
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR2, TIMx_CCMR2_CC3S_1);
		/*Select the polarity to active high*/
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC3P);
		/*Choose PWM mode 1*/
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR2, TIMx_CCMR2_OC3M_0);
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR2, TIMx_CCMR2_OC3M_1);
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR2, TIMx_CCMR2_OC3M_2);
		/*Set the duty cycle*/
		TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCR3 = ( (0xffff * Copy_u8_DutyCycle) /100 );
		/*Set the preload bit*/
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR2, TIMx_CCMR2_OC3PE);
		/*Enable capture compare*/
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC3E);
		break;
	case CH4:
		/*Select output mode for channel 4*/
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR2, TIMx_CCMR2_CC4S_0);
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR2, TIMx_CCMR2_CC4S_1);
		/*Select the polarity to active high*/
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC4P);
		/*Choose PWM mode 1*/
		Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR2, TIMx_CCMR2_OC4M_0);
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR2, TIMx_CCMR2_OC4M_1);
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR2, TIMx_CCMR2_OC4M_2);
		/*Set the duty cycle*/
		TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCR4 = ( (0xffff * Copy_u8_DutyCycle) /100 );
		/*Set the preload bit*/
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR2, TIMx_CCMR2_OC4PE);
		/*Enable capture compare*/
		Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC4E);
		break;
	default:
		break;
	}

	/*Initialize all counters*/
	Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_EGR, TIMx_EGR_UG);
	/*Enable Timer */
	Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_CEN);
}

void TimerX_EncoderMode(Timer_No_e Copy_e_Timer)
{
	/*Map IC1 on TI1*/
	Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_CC1S_0);
	Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_CC1S_1);
	/*Map IC2 on TI2*/
	Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_CC2S_0);
	Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_CC2S_1);
	/*Circuit is sensitive to TI1FP1 rising edge*/
	Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC1P);
	Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC1NP);
	/*No filter on IC1*/
	TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1 &= ~( 0b1111 << TIMx_CCMR1_IC1F_0);
	/*Circuit is sensitive to TI2FP1 rising edge*/
	Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC2P);
	Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC2NP);
	/*No filter on IC2*/
	TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CCMR1 &= ~( 0b1111 << TIMx_CCMR1_IC2F_0);
	/*Select encoder mode 3*/
	Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_SMCR, TIMx_SMCR_SMS_0);
	Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_SMCR, TIMx_SMCR_SMS_1);
	Clr_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_SMCR, TIMx_SMCR_SMS_2);
	/*Enable Timer */
	Set_Bit(TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_CEN);
}
