//
//  WeemoData.h
//  iOS-SDK
//
//  Created by Charles Thierry on 7/16/13.
//  Copyright (c) 2013 Weemo. All rights reserved.
//

typedef struct  //9*4 + 6*2 + 3 : 51 bytes
{
	uint8_t  LocalCPU;
	uint32_t NetworkLatency;
	
	uint32_t Audio_SentIPThroughput;
	uint32_t Audio_ReceivedIPThroughput;
	uint32_t Audio_SentPcktLoss;
	uint32_t Audio_ReceivedPcktLoss;
	
	uint32_t Video_SentIPThroughput;
	uint32_t Video_ReceivedIPThroughput;
	float	 Video_RealSentRate;
	float	 Video_ReceivedRate;
	uint32_t Video_SentPcktLoss;
	uint32_t Video_ReceivedPcktLoss;
	uint16_t Video_ReceivedJitter;
	uint16_t Video_SendWidth;
	uint16_t Video_SendHeight;
	uint16_t Video_ReceivedWidth;
	uint16_t Video_ReceivedHeight;
	char	 pfm[8];
} WeemoStat;


#define CALLSTATUS_INCOMING 				0x7110
#define CALLSTATUS_RINGING 					0x7120
#define CALLSTATUS_ACTIVE 					0x7130
#define CALLSTATUS_ENDED 					0x7140
#define CALLSTATUS_PROCEEDING 				0x7150
#define CALLSTATUS_PAUSED 					0x7160
