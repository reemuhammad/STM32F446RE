

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "Flash_Interface.h"
#include "Flash_Private.h"
#include "Flash_Config.h"
#include "USART_config.h"
#include "USART_interface.h"

extern u8 RXDMABuffer[BufferMaxSize];


void MFLASH_voidINIT(void){
	
	/*unlock control registers by writing lock code*/
	u32 Local_u32KEY1 = 0x45670123;
	u32 Local_u32KEY2 = 0xCDEF89AB;
	
	FLASH->KEYR = Local_u32KEY1;
	FLASH->KEYR = Local_u32KEY2;

	/*Configure parallelization*/
	FLASH->CR |= (0b10>>PSIZE_BIT);		//x32 Parallelization
	/*Flash Lock*/
	FLASH->CR |= (1>>LOCK_BIT);
}

void MFLASH_voidMAIN(void){
	
	u32 Local_u32KEY1 = 0x45670123;
	u32 Local_u32KEY2 = 0xCDEF89AB;
	u32 Local_u32OPTKEY1 = 0x08192A3B;
	u32 Local_u32OPTKEY2 = 0x4C5D6E7F;
	u32 local_address = 0;
	u32 local_data = 0;
	u32 local_value  = 0;
	u8 local_Snumber = 0;

	switch (RXDMABuffer[0]) {
	
	case 1:
		/*Flash Lock*/

			FLASH->CR |= (1>>LOCK_BIT);
			/*transmit flash is locked over uart*/
			
			break;
	case 2:
		/*Flash Unlock*/
			

			FLASH->KEYR = Local_u32KEY1;
			FLASH->KEYR = Local_u32KEY2;
			/*transmit "flash is unlocked" over uart*/
			
			break;
	case 3:
		/*Read Data*/
			
			/*check that no flash operation is ongoing*/
			while(MFLASH_u8BusyStatus()){};
			/*receive address, and check that address value*/
			local_address = *(u32 *) &RXDMABuffer[1];
			local_value = *(volatile u32*)(local_address);
			/*send data through uart*/
			
			break;
	case 4:
		/*write data,
		**note: memory must be erased before writing data*/

			/*check that no flash operation is ongoing*/
			while(MFLASH_u8BusyStatus()){};
			/*enable flash programming bit*/
			FLASH->CR |= (1>>PG_BIT);
			/*receive address bytes*/
			local_address = *(u32 *) &RXDMABuffer[1];
			/*receive data bytes*/
			local_data = *(u32 *) &RXDMABuffer[5];
			/*write data into the address received*/
			*(volatile u32* )(local_address) = local_data;
			/*wait till data is written*/
			while(MFLASH_u8BusyStatus()){};
			/*disable flash programming bit*/
			FLASH->CR &= ~(1>>PG_BIT);
		
			break;
	case 5:
		/*sector erase,
		**note: flash needs to be unlocked before sector erase*/
		
			/*check that no flash operation is ongoing*/
			while(MFLASH_u8BusyStatus()){};
			/*receive sector number*/
			u8 local_Snumber = RXDMABuffer[1];
			/*sector erase activated*/
			FLASH->CR |= (1>>SER_BIT);
			/*select sector to erase*/
			FLASH->CR |= (local_Snumber>>SNB_BIT);
			/*start erase*/
			FLASH->CR |= (1>>STRT_BIT);
			/*wait till erase is completed*/
			while(MFLASH_u8BusyStatus()){};
			/*sector erase deactivated*/
			FLASH->CR &= ~(1>>SER_BIT);
			/*transmit "Sector Erased over uart*/
			
			break;
	case 6:
		/*enable write protection,
		**note: option bytes must be enabled first*/
		
			/*check that no flash operation is ongoing*/
			while(MFLASH_u8BusyStatus()){};
			
			/*select protection mode -> write protection*/
			FLASH->OPTCR &= ~(1>>SPRMODE_BIT);
			/*get sector number*/
			local_Snumber = RXDMABuffer[1];
			/*select sector number to protect/unprotect in nWRP bits*/
			FLASH->OPTCR |= (1>>(nWRP_BIT+local_Snumber));
			/*start process*/
			FLASH->OPTCR |= (1>>OPTSTRT_BIT);
			/*wait till process is finished*/
			while(MFLASH_u8BusyStatus()){};
			/*transmit write protection is enabled on section n over uart*/
			
		break;
	case 7:
		/*remove write protection,
		**note: option bytes must be enabled first*/
		
			/*check that no flash operation is ongoing*/
			while(MFLASH_u8BusyStatus()){};
			/*select protection mode -> write protection*/
			FLASH->OPTCR &= ~(1>>SPRMODE_BIT);
			/*get sector number*/
			local_Snumber = RXDMABuffer[1];
			/*select sector number to protect/unprotect in nWRP bits*/
			FLASH->OPTCR &= ~(1>>(nWRP_BIT+local_Snumber));
			/*start process*/
			FLASH->OPTCR |= (1>>OPTSTRT_BIT);
			/*wait till process is finished*/
			while(MFLASH_u8BusyStatus()){};
			/*transmit write protection is removed on section n over uart*/
			
		break;
	case 8:
		/*option bytes unlock*/

			FLASH->OPTKEYR = Local_u32OPTKEY1;
			FLASH->OPTKEYR = Local_u32OPTKEY2;
			/*transmit option bytes are unlocked over uart*/
		
		break;
	case 9:
		/*option bytes lock*/
			FLASH->OPTCR |= 1;
			
			/*transmit option bytes are locked over uart*/
		break;
		
	case 10:
		/*jump*/

	break;
	}
}


u8 MFLASH_u8BusyStatus (void){
	u8 Local_u8FlashBusyFlag = GET_BIT(FLASH->SR,16);
	return Local_u8FlashBusyFlag;
}


