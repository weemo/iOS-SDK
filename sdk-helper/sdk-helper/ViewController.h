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

@property (nonatomic) CallViewController *cvc_active;

- (IBAction)authenticate:(id)sender;
- (IBAction)disconnect:(id)sender;
- (IBAction)call:(id)sender;

#pragma mark - ControllerDelegation

- (void)statusChange:(int)newStatus from:(id)sender;
- (void)callStatusChange:(int)newStatus from:(id)sender;
- (void)displayNameChange:(NSString *)newDN from:(id)sender;

@end
