//
//  WeemoDelegate.m
//  sdk-helper
//
//  Created by Charles Thierry on 7/18/13.
//  Copyright (c) 2013 Weemo SAS. All rights reserved.
//

#import "Controller.h"

@implementation Controller

@synthesize activated;

#pragma mark - Delegate
- (void) incomingCall:(WeemoCall*)call
{
	
}

- (void) weemoDidConnect:(NSError*)error
{
	[self setActivated:YES];
}

- (void) weemoDidDisconnect:(NSError*)error
{
	[self setActivated:NO];
}

#pragma mark -
- (void)activate:(NSString *)APIKey
{
	[Weemo WeemoWithAPIKey:APIKey onInit:^(Weemo * w, NSError *err) {
		NSAssert(!err, @"Could not initiate the WeemoDriver");
	}];
}

- (void)authenticate:(NSString *)UID
			  domain:(NSString *)techdomain
{
		[[Weemo instance] connectWithUserID:UID
								   toDomain:techdomain
								   delegate:self];
}

@end
