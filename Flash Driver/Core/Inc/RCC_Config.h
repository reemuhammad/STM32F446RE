/********************************************/	
/* Author: Abdelrahman Ramzi Fahmi				  		*/
/* Date: 07-Nov. 2021												*/
/* Version: 0.1															*/
/********************************************/

#ifndef _RCC_CONFIG_H_
#define _RCC_CONFIG_H_

/*	Please Choose Clock System Source
	Options: 
	 1- RCC_HSI_RC (High-Speed Internal RC Clock)
	 2- RCC_HSE_RC (High-Speed External RC Clock)
	 3- RCC_HSE_CRYSTAL ( High-Speed External Crystal Clock)
	 4- RCC_PLL	(Phase-Locked Loop)

*/

#define RCC_SYSTEM_CLOCK  RCC_HSI_RC

#if RCC_SYSTEM_CLOCK == RCC_PLL

/*		Choose PLL Source
		Options: 
		1- RCC_PLL_HSI
		2- RCC_PLL_HSE */
#define RCC_PLL_HSI 0
#define RCC_PLL_HSE 1
#define RCC_PLL_SRC RCC_PLL_HSI /*choose PLL source*/


/*** Only Choose PLL Mode if you choose RCC_SYSTEM_CLOCK as PLL
	Select Multiplication Factor, Following the equations:
		F(VCO) = F(PLL_INPUT_SOURCE) * [PLLN/PLLM]
		F(PLL Clock Output) = F(VCO) / PLLP
		**F(VCO) Should be between 100MHz and 432MHz
		where PLLN is between 50 and 432
			  PLLM is between 2 and 63
			  PLLP is 2,4,6 and 8
*/

#define PLLN 56
#define PLLM 14
#define PLLP 2

#endif


#endif
