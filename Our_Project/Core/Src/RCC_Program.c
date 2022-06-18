/********************************************/	
/* Author: Abdelrahman Ramzi Fahmi				  		*/
/* Date: 07-Nov. 2021									*/
/* Version: 0.1											*/
/********************************************/

/*Include Library Header Files*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*Include SWC Header Files*/
#include "RCC_Interface.h"
#include "RCC_Private.h"
#include "RCC_Config.h"

/*								System Clocks								*/

void RCC_voidInitSystemClock(void){

	
	#if RCC_SYSTEM_CLOCK == RCC_HSE_CRYSTAL
		/* ByPass Bit is off*/
			RCC_CR &= ~(0x00040000);
		/* Enable HSE Clock*/
			RCC_CR |= 0x00010000;
		/* Check when HSE is READY*/
			while(!GET_BIT(RCC_CR,RCC_HSE_READY_BIT));
		/*	Set HSE as System Clock*/
			RCC_CFGR &= ~(0x00000003);		/*Clear Bits*/
			RCC_CFGR |= 0x00000001;			/*Set Bits*/
			
			
	#elif RCC_SYSTEM_CLOCK == RCC_HSE_RC
		/*ByPass Bit is on*/
			RCC_CR |= (0x00040000);
		/*Enable HSE Clock*/
			RCC_CR |= 0x00010000;
		/*Check HSE ready*/
			while(!GET_BIT(RCC_CR,RCC_HSE_READY_BIT));
		/*Set HSE as System Clock*/
			RCC_CFGR &= ~(0x00000003);		/*Clear Bits*/
			RCC_CFGR |= 0x00000001;			/*Set Bits*/
			
			
	#elif RCC_SYSTEM_CLOCK == RCC_HSI_RC
		/* Enable HSI Clock*/
			RCC_CR |= 0x00000001;
		/* Check if HSI is ready*/
			while(!GET_BIT(RCC_CR,RCC_HSI_READY_BIT));
		/*Set HSI as System Clock*/
			RCC_CFGR &= ~(0x00000003);	/*Clear Bits, Set HSI Mode*/

			
	#elif RCC_SYSTEM_CLOCK == RCC_PLL
		/* 	Select Multiplication Factor, Following the equations:
			F(VCO) = F(PLL_INPUT_SOURCE) * [PLLN/PLLM]
			F(PLL Clock Output) = F(VCO) / PLLP
			**	F(VCO) Should be between 100MHz and 432MHz
				where PLLN is between 50 and 432
					  PLLM is between 2 and 63
					  PLLP is 2,4,6 and 8

		/*Selecting PLLN as 56, PLLM as 13, PLLP as 2*/
			/*Clear PLLN Bits Values*/
			RCC_PLLCFGR &= ~(0b111111111<<6);
			/*Set PLLN from configuration*/
			RCC_PLLCFGR |= (PLLN<<6);
			/*Clear PLLM Bits Values*/
			RCC_PLLCFGR &= ~(0b111111);
			/*Set PLLM from configuration*/
			RCC_PLLCFGR |= (PLLM);
			/*Clear PLLP Bits Values*/
			RCC_PLLCFGR &= ~(0b11<<16);
			/*Set PLLM from configuration*/
			RCC_PLLCFGR |= (PLLP<<16);
		/*Select PLL Source *PLLSRC* , 0 for HSI , 1 for HSE*/
			#if RCC_PLL_SRC == RCC_PLL_HSI
				CLR_BIT(RCC_PLLCFGR,PLLSRC_BIT);
			#elif RCC_PLL_SRC == RCC_PLL_HSE
				SET_BIT(RCC_PLLCFGR,PLLSRC_BIT);
			#endif
		/*Enable PLL*/
			SET_BIT(RCC_CR,PLLON_BIT);
		/*wait till PLL is Ready*/
			while(!GET_BIT(RCC_CR,RCC_PLL_READY_BIT));
		/*Select PLL as System Clock*/
			RCC_CFGR &= ~(0x00000003);		/*Clear Bits*/
			RCC_CFGR |= 0x00000002;			/*Set Bits*/
		
		
	#else
			#error("Wrong Clock Selected")
	
	#endif

}

/*							Peripherals Clocks								*/
void RCC_voidEnableCompClk(u8 Copy_uint8Bus, u8 Copy_uint8PerID){
	if(Copy_uint8PerID <= 31){
		switch(Copy_uint8Bus){
			case RCC_AHB1:	SET_BIT(RCC_AHB1ENR,Copy_uint8PerID);	break;
			case RCC_AHB2:	SET_BIT(RCC_AHB2ENR,Copy_uint8PerID);	break;
			case RCC_AHB3:	SET_BIT(RCC_AHB3ENR,Copy_uint8PerID);	break;
			case RCC_APB1:	SET_BIT(RCC_APB1ENR,Copy_uint8PerID);	break;
			case RCC_APB2:	SET_BIT(RCC_APB2ENR,Copy_uint8PerID);	break;
		}
	}
	else{
		/*Return Error*/
	}
}
void RCC_voidDisableCompClk(u8 Copy_uint8Bus, u8 Copy_uint8PerID){
	if(Copy_uint8PerID <= 31){
		switch(Copy_uint8Bus){
		case RCC_AHB1:	CLR_BIT(RCC_AHB1ENR,Copy_uint8PerID);	break;
		case RCC_AHB2:	CLR_BIT(RCC_AHB2ENR,Copy_uint8PerID);	break;
		case RCC_AHB3:	CLR_BIT(RCC_AHB3ENR,Copy_uint8PerID);	break;
		case RCC_APB1:	CLR_BIT(RCC_APB1ENR,Copy_uint8PerID);	break;
		case RCC_APB2:	CLR_BIT(RCC_APB2ENR,Copy_uint8PerID);	break;
		}
	}
	else{
		/*Return Error*/
	}
}
