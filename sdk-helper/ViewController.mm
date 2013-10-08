//
//  ViewController.m
//  sdk-helper
//
//  Created by Charles Thierry on 7/16/13.
//  Copyright (c) 2013 Weemo SAS. All rights reserved.
//

#import "ViewController.h"


@interface ViewController ()
@property (nonatomic)BOOL autoreconnect;
@end

@implementation ViewController

@synthesize l_callStatus;
@synthesize tv_errorField;
@synthesize status;
@synthesize displayName;
@synthesize autoreconnect;

- (void)viewDidLoad
{
    [super viewDidLoad];
	
	_cvc_active = nil;
	autoreconnect = NO;
	[[self b_authenticate]setTitle:@"Auth." forState:UIControlStateNormal];
	NSError *err;
	//initializing the SDK
	[Weemo WeemoWithURLReferer:MOBILEAPPID
			   andDelegate:self error:&err];
}

- (IBAction)authenticate:(id)sender
{
	[[self tf_yourID] resignFirstResponder];
	if (![sender isEqual:[self b_authenticate]]) return;
	if ([[[sender titleLabel]text]isEqualToString:@"Auth."])
	{
		if ([[Weemo instance]authenticateWithToken:[[self tf_yourID]text]
										   andType:USERTYPE_INTERNAL])
		{
			[self setDisplayName:[[self tf_yourID] text]];
		} else {
			[self setDisplayName:@"<not authenticated>"];
		}
	} else {
		[[self tf_yourID]setText:@""];
		[[self tf_contactID]setText:@""];
		[[self l_displayname]setText:@"<not authenticated>"];
		[[self l_callStatus]setText:@"<no call>"];
		[self disconnect];
	}
}

- (IBAction)call:(id)sender
{
	[[Weemo instance]createCall:[[self tf_contactID] text]];
	[[self view] endEditing:YES];
}

- (void)createCallView
{
	NSLog(@">>>> createCallView");
	if (_cvc_active) return;
	
	NSString *storyboardname = ([[UIDevice currentDevice]userInterfaceIdiom] == UIUserInterfaceIdiomPhone)?@"iphone":@"ipad";
	_cvc_active = [[UIStoryboard storyboardWithName:storyboardname bundle:[NSBundle mainBundle]] instantiateViewControllerWithIdentifier:@"CallViewController"];
	
	[[[Weemo instance]activeCall]setDelegate:_cvc_active];
	[self addChildViewController:_cvc_active];
}

- (void)addCallView
{
	NSLog(@">>>> addCallView ");
	if (!_cvc_active) [self createCallView];

	if ([[[_cvc_active view] superview] isEqual:[self view]] )
	{
		return;
	}

	[[_cvc_active view]setFrame:CGRectMake(0., 0., [[self view]frame].size.width, [[self view]frame].size.height)];
	[[self view] addSubview:[_cvc_active view]];
}

- (void)removeCallView
{
	
	[_cvc_active removeFromParentViewController];
	[[_cvc_active view]removeFromSuperview];
	[[self l_callStatus]setText:@"<no call>"];
	_cvc_active = nil;
	[self setStatus:2];
}

- (void)disconnect
{
	[[self tf_contactID]setText:@""];
	[[self l_callStatus]setText:@"<no call>"];
	autoreconnect = YES;
	[[Weemo instance] disconnect];
}

- (void)setStatus:(int)newStatus
{
	status = newStatus;
	switch (newStatus)
	{
		case 1:{
			dispatch_async(dispatch_get_main_queue(), ^{
				[[self b_authenticate]setTitle:@"Auth." forState:UIControlStateNormal];
				[[self tf_yourID]setEnabled:YES];
				[[self tf_contactID]setEnabled:NO];
				[[self b_authenticate]setEnabled:YES];
				[[self b_call]setEnabled:NO];
			});}
			break;
		case 2:{
			dispatch_async(dispatch_get_main_queue(), ^{
				[[self b_authenticate]setTitle:@"Disc." forState:UIControlStateNormal];
				[[self tf_yourID]setEnabled:NO];
				[[self tf_contactID]setEnabled:YES];
				[[self b_authenticate]setEnabled:YES];
				[[self b_call]setEnabled:YES];
			});}
			break;
		case 3:{
			dispatch_async(dispatch_get_main_queue(), ^{
				[[self b_authenticate]setTitle:@"Disc." forState:UIControlStateNormal];
				[[self tf_yourID]setEnabled:NO];
				[[self tf_contactID]setEnabled:YES];
				[[self b_authenticate]setEnabled:YES];
				[[self b_call]setEnabled:NO];
			});}
		default:{
			dispatch_async(dispatch_get_main_queue(), ^{
				[[self b_authenticate]setTitle:@"Disc." forState:UIControlStateNormal];
				[[self tf_yourID]setEnabled:NO];
				[[self tf_contactID]setEnabled:NO];
				[[self b_authenticate]setEnabled:NO];
				[[self b_call]setEnabled:NO];
			});}
	}
}

- (void)setCallStatus:(int)newStatus
{
	dispatch_async(dispatch_get_main_queue(), ^{
		switch (newStatus) {
			case CALLSTATUS_ACTIVE:
			{
				NSLog(@">>> Call Active");
				[[self l_callStatus] setText:@"Active"];
				[self createCallView];
				[self addCallView];
			}break;
			case CALLSTATUS_PROCEEDING:
			{
				NSLog(@">>>> Call Proceeding");
				[[self l_callStatus] setText:@"Proceeding"];
				[self createCallView];
			}break;
			case CALLSTATUS_INCOMING:
			{
				NSLog(@">>>> Call Incoming");
				[[self l_callStatus]setText:@"Incoming"];
				[self createCallView];
				
			}break;
			case CALLSTATUS_ENDED:
			{
				[[self l_callStatus] setText:@"Ended"];
				[self removeCallView];
				
			}break;
			default:
			{
				[[self l_callStatus]setText:@"<none>"];
				
			}break;
		}
	});
}

- (void)displayNameChange:(NSString *)newDN
{
	dispatch_async(dispatch_get_main_queue(), ^{
		[[self l_displayname]setText: [self displayName]];
	});

}

- (void)setDisplayName:(NSString *)dn
{
	if (dn == nil) {
		displayName = @"<nop>";
		NSLog(@">>>> WARNING: Trying to change the display name to nil");
	} else {
		displayName = [NSString stringWithString:dn];
	}
	[self displayNameChange:displayName];
}

#pragma mark - dealing with the incoming call
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
	if (buttonIndex == 0)
	{
		//user took the call
		[self createCallView];
		[self addCallView];
		[self setCallStatus:[[[Weemo instance] activeCall]callStatus]];
		[[[Weemo instance] activeCall]resume];
	} else {
		//user hangup
		[self removeCallView];
		[[[Weemo instance] activeCall]hangup];
	}
}

#pragma mark - WeemoDelegation
- (void)weemoCallCreated:(WeemoCall*)call
{
	NSLog(@">>>> Controller callCreated: 0x%X", [call callStatus]);
	if ([call callStatus] == CALLSTATUS_INCOMING)
	{
		[self setStatus:3];
		incomingcall = [[UIAlertView alloc]initWithTitle:@"Incoming Call"
															  message:[NSString stringWithFormat:@"%@ is calling", [call contactID]]
															 delegate:self
													cancelButtonTitle:@"Pick-up"
													otherButtonTitles:@"Deny", nil];
		dispatch_async(dispatch_get_main_queue(), ^{
			[incomingcall show];
		});
	}
	[self setCallStatus:[call callStatus]];
}


- (void)weemoCallEnded:(WeemoCall *)call
{
	dispatch_async(dispatch_get_main_queue(), ^{
		[self removeCallView];
		[incomingcall dismissWithClickedButtonIndex:1 animated:YES];
		incomingcall = nil;
	});
}

- (void)weemoDidConnect:(NSError*)error
{
	[self setStatus:1];
	dispatch_async(dispatch_get_main_queue(), ^{
		if (error)
		{
			[[self tv_errorField]setText:[error debugDescription]];
		} else {
			[[self tv_errorField]setText:@"<No Error>"];
		}
	});
}

- (void)weemoDidAuthenticate:(NSError *)error
{

	NSLog(@">>>> Weemo did authenticate: current status: %d, error: %@", [self status], error);
	if (!error) {
		dispatch_async(dispatch_get_main_queue(), ^{
			[self setDisplayName: [[self tf_yourID]text]];
			[[self tv_errorField]setText:@"<No Error>"];
		});
		[[Weemo instance]setDisplayName:[self displayName]];
		[self setStatus:2];
	} else {
		dispatch_async(dispatch_get_main_queue(), ^{
			[self setDisplayName:[NSString stringWithFormat: @"SIP NOK"]];
			[[self tv_errorField] setText:[error debugDescription]];
		});
	}
}

- (void)weemoDidDisconnect:(NSError*)error
{
	[self setStatus:0];
	[self setDisplayName:@"<not authentified>"];
	if (error){
		[[self tv_errorField]setText:[error debugDescription]];
	} else {
		[[self tv_errorField]setText:@"<No Error>"];
	}
	if (autoreconnect)
	{
		NSError *err;
		[Weemo WeemoWithURLReferer:MOBILEAPPID andDelegate:self error:&err];
	}
}

- (void)weemoContact:(NSString*)contact canBeCalled:(BOOL)can
{
	NSLog(@">>>> Contact %@ can %@ be called.", contact, can?@"":@"NOT");
}

@end
