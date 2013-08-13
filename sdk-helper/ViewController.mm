//
//  ViewController.m
//  sdk-helper
//
//  Created by Charles Thierry on 7/16/13.
//  Copyright (c) 2013 Weemo SAS. All rights reserved.
//

#import "ViewController.h"


@interface ViewController ()

@end

@implementation ViewController

@synthesize l_callStatus;
@synthesize tv_errorField;
@synthesize currentCall;
@synthesize status;
@synthesize displayName;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
	
	_cvc_active = nil;
	[Weemo WeemoWithAPIKey:APIKEY andDelegate:self onInit:^(Weemo * w, NSError *err) {
		NSAssert(!err, [err debugDescription]);
	}];
	[[self b_authenticate]setTitle:@"Authenticate" forState:UIControlStateNormal];
}

- (IBAction)authenticate:(id)sender
{
	[[self tf_yourID] resignFirstResponder];
	if (![sender isEqual:[self b_authenticate]]) return;
	if ([[[sender titleLabel]text]isEqualToString:@"Authenticate"])
	{
		[self setDisplayName:[[self tf_yourID] text]];
		[[Weemo instance] connectWithUserID:[[self tf_yourID]text]
								   toDomain:@"weemo-poc.com"];
	} else {
		[self disconnect];
		[[self tf_yourID]setText:@""];
		[[self tf_contactID]setText:@""];
		[[self l_displayname]setText:@"<not authenticated>"];
		[[self l_callStatus]setText:@"<none>"];
		[Weemo WeemoWithAPIKey:APIKEY andDelegate:self onInit:^(Weemo * w, NSError *err) {
			NSAssert(!err, [err debugDescription]);
		}];
	}
}

- (IBAction)call:(id)sender
{
//	[[Weemo instance]call:[[self tf_contactID] text]];
	[[Weemo instance] getStatus:[[self tf_contactID] text]];
	[[self tf_contactID]resignFirstResponder];
}

- (IBAction)hangup:(id)sender
{
	[[self tf_contactID]setText:@""];
	[[self l_callStatus]setText:@"<none>"];
}

- (void)createCallView
{
	if (_cvc_active) return; //call view already instanciated
	NSString *storyboardname = ([[UIDevice currentDevice]userInterfaceIdiom] == UIUserInterfaceIdiomPhone)?@"iphone":@"ipad";
	_cvc_active = [[UIStoryboard storyboardWithName:storyboardname bundle:[NSBundle mainBundle]] instantiateViewControllerWithIdentifier:@"CallViewController"];
	[[[Weemo instance]activeCall]setDelegate:_cvc_active];
	[self addChildViewController:_cvc_active];
}

- (void)addCallView
{
	if (!_cvc_active) [self createCallView];
	if ([[[_cvc_active view] superview] isEqual:[self view]] ) return; //view was already added
	[[_cvc_active view]setFrame:CGRectMake(0., 0., [[self view]frame].size.width, [[self view]frame].size.height)];

	[[self view] addSubview:[_cvc_active view]];
}

- (void)removeCallView
{
	[_cvc_active removeFromParentViewController];
	[[_cvc_active view]removeFromSuperview];
	[[self l_callStatus]setText:@"<none>"];
	_cvc_active = nil;
}

- (void)disconnect
{
	[self hangup:nil];
	[[Weemo instance] disconnect];
}

- (void)setStatus:(int)newStatus
{
	status = newStatus;
	switch (newStatus)
	{
		case 1:{
			dispatch_async(dispatch_get_main_queue(), ^{
				[[self b_authenticate]setTitle:@"Authenticate" forState:UIControlStateNormal];
				[[self tf_yourID]setEnabled:YES];
				[[self tf_contactID]setEnabled:NO];
				[[self b_authenticate]setEnabled:YES];
				[[self b_call]setEnabled:NO];
				[[self b_hangup]setEnabled:NO];
			});}
			break;
		case 2:{
			dispatch_async(dispatch_get_main_queue(), ^{
				[[self b_authenticate]setTitle:@"Disconnect" forState:UIControlStateNormal];
				[[self tf_yourID]setEnabled:NO];
				[[self tf_contactID]setEnabled:YES];
				[[self b_authenticate]setEnabled:YES];
				[[self b_call]setEnabled:YES];
				[[self b_hangup]setEnabled:NO];
			});}
			break;
		case 3:{
			dispatch_async(dispatch_get_main_queue(), ^{
				[[self b_authenticate]setTitle:@"Disconnect" forState:UIControlStateNormal];
				[[self tf_yourID]setEnabled:NO];
				[[self tf_contactID]setEnabled:YES];
				[[self b_authenticate]setEnabled:YES];
				[[self b_call]setEnabled:NO];
				[[self b_hangup]setEnabled:YES];
			});}
		default:{
			dispatch_async(dispatch_get_main_queue(), ^{
				[[self b_authenticate]setTitle:@"Authenticate" forState:UIControlStateNormal];
				[[self tf_yourID]setEnabled:NO];
				[[self tf_contactID]setEnabled:NO];
				[[self b_authenticate]setEnabled:NO];
				[[self b_call]setEnabled:NO];
				[[self b_hangup]setEnabled:NO];
			});}
	}
}

- (void)setCallStatus:(int)newStatus
{
	dispatch_async(dispatch_get_main_queue(), ^{
		switch (newStatus) {
			case CALLSTATUS_ACTIVE:
			{
				[[self l_callStatus] setText:@"Active"];
				[self addCallView];
			}break;
			case CALLSTATUS_PROCEEDING:
			{
				[[self l_callStatus] setText:@"Proceeding"];
				break;
			}
			case CALLSTATUS_INCOMING:
			{
				[[self l_callStatus]setText:@"Incoming"];
				[[self b_hangup]setEnabled:YES];
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
	displayName = [NSString stringWithString:dn];
	[self displayNameChange:displayName];
}

#pragma mark - dealing with the incoming call
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
	if (buttonIndex == 0)
	{
		//user took the call
		[[self currentCall]resume];
	} else {
		//user hangup
		[[self currentCall]hangup];
	}
}

#pragma mark - WeemoDelegation
- (void)weemoCallCreated:(WeemoCall*)call
{
	[self setCurrentCall:call];
	NSLog(@">>>> Controller callCreated: ");
	if ([call callStatus]==CALLSTATUS_INCOMING)
	{
		[self setStatus:3];
		UIAlertView *callIncoming = [[UIAlertView alloc]initWithTitle:@"Incoming Call"
															  message:[NSString stringWithFormat:@"%@ is calling", [call contactID]]
															 delegate:self
													cancelButtonTitle:@"Pick-up"
													otherButtonTitles:@"Deny", nil];
		dispatch_async(dispatch_get_main_queue(), ^{
			[callIncoming show];
		});
	} else if ([call callStatus] == CALLSTATUS_PROCEEDING)
	{
		//we are calling someone, might as well display the callview
	}
	[self setCallStatus:[call callStatus]];
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
	dispatch_async(dispatch_get_main_queue(), ^{
		if (!error) {
			if ([self status] == 2)
			{
				[self setDisplayName:[NSString stringWithFormat: @"%@ | SIP OK", [[Weemo instance] displayName]]];
			} else {
				[self setStatus:2];
				[[Weemo instance]setDisplayName:[self displayName]];
			}
			[[self tv_errorField]setText:@"<No Error>"];
		} else {
			[self setDisplayName:[NSString stringWithFormat: @"%@ | SIP NOK", [[Weemo instance] displayName]]];
			[[self tv_errorField]setText:[error debugDescription]];
		}
	});
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
}

- (void)weemoContact:(NSString*)contact CanBeCalled:(BOOL)can
{
		
}

@end
