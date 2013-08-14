//
//  CallViewController.h
//  sdk-helper
//
//  Created by Charles Thierry on 7/19/13.
//  Copyright (c) 2013 Weemo SAS. All rights reserved.
//

@interface CallViewController : UIViewController <WeemoCallDelegate>

@property (weak, nonatomic) IBOutlet UIButton *b_hangup;
@property (weak, nonatomic) IBOutlet UIButton *b_profile;
@property (weak, nonatomic) IBOutlet UIButton *b_toggleVideo;
@property (weak, nonatomic) IBOutlet UIButton *b_toggleAudio;
@property (weak, nonatomic) IBOutlet UIView *v_videoIn;
@property (weak, nonatomic) IBOutlet UIView *v_videoOut;


@property (weak, nonatomic) WeemoCall *call;

/**
 * The user tapped on the "Hangup" button
 */
- (IBAction)hangup:(id)sender;
/**
 * The user tapped on the "HD" button
 */
- (IBAction)profile:(id)sender;
/**
 * The user tapped on the "Enable Video"
 */
- (IBAction)toggleVideo:(id)sender;
/**
 * The user tapped on "Enable Mic." button
 */
- (IBAction)toggleAudio:(id)sender;

- (void)weemoCall:(id)sender videoReceiving:(BOOL)isReceiving;
- (void)weemoCall:(id)sender videoSending:(BOOL)isSending;
- (void)weemoCall:(id)sender videoProfile:(int)profile;
- (void)weemoCall:(id)sender videoSource:(int)source;
- (void)weemoCall:(id)sender audioRoute:(int)route;
- (void)weemoCall:(id)sender callStatus:(int)status;

@end
