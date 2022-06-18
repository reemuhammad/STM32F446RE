/*
 * ESP8266_inteface.h
 *
 *  Created on: Jan 20, 2022
 *      Author: Omar el Masry
 */

#ifndef ESP8266_INTEFACE_H_
#define ESP8266_INTEFACE_H_
#include "STD_TYPES.h"

void  ESP8266_VidInit            ( void                                                    				      ) ;
void  ESP8266_VidConnectToWiFi   ( u8 * SSID 		 	, u8 * Password                                ) ;
void  ESP8266_VidConnectToSrvTcp ( u8 * Copy_u8Domain 	, u8 * Copy_u8Port                   		  ) ;
void  ESP8266_VidSendHttpReq     ( u8 * Copy_u8Key 	 	, u8 * Copy_u8Data 	, u8 * Copy_u8Length   ) ;
u8 ESP8266_u8ReceiveHttpReq   ( u8 * Copy_u8ChannelID , u8 * Copy_u8Length              		      ) ;
void  ESP8266_VidClearBuffer     ( void                                                    					  ) ;



#endif /* ESP8266_INTEFACE_H_ */
