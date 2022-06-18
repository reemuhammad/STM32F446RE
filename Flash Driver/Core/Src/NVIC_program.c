/*
 * NVIC_program.c
 *
 *  Created on: Jan 11, 2022
 *      Author: Omar el Masry
 */



#include "NVIC_interface.h"
/***************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*****************************************************************************/
#define AIRCR_VECTKEY 							0xFA05

/****************************************************************************
*  LOCAL DATA
*****************************************************************************/
u32 intNum;
u32 locGroup;
u32 i;
u32 locSubGroup;
u32 enRegOffset;
u32 enBitOffset;
u32 locGroupingField;
u32 priRegOffset;
u32 priBitOffset;
/****************************************************************************
*  GLOBAL DATA
*****************************************************************************/

/****************************************************************************
*  FUNCTIONS
*****************************************************************************/


/****************************************************************************
* \Syntax : void IntCtrl_Init(void)
* \Description: Initilze NVIC/SCB Module
*
* \Sync\Async: Sync
* \Reentrancy: none
* \Parameters (in): none
* \Parameters (out): none
* \Return Value:    none
*
******************************************************************************/
void NVIC_Init(void)
{

/*TODO Configure Grouping/SubGroubing System In APINT register in SCB*/
AIRCR= ( AIRCR_VECTKEY << 16U ) |(NVIC_GROUPING_SYSTEM<<8U);

for(i=0; i< NVIC_ACTIVATED_INT_SIZE ;i++)
	{
		intNum			= NVIC_Cfg[i].Interupt_Number;
		locGroup		= NVIC_Cfg[i].Group_Priority;
		locSubGroup     = NVIC_Cfg[i].SubGroup_Priority;

		/* enable\disable based on user configuration */
		enRegOffset = (intNum/WORD_LENGTH_BITS)*WORD_LENGTH_BYTES;
		enBitOffset = intNum%WORD_LENGTH_BITS;

		GET_HWREG(NVIC_BASE_ADDRESS,enRegOffset) |= (1 << enBitOffset);


#if NVIC_GROUPING_SYSTEM == NVIC_GROUPING_SYSTEM_XXX
			locGroupingField = locGroup;

#elif NVIC_GROUPING_SYSTEM == NVIC_GROUPING_SYSTEM_XXY
			locGroupingField = ((locGroup<<1)&0x6) | (locSubGroup&0x1);

#elif NVIC_GROUPING_SYSTEM == NVIC_GROUPING_SYSTEM_XYY
        	locGroupingField = ((locGroup<<2)&0x4) | (locSubGroup&0x3);

#elif NVIC_GROUPING_SYSTEM == NVIC_GROUPING_SYSTEM_YYY
        	locGroupingField = locGroup;
#else
     #error INVALID GROUPING SELECTION
#endif

			/* assign group\subgroup priority */

			priRegOffset = (intNum/4U)*WORD_LENGTH_BYTES;
			priBitOffset = 5 + (8 * (intNum%4U));
			GET_HWREG(NVIC_PRIORTY_BASE,priRegOffset) |= (locGroupingField << priBitOffset);


	}
}
