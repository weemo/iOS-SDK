//
//  ViewController.h
//  sdk-helper
//
//  Created by Charles Thierry on 7/16/13.
//  Copyright (c) 2013 Weemo SAS. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CallViewController.h"
/** 
 * This is the main View Controller. Deals with the connection parameters and call start.
 */
@interface ViewController : UIViewController <WeemoDelegate, UIAlertViewDelegate>

@property (weak, nonatomic) IBOutlet UIButton *b_authenticate;
@property (weak, nonatomic) IBOutlet UIButton *b_call;
@property (weak, nonatomic) IBOutlet UIButton *b_hangup;
@property (weak, nonatomic) IBOutlet UILabel *l_displayname;
@property (weak, nonatomic) IBOutlet UITextField *tf_yourID;
@property (weak, nonatomic) IBOutlet UITextField *tf_contactID;
@property (weak, nonatomic) IBOutlet UILabel *l_callStatus;
@property (weak, nonatomic) IBOutlet UITextView *tv_errorField;

@property (nonatomic) CallViewController *cvc_active;
@property (nonatomic) WeemoCall *currentCall;
@property (nonatomic) NSString *displayName;
@property (nonatomic) int status;


/** Called when the user taps the authenticate button */
- (IBAction)authenticate:(id)sender;

/** Called when the user taps the Call button */
- (IBAction)call:(id)sender;

/** Called when the user taps the hangup button */
- (IBAction)hangup:(id)sender;

- (void)addCallView;
- (void)removeCallView;


- (void)weemoContact:(NSString*)contact CanBeCalled:(BOOL)can;

@end
