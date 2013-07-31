//
//  ViewController.h
//  sdk-helper
//
//  Created by Charles Thierry on 7/16/13.
//  Copyright (c) 2013 Weemo SAS. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Controller.h"
#import "CallViewController.h"
/** 
 * This is the main View Controller. Deals with the connection parameters and call start.
 */
@interface ViewController : UIViewController <ControllerDelegate>

@property Controller *we_deleg;

@property (weak, nonatomic) IBOutlet UIButton *b_authenticate;
@property (weak, nonatomic) IBOutlet UIButton *b_disconnect;
@property (weak, nonatomic) IBOutlet UIButton *b_call;
@property (weak, nonatomic) IBOutlet UIButton *b_hangup;
@property (weak, nonatomic) IBOutlet UILabel *l_displayname;
@property (weak, nonatomic) IBOutlet UITextField *tf_yourID;
@property (weak, nonatomic) IBOutlet UITextField *tf_contactID;
@property (weak, nonatomic) IBOutlet UILabel *l_callStatus;
@property (weak, nonatomic) IBOutlet UITextView *tv_errorField;

@property (nonatomic) CallViewController *cvc_active;

/** Called when the user taps the authenticate button */
- (IBAction)authenticate:(id)sender;

/** Called when the user taps the Call button */
- (IBAction)call:(id)sender;

/** Called when the user taps the hangup button */
- (IBAction)hangup:(id)sender;

- (void)addCallView;
- (void)removeCallView;

#pragma mark - ControllerDelegation
- (void)statusChange:(int)newStatus from:(id)sender;
- (void)callStatusChange:(int)newStatus from:(id)sender;
- (void)displayNameChange:(NSString *)newDN from:(id)sender;

@end
