//
//  JabberClientAppDelegate.h
//  JabberClient
//
//  Created by cesarerocchi on 8/3/11.
//  Copyright 2011 studiomagnolia.com. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "XMPPRoster.h"
#import "XMPP.h"
#import "SMChatDelegate.h"
#import "SMMessageDelegate.h"

#import <iOS-SDK/WeemoData.h>
#import <iOS-SDK/Weemo.h>

#import "CallViewController.h"

@class SMBuddyListViewController;

@interface JabberClientAppDelegate : NSObject <UIApplicationDelegate, WeemoDelegate, UIAlertViewDelegate> {
    UIWindow *window;
    SMBuddyListViewController *viewController;
	
	XMPPStream *xmppStream;
	XMPPRoster *__weak xmppRoster;
	
	NSString *password;
	
	BOOL isOpen;
	
	 NSObject <SMChatDelegate> *__weak _chatDelegate;
	 NSObject <SMMessageDelegate> *__weak _messageDelegate;
}

@property (nonatomic) CallViewController *cvc_active;

@property (nonatomic, strong) IBOutlet UIWindow *window;
@property (nonatomic, strong) IBOutlet SMBuddyListViewController *viewController;


@property (nonatomic, readonly) XMPPStream *xmppStream;
@property (weak, nonatomic, readonly) XMPPRoster *xmppRoster;

@property (nonatomic, weak) id  _chatDelegate;
@property (nonatomic, weak) id  _messageDelegate;

- (BOOL)connect;
- (void)disconnect;
- (void)weemoContact:(NSString*)contactID canBeCalled:(BOOL)canBeCalled;

@end

