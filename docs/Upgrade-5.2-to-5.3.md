# Migration 5.2 - 5.3

## Media Libraries

The video and audio libraries are now integrated in the SDK, and are not to be integrated in 
the app.
Please remove libvpx.a and libopus.a from the list of libraries in your application.

## Call's statuses 


In **5.2 iOS SDK**, call's statuses are described by defines:

	#define CALLSTATUS_RINGING 					0x7120
	#define CALLSTATUS_ACTIVE 					0x7130
	#define CALLSTATUS_ENDED 					0x7140
	#define CALLSTATUS_PROCEEDING 				0x7150

In **5.3 iOS SDK**, call's statuses are described by enum:

	typedef enum
	{
		callStatus_proceeding = 0,
		callStatus_ringing,
		callStatus_active,
		callStatus_ended,
		callStatus_paused
	} callStatus_t;
	
Make sure to modify your mobile App is this way !

Appearance of `callStatus_paused`, that is not used as of now


## Connection's and Authentication's errors


In **5.2 iOS SDK**, Connection's and Authentication's errors are described by defines:


	#define ERROR_INIT						0x0100
	#define NETWORK_ERROR					ERROR_INIT | 1
	#define BAD_APIKEY						ERROR_INIT | 2
	#define NOT_CONNECTED					ERROR_INIT | 3
	#define ALREADY_AUTHENTICATED			ERROR_INIT | 4
	#define INVALID_TOKEN					ERROR_INIT | 5

	#define ERROR_CONN						0x0200
	#define NETWORK_LOST					ERROR_CONN | 1
	#define CLOSED							ERROR_CONN | 2

	#define ERROR_AUTH						0x0300
	#define	SIP_NOK							ERROR_AUTH | 1

In **5.3 iOS SDK**, Connection's and Authentication's errors are now described by enum:

	typedef enum
	{
		errInit_general = 0x100, /**< An non specific error occured */
		errInit_network, /**< A network related error occured while trying to connect*/
		errInit_badAppID, /**< The appID you provided was nil or equal to  @"" */
		errConn_closed = 0x200, /**< An error occured while you were disconnecting */
		errAuth_notConnected = 0x300, /**< You tried to authenticate although you are not connected*/
		errAuth_alreadyAuthenticated, /**< You tried to authenticate although you are already authenticated*/
		errAuth_sip /**<  An error occured while you were trying to authenticate*/
	} errorCode_t;

Make sure to modify your mobile App is this way !

`INVALID_TOKEN`, `NETWORK_LOST` and `ERROR_CONN`, which were not used, have been removed in **5.3 iOS SDK**.


## User types

In **5.2 iOS SDK**, user types are described by defines:


	#define USERTYPE_INTERNAL 0x00
	#define USERTYPE_EXTERNAL 0x01

In **5.3 iOS SDK**, user types are now described by enum:

	typedef enum
	{
		userInternal = 0,
		userExternal
	} userProfile_t;

Make sure to modify your mobile App is this way !
