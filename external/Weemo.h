//
//  Weemo.h
//  iOS-SDK
//
//  Created by Salomon BRYS on 11/07/13.
//  Copyright (c) 2013 Weemo. All rights reserved.
//

#import "WeemoData.h"
#import "WeemoCall.h"
#import "mucl.h"

/**
 * \brief Base class of a weemo video view
 */
@interface WeemoView : UIView

/**
 * \brief Set this view as active or not, meaning that this will be the only view being painted
 *
 * When setting to true, if another view is active, it will steal the focus,
 * meaning it will make the current active view inactive before setting this view active
 */
@property(assign) BOOL active;

@end

/**
 * \brief Weemo video out preview view
 *
 * Once created by hand or by IB, you should call setActive on it.
 * Only one WeemoVideoOut view can be active and will be painted with the preview of the camera.
 */
@interface WeemoVideoOut : WeemoView
@end

/**
 * \brief Weemo video in view
 *
 * Once created by hand or by IB, you should call setActive on it.
 * Only one WeemoVideoIn view can be active and will be painted with the video from the conference.
 */
@interface WeemoVideoIn : WeemoView
@end




/**
 * \brief Delegate for the Weemo Singleton
 */
@protocol WeemoDelegate <NSObject>

/**
 * \brief Will be called in case of an incoming call
 *
 * To accept the call, use resume on it.
 * To refuse the call, use hangup on it.
 *
 * \param call The incoming call
 */
- (void) incomingCall:(WeemoCall*)call;

/**
 * \brief Called when Weemo ended it's initialization.
 *
 * \param error Nil if no error occured.
 *              If this is not nil, then the connection did NOT succeed
 */
- (void) weemoDidConnect:(NSError*)error;

@optional

/**
 * \brief Called when Weemo disconnected from the server
 *
 * \param error Nil if weemo disconnected normally
 */
- (void) weemoDidDisconnect:(NSError*)error;

@end

@interface Weemo : NSObject

/**
 * \brief Create a Weemo singleton Object. The initialization is asynchronous, hence the onInit block.
 *
 * \param APIKey The Weemo API Key
 * \param onInit Will be called when Weemo has been properly initialized (with the Weemo object and a nil NSError)
 *               or when initialization has failed (with a nil Weemo and an NSError object)
 */
+ (void) WeemoWithAPIKey:(NSString*)APIKey toDomain:(NSString*)domain onInit:(void (^)(Weemo*,NSError*))onInit;

/**
 * \brief Get the Weemo singleton instance.
 *
 * \return The weemo singleton or nil if Weemo was not instanciated properly
 */
+ (Weemo*) instance;

/**
 * \brief Register a block to be called when Weemo has been instanciated
 *
 * This will call the block immediately if Weemo has already been initialized
 * or delay it's execution until Weemo is initialized.
 *
 * The block may never be called if Weemo is not properly instanciated.
 */
+ (void) instanceWhenReady:(void (^)(Weemo*))whenReady;

/**
 * \brief Connect to Weemo servers with given userID. The connection is asynchronous, hence the onConnect block.
 *
 * \param userID The userID that will represent this user in Weemo's platform
 * \param delegate Will be called on various weemo events
 */
- (void) connectWithUserID:(NSString*)userID delegate:(id<WeemoDelegate>)delegate;

/**
 * \brief Disconnect properly from weemo servers.
 */
- (void) disconnect;

/**
 * \brief Desctructor
 */
- (void) dealloc;

/**
 * This function is to be called when the application goes to background
 */
- (void) weemoBackground;

/**
 * This function is to be called when the application comes to foreground
 */
- (void) weemoForeground;


/**
 * \brief Starts a call to the given contact ID.
 * verify the status of contactID
 * \param contactID The ID of the contact or the conference to call.
 */
- (WeemoCall*) call:(NSString*)contactID;

/**
 * \brief The current active WeemoVideoIn view
 */
@property(readonly) WeemoVideoIn *activeVideoIn;

/**
 * \brief The current active WeemoVideoOut view
 */
@property(readonly) WeemoVideoOut *activeVideoOut;

/**
 * \brief The current active (not paused) call, if any
 */
@property(readonly) WeemoCall *activeCall;

/**
 * \brief The curent userID connected
 */
@property(readonly) NSString *userID;

/**
 * \brief the delegate for the current connection
 */
@property(readonly) id<WeemoDelegate> delegate;

@end
