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

@synthesize s_lastError;
@synthesize we_deleg;
@synthesize l_callStatus;
@synthesize tv_errorField;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
	
	_cvc_active = nil;
	[self setWe_deleg:[[Controller alloc] init]];
	[[self we_deleg]setDelegate:self];
	[[self we_deleg]activate:APIKEY];
	[[self b_authenticate]setTitle:@"Authenticate" forState:UIControlStateNormal];
}

- (IBAction)authenticate:(id)sender
{
	[[self tf_yourID] resignFirstResponder];
	if (![sender isEqual:[self b_authenticate]]) return;
	if ([[[sender titleLabel]text]isEqualToString:@"Authenticate"])
	{
		[[self we_deleg]setDisplayName:[[self tf_yourID] text]];
		[[self we_deleg]authenticate:[[self tf_yourID]text] domain:@"weemo-poc.com"];
	} else {
		[[self we_deleg]disconnect];
		[[self tf_yourID]setText:@""];
		[[self tf_contactID]setText:@""];
		[[self l_displayname]setText:@"<not authenticated>"];
		[[self l_callStatus]setText:@"<none>"];
		
		[[self we_deleg]activate:APIKEY];
	}
}

- (IBAction)disconnect:(id)sender
{
	if ([sender isEqual:[self b_disconnect]]) return;
	[[Weemo instance]disconnect];
}

- (IBAction)call:(id)sender
{
	[we_deleg call:[[self tf_contactID] text]];
	[[self tf_contactID]resignFirstResponder];
}

- (IBAction)hangup:(id)sender
{
	[we_deleg hangup];
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

#pragma mark - ControllerDelegate

- (void)setS_lastError:(NSString *)newError;
{
	s_lastError = [NSString stringWithString:newError];
	dispatch_async(dispatch_get_main_queue(), ^{
		[[self tv_errorField]setText:[self s_lastError]];
	});
}

- (void)statusChange:(int)newStatus from:(id)sender
{
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

- (void)callStatusChange:(int)newStatus from:(id)sender
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

- (void)displayNameChange:(NSString *)newDN from:(id)sender
{
	dispatch_async(dispatch_get_main_queue(), ^{
		[[self l_displayname]setText: [we_deleg displayName]];
	});

}

@end
