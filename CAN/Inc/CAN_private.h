/*
 * CAN_private.h
 *
 *  Created on: May 7, 2022
 *      Author: Reem
 */

#ifndef CAN_PRIVATE_H_
#define CAN_PRIVATE_H_

typedef struct{
	volatile u32 CAN_MCR;
	volatile u32 CAN_MSR;
	volatile u32 CAN_TSR;
	volatile u32 CAN_RF0R;
	volatile u32 CAN_RF1R;
	volatile u32 CAN_IER;
	volatile u32 CAN_ESR;
	volatile u32 CAN_BTR;

}CAN_Control_Status_registers_t;

#define CAN_CONTROL_AND_STATUS		 ( (volatile CAN_Control_Status_registers_t *) 0x40006400 )

typedef struct{
	volatile u32 CAN_TI0R;
	volatile u32 CAN_TDT0R;
	volatile u32 CAN_TDL0R;
	volatile u32 CAN_TDH0R;
	volatile u32 CAN_TI1R;
	volatile u32 CAN_TDT1R;
	volatile u32 CAN_TDL1R;
	volatile u32 CAN_TDH1R;
	volatile u32 CAN_TI2R;
	volatile u32 CAN_TDT2R;
	volatile u32 CAN_TDL2R;
	volatile u32 CAN_TDH2R;
	volatile u32 CAN_RI0R;
	volatile u32 CAN_RDT0R;
	volatile u32 CAN_RDL0R;
	volatile u32 CAN_RDH0R;
	volatile u32 CAN_RI1R;
	volatile u32 CAN_RDT1R;
	volatile u32 CAN_RDL1R;
	volatile u32 CAN_RDH1R;

}CAN_mailbox_registers_t;

#define CAN_MAILBOX		 ( (volatile CAN_mailbox_registers_t *) ( 0x40006400 + 0x180 ) )

#define CAN_FMR		      *( (volatile u32 *) ( 0x40006400 + 0x200 ) )
#define CAN_FM1R          *( (volatile u32 *) ( 0x40006400 + 0x204 ) )
#define CAN_FS1R	      *( (volatile u32 *) ( 0x40006400 + 0x20C ) )
#define CAN_FFA1R	      *( (volatile u32 *) ( 0x40006400 + 0x214 ) )
#define CAN_FA1R	      *( (volatile u32 *) ( 0x40006400 + 0x21C ) )

typedef struct{
    volatile u32 CAN_F0R1;
    volatile u32 CAN_F0R2;
    volatile u32 CAN_F1R1;
    volatile u32 CAN_F1R2;
    volatile u32 CAN_F2R1;
    volatile u32 CAN_F2R2;
    volatile u32 CAN_F3R1;
    volatile u32 CAN_F3R2;
    volatile u32 CAN_F4R1;
    volatile u32 CAN_F4R2;
    volatile u32 CAN_F5R1;
    volatile u32 CAN_F5R2;
    volatile u32 CAN_F6R1;
    volatile u32 CAN_F6R2;
    volatile u32 CAN_F7R1;
    volatile u32 CAN_F7R2;
    volatile u32 CAN_F8R1;
    volatile u32 CAN_F8R2;
    volatile u32 CAN_F9R1;
    volatile u32 CAN_F9R2;
    volatile u32 CAN_F10R1;
    volatile u32 CAN_F10R2;
    volatile u32 CAN_F11R1;
    volatile u32 CAN_F11R2;
    volatile u32 CAN_F12R1;
    volatile u32 CAN_F12R2;
    volatile u32 CAN_F13R1;
    volatile u32 CAN_F13R2;
    volatile u32 CAN_F14R1;
    volatile u32 CAN_F14R2;
    volatile u32 CAN_F15R1;
    volatile u32 CAN_F15R2;
    volatile u32 CAN_F16R1;
	volatile u32 CAN_F16R2;
	volatile u32 CAN_F17R1;
	volatile u32 CAN_F17R2;
	volatile u32 CAN_F18R1;
	volatile u32 CAN_F18R2;
	volatile u32 CAN_F19R1;
	volatile u32 CAN_F19R2;
	volatile u32 CAN_F20R1;
	volatile u32 CAN_F20R2;
	volatile u32 CAN_F21R1;
	volatile u32 CAN_F21R2;
	volatile u32 CAN_F22R1;
	volatile u32 CAN_F22R2;
	volatile u32 CAN_F23R1;
	volatile u32 CAN_F23R2;
	volatile u32 CAN_F24R1;
	volatile u32 CAN_F24R2;
	volatile u32 CAN_F25R1;
	volatile u32 CAN_F25R2;
	volatile u32 CAN_F26R1;
	volatile u32 CAN_F26R2;
	volatile u32 CAN_F27R1;
	volatile u32 CAN_F27R2;

}CAN_Filter_Bank_Registers_t;

#define CAN_FILTER_BANK		 ( (volatile CAN_Filter_Bank_Registers_t *) ( 0x40006400 + 0x240 ) )

#define CAN_FILTER_BANK_BASE_ADDRESS								0x40006400

volatile u32 * Filter_Bank[28*2] =
{
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x240),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x244),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x248),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x24C),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x250),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x254),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x258),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x25C),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x260),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x264),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x268),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x26C),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x270),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x274),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x278),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x27C),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x280),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x284),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x288),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x28C),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x290),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x294),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x298),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x29C),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2A0),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2A4),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2A8),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2AC),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2B0),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2B4),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2B8),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2BC),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2C0),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2C4),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2C8),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2CC),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2D0),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2D4),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2D8),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2DC),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2E0),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2E4),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2E8),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2EC),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2F0),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2F4),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2F8),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x2FC),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x300),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x304),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x308),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x30C),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x310),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x314),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x318),
	(volatile u32 *) (CAN_FILTER_BANK_BASE_ADDRESS + 0x31C),

};

enum{
	/*CAN master control register (CAN_MCR)*/
	CAN_MCR_INRQ =0,
	CAN_MCR_SLEEP,
	CAN_MCR_TXFP,
	CAN_MCR_RFLM,
	CAN_MCR_NART,
	CAN_MCR_AWUM,
	CAN_MCR_ABOM,
	CAN_MCR_TTCM,
	CAN_MCR_RESET =15,
	CAN_MCR_DBF,

	/*CAN master status register (CAN_MSR)*/
	CAN_MSR_INAK =0,
	CAN_MSR_SLAK,
	CAN_MSR_ERRI,
	CAN_MSR_WKUI,
	CAN_MSR_SLAKI,
	CAN_MSR_TXM =8,
	CAN_MSR_RXM,
	CAN_MSR_SAMP,
	CAN_MSR_RX,

	/*CAN transmit status register (CAN_TSR)*/
	CAN_TSR_RQCP0 =0,
	CAN_TSR_TXOK0,
	CAN_TSR_ALST0,
	CAN_TSR_TERR0,
	CAN_TSR_ABRQ0 =7,
	CAN_TSR_RQCP1,
	CAN_TSR_TXOK1,
	CAN_TSR_ALST1,
	CAN_TSR_TERR1,
	CAN_TSR_ABRQ1 =15,
	CAN_TSR_RQCP2,
	CAN_TSR_TXOK2,
	CAN_TSR_ALST2,
	CAN_TSR_TERR2,
	CAN_TSR_ABRQ2 =23,
	CAN_TSR_CODE_0,
	CAN_TSR_CODE_1,
	CAN_TSR_TME0,
	CAN_TSR_TME1,
	CAN_TSR_TME2,
	CAN_TSR_LOW0,
	CAN_TSR_LOW1,
	CAN_TSR_LOW2,

	/*CAN receive FIFO 0 register (CAN_RF0R)*/
	CAN_RF0R_FMP0_0 =0,
	CAN_RF0R_FMP0_1,
	CAN_RF0R_FULL0 =3,
	CAN_RF0R_FOVR0,
	CAN_RF0R_RFOM0,

	/*CAN receive FIFO 1 register (CAN_RF1R)*/
	CAN_RF1R_FMP1_0 =0,
	CAN_RF1R_FMP1_1,
	CAN_RF1R_FULL1 =3,
	CAN_RF1R_FOVR1,
	CAN_RF1R_RFOM1,

	/*CAN interrupt enable register (CAN_IER)*/
	CAN_IER_TMEIE =0,
	CAN_IER_FMPIE0,
	CAN_IER_FFIE0,
	CAN_IER_FOVIE0,
	CAN_IER_FMPIE1,
	CAN_IER_FFIE1,
	CAN_IER_FOVIE1,
	CAN_IER_EWGIE =8,
	CAN_IER_EPVIE,
	CAN_IER_BOFIE,
	CAN_IER_LECIE,
	CAN_IER_ERRIE =15,
	CAN_IER_WKUIE,
	CAN_IER_SLKIE,

	/*CAN error status register (CAN_ESR)*/
	CAN_ESR_EWGF,
	CAN_ESR_EPVF,
	CAN_ESR_BOFF,
	CAN_ESR_LEC_0,
	CAN_ESR_LEC_1,
	CAN_ESR_LEC_2,
	CAN_ESR_TEC_0 =16,
	CAN_ESR_TEC_1,
	CAN_ESR_TEC_2,
	CAN_ESR_TEC_3,
	CAN_ESR_TEC_4,
	CAN_ESR_TEC_5,
	CAN_ESR_TEC_6,
	CAN_ESR_TEC_7,
	CAN_ESR_REC_0,
    CAN_ESR_REC_1,
	CAN_ESR_REC_2,
	CAN_ESR_REC_3,
	CAN_ESR_REC_4,
	CAN_ESR_REC_5,
	CAN_ESR_REC_6,
	CAN_ESR_REC_7,

	/*CAN bit timing register (CAN_BTR)*/
	CAN_BTR_BRP_0 =0,
	CAN_BTR_BRP_1,
	CAN_BTR_BRP_2,
	CAN_BTR_BRP_3,
	CAN_BTR_BRP_4,
	CAN_BTR_BRP_5,
	CAN_BTR_BRP_6,
	CAN_BTR_BRP_7,
	CAN_BTR_BRP_8,
	CAN_BTR_BRP_9,
	CAN_BTR_TS1_0 =16,
	CAN_BTR_TS1_1,
	CAN_BTR_TS1_2,
	CAN_BTR_TS1_3,
	CAN_BTR_TS2_0,
	CAN_BTR_TS2_1,
	CAN_BTR_TS2_2,
	CAN_BTR_SJW_0 =24,
	CAN_BTR_SJW_1,
	CAN_BTR_LBKM =30,
	CAN_BTR_SILM,

	/*CAN TX mailbox identifier register (CAN_TIxR) (x = 0..2)*/
	CAN_TIxR_TXRQ =0,
	CAN_TIxR_RTR,
	CAN_TIxR_IDE,
	CAN_TIxR_EXID,
	CAN_TIxR_STID = 21,

	/*CAN mailbox data length control and time stamp register (CAN_TDTxR) (x = 0..2)*/
	AN_TDTxR_DLC =0,
	AN_TDTxR_TIME =16,

	/*CAN mailbox data low register (CAN_TDLxR) (x = 0..2)*/
	CAN_TDLxR_DATA0 =0,
	CAN_TDLxR_DATA1 =8,
	CAN_TDLxR_DATA2 =16,
	CAN_TDLxR_DATA3 =24,

	/*CAN mailbox data high register (CAN_TDHxR) (x = 0..2)*/
	CAN_TDHxR_DATA4 =0,
	CAN_TDHxR_DATA5 =8,
	CAN_TDHxR_DATA6 =16,
	CAN_TDHxR_DATA7 =24,

	/*CAN receive FIFO mailbox identifier register (CAN_RIxR) (x = 0..1)*/
    CAN_RIxR_RTR =1,
	CAN_RIxR_IDE,
    CAN_RIxR_EXID,
    CAN_RIxR_STID = 21,

	/*CAN receive FIFO mailbox data length control and time stamp register (CAN_RDTxR) (x = 0..1) */
	CAN_RDTxR_DLC =0,
	CAN_RDTxR_FMI =8,
	CAN_RDTxR_TIME =16,

	/*CAN receive FIFO mailbox data low register (CAN_RDLxR) (x = 0..1)*/
    CAN_RDLxR_DATA0 =0,
	CAN_RDLxR_DATA1 =8,
	CAN_RDLxR_DATA2 =16,
	CAN_RDLxR_DATA3 =24,

	/*CAN receive FIFO mailbox data high register (CAN_RDHxR) (x = 0..1)*/
	CAN_RDHxR_DATA4 =0,
	CAN_RDHxR_DATA5 =8,
	CAN_RDHxR_DATA6 =16,
	CAN_RDHxR_DATA7 =24,

	/*CAN filter master register (CAN_FMR)*/
	CAN_FMR_FINIT =0,
	CAN_FMR_CANSB =8,

}Registers_Bits_e;

void (*CAN1_TX_CallBack)  (void) = NULL ;
void (*CAN1_RX0_CallBack) (void) = NULL ;
void (*CAN1_RX1_CallBack) (void) = NULL ;
void (*CAN1_SCE_CallBack) (void) = NULL ;

#endif /* CAN_PRIVATE_H_ */
