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
 * delegate of its own, WeemoCallDelegate.
 *
 * \param call The call created, can't be nil. Host App depends on the WeemoCall::callStatus value (CALLSTATUS_* type value)
 *
 * \sa Weemo::createCall:
 * \sa The definition of the CALLSTATUS_* variables (found in WeemoData.h).
 */
- (void)weemoCallCreated:(WeemoCall*)call;

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
 * \sa Weemo::WeemoWithAPIKey:andDelegate:error:
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
 
 * While the contact availability is checked upon Weemo::createCall: call, this delegate function
 * is only called when the user/host application specifically call the Weemo::getStatus: method.
 *
 * Use this function as a GUI updater, e.g. disabling a call button in case of !canBeCalled before displaying the view.
 *
 * \param contactID the contact checked
 * \param canBeCalled YES if the contact can be called, NO otherwise.
 * \sa Weemo::getStatus:
 */
- (void)weemoContact:(NSString*)contactID canBeCalled:(BOOL)canBeCalled;

@end

/**
 * \brief Weemo singleton. This is the main object of the SDK.
 *
 * Remarks:
 *
 * This singleton is instancianted in the host application by using the Weemo::WeemoWithAPIKey:andDelegate:error: class function. After initiating the singleton, authentication can happen, upon WeemoDelegate::weemoDidAuthenticate: call.
 *
 * The singleton can be invoked anytime after instantiation through Weemo::instance. If the instantiation isn't completed by the time Weemo::instance is called, nil is returned.
 *
 * The Weemo::foreground and Weemo::background method are to be called everytime the host application goes to background/foreground. Failure to do so will result in undefined behavior, especially regarding on-going calls.
 */
@interface Weemo : NSObject

/**
 * \brief Creates a Weemo singleton Object. The initialization is asynchronous, the WeemoDelegate::weemoDidConnect: will be called upon singleton connection.
 *
 * \param APIKey The Weemo API Key
 * \param delegate The delegate object that implements the WeemoDelegate protocol
 * \param error When initialization has failed and this is not nil, this will be filled with a describing error. The debugDescription field of the NSError returns a
 * NSString* describing the error in human terms.
 * \sa WeemoDelegate::weemoDidConnect:
 */
+ (Weemo*) WeemoWithAPIKey:(NSString*)APIKey andDelegate:(id<WeemoDelegate>)delegate error:(NSError**)error;

/**
 * \brief Returns the Weemo singleton instance, if instantiated
 *
 * \return The Weemo singleton or nil if the SDK was not instantiated properly
 */
+ (Weemo*)instance;

/**
 * \brief Destructor
 */
- (void)dealloc;

/**
 * \brief Connects to servers with given userID. The connection is asynchronous, WeemoDelegate::weemoDidAuthenticate: will be called
 * upon user authentication.
 *
 * \param userID The userID that will represent this user in Weemo's platform.
 * \param domain The domain to which the user will connect.
 * \return YES if the UID was correctly formed, NO otherwise
  * \sa WeemoDelegate::weemoDidAuthenticate:
 */
- (BOOL)authenticateWithUserID:(NSString*)userID toDomain:(NSString*)domain;

/**
 * \brief Disconnects properly from weemo servers. A Call to WeemoDelegate::weemoDidDisconnect: is to be expected upon disconnection.
 * \sa WeemoDelegate::weemoDidDisconnect:
 */
- (BOOL)disconnect;

/**
 * \brief This function is to be called when the application goes to background. Not calling this function will result in undefined behavior.
 */
- (void)background;

/**
 * \brief This function is to be called when the application comes to foreground. Not calling this function will result in undefined
 * behavior.
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
 * \brief Creates a call whose recipient is contactUID. The call is created when the user is deemed available and returned through the use of the WeemoDelegate::weemoCallCreated: method.
 *
 * \param contactUID The ID of the contact or the conference to call.
 * \sa WeemoDelegate::weemoCallCreated:
 */
- (void)createCall:(NSString*)contactUID;

/**
 * \brief The current active (not paused) call, if any.
 */
@property(nonatomic, readonly) WeemoCall *activeCall;

/**
 * \brief The curent userID connected.
 */
@property(nonatomic, readonly) NSString *userID;

/**
 * \brief The delegate for the current connection.
 */
@property(nonatomic, readonly) id<WeemoDelegate> delegate;

/**
 * The display name used by the application.
 */
@property(nonatomic, strong) NSString *displayName;

@end


