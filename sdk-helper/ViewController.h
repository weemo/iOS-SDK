//
//  ViewController.h
//  sdk-helper
//
//  Created by Charles Thierry on 7/16/13.

#import <UIKit/UIKit.h>
#import "CallViewController.h"
/** 
 * \brief This is the main View Controller. Deals with the connection parameters and call start.
 * The MainViewController is a WeemoDelegate. As such, it is responsible for the WeemoDriver connecting to the WeemoCloud and for user authentication. Any error sent by the Weemo singleton is dealt with here.
 *
 * On Application start, the Weemo singleton is instanciated automatically with a preset APIKey found in the project pch. When the delegate is notified of the connection success, the Authenticate button and the YourID textfield are activated, allowing a user to authenticate oneself on the cloud.
 *
 * After authentication, the Call button and ContactID textfield are activated, allowing the user to call another contact.
 *
 * Three labels display information about the current session. 
 *		The first display the username (which is here equivalent to the UserID, for no special reason) followed by "| SIPOK" if the user can call. If the user can not call, the suffix is "| SIPNOK".
 *		The second display the status of the ongoing call or <No call> if no call is currently ongoing.
 *		The third field displays the debugInformation of the last encountered error.
 */
@interface ViewController : UIViewController <WeemoDelegate, UIAlertViewDelegate>
@property (weak, nonatomic) IBOutlet UIButton *b_authenticate;
@property (weak, nonatomic) IBOutlet UIButton *b_call;

@property (weak, nonatomic) IBOutlet UITextField *tf_yourID; //< the UserID of the user
@property (weak, nonatomic) IBOutlet UITextField *tf_contactID; //< The UserID of the contact you want to call

@property (weak, nonatomic) IBOutlet UILabel *l_displayname; //< the user displayname and possibly a suffix
@property (weak, nonatomic) IBOutlet UILabel *l_callStatus; //the status of the ongoing call if any
@property (weak, nonatomic) IBOutlet UITextView *tv_errorField; //< any error occuring will have its debugError NSString printed here.

@property (nonatomic) CallViewController *cvc_active;
@property (nonatomic) NSString *displayName; //the user display name is stored here, without the possible suffix

/**
 * four possible values.
 * 0: the SDK could not connect to weemo servers
 * 1: the SDK is connected to the servers, users can authenticate
 * 2: the SDK is connected, users can place a call
 * 3: call ongoing, not possible to press call
 */
@property (nonatomic) int status;

/** Called when the user taps the authenticate button */
- (IBAction)authenticate:(id)sender;

/** Called when the user taps the Call button */
- (IBAction)call:(id)sender;

- (void)addCallView;
- (void)removeCallView;



#pragma mark - optional delegate methods used
- (void)weemoContact:(NSString*)contact canBeCalled:(BOOL)can;
- (void)weemoDidDisconnect:(NSError*)error;

@end
