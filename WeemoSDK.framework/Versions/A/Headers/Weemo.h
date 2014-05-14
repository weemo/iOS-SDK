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
 * \brief Delegate for the Weemo Singleton. Allows the Host Application to be notified upon events.
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
 */
- (void)weemoCallCreated:(WeemoCall*)call;


/**
 * \brief This function will be called after a call is stopped. The \param call will be released soon after this method returns.
 *
 * \param call The call that is stopped.
 */
- (void)weemoCallEnded:(WeemoCall*)call;


/**
 * \brief Called by the Weemo singleton after the authentication step.
 * \param error If authentication failed, error will be different from nil. The debugDescription field of the NSError returns a
 * NSString* describing the error in human terms. Otherwise, it is nil.
 * \sa Weemo::authenticateWithUserID:toDomain:
 */
- (void)weemoDidAuthenticate:(NSError*)error;


/**
 * \brief Called when Weemo singleton ended its initialization. If no error occured the Weemo singleton is connected and users can proceed to the authentication step.
 *
 * \param error Nil if no error occured. If different from nil then the connection did NOT succeed. The debugDescription field of
 * the NSError returns a NSString* describing the error in human terms.
 * \sa Weemo::WeemoWithURLReferer:andDelegate:error:
 */
- (void)weemoDidConnect:(NSError*)error;

@optional

/**
 * \brief Called when Weemo disconnected from the server
 * 
 * \param error Nil if the Weemo singleton disconnected normally. The debugDescription field of the NSError returns a
 * NSString* describing the error in human terms.
 * \sa Weemo::disconnect
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
 */
- (void)weemoContact:(NSString*)contactID canBeCalled:(BOOL)canBeCalled;

/**
 * \brief This function is called between the app's call to Weemo::authenticateWithToken:andType: and the WeemoDelegate::weemoDidAuthenticate: call.
 *
 * \param error If an error occured during authentication, this function may be called with an error param non nil.
 */
- (void)weemoWillAuthenticate:(NSError *)error;

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
 * \param appID The Application Identifier
 * \param delegate The delegate object that implements the WeemoDelegate protocol
 * \param error When initialization has failed and this is not nil, this will be filled with a describing error. The debugDescription 
 * field of the NSError returns a NSString* describing the error in human terms.
 * \sa WeemoDelegate::weemoDidConnect:
 */
+ (Weemo *)WeemoWithAppID:(NSString *)appID
			  andDelegate:(id<WeemoDelegate>)delegate
					error:(NSError *__autoreleasing *)error;

/**
 * \brief Returns the Weemo singleton instance, if instantiated.
 *
 * \return The Weemo singleton or nil if the SDK was not instantiated.
 */
+ (Weemo*)instance;

/**
 * Used for identification purpose.
 * \return The version of the Weemo SDK
 */
+ (NSString *)getVersion;

/*
* \brief Destructor
*/
- (void)dealloc;


/**
 * \brief Connects to servers with the given token. The connection is asynchronous, WeemoDelegate::weemoDidAuthenticate: will be called
 * upon user token validation.
 * \param token The token to be used for authentication
 * \param type The type of the userID, USERTYPE_EXTERNAL or USERTYPE_INTERNAL
 * \sa WeemoDelegate::weemoDidAuthenticate:
 */
- (BOOL)authenticateWithToken:(NSString*)token andType:(int)type;

/**
 * \brief Disconnects from weemo servers. A call to WeemoDelegate::weemoDidDisconnect: is to be expected upon disconnection.
 * \sa WeemoDelegate::weemoDidDisconnect:
 */
- (BOOL)disconnect;

/**
 * \brief This function is to be called when the application goes to background. Not calling this function will result in undefined behavior.
 * \sa Weemo::foreground
 * \deprecated This method was deprecated in version 4.1.24. The background transition is now detected using the related UIApplication notification (UIApplicationDidEnterBackgroundNotification).
 */
- (void)background;

/**
 * \brief This function is to be called when the application comes to foreground. Not calling this function will result in undefined
 * behavior.
 * \sa Weemo::background
 * \deprecated This method was deprecated in version 4.1.24. The foreground  transition is now detected using the related UIApplication notification (UIApplicationDidBecomeActiveNotification).
 */
- (void)foreground;

/**
 * \brief Check if a user can be called. WeemoDelegate::weemoContact:canBeCalled: is called upon callback from the network.
 *
 * \param contactUID The ID of the contact to check
 * \sa WeemoDelegate::weemoContact:canBeCalled:
 */
- (void)getStatus:(NSString*)contactUID;

/**
 * \brief Creates a call whose recipient is \c contactUID. The call is immediately created. If the addressee is not 
 * available, the call is ended almost immediately. The call is returned to the application throught the use of the
 * WeemoDelegate::weemoCallCreated: method.
 *
 * \param contactUID The ID of the contact or the conference to call.
 * \sa WeemoDelegate::weemoCallCreated:
 * \sa WeemoCall::contactID
 * \sa Weemo::createCall:andSetDisplayName:
 */
- (void)createCall:(NSString*)contactUID;

/**
 * \brief Creates a call whose recipient is \p contactUID and set the contact's display name to \p displayName. The call is
 * immediately created. If the addressee is not available, the call is ended almost immediately. The call is returned to the 
 * application throught the use of the WeemoDelegate::weemoCallCreated: method.
 *
 * \param contactUID The ID of the contact or the conference to call.
 * \param displayName The contact display name to be used.
 * \sa WeemoDelegate::weemoCallCreated:
 * \sa WeemoCall::contactID
 * \sa WeemoCall::contactDisplayName
 * \sa Weemo::createCall:
 */
- (void)createCall:(NSString *)contactUID andSetDisplayName:(NSString *)displayName;


/**
 * \brief This property is accessed through the isConnected method and reflects the state of the Weemo singleton connection.
 *
 */
@property(nonatomic, getter = isConnected, readonly)BOOL connected;

/**
 * \brief This property is accessed through the isConnected method and reflects the state of the Weemo singleton connection. A value of YES implies Weemo::isConnected.
 *
 */
@property(nonatomic, getter = isAuthenticated, readonly)BOOL authenticated;

/**
 * \brief The current active (not paused) call, if any. Currently, only one call at a time is supported.
 */
@property(nonatomic, readonly) WeemoCall *activeCall;

/**
 * \brief The delegate for the current connection. Mandatory to do anything, really.
 */
@property(nonatomic, readonly) id<WeemoDelegate> delegate;

/**
 * The display name used by the application. Set this before calling to ensure the call can be created.
 */
@property(nonatomic, strong) NSString *displayName;

/**
 * Set the log level currently used.
 * \sa logLevel_t int WeemoData.h
 */
+ (void)setLogLevel:(logLevel_t)logLevel;

/**
 * Returns the current log level.
 * \sa logLevel_t int WeemoData.h
 */
+ (logLevel_t)getLogLevel;

@end


