//
//  WeemoDelegate.m
//  sdk-helper
//
//  Created by Charles Thierry on 7/18/13.
//  Copyright (c) 2013 Weemo SAS. All rights reserved.
//

#import "Controller.h"

@implementation Controller
@synthesize displayName;
@synthesize status;
@synthesize currentCall;
@synthesize userName;

#pragma mark - 

- (void)setCurrentCall:(WeemoCall*)call
{
	currentCall = call;
}

#pragma mark - UI Action
- (void)activate:(NSString *)APIKey
{
	[Weemo WeemoWithAPIKey:APIKey andDelegate:self onInit:^(Weemo * w, NSError *err) {
		NSAssert(!err, [err debugDescription]);
	}];
}

- (void)authenticate:(NSString *)UID
			  domain:(NSString *)techdomain
{
	[[Weemo instance] connectWithUserID:UID
							   toDomain:techdomain];
}

- (void)disconnect
{
	[self hangup];
	[[Weemo instance] disconnect];
}

- (void)call:(NSString*)remoteUID
{
	[[Weemo instance]call:remoteUID];
}

- (void)hangup
{
	[[self currentCall]hangup];
}


- (void)setDisplayName:(NSString *)dn
{
	if (!userName) [self setUserName:[NSString stringWithString:dn]];
	displayName = [NSString stringWithString:dn];
	[[self delegate]displayNameChange:[self userName] from:self];
}

- (void)setStatus:(int)st
{
	status = st;
	[[self delegate]statusChange:st from:self];
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
- (void)callCreated:(WeemoCall*)call
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
	} else {
		//we are calling someone, might as well display the callview
	}
	[[self delegate]callStatusChange:[call callStatus] from:self];
}


- (void)didConnect:(NSError*)error
{
	[self setStatus:1];
	if (error)
	{
		[[self delegate] setS_lastError:[error debugDescription]];
	} else {
		[[self delegate] setS_lastError:@"<No Error>"];
	}
}

- (void)didAuthenticate:(NSError *)error
{
	if (!error) {
		if ([self status] == 2)
		{
			[self setDisplayName:[NSString stringWithFormat: @"%@ | SIP OK", [[Weemo instance] displayName]]];
		} else {
			[self setStatus:2];
			[[Weemo instance]setDisplayName:[self displayName]];
		}
		[[self delegate] setS_lastError:@"<No Error>"];
	} else {
		[self setDisplayName:[NSString stringWithFormat: @"%@ | SIP NOK", [[Weemo instance] displayName]]];
		[[self delegate] setS_lastError:[error debugDescription]];
	}
}

- (void)didDisconnect:(NSError*)error
{
	[self setStatus:0];
	[self setDisplayName:@"<not authentified>"];
	if (error){
		[[self delegate] setS_lastError:[error debugDescription]];
	} else {
		[[self delegate] setS_lastError:@"<No Error>"];
	}
}


@end
