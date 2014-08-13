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
 * \param contactID the contact checked
 * \param canBeCalled YES if the contact can be called, NO otherwise.
 * \sa Weemo::getStatus:
 * \since 5.0
 */
- (void)weemoContact:(NSString*)contactID canBeCalled:(BOOL)canBeCalled;

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
 * \param contact The name of the contact who sent the message
 * \param contactID Used to reply to the message, as second argument to the Weemo::replyData:toContactID:
 * \sa Weemo::sendData:toContact:
 * \since 5.2
 */
- (void)weemoReceivedData:(NSData *)data from:(NSString *)contact withID:(uint8_t)contactID;

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
 * \param token The token to be used for authentication. Must not be nil.
 * \param type The type of the userID, USERTYPE_EXTERNAL or USERTYPE_INTERNAL
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
 * Settings any of this value to 0 will reset the setting to default values. Using this leads to undefined behaviour where
 * WeemoCall::videoProfile values are concerned.
 * \param maxfps The max FPS wanted from the encoder. valid values are 1-30. Set to 0 to get back to defaults
 * \param maxBitrate Max bitrate for the video encding. 1-1000000, unit is bps
 * \param resolutionDiv Values are 1 or 2. Setting 2 will divide the video frame dimension by 2 (i.e. 352*288 becomes 176*144)
 * \since 5.1
 */
- (void)overrideVideoFPS:(int)maxfps andVideoMaxBitrate:(int)maxBitrate andResolutionDivider:(int)resolutionDiv;

/**
 * Overrides two audio encoding parameters and the CPU usage of the video encoder.
 * \param complex The complexity used for the audio encoding. 0-10, 10 is better quality, more cpu consuming. Default is 4.
 * \param bitrate The audio bitrate in bps. 16000 - 64000. default is 24000.
 * \param vp8cpuusage The cpu usage of the video encoder. 0-16, 0 being the most intensive. default is 8.
 * \since 5.2
 */
- (void)overrideAudioComplexity:(int)complexity andAudioBitrate:(int)bitrate andVideoCPUUsage:(int)vp8cpuusage;

/**
 * Restore defaults bandwidth parameters. Equivalent to call [[Weemo instance] setCallMaxFPS:0 andVideoMaxBitrate:0 andResolutionDivider:0];
 * \since 5.1
 */
- (void)resetBandwidthDefaults;

#pragma mark - One-on-One Call
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
 * application throught the use of the WeemoDelegate::weemoCallCreated: method. The only option available is novideo. More options
 * to ba added.
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

/**
 * \brief Creates a call whose recipient is \p contactUID and set the contact's display name to \p displayName.
 *
 * The call is immediately created. If the addressee is not available, the call is ended almost immediately. The call is returned to the
 * application throught the use of the WeemoDelegate::weemoCallCreated: method. The only option available is novideo. More options
 * to ba added.
 *
 * \param contactUID The ID of the contact or the conference to call. Must not be nil.
 * \param displayName The contact display name to be used. Must not be nil.
 * \param videoEnabled true if the call should have videoOut enable by the time the remote picks up
 * \sa WeemoDelegate::weemoCallCreated:
 * \sa WeemoCall::contactID
 * \sa WeemoCall::contactDisplayName
 * \sa Weemo::createCall:
 * \since 5.3 HP Special
 */
- (void)createCall:(NSString *)contactUID andSetDisplayName:(NSString *)displayName withVideo:(BOOL)videoEnabled andAudio:(BOOL)audioEnabled __attribute__((nonnull (1, 2)));


#pragma mark - Data Channel

/**
 * Sends data using the WebRTC data channel. Data should not be bigger than 1536B. The data is transfered as is
 * to the remote client authenticated as contactID. The contact is notified of the message's sender's name.
 * \param data The data to send to the user. Must not be nil.
 * \param contactName The recipient. Must not be nil.
 * \sa WeemoDelegate::weemoReceivedData:from:withID:
 * \since 5.2
 */
- (void)sendData:(NSData *)data toContact:(NSString *)contactName __attribute__((nonnull (1, 2)));


/**
 * Repy to a specified contact. To be used with the ID in the callback WeemoDelegate::weemoReceivedData:from:withID:
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


