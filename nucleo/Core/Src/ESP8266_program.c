/*
 * ES8266_program.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Omar el Masry
 */

#include "STD_TYPES.h"
#include "USART_interface.h"

#include "ESP8266_interface.h"

#include "Delay_interface.h"

u8 volatile Iterator = 0  ;
u8 volatile DataCome[200] ;


void MUSART_CallBack ( void ){

	/* Receive ESP8266 Response */
	DataCome[ Iterator ] = MSUART_u8ReadDataRegister(2);
	/* ------------------ */
	Iterator++;
	MUSART_VidClearFlags(2);

}

void ESP8266_VidInit ( void ){

	/* Set USART1 CallBack To Receive The Response Of The ESP8266 */
	MUSART3_voidSetCallBack( MUSART_CallBack );

	/* Sending AT Command To Check ESP8266 Is Working Or Not  */
	MSUART_voidTransmitStringArrayWait(2,(u8*)"AT\r\n" );

	_delay_ms( 3000 );

	/* Clear ESP8266 Buffer */
	ESP8266_VidClearBuffer();

	MSUART_voidTransmitStringArrayWait(2, (u8)"AT+CWMODE=3\r\n" );
	_delay_ms( 3000 );

	ESP8266_VidClearBuffer();

	MSUART_voidTransmitStringArrayWait(2, (u8*)"AT+CIPMODE=0\r\n" );
	_delay_ms( 3000 );

}

void ESP8266_VidConnectToWiFi ( u8* SSID , u8* Password ){

	ESP8266_VidClearBuffer();

	MSUART_voidTransmitStringArrayWait( 2	,	(u8*) "AT+CWJAP=\"" );
	MSUART_voidTransmitStringArrayWait(	2	, 	(u8*) SSID );
	MSUART_voidTransmitStringArrayWait( 2	,	(u8*) "\",\"" );
	MSUART_voidTransmitStringArrayWait( 2	,	(u8*) Password);
	MSUART_voidTransmitStringArrayWait(	2 	,	(u8*) "\"\r\n");
	_delay_ms( 8000 );

}


void ESP8266_VidConnectToSrvTcp ( u8* Copy_u8Domain , u8* Copy_u8Port ){

	ESP8266_VidClearBuffer();

	MSUART_voidTransmitStringArrayWait(	2	,	 (u8*) "AT+CIPSTART=\"TCP\",\"" );
	MSUART_voidTransmitStringArrayWait(	2	,	 (u8*) Copy_u8Domain );
	MSUART_voidTransmitStringArrayWait( 2	,	 (u8*) "\"," );
	MSUART_voidTransmitStringArrayWait(	2	, 	 (u8*) Copy_u8Port );
	MSUART_voidTransmitStringArrayWait(	2	, 	 (u8*) "\r\n" );
	_delay_ms( 2000 );

}

void ESP8266_VidSendHttpReq( u8* Copy_u8Key , u8* Copy_u8Data , u8* Copy_u8Length ){

	ESP8266_VidClearBuffer();

	MSUART_voidTransmitStringArrayWait(	2	,	  (u8*) "AT+CIPSEND=" );
	MSUART_voidTransmitStringArrayWait(	2	,	  (u8*) Copy_u8Length );
	MSUART_voidTransmitStringArrayWait(	2	,	  (u8*) "\r\n" );
	_delay_ms( 4000 );

	ESP8266_VidClearBuffer();

	MSUART_voidTransmitStringArrayWait(	2	,	  (u8*) "GET /update?api_key=" );
	MSUART_voidTransmitStringArrayWait(	2	,	  (u8*) Copy_u8Key );
	MSUART_voidTransmitStringArrayWait(	2	,	  (u8*) "&field1=" );
	MSUART_voidTransmitStringArrayWait(	2	,	  (u8*) Copy_u8Data );
	MSUART_voidTransmitStringArrayWait(	2	,	  (u8*) "\r\n" );
	_delay_ms( 20000 );

}

u8  ESP8266_u8ReceiveHttpReq( u8* Copy_u8ChannelID , u8* Copy_u8Length ){

	ESP8266_VidClearBuffer();

	MSUART_voidTransmitStringArrayWait(	2	,	  (u8*) "AT+CIPSEND=" );
	MSUART_voidTransmitStringArrayWait(	2	,	  (u8*) Copy_u8Length );
	MSUART_voidTransmitStringArrayWait(	2	,	  (u8*) "\r\n" );
	_delay_ms( 4000 );

	ESP8266_VidClearBuffer();

	MSUART_voidTransmitStringArrayWait(	2	,	  (u8*) "GET http://" );
	MSUART_voidTransmitStringArrayWait(	2	,	  (u8*) Copy_u8ChannelID );
	MSUART_voidTransmitStringArrayWait(	2	,	  (u8*) "/code.txt\r\n" );
	_delay_ms( 20000 );

	ESP8266_VidConnectToSrvTcp( (u8*)"162.253.155.226" , (u8*)"80" );

	/*For yrabiot3.freevar.com ( Value Array Index )*/
	return  DataCome[82] ;

}

void ESP8266_VidClearBuffer ( void ){

	u8 LOC_u8Iterator1 = 0 ;
	Iterator     = 0 ;

	for( LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 150 ; LOC_u8Iterator1++ ){

		DataCome[ LOC_u8Iterator1 ] = 0 ;

	}

}


