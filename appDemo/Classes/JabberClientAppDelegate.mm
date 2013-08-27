#import "SMBuddyListViewController.h"


@interface JabberClientAppDelegate()

- (void)setupStream;

- (void)goOnline;
- (void)goOffline;

@end


@implementation JabberClientAppDelegate

@synthesize xmppStream;
@synthesize xmppRoster;
@synthesize window;
@synthesize viewController;
@synthesize _chatDelegate;
@synthesize _messageDelegate;



- (void)applicationWillEnterForeground:(UIApplication *)application
{
	[[Weemo instance] foreground];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
//	[(UINavigationController*)[[self window]rootViewController]popToRootViewControllerAnimated:YES];
	[[Weemo instance] background];
}

- (void)applicationWillResignActive:(UIApplication *)application
{

}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
	if (![xmppStream isConnected])
		[self connect];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	setenv("XcodeColors", "YES", 0);
	self.viewController = (SMBuddyListViewController*)[(UINavigationController *)[self.window rootViewController] visibleViewController];

    return YES;
}


- (void)setupStream
{
	if (!xmppStream)
	{
		xmppStream = [[XMPPStream alloc] init];
		[xmppStream addDelegate:self delegateQueue:dispatch_get_main_queue()];
	}
}

- (void)goOnline {
	XMPPPresence *presence = [XMPPPresence presence];
	[[self xmppStream] sendElement:presence];
}

- (void)goOffline {
	XMPPPresence *presence = [XMPPPresence presenceWithType:@"unavailable"];
	[[self xmppStream] sendElement:presence];
}

- (BOOL)connect {
	
	[self setupStream];
	
	NSString *jabberID = [[NSUserDefaults standardUserDefaults] stringForKey:@"userID"];
	NSString *myPassword = [[NSUserDefaults standardUserDefaults] stringForKey:@"userPassword"];
	
	if (![xmppStream isDisconnected]) {
		return YES;
	}
	
	
	if (jabberID == nil || myPassword == nil) {
		
		return NO;
	}
	
	[xmppStream setMyJID:[XMPPJID jidWithString:jabberID]];
	password = myPassword;
	
	NSError *error = nil;
	if (![xmppStream connectWithTimeout:XMPPStreamTimeoutNone error:&error])
	{
		UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Error" 
															message:[NSString stringWithFormat:@"Can't connect to server %@", [error localizedDescription]]  
														   delegate:nil 
												  cancelButtonTitle:@"Ok" 
												  otherButtonTitles:nil];
		[alertView show];
		
		
		return NO;
	}
	
	[_chatDelegate xmppDidConnect:jabberID];
	if( ![Weemo instance] )
	{
		NSError *err = nil;
		[Weemo WeemoWithAPIKey:APIKEY andDelegate:self error: &err];
		if (err)
		{
			NSLog(@">>>> connecting error: %@", [err debugDescription]);
		}
	}
	
	return YES;
}

- (void)disconnect {
	
	[self goOffline];
	[xmppStream disconnect];
	[_chatDelegate didDisconnect];
}



#pragma mark -
#pragma mark XMPP delegates 


- (void)xmppStreamDidConnect:(XMPPStream *)sender {
	
	isOpen = YES;
	NSError *error = nil;
	[[self xmppStream] authenticateWithPassword:password error:&error];
	
}

- (void)xmppStreamDidAuthenticate:(XMPPStream *)sender {
	
	[self goOnline];
	
}


- (BOOL)xmppStream:(XMPPStream *)sender didReceiveIQ:(XMPPIQ *)iq {
	
	return NO;
	
}

- (void)xmppStream:(XMPPStream *)sender didReceiveMessage:(XMPPMessage *)message
{
	NSString *msg = [[message elementForName:@"body"] stringValue];
	NSString *from = [[message attributeForName:@"from"] stringValue];
	if (!msg )
	{//ignore
		return;
	}
	NSMutableDictionary *m = [[NSMutableDictionary alloc] init];
	[m setObject:msg forKey:@"msg"];
	[m setObject:from forKey:@"sender"];
	[viewController newMessageReceived:m];
	[_messageDelegate newMessageReceived:m];
}

- (void)xmppStream:(XMPPStream *)sender didReceivePresence:(XMPPPresence *)presence {
	
	NSString *presenceType = [presence type]; // online/offline
	NSString *myUsername = [[sender myJID] user];
	NSString *presenceFromUser = [[presence from] user];
	
	if (![presenceFromUser isEqualToString:myUsername])
	{
		if ([presenceType isEqualToString:@"available"])
		{
			[_chatDelegate newBuddyOnline:[NSString stringWithFormat:@"%@@%@", presenceFromUser, [[presence from] domain]]];
		} else if ([presenceType isEqualToString:@"unavailable"]) {
			[_chatDelegate buddyWentOffline:[NSString stringWithFormat:@"%@@%@", presenceFromUser, [[presence from] domain]]];
		}
	}
}


- (void)dealloc
{
	[xmppStream removeDelegate:self];
	[xmppRoster removeDelegate:self];
	[xmppStream disconnect];
}

#pragma mark - weemo call view management
- (void)createCallView
{
	NSLog(@">>>> createCallView");
	if (_cvc_active) return; //call view already instanciated
	NSString *storyboardname = ([[UIDevice currentDevice]userInterfaceIdiom] == UIUserInterfaceIdiomPhone)?@"iphone":@"ipad";
	_cvc_active = [[UIStoryboard storyboardWithName:storyboardname bundle:[NSBundle mainBundle]] instantiateViewControllerWithIdentifier:@"CallViewController"];
	
	[[[Weemo instance]activeCall]setDelegate:_cvc_active];
	[[(UINavigationController*)[window rootViewController] visibleViewController] addChildViewController:_cvc_active];
}

- (void)addCallView
{
	NSLog(@">>>> addCallView ");
	if (!_cvc_active) [self createCallView];
	
	if ([[[_cvc_active view] superview] isEqual:viewController] )
	{
		return; //view was already added
	}
	
	[[_cvc_active view]setFrame:CGRectMake(0., 0., [window frame].size.width, [window frame].size.height)];

	[[[(UINavigationController*)[window rootViewController] visibleViewController]view]addSubview:[_cvc_active view]];
//	[[[[window rootViewController]visibleViewController]view] addSubview:[_cvc_active view]];
	[(UINavigationController*)[window rootViewController] setNavigationBarHidden:YES animated:YES];
}

- (void)removeCallView
{
	[(UINavigationController*)[window rootViewController] setNavigationBarHidden:NO animated:YES];
	[_cvc_active removeFromParentViewController];
	[[_cvc_active view] removeFromSuperview];
	_cvc_active = nil;
}

#pragma mark - Weemo delegate
- (void)weemoCallEnded:(WeemoCall *)call
{
	dispatch_async(dispatch_get_main_queue(), ^{
		[self removeCallView];		
	});

}

- (void)weemoCallCreated:(WeemoCall*)call
{
	NSLog(@"weemo call created: %@ - status: 0x%X", [call contactID], [call callStatus]);
	switch ([call callStatus]) {
		case CALLSTATUS_INCOMING:
		{
			dispatch_async(dispatch_get_main_queue(), ^{
				UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Call Created"
																	message:[NSString stringWithFormat:@"Incoming call from contact %@", [call contactID]]
																   delegate:self
														  cancelButtonTitle:@"Pick-up"
														  otherButtonTitles:@"Dismiss", nil];
				[alertView show];
			});

		}break;
		case CALLSTATUS_ACTIVE:
		{
			dispatch_async(dispatch_get_main_queue(), ^{
				[self createCallView];
				[self addCallView];
			});
		}break;
		case CALLSTATUS_PROCEEDING:
		{
			dispatch_async(dispatch_get_main_queue(), ^{
				[self createCallView];
			});
		}
		case CALLSTATUS_ENDED:
		{
			[self removeCallView];
		
		}break;
		default:
			break;
	}
}

- (void)weemoDidAuthenticate:(NSError*)error
{
	if (error)
		NSLog(@">>> weemoDidAuthenticate error: %@", [error debugDescription]);
	 else
		 [[Weemo instance] setDisplayName: [[[self xmppStream]myJID]user]];
}

- (void)weemoDidConnect:(NSError*)error
{
	if (error)
	{
		NSLog(@">>>> WeemoDidConnect error %@", [error debugDescription]);
	} else {
		if (![[Weemo instance] isAuthenticated])
		{
			[[Weemo instance] authenticateWithUserID:[[NSUserDefaults standardUserDefaults] stringForKey:@"userID"] toDomain:@"weemo-poc.com"];
			NSLog(@"weemo authenticating %@", [[NSUserDefaults standardUserDefaults] stringForKey:@"userID"]);
		}
	}
}

- (void)weemoDidDisconnect:(NSError*)error
{
	NSLog(@"weemo disconnected %@", [error debugDescription]);
}

- (void)weemoContactCanBeCalled:(BOOL)canBeCalled
{
	NSLog(@">>>> weemo contactCanBeCalled %@", canBeCalled?@"YES":@"NO");
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
	if (buttonIndex ==0)
	{
		[self createCallView];
		[self addCallView];
		[[[[self window] rootViewController] view]endEditing:YES];
		[[[Weemo instance] activeCall]resume];
	} else {
		[[[Weemo instance] activeCall]hangup];
		[self removeCallView];
	}
}

@end
