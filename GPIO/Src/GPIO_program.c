/*
 * GPIO_program.c
 * Version: 1
  */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"

void GPIO_voidSetPinDirection(GPIO_enum Copy_u8Port, GPIO_enum Copy_u8Pin, GPIO_enum Copy_PinMode)
{
	/* Copy_PinMode is a 7-bit number defined in the GPIO_enum.
	 * bits [5,6]: for pin mode (either I/P or O/P or AF)
	 * bit   [4] : for output type (either PP or OD)
	 * bits [2,3]: for pin output speed
	 * bits [0,1]: for pull up and pull down
	 */
	u8 Local_u8Mode= (Copy_PinMode >> 5);
	u8 Local_u8OutputType= GET_BIT(Copy_PinMode,4);
	u8 Local_u8Speed= (Copy_PinMode>>2) & 0b11;
	u8 Local_u8PUPD= (Copy_PinMode) & 0b11;

	switch(Copy_u8Port)
		{
		/* If port A is chosen */
			case GPIOA:
				/*Clear the two corresponding bits of the pin in GPIO port A mode register */
				GPIOA_MODER &= ~( 0b11 << (Copy_u8Pin*2) );
				/*Set the value of the two corresponding bits of the pin in GPIO port A mode register */
				GPIOA_MODER |=  ( (Local_u8Mode) << (Copy_u8Pin*2) );

				/*Clear the corresponding bit of the pin in GPIO port A output type register */
				CLR_BIT(GPIOA_OTYPER,Copy_u8Pin);
				/*Set the value of the corresponding bit of the pin in GPIO port A output type register */
				GPIOA_OTYPER |= ( (Local_u8OutputType) << (Copy_u8Pin) );

				/*Clear the two corresponding bits of the pin in GPIO port A output speed register */
				GPIOA_OSPEEDER &= ~( 0b11 << (Copy_u8Pin*2) );
				/*Set the value of the two corresponding bits of the pin in GPIO port A output speed register */
				GPIOA_OSPEEDER |= ( (Local_u8Speed) << (Copy_u8Pin*2));

				/*Clear the two corresponding bits of the pin in GPIO port A pull-up/pull-down register */
				GPIOA_PUPDR &= ~( 0b11 << (Copy_u8Pin*2) );
				/*Set the value of the two corresponding bits of the pin in GPIO port A pull-up/pull-down register */
				GPIOA_PUPDR |= ( (Local_u8PUPD) << (Copy_u8Pin*2));

				break;


		/* If port B is chosen */
		    case GPIOB:
                /*Clear the two corresponding bits of the pin in GPIO port B mode register */
                GPIOB_MODER &= ~( 0b11 << (Copy_u8Pin*2) );
		    	/*Set the value of the two corresponding bits of the pin in GPIO port B mode register */
		    	GPIOB_MODER |=  ( (Local_u8Mode) << (Copy_u8Pin*2) );

		    	/*Clear the corresponding bit of the pin in GPIO port B output type register */
		    	CLR_BIT(GPIOB_OTYPER,Copy_u8Pin);
		    	/*Set the value of the corresponding bit of the pin in GPIO port B output type register */
		    	GPIOB_OTYPER |= ( (Local_u8OutputType) << (Copy_u8Pin) );

		    	/*Clear the two corresponding bits of the pin in GPIO port B output speed register */
		    	GPIOB_OSPEEDER &= ~( 0b11 << (Copy_u8Pin*2) );
		    	/*Set the value of the two corresponding bits of the pin in GPIO port B output speed register */
		    	GPIOB_OSPEEDER |= ( (Local_u8Speed) << (Copy_u8Pin*2));

		    	/*Clear the two corresponding bits of the pin in GPIO port B pull-up/pull-down register */
		    	GPIOB_PUPDR &= ~( 0b11 << (Copy_u8Pin*2) );
		    	/*Set the value of the two corresponding bits of the pin in GPIO port B pull-up/pull-down register */
		    	GPIOB_PUPDR |= ( (Local_u8PUPD) << (Copy_u8Pin*2));

		    	break;


		/* If port C is chosen */
		    case GPIOC:
		    	/*Clear the two corresponding bits of the pin in GPIO port C mode register */
		    	GPIOC_MODER &= ~( 0b11 << (Copy_u8Pin*2) );
		    	/*Set the value of the two corresponding bits of the pin in GPIO port C mode register */
		    	GPIOC_MODER |=  ( (Local_u8Mode) << (Copy_u8Pin*2) );

		    	/*Clear the corresponding bit of the pin in GPIO port C output type register */
		    	CLR_BIT(GPIOC_OTYPER,Copy_u8Pin);
		    	/*Set the value of the corresponding bit of the pin in GPIO port C output type register */
		    	GPIOC_OTYPER |= ( (Local_u8OutputType) << (Copy_u8Pin) );

		    	/*Clear the two corresponding bits of the pin in GPIO port C output speed register */
		    	GPIOC_OSPEEDER &= ~( 0b11 << (Copy_u8Pin*2) );
		    	/*Set the value of the two corresponding bits of the pin in GPIO port C output speed register */
		    	GPIOC_OSPEEDER |= ( (Local_u8Speed) << (Copy_u8Pin*2));

		    	/*Clear the two corresponding bits of the pin in GPIO port C pull-up/pull-down register */
		    	GPIOC_PUPDR &= ~( 0b11 << (Copy_u8Pin*2) );
		    	/*Set the value of the two corresponding bits of the pin in GPIO port C pull-up/pull-down register */
		    	GPIOC_PUPDR |= ( (Local_u8PUPD) << (Copy_u8Pin*2));

		    	break;

		    default:
		    	break;
		}
}

void GPIO_voidSetPinValue(GPIO_enum Copy_u8Port, GPIO_enum Copy_u8Pin, GPIO_enum Copy_u8PinValue)
{
	/* In GPIOx_BSRR register:
	 *  bits (0 to 15) are for atomic set
	 *  bits (16 to 31) are for atomic reset */
	if(Copy_u8PinValue == GPIO_LOW)
		{
			Copy_u8Pin += 16;
		}

	switch(Copy_u8Port)
		{
		/* If port A is chosen */
			case GPIOA:
				SET_BIT(GPIOA_BSRR,Copy_u8Pin);
				break;
		/* If port B is chosen */
		    case GPIOB:
		    	SET_BIT(GPIOB_BSRR,Copy_u8Pin);
		    	break;
		/* If port C is chosen */
		    case GPIOC:
		    	SET_BIT(GPIOC_BSRR,Copy_u8Pin);
		    	break;

		    default:
		   		break;
		}
}

u8 GPIO_u8GetPinValue(GPIO_enum Copy_u8Port, GPIO_enum Copy_u8Pin)
{
	u8 Local_u8PinValue=0;
	switch(Copy_u8Port)
		{
		/* If port A is chosen */
			case GPIOA:
				Local_u8PinValue = GET_BIT(GPIOA_IDR,Copy_u8Pin);
				break;
		/* If port B is chosen */
		    case GPIOB:
		    	Local_u8PinValue = GET_BIT(GPIOB_IDR,Copy_u8Pin);
		    	break;
    	/* If port C is chosen */
		    case GPIOC:
		    	Local_u8PinValue = GET_BIT(GPIOC_IDR,Copy_u8Pin);
		    	break;

		    default:
		   		break;
        }
	return Local_u8PinValue;
}

void GPIO_voidWritePort(GPIO_enum Copy_u8Port, u16 Copy_u16PortValue)
{
     switch(Copy_u8Port)
	 	{
	 	/* If port A is chosen */
	 		case GPIOA:
	 			GPIOA_ODR = Copy_u16PortValue;
	 			break;
	 	/* If port B is chosen */
	 	    case GPIOB:
	 	    	GPIOB_ODR = Copy_u16PortValue;
	 	    	break;
	 	/* If port C is chosen */
	 	    case GPIOC:
	 	    	GPIOC_ODR = Copy_u16PortValue;
	 	    	break;

	 	   default:
	 	  		break;
	 	}
}

void GPIO_voidLockPin(GPIO_enum Copy_u8Port, GPIO_enum Copy_u8Pin)
{
	/* This function is used to lock the setup of a GPIO pin
	 * The lock operation happens by writing a special sequence on LCKR register.
	 * The value of bits LCKR[15:0] during writing the sequence can not change.
	 * Write LCKR[16] = �1� + LCKR[15:0]
	   Write LCKR[16] = �0� + LCKR[15:0]
	   Write LCKR[16] = �1� + LCKR[15:0]
       Read LCKR
	 */

    u8 Local_u8Lock = (1<<16) | (1<<Copy_u8Pin);
	switch(Copy_u8Port)
		{
		/* If port A is chosen */
			case GPIOA:
				GPIOA_LCKR = Local_u8Lock;
				GPIOA_LCKR = (1<<Copy_u8Pin);
				GPIOA_LCKR = Local_u8Lock;
				Local_u8Lock = GPIOA_LCKR;
				break;

		/* If port B is chosen */
		    case GPIOB:
		    	GPIOB_LCKR = Local_u8Lock;
		    	GPIOB_LCKR = (1<<Copy_u8Pin);
		    	GPIOB_LCKR = Local_u8Lock;
		    	Local_u8Lock = GPIOB_LCKR;
		    	break;

		/* If port C is chosen */
		    case GPIOC:
		    	GPIOC_LCKR = Local_u8Lock;
		    	GPIOC_LCKR = (1<<Copy_u8Pin);
		    	GPIOC_LCKR = Local_u8Lock;
		    	Local_u8Lock = GPIOC_LCKR;
		    	break;

		    default:
		   		break;
		}
}


void GPIO_voidSetAlternatingFunction(GPIO_enum Copy_u8Port, GPIO_enum Copy_u8Pin, GPIO_enum Copy_u8Peripheral)
{
	switch(Copy_u8Port)
	{
		case GPIOA:
			if(Copy_u8Pin <= 7)
			{
				GPIOA_AFRL = Copy_u8Peripheral << (Copy_u8Pin *4) ;
			}
			else if (Copy_u8Pin >= 8)
			{
				GPIOA_AFRH = Copy_u8Peripheral << ((Copy_u8Pin - 8) *4) ;
			}
		case GPIOB:
			if(Copy_u8Pin <= 7)
			{
				GPIOB_AFRL = Copy_u8Peripheral << (Copy_u8Pin *4) ;
			}
			else if (Copy_u8Pin >= 8)
			{
				GPIOB_AFRH = Copy_u8Peripheral << ((Copy_u8Pin - 8) *4) ;
			}
		case GPIOC:
			if(Copy_u8Pin <= 7)
			{
				GPIOC_AFRL = Copy_u8Peripheral << (Copy_u8Pin *4) ;
			}
			else if (Copy_u8Pin >= 8)
			{
				GPIOC_AFRH = Copy_u8Peripheral << ((Copy_u8Pin - 8) *4) ;
			}
		default:
			break;
	}

}
