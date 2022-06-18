/*****************************************************************************/
/*
*Author: Reem 
*Date: 3/11/2021
*Version: 1
*/
/****************************************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H

#define NULL ( (void *) 0)

#define WORD_LENGTH_BITS      32u
#define WORD_LENGTH_BYTES     4u
#define MSB_FIRST             0u    		/* big endian bit ordering */
#define LSB_FIRST  	           1u    		/* little endian bit ordering */

#define HIGH_BYTE_FIRST       0u    		/* big endian byte ordering */
#define LOW_BYTE_FIRST        1u    		/* little endian byte ordering */

#ifndef TRUE
   #define TRUE               1u
#endif

#ifndef FALSE
   #define FALSE              0u
#endif

#define ENABLE                1u
#define DISABLE               0u


#define STD_HIGH    		  1u 			/* Physical state 5V or 3.3V */
#define STD_LOW      		  0u 			/* Physical state 0V */

#define STD_ACTIVE  		  1u 			/* Logical state active */
#define STD_IDLE    		  0u 			/* Logical state idle */

#define STD_ON       		  1u
#define STD_OFF      		  0u

#define CPU_BIT_ORDER    	LSB_FIRST        /*little endian bit ordering*/
#define CPU_BYTE_ORDER   	LOW_BYTE_FIRST   /*little endian byte ordering*/


typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;

typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;

typedef float f32;
typedef double f64;

#endif
