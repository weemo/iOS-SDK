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
- (void)weemoCall:(id)sender videoReceiving:(BOOL)isReceiving;
/**
 * Called when the call starts sending video.
 * \param isSending Answers "Are we sending video?"
 * \param sender The Call which property changed
 */
- (void)weemoCall:(id)sender videoSending:(BOOL)isSending;
/**
 * Called when the incoming video profile changes
 * \param profile The new profile used by the incoming video (impacts the videoIn view size)
 * \param sender The Call which property changed
 */
- (void)weemoCall:(id)sender videoProfile:(int)profile;
/**
 * Called when the video source changes
 * \param source The new source. 0 is the front (on the screen side of the device) camera, 1 is the back camera
 * \param sender The Call which property changed
 */
- (void)weemoCall:(id)sender videoSource:(int)source;
/**
 * Called when the audio route changes
 * \param route The new route used. 0 is the usual route (regular phone equipment), 1 is the phone's speaker
 * \param sender The Call which property changed
 */
- (void)weemoCall:(id)sender audioRoute:(int)route;
/** 
 *
 */
/**
 * Called when the status of the call changes
 * \param status The new status of the call (i.e. CALLSTATUS_RINGING)
 * \param sender The Call which property changed
 */
- (void)weemoCall:(id)sender callStatus:(int)status;

@end


/**
 * \brief Represents a call to a contact or a conference. Such an object is created on -[[Weemo instance]call:] call.
 *
 * Remarks:
 * 
 * The Video views autorotates with the interface and following the interface rotation rules set by the Host App. However, the outgoing video stream rotates with the device. This allow the outgoing video to be shown with a correct rotation within the receiving device, even if the user sending the video is holding the device using a rotation not supported by the Host App.
 * 
 * When the device is held in a non supported rotation, the outgoing video view is rotated to indicate that the rotation is not supported.
 */
@interface WeemoCall : NSObject

/**
 * \brief Hang up the call and stop it
 */
- (void)hangup;

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
 * Request an incoming video profile change. The -[WeemoCallDelegate videoProfile:from:] is called when the profile modification is
 * validated.
 */
- (void)toggleVideoProfile;


/**
 * Value changes after a toggleVideoProfile. 0 is low quality profile, 1 if higher quality.
 * The delegate is notified about the change through -[WeemoCallDelegate videoProfile:from:]
 */
@property (nonatomic, readonly) int videoProfile;

/**
 * Value changes after a toggleAudioRoute. 0 is default route (phone
 * standard equipment), 1 is speaker/mic.
 * The delegate is notified about the change through -[WeemoCallDelegate audioSource:from:]
 */
@property (nonatomic, readonly) int audioRoute;

/**
 * Value changes after a toggleCameraSource. 0 is front camera, 1 is back camera.
 * The delegate is notified about the change through -[WeemoCallDelegate videoSource:from:]
 */

@property (nonatomic, readonly) int cameraSource;

/**
 * \brief Duration of the call (changes every second...)
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
@property(nonatomic, weak) UIView *viewVideoIn;

/**
 * \brief Whether or not the call is sending video
 */
@property(nonatomic, readonly, getter = isSendingVideo) BOOL sendingVideo;

/**
 * \brief The view in wich the call should display the outgoing video.
 */
@property(nonatomic, weak) UIView *viewVideoOut;

/**
 * \brief Statistics of the current instant in the call
 *
 * As the structure is reused, it's content is only valid until next retrieval of this property
 */
@property(readonly) WeemoStat *stats;

/**
 * \brief Programers can attach any kind of object to a call with this property
 */
@property(strong) id userInfo;

/**
 * \brief Status of the call (the value is one of the CALLSTATUS_* defines)
 * The delegate is notified about the change through -[WeemoCallDelegate callStatus:from:].
 */
@property(nonatomic, readonly) int callStatus;

/**
 * \brief YES if this call is a conference
 */
@property(readonly) BOOL isConference;

/**
 * \brief The host app should set this value if it wants to be notified about call changes.
 */
@property(nonatomic, strong) id<WeemoCallDelegate>delegate;

@end
