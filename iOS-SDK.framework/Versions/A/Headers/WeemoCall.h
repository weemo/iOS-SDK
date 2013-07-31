//
//  WeemoCall.h
//  iOS-SDK
//
//  Created by Charles Thierry on 7/16/13.
//  Copyright (c) 2013 Weemo. All rights reserved.
//
@protocol WeemoCallDelegate <NSObject>
@optional
/**
 * Called when the call starts receiving video.
 * \param isReceiving Answers "Are we receing video?"
 * \param sender The call which property changed
 */
- (void)videoReceiving:(BOOL)isReceiving from:(id)sender;
/**
 * Called when the call starts sending video.
 * \param isSending Answers "Are we sending video?"
 * \param sender The Call which property changed
 */
- (void)videoSending:(BOOL)isSending from:(id)sender;
/**
 * Called when the incoming video profile changes.
 * \param profile The new profile used by the incoming video (impacts the videoIn view size)
 * \param sender The Call which property changed
 */
- (void)videoProfile:(int)profile from:(id)sender;
/**
 * Called when the video source changes.
 * \param source The new source. 0 is the front (on the screen side of the device) camera, 1 is the back camera
 * \param sender The Call which property changed
 */
- (void)videoSource:(int)source from:(id)sender;
/**
 * Called when the audio route changes.
 * \param route The new route used. 0 is the usual route (regular phone equipment), 1 is the phone's speaker
 * \param sender The Call which property changed
 */
- (void)audioRoute:(int)route from:(id)sender;
/**
 * Called when the status of the call changes.
 * \param status The new status of the call, as described in the WeemoData file
 * \param sender The Call which property changed
 */
- (void)callStatus:(int)status from:(id)sender;

@end


/**
 * \brief Represents a call to a contact or a conference. Such an object is created on -[[Weemo instance]call:] call. It is strongly advised to attach an object implementing the WeemoCallDelegate protocol to the WeemoCall.
 */
@interface WeemoCall : NSObject

/**
 * \brief Hang up the call and stop it
 */
- (void) hangup;

/**
 * \brief Pause the call so it can be later resumed. WARNING: Not Yet Available
 */
- (void)pause;

/**
 * \brief Resume the call if it was paused. Pick it up if it is ringing.
 */
- (void)resume;

/**
 * \brief Start sending video from the camera. The video starts automatically upon call start.
 */
- (void)videoStart;

/**
 * \brief Stop sending video from the camera
 */
- (void)videoStop;

/**
 * \brief Start sending audio from the microphone. The audio starts automatically upon call start.
 */
- (void)audioStart;

/**
 * \brief Stop sending audio from the microphone, sends empty audio frame.
 */
- (void)audioStop;

/**
 * \brief Switches camera source between front and back. [WeemoCallDelegate videoSource:from:] is called on modification.
 */
- (void)toggleCameraSource;

/**
 * Changes the audio route used by the call. Two audio outputs are possible: Loudspeaker(1) or Earphone/Headset(0). Upon change, the - [WeemoCallDelegate audioRoute:from:] is called.
 */
- (void)toggleAudioRoute;


/**
 * Request an incoming video profile change. The -[WeemoCallDelegate videoProfile:from:] is called when the profile modification is validated.
 */
- (void)toggleVideoProfile;


/**
 * Value changes after a toggleVideoProfile. 0 is low quality profile, 1 if higher quality. The delegate is notified about the change through -[WeemoCallDelegate videoProfile:from:]
 */
@property (nonatomic, readonly) int videoProfile;

/**
 * Value changes after a toggleAudioRoute. 0 is default route (phone  standard equipment), 1 is speaker/mic. The delegate is notified about the change through -[WeemoCallDelegate audioSource:from:]
 */
@property (nonatomic, readonly) int audioRoute;

/**
 * Value changes after a toggleCameraSource. 0 is front camera, 1 is back camera. The delegate is notified about the change through -[WeemoCallDelegate videoSource:from:]
 */

@property (nonatomic, readonly) int cameraSource;

/**
 * \brief Current duration of the call
 */
@property(readonly) NSTimeInterval duration;

/**
 * \brief ID of the contact or the conference being called
 */
@property(readonly) NSString *contactID;

/**
 * \brief Whether or not the call is receiving video
 */
@property(nonatomic, readonly, getter = isReceivingVideo) BOOL receivingVideo;

/**
 * \brief The view in wich the call should display the incoming video.
 */
@property(nonatomic) UIView *viewVideoIn;

/**
 * \brief Whether or not the call is sending video
 */
@property(nonatomic, readonly, getter = isSendingVideo) BOOL sendingVideo;

/**
 * \brief The view in wich the call should display the outgoing video.
 */
@property(nonatomic) UIView *viewVideoOut;

/**
 * \brief Statistics of the current instant in the call
 *
 * As the structure is reused, it's content is only valid until next retrieval of this property
 */
@property(readonly) WeemoStat *stats;

/**
 * \brief Programers can attach any kind of object to a call with this property. Attached data is not copied, any scope work is to be done by the host app.
 */
@property(strong) id userInfo;

/**
 * \brief Status of the call (the value is one of the CALLSTATUS_ defines described in WeemoData.h).
 * The delegate is notified about the change through -[WeemoCallDelegate callStatus:from:].
 */
@property(nonatomic, readonly) int callStatus;

/**
 * \brief YES if this call is a conference
 */
@property(readonly) BOOL isConference;

/**
 * \brief The call Delegate will be notified of any call status modification (receiving/sending video, audio, call terminated and so on).
 */
@property(nonatomic) id<WeemoCallDelegate>delegate;

@end
