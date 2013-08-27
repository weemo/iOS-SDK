//
//  UserCell.h
//  JabberClient
//
//  Created by Charles Thierry on 8/9/13.
//
//

#import <UIKit/UIKit.h>

@interface UserCell : UITableViewCell
@property (nonatomic, weak) IBOutlet UIImageView *iv_avatar;
@property (nonatomic, weak) IBOutlet UILabel *l_name;

@end
