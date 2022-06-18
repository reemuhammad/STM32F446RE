#ifndef _Flash_Private_H_
#define _Flash_Private_H_

//#define Flash_Base_Address			0x40023C00


typedef struct{
	volatile u32 ACR;
	volatile u32 KEYR;
	volatile u32 OPTKEYR;
	volatile u32 SR;
	volatile u32 CR;
	volatile u32 OPTCR;
	
}FLASH_t;

#define FLASH ((volatile FLASH_t *) 0x40023C00)

/*FLASH CONTROL REGISTER BITs*/
#define PG_BIT			0
#define SER_BIT 		1
#define MER_BIT 		2
#define SNB_BIT			3
#define PSIZE_BIT 		8
#define STRT_BIT		16
#define EOPIE_BIT		24
#define ERRIE_BIT		25
#define LOCK_BIT		31

/*FLASH OPTION BYTES CONTROL REGISTER BITs*/
#define OPTLOCK_BIT		0
#define OPTSTRT_BIT		1
#define nWRP_BIT		16
#define SPRMODE_BIT		31


#endif /*_Flash_Private_H_*/
