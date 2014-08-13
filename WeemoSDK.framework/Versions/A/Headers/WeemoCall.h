//
//  WeemoCall.h
//  iOS-SDK
//
//  Created by Charles Thierry on 7/16/13.
//  Copyright (c) 2013 Weemo. All rights reserved.
//
#include "WeemoData.h"

@class WeemoContact;

/**
 * \brief Delegate for the Weemo Singleton. Allows the Host Application to be notified upon events. All functions are optionals.
 * \since 5.0
 */
@protocol WeemoCallDelegate <NSObject>
@optional
/**
 * \brief Called when the call starts or stops receiving video.
 * \param sender The WeemoCall which property changed
 * \param isReceiving Answers "Are we receing video?"
 * \sa WeemoCall::receivingVideo
 * \since 5.0
 */
- (void)weemoCall:(id)sender videoReceiving:(BOOL)isReceiving;

/**
 * \brief Called when the SDK receives cursor location. This location is in percent, between 0 and 99 (width%, height%). If the cursor is out of the video, location is -1x-1.
 * \param sender The WeemoCall which property changed
 * \param location The inbound video cursor location. If -1x-1, the remote's cursor is not over the video.
 * \since 5.3
 */
- (void)WeemoCall:(id)sender cursorLocationPosition:(CGPoint)location;

/**
 * \brief Fired when the SDK starts or stops receiving share data.
 * \param sender The WeemoCall which property changed
 * \param isReceiving YES if we are receiving share
 * \since 5.1
 */
- (void)weemoCall:(id)sender shareReceiving:(BOOL)isReceiving;

/**
 * \brief Called when the call starts sending video.
 * \param sender The WeemoCall which property changed
 * \param isSending Answers "Are we sending video?"
 * \sa WeemoCall::sendingVideo
 * \since 5.0
 */
- (void)weemoCall:(id)sender videoSending:(BOOL)isSending;

/**
 * \brief Fired when the SDK starts or stops sending share data.
 * \param sender The WeemoCall which property changed
 * \param isSending YES if we are sending share
 * \since 5.1
 */
- (void)weemoCall:(id)sender shareSending:(BOOL)isSending;


/**
 * \brief Called when the incoming video profile changes. Use this method to know when the video incoming size/profile changes.
 * \param sender The WeemoCall which property changed
 * \param profile The new profile used by the incoming video. Can be profile_unknown.
 * \sa WeemoCall::videoInProfile
 * \sa WeemoCall::getVideoInSize
 * \since 5.0
 * \deprecated Replaced by the WeemoCallDelegate::weemoCall:videoInSizeChange:. Names sanitization effort.
 */
- (void)weemoCall:(id)sender videoProfile:(video_profile_t)profile __deprecated;


/**
 * \brief Called when the incoming video profile changes. Use this method to know when the video incoming size/profile changes.
 * \param sender The WeemoCall which property changed
 * \param size The new profile used by the incoming video. Can be CGSizeZero.
 * \sa WeemoCall::videoInProfile
 * \sa WeemoCall::getVideoInSize
 * \since 5.1
 */
- (void)weemoCall:(id)sender videoInSizeChange:(CGSize)size;

/**
 * \brief Called when the outgoing video size changes (that is, even if the device rotates).
 * \param sender The WeemoCall which property changed
 * \param size The new size of the monitoring video. Can be CGSizeZero
 * \sa WeemoCall::videoProfile
 * \sa WeemoCall::getVideoOutSize
 * \since 5.1
 */
- (void)weemoCall:(id)sender videoOutSizeChange:(CGSize)size;

/**
 * \brief Called when the video source changes
 * \param sender The WeemoCall which property changed
 * \param source The new source. 0 if front (on the screen side of the device) camera, back camera otherwise
 * \sa WeemoCall::videoSource
 * \since 5.0
 */
- (void)weemoCall:(id)sender videoSource:(int)source;

/**
 * \brief Called when the microphone is muted.
 * \param sender The WeemoCall which property changed
 * \param isSending sending captured audio stream if true, sending empty packets otherwise
 * \sa WeemoCall::audioStart
 * \sa WeemoCall::audioStop
 * \since 5.0
 */
- (void)weemoCall:(id)sender audioSending:(BOOL)isSending;

/**
 * \brief Called when the audio route changes
 * \param sender The WeemoCall which property changed
 * \param route The new route used. 0 is the usual route (regular phone equipment), 1 is the phone's speaker
 * \sa WeemoCall::audioRoute
 * \since 5.0
 */
- (void)weemoCall:(id)sender audioRoute:(int)route;

/**
 * \brief Called when the status of the call changes
 * \param sender The WeemoCall which property changed
 * \param status The new status of the call (i.e. CALLSTATUS_RINGING)
 * \sa WeemoCall:callStatus
 * \since 5.0
 */
- (void)weemoCall:(id)sender callStatus:(int)status;

/**
 * \brief The call unique SIP identifier as been received. This occurs *after* the call goes active. After this delegate
 * method is fired, the WeemoCall::getSipID message can be fired anytime to retreive this ID.
 * \param sender The WeemoCall which sipID was received
 * \param sipID The sipID
 * \sa WeemoCall::getSipID
 * \since 5.2
 */
- (void)weemoCall:(id)sender sipID:(NSString *)sipID;
@end

/**
 * \brief Represents a call to a contact or a conference. Such an object is created on Weemo::createCall:.
 *
 * Remarks:
 * 
 * The Video views autorotates with the interface and following the interface rotation rules set by the Host App. However, the outgoing video stream rotates with the device. This allow the outgoing video to be shown with a correct rotation within the receiving device, even if the user sending the video is holding the device using a rotation not supported by the Host App.
 * 
 * When the device is held in a non supported rotation, the monitoring view of the outgoing video is rotated to indicate that the rotation is not supported, though the outgoing video is sent correctly rotated.
 * \since 5.0
 */
@interface WeemoCall : NSObject
#pragma mark - Call details
/**
 * \brief The host app should set this value if it wants to be notified about call changes.
 * \since 5.0
 */
@property(nonatomic, strong) id<WeemoCallDelegate>delegate;

/**
 * \brief The ID of the call. Not really used for now since only one call can be held at a time, will become useful when the multicall functionality will be brought to the MobileSDK.
 * \since 5.0
 */
@property(readonly) int callid;

/**
 * \brief This is the duration of this call, in seconds. Not KVO, as it is updated only when the value is requested.
 * \since 5.1
 */
@property(nonatomic, readonly)NSTimeInterval callDuration;

/**
 * \brief Date of call start.
 * \since 5.1
 */
@property(nonatomic, readonly)NSDate *startDate;

/**
 * \brief ID of the contact or the conference being called.
 * \sa WeemoCall::contactDisplayName
 * \since 5.0
 */
@property(readonly) NSString *contactID;

/**
 * \brief Display name of the contact or conference being called. If this name is not set, a call to this variable returns
 * the same value as WeemoCall::contactID. The only way to set this variable is on call creation through Weemo::createCall:andSetDisplayName:
 * \sa WeemoCall::contactID
 * \since 5.0
 */
@property(nonatomic, readonly) NSString *contactDisplayName;


#pragma mark - Basic controls
/**
 * \brief Hang up the call and stop it
 * \since 5.0
 */
- (void)hangup;

/**
 * \brief Pause the call so it can be later resumed. WARNING: Not Yet Available
 * \since 5.0
 */
- (void)pause;

/**
 * \brief Resume the call if it was paused. Pick it up if it is ringing.
 * \since 5.0
 */
- (void)resume;

/**
 * \brief Pick up a call without activating the outgoing video.
 * \since 5.2
 */
- (void)resumeWithoutVideo;

/**
 * \brief Start the share view and set the view to be shared. Starting an outgoing share stops the incoming video.
 * \param view This view is *NOT* retained by the SDK (aka, its reference is kept with a `weak` property).
 * \warning Not available on iOS version earlier than the 7.0.
 * \since 5.1
 */
- (void)screenShareStart:(UIView *)view;

/**
 * \brief Stops the share. If the incoming video stream was active, it is resumed.
 * \since 5.1
 */
- (void)screenShareStop;

/**
 * \brief Start sending video from the camera. The video starts automatically upon call start.
 * \since 5.0
 */
- (void)videoStart;

/**
 * \brief Stop sending video from the camera
 * \since 5.0
 */
- (void)videoStop;

/**
 * \brief Start sending audio from the microphone.
 *
 * While the outgoing audio stream starts automatically upon call start, it is posisble to mute the microphone, thus sending only empty frames. This function starts the sending of captured audio packet.
 *
 * Upon change, WeemoCallDelegate::weemoCall:audioSending: is called.
 * \sa WeemoCallDelegate::weemoCall:audioSending:
 * \since 5.0
 */
- (void)audioStart;

/**
 * \brief Stop sending audio from the microphone.
 *
 * The function stops the sending of captured audio packet. Enpty audio frames are sent instead.
 *
 * Upon change, WeemoCallDelegate::weemoCall:audioSending: is called.
 * \sa WeemoCallDelegate::weemoCall:audioSending:
 * \since 5.0
 */
- (void)audioStop;

/**
 * \brief Switches camera source between front and back.
 *
 * Upon change, WeemoCallDelegate::weemoCall:videoSource: is called.
 * \sa WeemoCallDelegate::weemoCall:videoSource:
 * \since 5.0
 */
- (void)toggleVideoSource;

/**
 * \brief Changes the audio route used by the call.
 *
 * Two audio outputs are possible: Loudspeaker(1) or Earphone/Headset(0).
 *
 * Upon change, WeemoCallDelegate::weemoCall:audioRoute: is called.
 * \sa WeemoCallDelegate::weemoCall:audioRoute:
 * \since 5.0
 */
- (void)toggleAudioRoute;


#pragma mark - Call status
/**
 * \brief Status of the call
 *
 * Upon change, WeemoCallDelegate::weemoCall:callStatus: is called.
 * \sa WeemoCallDelegate::weemoCall:callStatus:
 * \sa WeemoData.h
 * \since 5.0
 */
@property(nonatomic, readonly) int callStatus;

/**
 * \brief Value changes after a WeemoCall::toggleAudioRoute.
 *
 * 0 is default route (phone standard equipment), 1 is speaker/mic.
 *
 * Upon change, WeemoCallDelegate::weemoCall:audioRoute: is called.
 * \sa WeemoCallDelegate::weemoCall:audioRoute:
 * \since 5.0
 */
@property (nonatomic, readonly) int audioRoute;

/**
 * \brief Value changes after a WeemoCall::toggleVideoSource.
 *
 * 0 is front camera, 1 is back camera.
 *
 * Upon change, WeemoCallDelegate::weemoCall:videoSource: is called.
 * \sa WeemoCallDelegate::weemoCall:videoSource:
 * \since 5.0
 */
@property (nonatomic, readonly) int videoSource;

/**
 * \brief Whether or not the call is receiving video.
 *
 * This property changes when the video stream is started/ended on the other end.
 *
 * Upon change, WeemoCallDelegate::weemoCall:videoReceiving: is called.
 * \sa WeemoCallDelegate::weemoCall:videoReceiving:
 * \since 5.0
 */
@property(nonatomic, readonly, getter = isReceivingVideo) BOOL receivingVideo;

/**
 * \brief Whether or not the call is sending video.
 *
 * This property changes when the network acknowledge the video status change on this end.
 *
 * Upon change, WeemoCallDelegate::weemoCall:videoSending: is called.
 * \sa WeemoCallDelegate::weemoCall:videoSending:
 * \since 5.0
 */
@property(nonatomic, readonly, getter = isSendingVideo) BOOL sendingVideo;

/**
 * \brief Whether or not the call has an outbound view share ongoing
 *
 * This property changes when the share starts.
 *
 * Upon change, WeemoCallDelegate::weemoCall:shareReceiving: is called.
 * \sa WeemoCallDelegate::weemoCall:shareReceiving:
 * \since 5.1
 */
@property(nonatomic, readonly, getter = isReceivingShare) BOOL receivingShare;

/**
 * \brief Whether or not the call has an outbound view share ongoing
 *
 * This property changes when the network acknowledge the share is ongoing.
 *
 * Upon change, WeemoCallDelegate::weemoCall:shareSending: is called.
 * \sa WeemoCallDelegate::weemoCall:shareSending:
 * \since 5.1
 */
@property(nonatomic, readonly, getter = isSendingShare) BOOL sendingShare;

/**
 * \brief Whether or not the call is sending captured audio packet
 *
 * This property changes when the network acknowledge the microphone status change on this end.
 *
 * Upon change, WeemoCallDelegate::weemoCall:audioSending: is called.
 * \sa WeemoCallDelegate::weemoCall:audioSending:
 * \since 5.0
 */
@property(nonatomic, readonly, getter = isSendingAudio) BOOL sendingAudio;

/**
 * \brief The sip ID of the call.
 * This property is only available after the call is set to active.
 * Fetching it before the WeemoCallDelegate::weemoCall:sipID: callback is fired will return nil.
 * Fetching it with a callstatus different from CALLSTATUS_ACTIVE, CALLSTATUS_PAUSED or CALLSTATUS_ENDED
 * will return nil.
 * \sa WeemoCall::callStatus
 * \sa WeemoCallDelegate::weemoCall:sipID:
 * \since 5.2
 */
@property(nonatomic, readonly, getter = getSipID) NSString *sipID;


#pragma mark - Views and Video
/**
 * \brief The view in wich the call should display the incoming share. Set by the host application, it *MUST NOT* be a view already handled by a controller.
 * \sa WeemoCall::viewVideoIn
 * \since 5.1
 */
@property(nonatomic, weak) UIView *viewShareIn;

/**
 * \brief The view in wich the call should display the incoming video. Set by the host application, it *MUST NOT* be a view already handled by a controller.
 * \sa WeemoCall::viewShareIn
 * \since 5.0
 */
@property(nonatomic, weak) UIView *viewVideoIn;

/**
 * \brief The view in wich the call should display the outgoing video.
 * \since 5.0
 */
@property(nonatomic, weak) UIView *viewVideoOut;

/**
 * \brief Set this value to ask for a change in the incoming video resolution. Valid values are profile_small and profile_high
 *
 * Upon change, WeemoCallDelegate::weemoCall:videoProfile: is called.
 * \sa WeemoCallDelegate::weemoCall:videoProfile:
 * \since 5.1
 * \deprecated Replaced by WeemoCall::videoInProfile. Names sanitization effort.
 * WeemoCall::videoInProfile
 */
@property (nonatomic) video_profile_t videoProfile __attribute__ ((deprecated("Deprecated since 5.2")));

/**
 * \brief Set this value to ask for a change in the incoming video resolution. Valid values are profile_small and profile_high
 *
 * Upon change, WeemoCallDelegate::weemoCall:videoInProfileChange: is called.
 * \sa WeemoCallDelegate::weemoCall:videoOutProfile
 * \sa WeemoCallDelegate::weemoCall:getVideoInSize
 * \since 5.2
 */
@property (nonatomic) video_profile_t videoInProfile;

/**
 * \brief Set this value to ask for a change in the outgoing video resolution. Valid values are profile_small and profile_high
 *
 * Upon change, WeemoCallDelegate::weemoCall:videoProfile: is called.
 * \sa WeemoCallDelegate::weemoCall:videoInProfile
 * \sa WeemoCallDelegate::weemoCall:getVideoOutSize
 * \since 5.2
 */
@property (nonatomic) video_profile_t videoOutProfile;

/**
 * \brief Returns the incoming video size, used to resize the incoming video view (in case of ratio change and/or dimension change).
 * \return The size of the video.
 * \since 5.2
 */
- (CGSize)getVideoInSize;

/**
 * \brief Returns the outgoing video size, to be used to resize the momitoring video.
 * \return The size of the video, such as the video is correctly oriented.
 * \since 5.2
 */
- (CGSize)getVideoOutSize;

/**
 * \brief Returns the incoming video size, used to resize the incoming video view (in case of ratio change and/or dimension change).
 * \return The size of the video.
 * \since 5.1
 */
- (CGSize)getShareInSize;

/**
 * \brief Returns the incoming video size, used to resize the incoming video view (in case of ratio change and/or dimension change).
 * \return The size of the video.
 * \deprecated Replaced by WeemoCall::getVideoInSize. Names sanitization effort.
 * \since 5.1
 */
- (CGSize)getVideoInProfile __attribute__ ((deprecated("Deprecated since 5.2")));


/**
 * \brief Returns the outgoing video size, to be used to resize the momitoring video.
 * \return The size of the video, such as the video is correctly oriented.
 * \deprecated 5.2 Replaced by WeemoCall::getVideoOutSize. Names sanitization effort.
 * \since 5.1
 */
- (CGSize)getVideoOutProfile __attribute__ ((deprecated("Deprecated since 5.2")));

@end
