//
//  SMChatViewController.h
//  jabberClient
//
//  Created by cesarerocchi on 7/16/11.
//  Copyright 2011 studiomagnolia.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SMBuddyListViewController.h"
#import "XMPP.h"
#import "TURNSocket.h"
#import "SMMessageViewTableCell.h"

@interface SMChatViewController : UIViewController <UITableViewDelegate, UITableViewDataSource, SMMessageDelegate> {

	NSString		*chatWithUser;
	NSMutableArray	*messages;
	NSMutableArray *turnSockets;
}

@property (nonatomic,strong) NSString *chatWithUser;
@property (nonatomic,weak) IBOutlet UITableView *tView;


@property (nonatomic,weak) IBOutlet UITextField *tf_messageout;
@property (nonatomic,weak) IBOutlet UIButton *b_send;
@property (nonatomic) UIBarButtonItem *ib_call;


- (id)initWithUser:(NSString *) userName;
- (IBAction)sendMessage;
- (IBAction)closeChat;
- (IBAction)call:(id)sender;

@end
