/*****************************************************************************/
/*
*Author: Reem 
*Date: 3/11/2021
*Version: 1
*/
/****************************************************************************/
#ifndef BIT_MATH_H
#define BIT_MATH_H

/* set bit in a register */
#define SET_BIT(REG,BIT_NUM)		REG |= (1<< (BIT_NUM))
/* clear bit in a register */
#define CLR_BIT(REG,BIT_NUM)		REG &= ~(1<< (BIT_NUM))
/* get bit in a register */
#define GET_BIT(REG,BIT_NUM)		(( REG >> (BIT_NUM) ) & 1)
/* toggle bit in a register */
#define TOG_BIT(REG,BIT_NUM)		REG ^= ( 1<< (BIT_NUM) )

#endif 
