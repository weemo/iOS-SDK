//
//  WeemoData.h
//  iOS-SDK
//
//  Created by Charles Thierry on 7/16/13.
//  Copyright (c) 2013 Weemo. All rights reserved.
//
#include <stdint.h>


typedef struct
{
	uint8_t  LocalCPU; /**< the local CPU time usage */
	uint32_t NetworkLatency; /**< the round-trip time to the platform we are connected to. */
	
	uint32_t Audio_SentIPThroughput; /**< throughput related to the outgoing audio */
	uint32_t Audio_ReceivedIPThroughput; /**< throughput related to the incoming audio */
	uint32_t Audio_SentPcktLoss; /**< Outgoing Audio packet loss */
	uint32_t Audio_ReceivedPcktLoss; /**< Incoming Audio packet loss */
	
	uint32_t Video_SentIPThroughput; /**< network throughput related to the outgoing video */
	uint32_t Video_ReceivedIPThroughput; /**< throughput related to the incoming video */
	float	 Video_RealSentRate; /**< Capture framerate */
	float	 Video_ReceivedRate; /**< Incoming video receive rate */
	uint32_t Video_SentPcktLoss; /**< Outgoing Video packet loss */
	uint32_t Video_ReceivedPcktLoss; /**< Incoming Video packet loss */
	uint16_t Video_ReceivedJitter; /**< Incoming Video Jitter */
	uint16_t Video_SendWidth; /**< Width of the outgoing video (in px) */
	uint16_t Video_SendHeight; /**< Height of the outgoing video (in px) */
	uint16_t Video_ReceivedWidth; /**< Height of the incoming video (in px) */
	uint16_t Video_ReceivedHeight; /**< Height of the outgoing video (in px) */
	char	 pfm[8]; /**< The platform name */
} WeemoStat; /**< Statistics available for each call*/

#pragma mark - CallStatus

/** Call is incoming.*/
#define CALLSTATUS_INCOMING 				0x7110
/** Your call is outgoing, ringing not yet picked up.*/
#define CALLSTATUS_RINGING 					0x7120
/** The call is ongoing.*/
#define CALLSTATUS_ACTIVE 					0x7130
/** The call was ended.*/
#define CALLSTATUS_ENDED 					0x7140
/** The call is not yet ringing on the remote device.*/
#define CALLSTATUS_PROCEEDING 				0x7150
/** The call was paused.*/
#define CALLSTATUS_PAUSED 					0x7160
/** The recipient is not available.*/
#define CALLSTATUS_USERNOTAVAILABLE			0x7170


#pragma mark - Error codes
/** Error code class: initialization exceptions.*/
#define ERROR_INIT						0x0100
/** Server are not available*/
#define NETWORK_ERROR					ERROR_INIT | 1
/** The MobileApp Identifier is not formated properly*/
#define BAD_APIKEY						ERROR_INIT | 2
/** Tried to authenticate while not connected*/
#define NOT_CONNECTED					ERROR_INIT | 3
/** */
#define ALREADY_AUTHENTICATED			ERROR_INIT | 4

/** Error code class: connection exception.*/
#define ERROR_CONN						0x0200
/** Disconnected: lost network connection.*/
#define NETWORK_LOST					ERROR_CONN | 1
/** Disconnected: Weemo engine destroyed.*/
#define CLOSED							ERROR_CONN | 2

/** Error code class: authentication exception.*/
#define ERROR_AUTH						0x0300
/** Something went wrong on the server during authentication. Are you sure of the userID?*/
#define	SIP_NOK							ERROR_AUTH | 1


#pragma mark - User type
#define USERTYPE_INTERNAL 0x00
#define USERTYPE_EXTERNAL 0x01