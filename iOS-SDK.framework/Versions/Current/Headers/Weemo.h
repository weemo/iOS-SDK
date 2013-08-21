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
 * This function will be called after a call is created, either by calling a contact or receiving a call.
 * To accept the call, use -[call resume]. To deny it, use -[call hangup]. The WeemoCall object presents a 
 * delegate of its own, decribed in the WeemoCall object.
 *
 * \param call The call created, can't be nil. Host App depends on the [call callStatus] value (CALLSTATUS_* type value)
 *
 * \sa Weemo::createCall:
 * \sa The definition of the CALLSTATUS_ variable.
 */
- (void)weemoCallCreated:(WeemoCall*)call;

/**
 * Called by the Weemo singleton after the authentication step. 
 * \param error If authentication failed, error will be different from nil. The debugDescription field of the NSError returns a
 * NSString* describing the error in human terms. Otherwise, it is nil.
 * \sa Weemo::connectWithUserID:toDomain:
 */
- (void)weemoDidAuthenticate:(NSError*)error;

/**
 * \brief Called when Weemo ended its initialization. The blocks stored by the +[Weemo instanceWhenReady:] method are executed
 * just before this method is called.
 *
 * \param error Nil if no error occured. If different from nil then the connection did NOT succeed. The debugDescription field of
 * the NSError returns a NSString* describing the error in human terms.
 * \sa Weemo::WeemoWithAPIKey:andDelegate:onInit:
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
 * \brief Called after a contact is checked through the use of the -[Weemo getStatus:]. 
 
 * While the contact availability is checked upon -[[Weemo instance] call:] call, this delegate function
 * is only called when the user/host application specifically call the -[[Weemo instance ]getStatus:] method.
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
 * This singleton is instancianted in the host application by using the +[Weemo WeemoWithAPIKey:andDelegate:onInit:] class function. After initiating the singleton, authentication can happen, upon -[WeemoDelegate didAuthenticated:] call.
 *
 * The singleton can be invoked anytime after instantiation through +[Weemo instance]. If the instantiation isn't completed by the time +[Weemo instance] is called, nil is returned.
 *
 * The -[[Weemo instance] foreground] and -[[Weemo instance] background] method are to be called everytime the host application goes to background/foreground. Failure to do so will result in undefined behavior, especially regarding on-going calls.
 */
@interface Weemo : NSObject

/**
 * \brief Creates a Weemo singleton Object. The initialization is asynchronous. The onInit: block is called when the singleton is initialized.
 *
 * \param APIKey The Weemo API Key
 * \param delegate The delegate object that implements the WeemoDelegate protocol
 * \param onInit This block will be called when Weemo has been properly initialized (with the Weemo object and a nil NSError)
 * or when initialization has failed with (Nil, NSError*) as arguments. The debugDescription field of the NSError returns a 
 * NSString* describing the error in human terms.
 * \sa WeemoDelegate::weemoDidConnect:
 */
+ (void)WeemoWithAPIKey:(NSString*)APIKey andDelegate:(id<WeemoDelegate>)delegate onInit:(void (^)(Weemo*,NSError*))onInit;

/**
 * \brief Returns the Weemo singleton instance, if instanciated
 *
 * \return The Weemo singleton or nil if the SDK was not instanciated properly
 */
+ (Weemo*)instance;

/**
 * \brief Registers a block to be called when Weemo has been instanciated
 *
 * This will call the block immediately if Weemo has already been initialized or delay it's execution until Weemo is initialized. This blocks are executed after the -[WeemoDelegate didConnect:] is called.
 
 * These blocks will not be executed if Weemo is never properly instanciated.
 * \param whenReady The block to add to the list of tasks to be executed when the instance is ready.
 */
+ (void)instanceWhenReady:(void (^)(Weemo*))whenReady;

/**
 * \brief Destructor
 */
- (void)dealloc;

/**
 * \brief Connects to servers with given userID. The connection is asynchronous, -[WeemoDelegate didConnect:] will be called
 * upon instance initialization.
 *
 * \param userID The userID that will represent this user in Weemo's platform.
 * \param domain The domain to which the user will connect.
  * \sa WeemoDelegate::weemoDidAuthenticate:
 */
- (void)connectWithUserID:(NSString*)userID toDomain:(NSString*)domain;

/**
 * \brief Disconnects properly from weemo servers. A Call to -[WeemoDelegate didDisconnect:] is to be expected upon disconnection.
 * \sa WeemoDelegate::weemoDidDisconnect:
 */
- (BOOL)disconnect;

/**
 * This function is to be called when the application goes to background. Not calling this function will result in undefined behavior.
 */
- (void)background;

/**
 * This function is to be called when the application comes to foreground. Not calling this function will result in undefined 
 * behavior.
 */
- (void)foreground;

/**
 * Check if a user can be called. This method is to be called for GUI update (e.g. graying out a call button). -[WeemoDelegate contactCanBeCalled:] is called upon callback from the network.
 *
 * \param contactUID The ID of the contact to check
 * \sa WeemoDelegate::weemoContact:canBeCalled:
 */
- (void)getStatus:(NSString*)contactUID;

/**
 * \brief Creates a call whose recipient is contactUID. The call is created when the user is deemed available and returned through the use of the [WeemoDelegate callCreated:] method.
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


