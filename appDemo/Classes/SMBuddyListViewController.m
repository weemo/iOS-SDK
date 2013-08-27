//
//  jabberClientViewController.m
//  jabberClient
//
//  Created by cesarerocchi on 7/13/11.
//  Copyright 2011 studiomagnolia.com. All rights reserved.
//

#import "SMBuddyListViewController.h"

#import "XMPP.h"
#import "XMPPRoster.h"

@implementation SMBuddyListViewController

@synthesize addBuddyView, buddyField;


- (JabberClientAppDelegate *)appDelegate {
	return (JabberClientAppDelegate *)[[UIApplication sharedApplication] delegate];
}

- (XMPPStream *)xmppStream {
	return [[self appDelegate] xmppStream];
}

- (XMPPRoster *)xmppRoster {
	return [[self appDelegate] xmppRoster];
}


- (void)viewDidLoad {
	
    [super viewDidLoad];
	JabberClientAppDelegate *del = [self appDelegate];
	del._chatDelegate = self;
	onlineBuddies = [[NSMutableArray alloc ] init];
	
}


- (void)viewDidAppear:(BOOL)animated {
	
	[super viewDidAppear:animated];
	NSString *login = [[NSUserDefaults standardUserDefaults] objectForKey:@"userID"];
	
	if (login) {
		
		[[self appDelegate] connect];
		
	} else {
		[self showLogin];
	}
}

- (IBAction) showLogin {
	
	//SMLoginViewController *loginController = [[SMLoginViewController alloc] init];
	//[self presentModalViewController:loginController animated:YES];
	[self performSegueWithIdentifier:@"seg_login" sender:nil];
}

#pragma mark -
#pragma mark Table view delegates

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	
	NSString *s = (NSString *) [onlineBuddies objectAtIndex:indexPath.row];
	
	static NSString *CellIdentifier = @"UserCellIdentifier";
	UserCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
	if (cell == nil)
	{
		cell = [[UserCell alloc] initWithStyle:UITableViewCellStyleDefault
								  reuseIdentifier:CellIdentifier];
	}
	
	[[cell l_name]setText:s];
	
	return cell;
	
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	
	return [onlineBuddies count];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;	
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{	
	NSString *userName = (NSString *) [onlineBuddies objectAtIndex:indexPath.row];
	[self performSegueWithIdentifier:@"seg_chat" sender:userName];
//	SMChatViewController *chatController = [[SMChatViewController alloc] initWithUser:userName];
//	[self presentModalViewController:chatController animated:YES];	
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
	if ([[segue identifier]isEqualToString:@"seg_chat"])
		[(SMChatViewController *)[segue destinationViewController] setChatWithUser:sender];
}

#pragma mark -
#pragma mark Chat delegate


- (void)xmppDidConnect:(NSString *)username
{
//	dispatch_async(dispatch_get_main_queue(), ^{
//		[[self navigationItem]setTitle:username];
//	});
}

- (void)newBuddyOnline:(NSString *)buddyName {
	
	if (![onlineBuddies containsObject:buddyName]) {
	
		[onlineBuddies addObject:buddyName];
		[[self tableView] reloadData];
		
	}
	
}

- (void)buddyWentOffline:(NSString *)buddyName {
	
	[onlineBuddies removeObject:buddyName];
	[[self tableView] reloadData];
	
}

- (void)didDisconnect
{
	dispatch_async(dispatch_get_main_queue(), ^{
		[[self navigationItem]setTitle:@""];
	});

	[onlineBuddies removeAllObjects];
	[[self tableView] reloadData];
}

- (IBAction) addBuddy {
	
	//	XMPPJID *newBuddy = [XMPPJID jidWithString:self.buddyField.text];
	//	[self.xmppRoster addBuddy:newBuddy withNickname:@"ciao"];
	
}


- (void)newMessageReceived:(NSMutableDictionary *)messageContent
{
	dispatch_async(dispatch_get_main_queue(), ^{
		//check if showing
		if ([[self view]window])
		{
			UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:[NSString stringWithFormat:@"New Message from :%@", [messageContent objectForKey:@"sender"]]
															message:[NSString stringWithFormat:@"%@", [messageContent objectForKey:@"msg"]]
														   delegate:nil
												  cancelButtonTitle:@"Ok"
												  otherButtonTitles:nil];
			[alertView show];
		}
	});
}

@end
