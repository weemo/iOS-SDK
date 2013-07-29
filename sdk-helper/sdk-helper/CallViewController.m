//
//  CallViewController.m
//  sdk-helper
//
//  Created by Charles Thierry on 7/19/13.
//  Copyright (c) 2013 Weemo SAS. All rights reserved.
//

#import "CallViewController.h"
#import "ViewController.h"

@interface CallViewController ()

@end

@implementation CallViewController
@synthesize b_hangup;
@synthesize b_profile;
@synthesize b_toggleVideo;
@synthesize b_toggleAudio;
@synthesize call;
@synthesize v_videoIn;
@synthesize v_videoOut;

#pragma mark - Controller life cycle
- (id)initWithCoder:(NSCoder *)aDecoder
{
	self = [super initWithCoder:aDecoder];
	if (self)
	{
		[self setCall:[[Weemo instance] activeCall]];
	}
	return self;
}

- (void)viewDidLoad
{
	[super viewDidLoad];
	[[self call]setViewVideoIn:[self v_videoIn]];
	[[self call]setViewVideoOut:[self v_videoOut]];
}

- (void)viewDidAppear:(BOOL)animated
{
	[super viewWillAppear:animated];
	[self resizeView:[self interfaceOrientation]];

}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)tO duration:(NSTimeInterval)duration
{
	NSLog(@"CallVC: willAnimateRotationToInterfaceOrientation:");
	[self resizeView:tO];
}

- (void)resizeView:(UIInterfaceOrientation)tO
{
	[[self view]setFrame:CGRectMake(0., 0., [[[self view]superview]bounds].size.width, [[[self view]superview]bounds].size.height)];
	if (UIInterfaceOrientationIsPortrait(tO))
	{
		[[self v_videoIn] setCenter:CGPointMake([[self view]frame].size.width/2., [[self v_videoIn]frame].size.height/2.+ b_hangup.frame.size.height + 2.)];
		[[self v_videoOut]setCenter:CGPointMake([[self view]frame].size.width/2.,
												[[self view]frame].size.height - [[self v_videoOut]frame].size.height/2.)];
	} else if (UIInterfaceOrientationIsLandscape(tO))
	{
		[[self v_videoIn] setCenter:CGPointMake([[self v_videoIn]frame].size.width/2.+2., [[self view] frame].size.height/2.+ b_hangup.frame.size.height)];
		[[self v_videoOut]setCenter:CGPointMake([[self view]frame].size.width - [[self v_videoOut]frame].size.width / 2.,
												[[self view]frame].size.height/2.)];
	}
}

#pragma mark - Actions

- (IBAction)hangup:(id)sender
{
	[[[Weemo instance]activeCall]hangup];
}
- (IBAction)profile:(id)sender
{
	[[self call] toggleVideoProfile];
}
- (IBAction)toggleVideo:(id)sender
{
	if ([sender isSelected])
	{
		[[self call] videoStart];
	} else {
		[[self call] videoStop];
	}
}
- (IBAction)toggleAudio:(id)sender
{
	if ([sender isSelected])
	{
		[[self call] audioStart];
	} else {
		[[self call] audioStop];
	}
}


#pragma mark - Call delegate

- (void)videoReceiving:(BOOL)is from:(id)sender
{
	NSLog(@">>>> CallViewController: Receiving: %@", is ? @"YES":@"NO");
	dispatch_async(dispatch_get_main_queue(), ^{
		[[self v_videoIn]setHidden:!is];
	});
}

- (void)videoSending:(BOOL)is from:(id)sender
{
	NSLog(@">>>> CallViewController: Sending: %@", is ? @"YES":@"NO");
	dispatch_async(dispatch_get_main_queue(), ^{
		[[self b_toggleVideo]setSelected:!is];
		[[self v_videoOut]setHidden:!is];
	});
}

- (void)videoProfile:(int)profile from:(id)sender
{
	dispatch_async(dispatch_get_main_queue(), ^{
		[[self b_profile]setSelected:profile];
	});
}

- (void)videoSource:(int)source from:(id)sender
{
	
}

- (void)audioRoute:(int)route from:(id)sender
{
	
}

- (void)callStatus:(int)status from:(id)sender
{
	NSLog(@">>>> CallViewController: callStatus: 0x%X", status);
	dispatch_async(dispatch_get_main_queue(), ^{
		if (status == CALLSTATUS_ENDED)
		{
			[self removeFromParentViewController];
			[[self view]removeFromSuperview];
		}
	});
}


@end
