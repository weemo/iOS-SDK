//
//  WeemoCall.h
//  iOS-SDK
//
//  Created by Charles Thierry on 7/16/13.
//  Copyright (c) 2013 Weemo. All rights reserved.
//

/**
 * \brief Represents a call to a contact or a conference
 */
@interface WeemoCall : NSObject

/**
 * \brief Hang up the call and stop it
 */
- (void) hangup;

/**
 * \brief Pause the call so it can be later resumed
 */
- (void) pause;

/**
 * \brief Resume the call if it was paused. Pick it if it is ringing.
 */
- (void) resume;

/**
 * \brief Start sending video from the camera (the video DOES NOT start automatically)
 */
- (void) videoStart;

/**
 * \brief Stop sending video from the camera
 */
- (void) videoStop;

/**
 * \brief Start sending audio from the microphone (the audio DOES start automatically)
 */
- (void) audioStart;

/**
 * \brief Stop sending audio from the microphone
 */
- (void) audioStop;

/**
 * \brief Changes camera source from front to back and vice versa
 */
- (void)toggleCameraSource;

/**
 * Changes the audio output used by the device. Two audio outputs are possible: Loudspeaker or Earphone/Headset
 */
- (void)toggleAudioOutput;

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
 *
 * Users are encourage to use Key Value Observing on this property
 */
@property(readonly) NSString *isReceivingVideo;
             
/**
 * \brief Whether or not the call is sending video
 */
@property(readonly) NSString *isSendingVideo;

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
 *
 * Users are encourage to use Key Value Observing on this property
 */
@property(readonly) int status;

/**
 * \brief YES if this call is a conference
 */
@property(readonly) BOOL isConference;

@end
