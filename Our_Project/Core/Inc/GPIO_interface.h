/*****************************************************************************/
/*
*Version: 1
*/
/****************************************************************************/


#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

/******************************************************************************************************************/
/***********************************************FUNCTIONS PARAMETERS***********************************************/
typedef enum GPIO
{
/****************************************************************************************************************/
	/* PIN VALUE */
	GPIO_LOW,
	GPIO_HIGH,

/****************************************************************************************************************/
	/* GPIO PORTS */
	GPIOA,
	GPIOB,
	GPIOC,

/****************************************************************************************************************/
	/* PINS */
	PIN0 =0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15,

/************************************************PIN MODES*******************************************************/
/****************************************************************************************************************/
	/* PIN MODES FOR INPUT */
	INPUT_FLOATING 															= 0b0000000,
	INPUT_PULL_UP 															= 0b0000001,
	INPUT_PULL_DOWN														    = 0b0000010,
	INPUT_ANALOG 															= 0b1100000,

/****************************************************************************************************************/
	/* PIN MODES FOR OUTPUT */

	/* OUTPUT, PUSH PULL, NO PULL UP OR PULL DOWN */
	OUTPUT_PUSH_PULL_NO_PUPD_LOW_SPEED 										= 0b0100000,
	OUTPUT_PUSH_PULL_NO_PUPD_MEDIUM_SPEED 									= 0b0100100,
	OUTPUT_PUSH_PULL_NO_PUPD_FAST_SPEED 									= 0b0101000,
	OUTPUT_PUSH_PULL_NO_PUPD_VERY_FAST_SPEED							    = 0b0101100,

	/* OUTPUT, PUSH PULL, PULL UP */
	OUTPUT_PUSH_PULL_WITH_PU_LOW_SPEED                                      = 0b0100001,
	OUTPUT_PUSH_PULL_WITH_PU_MEDIUM_SPEED                                   = 0b0100101,
	OUTPUT_PUSH_PULL_WITH_PU_FAST_SPEED                                     = 0b0101001,
    OUTPUT_PUSH_PULL_WITH_PU_VERY_FAST_SPEED                                = 0b0101101,

	/* OUTPUT, PUSH PULL, PULL DOWN */
    OUTPUT_PUSH_PULL_WITH_PD_LOW_SPEED                                      = 0b0100010,
	OUTPUT_PUSH_PULL_WITH_PD_MEDIUM_SPEED                                   = 0b0100110,
	OUTPUT_PUSH_PULL_WITH_PD_FAST_SPEED                                     = 0b0101010,
	OUTPUT_PUSH_PULL_WITH_PD_VERY_FAST_SPEED                                = 0b0101110,

	/* OUTPUT, OPEN DRAIN, NO PULL UP OR PULL DOWN */
	OUTPUT_OPEN_DRAIN_NO_PUPD_LOW_SPEED                                     = 0b0110000,
	OUTPUT_OPEN_DRAIN_NO_PUPD_MEDIUM_SPEED                                  = 0b0110100,
	OUTPUT_OPEN_DRAIN_NO_PUPD_FAST_SPEED                                    = 0b0111000,
	OUTPUT_OPEN_DRAIN_NO_PUPD_VERY_FAST_SPEED                               = 0b0111100,

	/* OUTPUT, OPEN DRAIN, PULL UP */
	OUTPUT_OPEN_DRAIN_WITH_PU_LOW_SPEED                                     = 0b0110001,
	OUTPUT_OPEN_DRAIN_WITH_PU_MEDIUM_SPEED                                  = 0b0110101,
	OUTPUT_OPEN_DRAIN_WITH_PU_FAST_SPEED                                    = 0b0111001,
	OUTPUT_OPEN_DRAIN_WITH_PU_VERY_FAST_SPEED                               = 0b0111101,

	/* OUTPUT, OPEN DRAIN, PULL DOWN */
	OUTPUT_OPEN_DRAIN_WITH_PD_LOW_SPEED                                     = 0b0110010,
	OUTPUT_OPEN_DRAIN_WITH_PD_MEDIUM_SPEED                                  = 0b0110110,
	OUTPUT_OPEN_DRAIN_WITH_PD_FAST_SPEED                                    = 0b0111010,
	OUTPUT_OPEN_DRAIN_WITH_PD_VERY_FAST_SPEED                               = 0b0111110,

/****************************************************************************************************************/
	/* PIN MODES FOR ALTERNATING FUNCTION */

    /* ALTERNATING FUNCTION, PUSH PULL, NO PULL UP OR PULL DOWN */
    ALTERNATING_FUNCTION_PUSH_PULL_NO_PUPD_LOW_SPEED 						= 0b1000000,
    ALTERNATING_FUNCTION_PUSH_PULL_NO_PUPD_MEDIUM_SPEED 			      	= 0b1000100,
    ALTERNATING_FUNCTION_PUSH_PULL_NO_PUPD_FAST_SPEED 						= 0b1001000,
	ALTERNATING_FUNCTION_PUSH_PULL_NO_PUPD_VERY_FAST_SPEED				    = 0b1001100,

	/* ALTERNATING FUNCTION, PUSH PULL, PULL UP */
	ALTERNATING_FUNCTION_PUSH_PULL_WITH_PU_LOW_SPEED                        = 0b1000001,
	ALTERNATING_FUNCTION_PUSH_PULL_WITH_PU_MEDIUM_SPEED                     = 0b1000101,
	ALTERNATING_FUNCTION_PUSH_PULL_WITH_PU_FAST_SPEED                       = 0b1001001,
	ALTERNATING_FUNCTION_PUSH_PULL_WITH_PU_VERY_FAST_SPEED                  = 0b1001101,

	/* ALTERNATING FUNCTION, PUSH PULL, PULL DOWN */
	ALTERNATING_FUNCTION_PUSH_PULL_WITH_PD_LOW_SPEED                        = 0b1000010,
	ALTERNATING_FUNCTION_PUSH_PULL_WITH_PD_MEDIUM_SPEED                     = 0b1000110,
	ALTERNATING_FUNCTION_PUSH_PULL_WITH_PD_FAST_SPEED                       = 0b1001010,
	ALTERNATING_FUNCTION_PUSH_PULL_WITH_PD_VERY_FAST_SPEED                  = 0b1001110,

	/* ALTERNATING FUNCTION, OPEN DRAIN, NO PULL UP OR PULL DOWN */
	ALTERNATING_FUNCTION_OPEN_DRAIN_NO_PUPD_LOW_SPEED                       = 0b1010000,
	ALTERNATING_FUNCTION_OPEN_DRAIN_NO_PUPD_MEDIUM_SPEED                    = 0b1010100,
	ALTERNATING_FUNCTION_OPEN_DRAIN_NO_PUPD_FAST_SPEED                      = 0b1011000,
	ALTERNATING_FUNCTION_OPEN_DRAIN_NO_PUPD_VERY_FAST_SPEED                 = 0b1011100,

	/* ALTERNATING FUNCTION, OPEN DRAIN, PULL UP */
	ALTERNATING_FUNCTION_OPEN_DRAIN_WITH_PU_LOW_SPEED                       = 0b1010001,
	ALTERNATING_FUNCTION_OPEN_DRAIN_WITH_PU_MEDIUM_SPEED                    = 0b1010101,
	ALTERNATING_FUNCTION_OPEN_DRAIN_WITH_PU_FAST_SPEED                      = 0b1011001,
	ALTERNATING_FUNCTION_OPEN_DRAIN_WITH_PU_VERY_FAST_SPEED                 = 0b1011101,

	/* ALTERNATING FUNCTION, OPEN DRAIN, PULL DOWN */
	ALTERNATING_FUNCTION_OPEN_DRAIN_WITH_PD_LOW_SPEED                       = 0b1010010,
	ALTERNATING_FUNCTION_OPEN_DRAIN_WITH_PD_MEDIUM_SPEED                    = 0b1010110,
	ALTERNATING_FUNCTION_OPEN_DRAIN_WITH_PD_FAST_SPEED                      = 0b1011010,
	ALTERNATING_FUNCTION_OPEN_DRAIN_WITH_PD_VERY_FAST_SPEED                 = 0b1011110,
/****************************************************************************************************************/
	/* Alternating Functions */
	AF0 =0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15,

/****************************************************************************************************************/
}GPIO_enum;

/******************************************************************************************************************/
/***********************************************FUNCTIONS PROTOTYPES***********************************************/

void GPIO_voidSetPinDirection(GPIO_enum Copy_u8Port, GPIO_enum Copy_u8Pin, GPIO_enum Copy_PinMode);
/* purpose: set the direction of the pin
 * arguments: 1) an option from section GPIO PORTS in GPIO_enum
 * 			  2) an option from section PINS in GPIO_enum
 * 			  3) an option from section PIN MODES in GPIO_enum
 * return: none
 * */
void GPIO_voidSetPinValue(GPIO_enum Copy_u8Port, GPIO_enum Copy_u8Pin, GPIO_enum Copy_u8PinValue);
/* purpose: set the value of the pin in case it is output pin
 * arguments: 1) an option from section GPIO PORTS in GPIO_enum
 * 			  2) an option from section PINS in GPIO_enum
 * 			  3) an option from section PIN VALUE in GPIO_enum
 * return: none
 * */
u8 GPIO_u8GetPinValue(GPIO_enum Copy_u8Port, GPIO_enum Copy_u8Pin);
/* purpose: get the value of the pin
 * arguments: 1) an option from section GPIO PORTS in GPIO_enum
 * 			  2) an option from section PINS in GPIO_enum
 * return: pin value, expected options:( GPIO_LOW :0     OR     GPIO_HIGH :1 )
 * */
void GPIO_voidWritePort(GPIO_enum Copy_u8Port, u16 Copy_u16PortValue);
/* purpose: set the value of the whole port (16 pins together) in case it is output pin
 * arguments: 1) an option from section GPIO PORTS in GPIO_enum
 * 			  2) numeric value to write on the port
 * return: none
 * */
void GPIO_voidLockPin(GPIO_enum Copy_u8Port, GPIO_enum Copy_u8Pin);
/* purpose: lock the setup of a GPIO pin (can't change the direction and setup of the
 *          locked pin later in the code after calling this function until the next MC reset).
 * arguments: 1) an option from section GPIO PORTS in GPIO_enum
 * 			  2) an option from section PINS in GPIO_enum
 * return: none
 * */

void GPIO_voidSetAlternatingFunction(GPIO_enum Copy_u8Port, GPIO_enum Copy_u8Pin, GPIO_enum Copy_u8Peripheral);
/* purpose:
 * arguments:
 * return: none
 * */

#endif
