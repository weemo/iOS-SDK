//
//  Weemo.h
//  iOS-SDK
//
//  Created by Salomon BRYS on 11/07/13.
//  Copyright (c) 2013 Weemo. All rights reserved.
//


#import "WeemoData.h"
#import "WeemoCall.h"

/**
 * A meeting point is a virtual space. It is created by a Host and can be joined by Attendees. Hosts can update meeting
 * point's details, fetch the list of user wishing to join, send invitations (once the call is started) and accept/or 
 * deny attendees join requests. Attendees can request to join a meeting point, and once accepted can call the conference.
 *
 * The callflow should be thus:
 *
 * Host creates Meeting point
 * Host share the meetingPoint ID
 * Host can update the Meeting point details
 * Attendees send join requests based on the meeting point ID
 * Host is notified of the join requests
 * Host starts the conference
 * Host can accept/deny Attendees request
 * Host can send invites to Attendees
 * Potential Attendees receives join requests, accept or deny them.
 *
 * Host starts the call
 *
 * Host can accept/deny Attendees request
 * Host can send invites to Attendees
 * Potential Attendees receives join requests, accept or deny them.
 * \since 5.3
 */
@protocol WeemoMeetingPointDelegate <NSObject>

/**
 * The meeting point was created. Once this has been fired, the MP's ID can be shared to future Attendees and the 
 * call related to the Meeting Point can be created. Attendees can only be invited once this call has been created.
 *
 * \param mp The meeting point's details. Keys for the dictionary are:
 * <dl>
 * <dt>k_MPID:</dt>		<dd>NSString - the meeting point id </dd>
 * <dt>k_MPURLAttendee:</dt>	<dd>NSString - The attendee wall URL </dd>
 * <dt>k_MPURLHost:</dt>		<dd>NSString - The host wall URL </dd>
 * </dl>
 * If nil, an error occured.
 * \sa Weemo::createMeetingPointWithData:
 * \since 5.3
 */
- (void)weemoMeetingPointCreated:(NSDictionary *)mp;

/**
 * A meeting point was deleted.
 * \param mp The deleted meeting point id. If nil, an error occured.
 * \warning Can not delete Meeting point if it was created using type_permanent.
 * \sa Weemo::deleteMeetingPoint:
 * \since 5.3
 */
- (void)weemoMeetingPointDeleted:(NSString *)mp;

/**
 * A meeting point information were requested through Weemo::getMeetingPointData:
 * \param mp The meeting point's details.  Keys for the dictionary are:
 * <dl>
 * <dt>k_MPEnd:</dt>		<dd>NSNumber from int - end as unsigned int based on 1970 </dd>
 * <dt>k_MPID:</dt>	<dd>NSString - the meeting point id </dd>
 * <dt>k_MPLocation:</dt>	<dd>NSString describing the location - 128 char max </dd>
 * <dt>k_MPStart:</dt>		<dd>NSNumber from int - start as unsigned int based on 1970 </dd>
 * <dt>k_MPTitle:</dt>		<dd>NSString - a user defined name, describing the meeting - 128 char max </dd>
 * </dl>
 * If nil, an error occured.
 * \sa Weemo::getMeetingPointData:
 * \since 5.3
 */
- (void)weemoMeetingPointDetails:(NSDictionary *)mp;

/**
 *
 * \param mp The meeting point's details.  Keys for the dictionary are:
 * <dl>
 * <dt>k_MPURLAttendee:</dt>	<dd>NSString describing the attendee's Wall URL</dd>
 * <dt>k_MPID:</dt>		<dd>NSString - the meeting point id </dd>
 * <dt>k_MPURLHost:</dt>		<dd>NSString describing the host's Wall URL</dd>
 * </dl>
 * If nil, an error occured.
 * \sa Weemo::getMeetingPointData:
 * \since 5.3
 */
- (void)weemoMeetingPointURLs:(NSDictionary *)mp;

/**
 * The meeting point was updated, here comes the new infos.
 * \param mp The new meeting point's details.  Keys for the dictionary are:
 * <dl>
 * <dt>k_MPEnd:</dt>		<dd>NSNumber from int - end as unsigned int based on 1970 </dd>
 * <dt>k_MPID:</dt>	<dd>NSString - the meeting point id </dd>
 * <dt>k_MPLocation:</dt>	<dd>NSString describing the location - 128 char max </dd>
 * <dt>k_MPStart:</dt>		<dd>NSNumber from int - start as unsigned int based on 1970 </dd>
 * <dt>k_MPTitle:</dt>		<dd>NSString - a user defined name, describing the meeting - 128 char max </dd>
 * </dl>
 * If nil, an error occured.
 * \sa Weemo::updateMeetingPoint:withData:
 * \since 5.3
 */
- (void)weemoMeetingPointUpdated:(NSDictionary *)mp;


/**
 * \brief The meeting was cancelled by the host after the user reached it.
 * \param mpID The id of the cancelled meeting point. If nil, an error occured.
 * \since 5.3
 */
- (void)weemoMeetingPointCancelled:(NSString *)mpID;


/**
 * \brief The meeting point was stopped after the user reached it.
 * \param mpID The id of the stopped meeting point. If nil, an error occured.
 * \since 5.3
 */
- (void)weemoMeetingPointStopped:(NSString *)mpID;

@end

/**
 * \brief This protocol represent the callback an attendee expects.
 * \since 5.3
 */
@protocol WeemoHostDelegate <NSObject>

/**
 * \brief
 * \param infos Data about the soon-to-become attendee
 * <dl>
 * <dt>k_MPContactName</dt>	<dd>NSString - the contact ID</dd>
 * <dt>k_MPDisplayName</dt>	<dd>NSString - the display name of the pretender</dd>
 * <dt>k_MPID</dt>		<dd>NSString - the meeting point id </dd>
 * </dl>
 *
 * \since 5.3
 *
 */
- (void)weemoHostNewAttendee:(NSDictionary *)infos;

/**
 * An invite operation was cancelled. This is a common operation between the Host and the Delegate, 
 * so it is the responsability of the app to remember which operation has been cancelled (invite or join request).
 * \since 5.3
 */
- (void)weemoOperationCancelled;

/**
 * The Meeting Point authorization status was updated. Answers a host call to the the meeting point to Weemo::MeetingPoint:SetAuthorizationStatus:
 * \param mpID The ID of the related MeetinPoint
 * \param status One of the mpStatus_t value
 * \sa Weemo::MeetingPoint:SetAuthorizationStatus:
 * \since 5.3
 */
- (void)weemoMeetingPoint:(NSString *)mpID statusUpdate:(mpAuthorizationMode_t)status;


/**
 * A meeting point was hosted. Answers a Weemo::MeetingPointHostCall: by the host.
 * \param mpID The handle of the MeetingPoint.
 * \sa Weemo::MeetingPointHostCall:
 * \since 5.3
 */
- (void)weemoMeetingPointStarted:(NSString *)mpID;

@end

/**
 * This protocol represent the callback an attendee expects.
 * \since 5.3
 */
@protocol WeemoAttendeeDelegate <NSObject>

/**
 * An join request operation was cancelled. This is a common operation between the Host and the Delegate,
 * so it is the responsability of the app to remember which operation has been cancelled (invite or join request).
 * \since 5.3
 */
- (void)weemoOperationCancelled;

/**
 * The attendee asked to join a MP, this is the status.
 * \param status If mpAtt_pending: the Host did not accept nor refuse yet, mpAtt_granted: the Host granted access, mpAtt_denied: the Host denied access.
 * \param mpID The meeting point id.
 * \since 5.3
 */
- (void)weemoAttendeeAuthorization:(mpAttendeeStatus_t)status forMeeting:(NSString *)mpID;

/**
 * The attendee was invited to a meeting point.
 * \param mpID The meeting point id.
 * \since 5.3
 */
- (void)weemoAttendeeWasInvitedToMeeting:(NSString *)mpID;

@end


/**
 * \brief Delegate for the Weemo Singleton. Allows the Host Application to be notified upon connection events & call creation.
 * \since 5.0
 */
@protocol WeemoDelegate <NSObject>

/**
 * \brief This function will be called after a call is created, either by calling a contact or receiving a call.
 * To accept the call, use WeemoCall::resume. To deny it, use WeemoCall::hangup. The WeemoCall object can possess a
 * delegate of its own, WeemoCallDelegate. In case of an incoming call, the WeemoCall::contactID is nil, as only the display
 * name is sent through the network.
 *
 * \param call The call created, can't be nil. Host App depends on the WeemoCall::callStatus value (CALLSTATUS_* type value)
 *
 * \sa Weemo::createCall:
 * \sa The definition of the CALLSTATUS_* variables (found in WeemoData.h).
 * \since 5.0
 */
- (void)weemoCallCreated:(WeemoCall*)call;


/**
 * \brief This function will be called after a call is stopped. The \param call will be released soon after this method returns.
 *
 * \param call The call that is stopped.
 * \since 5.0
 */
- (void)weemoCallEnded:(WeemoCall*)call;

/**
 * \brief Called by the Weemo singleton after the authentication step.
 * \param error If authentication failed, error will be different from nil. The debugDescription field of the NSError returns a
 * NSString* describing the error in human terms. Otherwise, it is nil.
 * \sa Weemo::authenticateWithUserID:toDomain:
 * \since 5.0
 */
- (void)weemoDidAuthenticate:(NSError*)error;


/**
 * \brief Called when Weemo singleton ended its initialization. If no error occured the Weemo singleton is connected and users can proceed to the authentication step.
 *
 * \param error Nil if no error occured. If different from nil then the connection did NOT succeed. The debugDescription field of
 * the NSError returns a NSString* describing the error in human terms.
 * \sa Weemo::WeemoWithURLReferer:andDelegate:error:
 * \since 5.0
 */
- (void)weemoDidConnect:(NSError*)error;

@optional

/**
 * \brief Called when Weemo disconnected from the server
 *
 * \param error Nil if the Weemo singleton disconnected normally. The debugDescription field of the NSError returns a
 * NSString* describing the error in human terms.
 * \sa Weemo::disconnect
 * \since 5.0
 */
- (void)weemoDidDisconnect:(NSError*)error;

/**
 * \brief Called after a contact is checked through the use of the Weemo::getStatus:.
 *
 * This delegate function is only called when the user/host application specifically calls the Weemo::getStatus: method.
 *
 * Use this function as a GUI updater, e.g. disabling a call button in case of \c !canBeCalled before displaying the view.
 *
 * \param contactUID the contact checked
 * \param canBeCalled YES if the contact can be called, NO otherwise.
 * \sa Weemo::getStatus:
 * \since 5.0
 */
- (void)weemoContact:(NSString*)contactUID canBeCalled:(BOOL)canBeCalled;

/**
 * \brief This function is called between the app's call to Weemo::authenticateWithToken:andType: and the WeemoDelegate::weemoDidAuthenticate: call.
 *
 * \param error If an error occured during authentication, this function may be called with an error param non nil.
 * \since 5.0
 */
- (void)weemoWillAuthenticate:(NSError *)error;

/**
 * This callback is called upon data reception. This data packet size is less than 1536B.
 * \param data The data received
 * \param contactUID The name of the contact who sent the message
 * \param contactID Used to reply to the message, as second argument to the Weemo::replyData:toContactID:
 * \sa Weemo::sendData:toContact:
 * \since 5.2
 */
- (void)weemoReceivedData:(NSData *)data from:(NSString *)contactUID withID:(uint8_t)contactID;

@end

/**
 * \brief Weemo singleton. This is the main object of the SDK.
 *
 * Remarks:
 *
 * This singleton is instancianted in the host application by using the Weemo::WeemoWithURLReferer:andDelegate:error: class function. After initiating the singleton, authentication can happen, upon WeemoDelegate::weemoDidAuthenticate: call.
 *
 * The singleton can be invoked anytime after instantiation through Weemo::instance. If the instantiation isn't completed by the time Weemo::instance is called, nil is returned.
 *
 * The Weemo::foreground and Weemo::background method are to be called everytime the host application goes to background/foreground. Failure to do so will result in undefined behavior, especially regarding on-going calls.
 */
@interface Weemo : NSObject

/**
 * \brief Creates a Weemo singleton Object. The initialization is asynchronous, the WeemoDelegate::weemoDidConnect:
 * will be called upon singleton connection.
 *
 * \param appID The Application Identifier. Must not be nil.
 * \param delegate The delegate object that implements the WeemoDelegate protocol
 * \param error When initialization has failed and this is not nil, this will be filled with a describing error. The debugDescription
 * field of the NSError returns a NSString* describing the error in human terms.
 * \sa WeemoDelegate::weemoDidConnect:
 * \since 5.0
 */
+ (Weemo *)WeemoWithAppID:(NSString *)appID
			  andDelegate:(id<WeemoDelegate>)delegate
					error:(NSError *__autoreleasing *)error __attribute__((nonnull (1)));

/**
 * \brief Returns the Weemo singleton instance, if instantiated.
 *
 * \return The Weemo singleton or nil if the SDK was not instantiated.
 * \since 5.0
 */
+ (Weemo*)instance;

/**
 * Used for identification purpose.
 * \return The version of the Weemo SDK
 * \since 5.0
 */
+ (NSString *)getVersion;


/**
 * \brief Connects to servers with the given token. The connection is asynchronous, WeemoDelegate::weemoDidAuthenticate: will be called
 * upon user token validation.
 * \param token The token to be used for authentication. Must not be nil. In case of type being USERTYPE_EXTERNAL, set it to the parent's UID.
 * \param type The type of the userID, USERTYPE_EXTERNAL or USERTYPE_INTERNAL.
 * \sa WeemoDelegate::weemoDidAuthenticate:
 * \since 5.0
 */
- (BOOL)authenticateWithToken:(NSString *)token andType:(int)type __attribute__((nonnull (1)));

/**
 * \brief Disconnects from weemo servers. A call to WeemoDelegate::weemoDidDisconnect: is to be expected upon disconnection.
 * \sa WeemoDelegate::weemoDidDisconnect:
 * \since 5.0
 */
- (BOOL)disconnect;

/**
 * Reset the whole thing. Connection is dropped and data forgotten.
 *
 */
+ (void)reset;

/**
 * \brief Check if a user can be called. WeemoDelegate::weemoContact:canBeCalled: is called upon callback from the network.
 *
 * \param contactUID The ID of the contact to check. Must not be nil.
 * \sa WeemoDelegate::weemoContact:canBeCalled:
 * \since 5.0
 */
- (void)getStatus:(NSString *)contactUID __attribute__((nonnull (1)));

/**
 * Overrides the default bandwidth parameters by changing the max video FPS and bandwith, and adding a resolution divider.
 * Settings any of this value to 0 will reset the setting to default values.
 * \param maxfps The max FPS wanted from the encoder. valid values are 1-30. Set to 0 to get back to defaults
 * \param maxBitrate Max bitrate for the video encding. 1-1000000, unit is bps
 * \param resolutionDiv Values are 1 or 2. Setting 2 will divide the video frame dimension by 2 (i.e. 352*288 becomes 176*144)
 * \since 5.1
 */
- (void)overrideVideoFPS:(int)maxfps andVideoMaxBitrate:(int)maxBitrate andResolutionDivider:(int)resolutionDiv;

/**
 * Overrides two audio encoding parameters and the CPU usage of the video encoder.
 * \param complexity The complexity used for the audio encoding. 0-10, 10 is better quality, more cpu consuming. Default is 4.
 * \param bitrate The audio bitrate in bps. 16000 - 64000. default is 24000.
 * \param cpuusage The cpu usage of the video encoder. 0-16, 0 being the most intensive. default is 8.
 * \since 5.2
 */
- (void)overrideAudioComplexity:(int)complexity andAudioBitrate:(int)bitrate andVideoCPUUsage:(int)cpuusage;

/**
 * Restore defaults bandwidth parameters. Equivalent to call [[Weemo instance] setCallMaxFPS:0 andVideoMaxBitrate:0 andResolutionDivider:0];
 * \since 5.1
 */
- (void)resetBandwidthDefaults;

#pragma mark - One-to-One Call

/**
 * \brief Creates a call whose recipient is \c contactUID.
 * 
 * The call is immediately created. If the callee is not available, the call is ended almost immediately. 
 * The call is returned to the application throught the use of the WeemoDelegate::weemoCallCreated: method.
 * \param contactUID The ID of the contact or the conference to call. Must not be nil.
 * \sa WeemoDelegate::weemoCallCreated:
 * \sa WeemoCall::contactID
 * \sa Weemo::createCall:andSetDisplayName:
 * \since 5.0
 */
- (void)createCall:(NSString*)contactUID __attribute__((nonnull (1)));

/**
 * \brief Creates a call whose recipient is \p contactUID and set the contact's display name to \p displayName.
 *
 * The call is immediately created. If the callee is not available, the call is ended almost immediately. The call is returned to the
 * application throught the use of the WeemoDelegate::weemoCallCreated: method.
 *
 * \param contactUID The ID of the contact or the conference to call. Must not be nil.
 * \param displayName The contact display name to be used. Must not be nil.
 * \sa WeemoDelegate::weemoCallCreated:
 * \sa WeemoCall::contactID
 * \sa WeemoCall::contactDisplayName
 * \sa Weemo::createCall:
 * \since 5.0
 */
- (void)createCall:(NSString *)contactUID andSetDisplayName:(NSString *)displayName __attribute__((nonnull (1, 2)));


/**
 * \brief Creates a call whose recipient is \p contactUID and set the contact's display name to \p displayName. 
 *
 * The call is immediately created. If the addressee is not available, the call is ended almost immediately. The call is returned to the
 * application throught the use of the WeemoDelegate::weemoCallCreated: method.
 *
 * \param contactUID The ID of the contact or the conference to call. Must not be nil.
 * \param displayName The contact display name to be used. Must not be nil.
 * \param videoEnabled true if the call should have videoOut enable by the time the remote picks up
 * \sa WeemoDelegate::weemoCallCreated:
 * \sa WeemoCall::contactID
 * \sa WeemoCall::contactDisplayName
 * \sa Weemo::createCall:
 * \since 5.2
 */
- (void)createCall:(NSString *)contactUID andSetDisplayName:(NSString *)displayName withVideo:(BOOL)videoEnabled
		__attribute__((nonnull (1, 2)));

#pragma mark - Data Channel

/**
 * Sends data using the WebRTC data channel. Data should not be bigger than 1536B. The data is transfered as is
 * to the remote client authenticated as contactID. The contact is notified of the message's sender's name.
 * \param data The data to send to the user. Must not be nil.
 * \param contactUID The recipient. Must not be nil.
 * \sa WeemoDelegate::weemoReceivedData:from:withID:
 * \since 5.2
 */
- (void)sendData:(NSData *)data toContact:(NSString *)contactUID __attribute__((nonnull (1, 2)));


/**
 * Repy to a specified contact. To be used with the ID in the callback WeemoDelegate::weemoReceivedData:from:withID:
 * \param data The data to send.
 * \param contactID The ID of the contact to reply to. Value received in WeemoDelegate::weemoReceivedData:from:withID:
 * \sa WeemoDelegate::weemoReceivedData:from:withID:
 * \sa Weemo::sendData:toContact:
 * \since 5.2
 */
- (void)replyData:(NSData *)data toContactID:(uint8_t)contactID __attribute__((nonnull (1)));


#pragma mark - Connection relevant
/**
 * \brief This property is accessed through the isConnected method and reflects the state of the Weemo singleton connection.
 * \since 5.0
 */
@property(nonatomic, getter = isConnected, readonly)BOOL connected;

/**
 * \brief This property is accessed through the isConnected method and reflects the state of the Weemo singleton connection. A value of YES implies Weemo::isConnected.
 * \since 5.0
 */
@property(nonatomic, getter = isAuthenticated, readonly)BOOL authenticated;

/**
 * \brief The current active (not paused) call, if any. Currently, only one call at a time is supported.
 * \since 5.0
 */
@property(nonatomic, readonly) WeemoCall *activeCall;



/**
 * \brief Delegate for the current connection.
 * \since 5.0
 */
@property(nonatomic, readonly) id<WeemoDelegate> delegate;

/**
 * The display name used by the application. Set this before placing a call to ensure the call can be created.
 * \since 5.0
 */
@property(nonatomic, strong) NSString *displayName;


#pragma mark - MeetingPoints
/**
 * \brief Delegate that implements the meeting point callbacks.
 * \since 5.3
 */
@property(nonatomic) id<WeemoMeetingPointDelegate> meetingDelegate;

/**
 * \brief Delegate that implements the attendee delegate.
 * \since 5.3
 */
@property(nonatomic) id<WeemoAttendeeDelegate> attendeeDelegate;

/**
 * \brief Delegate that implements the host delegate.
 * \since 5.3
 */
@property(nonatomic) id<WeemoHostDelegate> hostDelegate;

//Host only methods

/**
 * Creates a MeetingPoint based on values. Asynchronous call. Host only.
 * \param title			The title of the meeting point. 128 char. max
 * \param location		The location of the meeting. 128 char. max.
 * \param startDate	The date at which the call will start.
 * \param endDate			The date at which the call will end.
 * \param mpType			The meeting type.
 * \warning 5.3: For the key k_MPtype, the value type_adhoc is not yet supported
 * \since 5.3
 */
- (void)meetingPointCreateWithTitle:(NSString *)title
						 atLocation:(NSString *)location
						  startDate:(NSDate *)startDate
							endDate:(NSDate *)endDate
						   withType:(mpType_t)mpType;

/**
 * Changes the writable informations of the meeting point. Asychronous call. Host only.
 * \param mpID		The internal name of the meeting point that was returned after a creation callback. Must not be nil.
 * \param title			The title of the meeting point. 128 char. max
 * \param location		The location of the meeting. 128 char. max.
 * \param startDate	The date at which the call will start.
 * \param endDate			The date at which the call will end.
 * \since 5.3
 * \sa Weemo::meetingPointCreateWithTitle:atLocation:startDate:endDate:withType:
 */
- (void)meetingPointUpdate:(NSString *)mpID
				  newTitle:(NSString *)title
			   newLocation:(NSString *)location
			  newStartDate:(NSDate *)startDate
				newEndDate:(NSDate *)endDate
				__attribute__((nonnull (1)));

/**
 * Locks the meeting point. Equivalent to Weemo::MeetingPoint:SetAuthorizationStatus: with mpSta_autodeny as \c status
 * \param mpID The ID of the meeting point we want to lock. Must not be nil.
 * \since 5.3
 */
- (void)meetingPointLock:(NSString *)mpID __attribute__((nonnull (1)));

/**
 * Locks the meeting point. Equivalent to Weemo::MeetingPoint:SetAuthorizationStatus: with mpSta_autodeny
 * \param mpID The ID of the meeting point we want to lock. Must not be nil.
 * \param status One of mpAuthorizationMode_t;
 * \since 5.3
 */
- (void)meetingPoint:(NSString *)mpID setAuthorizationStatus:(mpAuthorizationMode_t)status __attribute__((nonnull (1)));


/**
 * Returns details about the meeting point. Asynchronous call.
 * \param mpID The meeting point id. Must not be nil.
 * \since 5.3
 */
- (void)meetingPointGetDetails:(NSString *)mpID __attribute__((nonnull (1)));

/**
 * Returns the list of contacts in the meeting point. Asynchronous call.
 * \param mpID The meeting point id. Must not be null.
 * \since 5.3
 */
- (void)meetingPointContactList:(NSString *)mpID  __attribute__((nonnull (1)));

/**
 * Deletes the meeting point from the system. Host only.
 * \param mpID The ID of the meeting point we want to delete. Must not be nil.
 * \sa Weemo::meetingPointCreateWithTitle:atLocation:startDate:endDate:withType:
 * \since 5.3
 */
- (void)meetingPointDelete:(NSString *)mpID __attribute__((nonnull (1)));


/**
 * Starts the meeting point. To be called only the host after this MP was created.
 * \param mpID The ID of the meeting point.
 * \sa Weemo::meetingPointCreateWithTitle:atLocation:startDate:endDate:withType:
 * \sa Weemo::meetingPointStop:
 * \since 5.3
 */
- (void)meetingPointStart:(NSString *)mpID __attribute__((nonnull (1)));


/**
 * Stops the meeting point.
 * \param mpID The ID of the meeting point.
 * \sa Weemo::meetingPointStart:
 * \since 5.3
 */
- (void)meetingPointStop:(NSString *)mpID __attribute__((nonnull (1)));

/**
 * Create the conference call related to the meeting point. It is only after this call is created and started that the Host can accept or deny attendees.
 * Can only be called after the meeting point is started through Weemo::meetingPointStart: .
 * \param mpID The ID of the meeting point.
 * \sa Weemo::meetingPointStart:
 * \sa Weemo::meetingPointJoinConferenceAttendee:
 * \since 5.3
 */
- (void)meetingPointJoinConferenceHost:(NSString *)mpID __attribute__((nonnull (1)));


/**
 * Accept an attendee in the conference. The related call must have been created. Host only.
 * \param mpID The ID of the meeting point. Must not be nil.
 * \param contactUID The ID of the user to be accepted. Must not be nil.
 * \sa WeemoHostDelegate::weemoHostNewAttendee:
 * \since 5.3
 */
- (void)meetingPoint:(NSString *)mpID acceptUser:(NSString *)contactUID __attribute__((nonnull (1, 2)));

/**
 * Denies an attendee access to the conference. The related call must have been created. Host only.
 * \param mpID The ID of the meeting point. Must not be nil.
 * \param contactUID The ID of the user. Must not be nil.
 * \sa WeemoHostDelegate::weemoHostNewAttendee:
 * \since 5.3
 */
- (void)meetingPoint:(NSString *)mpID denyUser:(NSString *)contactUID __attribute__((nonnull (1, 2)));

/**
 * Invites a user to a meeting point. The related call must have been created. Host only.
 * \param mpID The ID of the meeting point. Must not be nil.
 * \param contactUID The ID of the contact we want to invite. Must not be nil.
 * \sa WeemoHostDelegate::weemoHostNewAttendee:
 * \since 5.3
 */
- (void)meetingPoint:(NSString *)mpID inviteUser:(NSString *)contactUID __attribute__((nonnull (1,2)));

/**
 * Cancels the invitation sent by Weemo::MeetingPoint:inviteUser: . Host Only.
 * \param mpID The ID of the meeting point. Must not be nil.
 * \param contactUID The ID of the contact whose invitation will be revoked. Must not be nil.
 * \since 5.3
 */
- (void)meetingPoint:(NSString *)mpID cancelInviteTo:(NSString *)contactUID __attribute__((nonnull (1,2)));

//Attendee only methods
/**
 * Asks to join a meeting point as an attendee.
 * \param mpID The ID of the meeting point we want to join. Must not be nil.
 * \since 5.3
 */
- (void)meetingPointRequestJoin:(NSString *)mpID __attribute__((nonnull (1)));

/**
 * Cancels the join request.
 * \param mpID The ID of the meeting point we wanted to join. Must not be nil.
 * \since 5.3
 */
- (void)meetingPointCancelJoinRequest:(NSString *)mpID __attribute__((nonnull (1)));

/**
 * Call the meeting point. Attendee Call. This should be called only if already accepted (i.e. in response to a 
 * WeemoAttendeeDelegate::weemoAttendeeAuthorization:forMeeting:).
 *
 * \param mpID The meeting point ID. must not be nil.
 * \sa WeemoAttendeeDelegate::weemoAttendeeAuthorization:toMeeting:
 * \sa Weemo::meetingPointJoinConferenceHost for the matching Host function.
 * \warning To be called only after the host accepts the join request or the attendee receives an invite.
 * Calling otherwise will lead to a call error.
 * \since 5.3
 */
- (void)meetingPointJoinConferenceAttendee:(NSString *)mpID __attribute__((nonnull (1)));

/**
 * Used by an attendee to respond to an invitation to join a meeting point. Attendee Only. Should be send in response
 * to a WeemoAttendeeDelegate::weemoAttendeeWasInvitedToMeeting: .
 * \param mpID The meeting point ID. must not be nil.
 * \param accept YES if the attendee accepts to join the meeting point. NO if not.
 * \sa Weemo::meetingPoint:inviteUser:
 * \sa WeemoAttendeeDelegate::weemoAttendeeWasInvitedToMeeting:
 * \since 5.3
 */
- (void)meetingPoint:(NSString *)mpID attendeeAnswersToInvite:(BOOL)accept __attribute__((nonnull (1)));

#pragma mark - Logs
/**
 * Set the log level currently used.
 * \sa logLevel_t int WeemoData.h
 * \sa Weemo::getLogLevel
 * \since 5.1
 */
+ (void)setLogLevel:(logLevel_t)logLevel;

/**
 * Returns the current log level.
 * \sa logLevel_t int WeemoData.h
 * \sa Weemo::setLogLevel:
 * \since 5.1
 */
+ (logLevel_t)getLogLevel;

/**
 * Copy the logfile of the app to a temporary location (in the NSTemporaryDirectory() application folder.)
 * \return The URI of the logfile.
 * \since 5.3
 */
- (NSString*)createLogfile;
@end


