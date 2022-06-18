/********************************************/	
/* Author: Abdelrahman Ramzi Fahmi				  		*/
/* Date: 07-Nov. 2021												*/
/* Version: 0.1															*/
/********************************************/

#ifndef _RCC_RPIVATE_H_
#define _RCC_PRIVATE_H_

/********************************************/
/*				RCC Registers				*/
/********************************************/
		/*		RCC BASE ADDRESS		*/
#define RCC_BASE_ADDRESS		0x40023800
/*Clock control register (RCC_CR)*/
#define RCC_CR							*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x00))
/*PLL Configuration Register (RCC_PLLCFGR)*/
#define RCC_PLLCFGR						*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x04))
/*Clock configuration register (RCC_CFGR)*/
#define RCC_CFGR 						*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x08))
/*Clock interrupt register (RCC_CIR)*/
#define RCC_CIR 						*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x0C))

/*AHB1 peripheral reset register (RCC_APB1RSTR)*/
#define RCC_AHB1RSTR					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x10))
/*AHB2 peripheral reset register (RCC_APB1RSTR)*/			
#define RCC_AHB2RSTR					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x14))
/*AHB3 peripheral reset register (RCC_APB1RSTR)*/
#define RCC_AHB3RSTR					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x18))
/*APB1 peripheral reset register (RCC_APB1RSTR)*/	
#define RCC_APB1RSTR					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x20))
/*APB2 peripheral reset register (RCC_APB1RSTR)*/
#define RCC_APB2RSTR					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x24))
/*AHB1 peripheral clock enable register (RCC_AHBENR)*/
#define RCC_AHB1ENR						*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x30))
/*AHB2 peripheral clock enable register (RCC_AHBENR)*/
#define RCC_AHB2ENR 					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x34))
/*AHB3 peripheral clock enable register (RCC_AHBENR)*/
#define RCC_AHB3ENR 					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x38))
/*APB1 peripheral clock enable register (RCC_APB1ENR)*/	
#define RCC_APB1ENR						*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x40))
/*APB2 peripheral clock enable register (RCC_APB1ENR)*/
#define RCC_APB2ENR						*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x44))


#define RCC_AHB1LPENR 					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x50))
#define RCC_AHB2LPENR 					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x54))
#define RCC_AHB3LPENR 					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x58))
#define RCC_APB1LPENR					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x60))
#define RCC_APB2LPENR					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x64))


/*Backup domain control register (RCC_BDCR)*/
#define RCC_BDCR						*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x70))
/*Control/status register (RCC_CSR)*/
#define RCC_CSR							*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x74))


#define RCC_SSCGR						*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x80))
#define RCC_PLLI2S_CFGR					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x84))
#define RCC_PLLSAI_CFGR					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x88))
#define RCC_DCK_CFGR					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x8C))
#define RCC_CKGATENR					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x90))
#define RCC_DCKCFGR2					*(( volatile u32*)(RCC_BASE_ADDRESS	+	0x94))



/********************************************************/
/*				RCC System Clock Selection				*/
/********************************************************/


/*				Clock Types						*/
#define RCC_HSE_CRYSTAL			0
#define RCC_HSE_RC				1
#define RCC_HSI_RC				2
#define RCC_PLL					3

/*				PLL SRC Selection				*/
#define RCC_PLL_HSI				0
#define RCC_PLL_HSE				1
#define RCC_PLL_HSE_DIV_2		2

/*					RCC CR REGISTER BITS				*/
#define RCC_HSE_READY_BIT 	17
#define PLLON_BIT			24
#define RCC_PLL_READY_BIT 	25
#define RCC_HSI_READY_BIT	1
/*					RCC PLLCFGR REGISTER BITS				*/
#define PLLSRC_BIT				22


#endif /*_RCC_PRIVATE_H_*/
