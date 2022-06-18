/*
 * CAN_config.h
 *
 *  Created on: May 8, 2022
 *      Author: Reem
 */

#ifndef CAN_CONFIG_H_
#define CAN_CONFIG_H_

#ifndef	ENABLE
#define ENABLE 					1
#endif

#ifndef	DISABLE
#define DISABLE 				0
#endif

/* Choose either: ENABLE or DISABLE */
#define FIFO0_RECEIVE_INTERRUPT								DISABLE
#define FIFO1_RECEIVE_INTERRUPT								DISABLE

/*Activate lock-back mode from here if wanted*/
#define LOCK_BACK_MODE										DISABLE
#define LOCK_BACK_COMBINED_WITH_SILENT_MODE					ENABLE


u32 Filter_Banks_Config[28*2]=
		{
			/*Filter_0_Bank_1*/
				0xC0000000,
			/*Filter_0_Bank_2*/
				0xC0000000,

			/*Filter_1_Bank_1*/
				   0x0000,
			/*Filter_1_Bank_2*/
				   0x0000,

		    /*Filter_2_Bank_1*/
				   0x0000,
		    /*Filter_2_Bank_2*/
				   0x0000,

		    /*Filter_3_Bank_1*/
				   0x0000,
		    /*Filter_3_Bank_2*/
				   0x0000,

		    /*Filter_4_Bank_1*/
				   0x0000,
		    /*Filter_4_Bank_2*/
				   0x0000,

		    /*Filter_5_Bank_1*/
				   0x0000,
		    /*Filter_5_Bank_2*/
				   0x0000,

		    /*Filter_6_Bank_1*/
				   0x0000,
	        /*Filter_6_Bank_2*/
				   0x0000,

		    /*Filter_7_Bank_1*/
				   0x0000,
			/*Filter_7_Bank_2*/
				   0x0000,

		    /*Filter_8_Bank_1*/
				   0x0000,
			/*Filter_8_Bank_2*/
				   0x0000,

		    /*Filter_9_Bank_1*/
				   0x0000,
			/*Filter_9_Bank_2*/
				   0x0000,

		    /*Filter_10_Bank_1*/
				   0x0000,
		    /*Filter_10_Bank_2*/
				   0x0000,

		    /*Filter_11_Bank_1*/
				   0x0000,
			/*Filter_11_Bank_2*/
				   0x0000,

		    /*Filter_12_Bank_1*/
				   0x0000,
			/*Filter_12_Bank_2*/
				   0x0000,

		    /*Filter_13_Bank_1*/
				   0x0000,
			/*Filter_13_Bank_2*/
				   0x0000,

			/*Filter_14_Bank_1*/
				   0x0000,
			/*Filter_14_Bank_2*/
				   0x0000,

		    /*Filter_15_Bank_1*/
				   0x0000,
			/*Filter_15_Bank_2*/
				   0x0000,

			/*Filter_16_Bank_1*/
				   0x0000,
			/*Filter_16_Bank_2*/
				   0x0000,

		    /*Filter_17_Bank_1*/
				   0x0000,
			/*Filter_17_Bank_2*/
				   0x0000,

			/*Filter_18_Bank_1*/
				   0x0000,
			/*Filter_18_Bank_2*/
				   0x0000,

			/*Filter_19_Bank_1*/
				   0x0000,
			/*Filter_19_Bank_2*/
				   0x0000,

			/*Filter_20_Bank_1*/
				   0x0000,
			/*Filter_20_Bank_2*/
				   0x0000,

			/*Filter_21_Bank_1*/
				   0x0000,
			/*Filter_21_Bank_2*/
				   0x0000,

			/*Filter_22_Bank_1*/
				   0x0000,
			/*Filter_22_Bank_2*/
				   0x0000,

			/*Filter_23_Bank_1*/
				   0x0000,
			/*Filter_23_Bank_2*/
				   0x0000,

		    /*Filter_24_Bank_1*/
				   0x0000,
		    /*Filter_24_Bank_2*/
				   0x0000,

		    /*Filter_25_Bank_1*/
				   0x0000,
			/*Filter_25_Bank_2*/
				   0x0000,

			/*Filter_26_Bank_1*/
				   0x0000,
			/*Filter_26_Bank_2*/
				   0x0000,

			/*Filter_27_Bank_1*/
				   0x0000,
			/*Filter_27_Bank_2*/
				   0x0000
		};

#endif /* CAN_CONFIG_H_ */
