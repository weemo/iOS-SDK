//
//  SMMessageViewTableCell.h
//  JabberClient
//
//  Created by cesarerocchi on 9/8/11.
//  Copyright 2011 studiomagnolia.com. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface SMMessageViewTableCell : UITableViewCell {

	UILabel	*senderAndTimeLabel;
	UITextView *messageContentView;
	UIImageView *bgImageView;
	
}

@property (nonatomic) UILabel *senderAndTimeLabel;
@property (nonatomic) UITextView *messageContentView;
@property (nonatomic) UIImageView *bgImageView;

@end
