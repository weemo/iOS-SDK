//
//  SMChatViewController.m
//  jabberClient
//
//  Created by cesarerocchi on 7/16/11.
//  Copyright 2011 studiomagnolia.com. All rights reserved.
//

#import "SMChatViewController.h"
#import "NSString+Utils.h"
#import "NSString+DDXML.h"
#import "XMPP.h"

#import "DAKeyboardControl.h"

@implementation SMChatViewController

@synthesize chatWithUser, tView;
@synthesize ib_call;
@synthesize tf_messageout, b_send;

- (JabberClientAppDelegate *)appDelegate {
	return (JabberClientAppDelegate *)[[UIApplication sharedApplication] delegate];
}

- (XMPPStream *)xmppStream {
	return [[self appDelegate] xmppStream];
}

- (id) initWithUser:(NSString *) userName {

	if (self = [super init]) {
		
		chatWithUser = userName; // @ missing
		turnSockets = [[NSMutableArray alloc] init];
	}
	
	return self;

}

- (void)setChatWithUser:(NSString *)username
{
	chatWithUser = username;
	[[self navigationItem]setTitle:username];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
	[[self navigationController]popToRootViewControllerAnimated:YES];
}

- (void)viewDidLoad
{
	[super viewDidLoad];
	[self setupCallButton];
	self.tView.delegate = self;
	self.tView.dataSource = self;
	[self.tView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
	messages = [[NSMutableArray alloc ] init];
	
	JabberClientAppDelegate *del = [self appDelegate];
	del._messageDelegate = self;
//	[[self tf_messageout] becomeFirstResponder];

	XMPPJID *jid = [XMPPJID jidWithString:@"cesare@YOURSERVER"];
	
	NSLog(@"Attempting TURN connection to %@", jid);
	
	TURNSocket *turnSocket = [[TURNSocket alloc] initWithStream:[self xmppStream] toJID:jid];
	
	[turnSockets addObject:turnSocket];
	
	[turnSocket startWithDelegate:self delegateQueue:dispatch_get_main_queue()];

	[[self tView] setFrame:CGRectMake(0., 0., self.view.frame.size.width, self.view.frame.size.height)];
    tView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleRightMargin;

	[[self b_send] setTitle:@"Send" forState:UIControlStateNormal];
	
	self.view.keyboardTriggerOffset = tf_messageout.bounds.size.height/2.;
	
	[[self view] addKeyboardPanningWithActionHandler:^(CGRect keyboardFrame){
		CGRect frame = [[self view]bounds];
//		[tView setFrame:CGRectMake(0., 0.,
//									frame.size.width,
//									frame.size.height - keyboardFrame.size.height - tf_messageout.bounds.size.height - 2.)];
		[tf_messageout setFrame:CGRectMake(tf_messageout.frame.origin.x, keyboardFrame.origin.y - tf_messageout.bounds.size.height -1., tf_messageout.bounds.size.width, tf_messageout.bounds.size.height)];
		[b_send setFrame:CGRectMake(b_send.frame.origin.x, keyboardFrame.origin.y - b_send.bounds.size.height -1., b_send.bounds.size.width, b_send.bounds.size.height)];
	}];

	[[self view] bringSubviewToFront:tf_messageout];
	[[self view] bringSubviewToFront:b_send];

	[self checkContact];
}

- (void)checkContact
{
	[[Weemo instance] getStatus:[self chatWithUser]];
}

- (void)setupCallButton
{
	UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
	UIImage *buttonImage = [UIImage imageNamed:@"chat_phone"];
	[button setBackgroundImage:buttonImage forState:UIControlStateNormal];
	CGRect frame = [button frame];

	frame.size.width = fminf(buttonImage.size.width, 40);
	frame.size.height = fminf(buttonImage.size.height, 40);
	[button setFrame:frame];
	[button addTarget:self action:@selector(call:) forControlEvents:UIControlEventTouchUpInside];
    
	ib_call = [[UIBarButtonItem alloc] initWithCustomView:button];
	[[self navigationItem] setRightBarButtonItem:ib_call animated:YES];
}

- (void)turnSocket:(TURNSocket *)sender didSucceed:(GCDAsyncSocket *)socket
{
	NSLog(@"TURN Connection succeeded!");
	NSLog(@"You now have a socket that you can use to send/receive data to/from the other person.");
	
	[turnSockets removeObject:sender];
}

- (void)turnSocketDidFail:(TURNSocket *)sender
{
	NSLog(@"TURN Connection failed!");
	[turnSockets removeObject:sender];
}



#pragma mark -
#pragma mark Actions

- (IBAction)call:(id)sender
{	
	[[Weemo instance] createCall:chatWithUser];
	[[self tf_messageout] resignFirstResponder];
	NSLog(@"calling contact: %@", chatWithUser);
}
- (IBAction) closeChat
{
	[self dismissModalViewControllerAnimated:YES];
}

- (IBAction)sendMessage {
	
    NSString *messageStr = self.tf_messageout.text;
    if([messageStr length] > 0) {
		
        NSXMLElement *body = [NSXMLElement elementWithName:@"body"];
        [body setStringValue:messageStr];
		
        NSXMLElement *message = [NSXMLElement elementWithName:@"message"];
        [message addAttributeWithName:@"type" stringValue:@"chat"];
        [message addAttributeWithName:@"to" stringValue:chatWithUser];
        [message addChild:body];
		
        [self.xmppStream sendElement:message];
		self.tf_messageout.text = @"";
		

		NSMutableDictionary *m = [[NSMutableDictionary alloc] init];
		[m setObject:[messageStr substituteEmoticons] forKey:@"msg"];
		[m setObject:@"you" forKey:@"sender"];
		[m setObject:[NSString getCurrentTime] forKey:@"time"];
		
		[messages addObject:m];
		[self.tView reloadData];
		
    }
	if ([messages count] > 1)
	{
	
		NSIndexPath *topIndexPath = [NSIndexPath indexPathForRow:[messages count]-1
												   inSection:0];
		[self.tView scrollToRowAtIndexPath:topIndexPath
					  atScrollPosition:UITableViewScrollPositionMiddle 
							  animated:YES];
	}
}


#pragma mark -
#pragma mark Table view delegates

static CGFloat padding = 22.0;


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	
	
	NSDictionary *s = (NSDictionary *) [messages objectAtIndex:indexPath.row];
	
	static NSString *CellIdentifier = @"MessageCellIdentifier";
	
	SMMessageViewTableCell *cell = (SMMessageViewTableCell *)[tableView dequeueReusableCellWithIdentifier:CellIdentifier];
	
	if (cell == nil) {
		cell = [[SMMessageViewTableCell alloc] initWithFrame:CGRectZero reuseIdentifier:CellIdentifier];
	}

	NSString *sender = [s objectForKey:@"sender"];
	NSString *message = [s objectForKey:@"msg"];
	NSString *time = [s objectForKey:@"time"];
	CGSize  textSize = { self.view.frame.size.width*3/4, 10000.0 };
	CGSize size = [message sizeWithFont:[UIFont boldSystemFontOfSize:14]
					  constrainedToSize:textSize
						  lineBreakMode:NSLineBreakByWordWrapping];

	
	size.width += (padding/2);
	
	
	cell.messageContentView.text = message;
	cell.accessoryType = UITableViewCellAccessoryNone;
	cell.userInteractionEnabled = NO;
	

	UIImage *bgImage = nil;
	
		
	if ([sender isEqualToString:@"you"]) { // left aligned
	
		bgImage = [[UIImage imageNamed:@"chat_orange.png"] stretchableImageWithLeftCapWidth:24  topCapHeight:15];
		
		[cell.messageContentView setFrame:CGRectMake(padding, padding*2, size.width, size.height)];
		
		[cell.bgImageView setFrame:CGRectMake( cell.messageContentView.frame.origin.x - padding/2, 
											  cell.messageContentView.frame.origin.y - padding/2, 
											  size.width+padding,
											  size.height+padding)];
				
	} else {
	
		bgImage = [[UIImage imageNamed:@"chat_aqua.png"] stretchableImageWithLeftCapWidth:24  topCapHeight:15];
		
		[cell.messageContentView setFrame:CGRectMake(self.view.frame.size.width - size.width - padding,
													 padding*2, 
													 size.width, 
													 size.height)];
		
		[cell.bgImageView setFrame:CGRectMake(cell.messageContentView.frame.origin.x - padding/2, 
											  cell.messageContentView.frame.origin.y - padding/2, 
											  size.width+padding, 
											  size.height+padding)];
		
	}
	
	cell.bgImageView.image = bgImage;
	cell.senderAndTimeLabel.text = [NSString stringWithFormat:@"%@ %@", sender, time];
	
	return cell;
	
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	
	NSDictionary *dict = (NSDictionary *)[messages objectAtIndex:indexPath.row];
	NSString *msg = [dict objectForKey:@"msg"];
	
	CGSize  textSize = { 260.0, 10000.0 };
	CGSize size = [msg sizeWithFont:[UIFont boldSystemFontOfSize:13]
				  constrainedToSize:textSize 
					  lineBreakMode:NSLineBreakByWordWrapping];
	
	size.height += padding*2;
	
	CGFloat height = size.height < 65 ? 65 : size.height;
	return height;
	
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	
	return [messages count];
	
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	
	return 1;
	
}

#pragma mark -
#pragma mark Chat delegates


- (void)newMessageReceived:(NSMutableDictionary *)messageContent {
	
	NSString *m = [messageContent objectForKey:@"msg"];
	
	[messageContent setObject:[m substituteEmoticons] forKey:@"msg"];
	[messageContent setObject:[NSString getCurrentTime] forKey:@"time"];
	[messages addObject:messageContent];
	[self.tView reloadData];

	NSIndexPath *topIndexPath = [NSIndexPath indexPathForRow:messages.count-1 
												   inSection:0];
	
	[self.tView scrollToRowAtIndexPath:topIndexPath 
					  atScrollPosition:UITableViewScrollPositionMiddle 
							  animated:YES];
}


- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
	[[self view] removeKeyboardControl];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}



@end
