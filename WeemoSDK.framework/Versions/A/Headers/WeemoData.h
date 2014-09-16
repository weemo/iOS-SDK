//
//  WeemoData.h
//  iOS-SDK
//
//  Created by Charles Thierry on 7/16/13.
//  Copyright (c) 2013 Weemo. All rights reserved.
//
#include <stdint.h>
#import <AvailabilityMacros.h>

#pragma mark - Call status
typedef enum
{
	callStatus_proceeding = 0,
	callStatus_ringing,
	callStatus_active,
	callStatus_ended,
	callStatus_paused
} callStatus_t;

#pragma mark - Error codes
typedef enum
{
	errInit_general = 0x100,
	errInit_network,
	errInit_badApiKey,
	
	errConn_closed = 0x200,
	
	errAuth_notConnected = 0x300,
	errAuth_alreadyAuthenticated,
	errAuth_sip
} errorCode_t;

#pragma mark - User type

typedef enum
{
	userInternal = 0,
	userExternal
} userProfile_t;


#pragma mark - log levels
/**
 * Log levels used by the Weemo::setLogLevel: . Sending setLogLevel:logLevel_Warn will prevent every message whose priority is lower than Warn(ing) to be displayed.
 * \since 5.1.49
 */
typedef enum
{
	logLevel_Fatal = 0,
	logLevel_Error,
	logLevel_Warn,
	logLevel_Notice,
	logLevel_Info,
} logLevel_t;

/**
 * This is used to describe the video Profile returned by the SDK throught the WeemoCallDelegate::weemoCall:videoProfile: callback.
 * \since 5.1.66
 */
typedef enum
{
	profile_unknown = -1, //< The video in profile is unknown
	profile_lowest, //< landscape dimensions lower than 352*288
	profile_low, //< landscape dimensions between 352*280 included and 640*360 excluded
	profile_high //< High video profile lanscape dimensions greater or equal to 640*360
} video_profile_t;


#define k_MPType		@"MeetingPointType"			//< The type of Meeting point we are creating. One of mpType_t. value is a NSNumber.
#define k_MPLocation	@"MeetingPointLocation"		//< Where the meeting will take place. Value is a NSString, max 128 long.
#define k_MPTitle		@"MeetingPointTitle"		//< The meeting's "human" name. Value is a NSString, max 128 long.
#define	k_MPID			@"MeetingPointID"			//< The meeting's "system" name. Value is a NSString, max 128 long.
#define k_MPStart		@"MeetingPointStartTime"	//< Time at which the meeting will start. Value is a NSDate.
#define	k_MPEnd			@"MeetingPointEndTime"		//< Time at which the meeting will end. Value is a NSDate.

#define k_MPURLAttendee	@"MeetingPointURLAttendee"	//< The Attendee wall URL. Value is a NSString.
#define k_MPURLHost		@"MeetingPointURLHost"		//< The Host wall URL. Value is a NSString.

#define k_MPDisplayName	@"MeetingPointDisplayName"	//< The display name of the contact related to the action.
#define k_MPContactName	@"MeetingPointContactName"	//< The "system" name of the contact related to the action.


#define k_ContactID		@"contactID"
#define k_ContactDN		@"contactDisplayName"
#define k_WithVideo		@"withVideo"
#define k_WithAudio		@"withAudio"
#define k_isConference	@"isConference"
#define k_bkCamera		@"backCamera"


typedef enum
{
	mpType_permanent = 0,
	mpType_scheduled
}mpType_t;


typedef enum
{
	mpSta_default = 0,
	mpSta_autoaccept,
	mpSta_autodeny
} mpAuthorizationMode_t;


typedef enum
{
	mpAtt_pending,
	mpAtt_accepted,
	mpAtt_denied
} mpAttendeeStatus_t;
