//
//  WeemoContact.h
//  WeemoSDK
//
//  Created by Charles Thierry on 6/16/14.
//  Copyright (c) 2014 Weemo. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Pre declaration to avoid include looping
 */
@class WeemoCall;

/**
 * This class describes a contact. displayname, contactID and relatedCall are decided by the system, the renderView is 
 * left to the application.
 *
 */
@interface WeemoContact : NSObject
+ (WeemoContact *)contactWithUID:(NSString *)uid
				  andDisplayName:(NSString *)name
					andContactID:(NSNumber *)contactID
					   andStatus:(uint8_t)status;

/**
 * The call in which this contact exists.
 */
@property (nonatomic, readonly) WeemoCall *relatedCall;

/**
 * The contact display name
 */
@property (nonatomic, readonly) NSString *displayName;

/**
 * The contact ID. This value is immutable during call.
 */
@property (nonatomic, readonly) NSString *UID;

/**
 * The contact number in the call. This value is immutable during a call.
 */
@property (nonatomic, readonly) NSNumber *contactID;

#pragma mark - Video in
/**
 * The view in which the call is rendered.
 */
@property (nonatomic, weak) UIView *renderView;

/**
 * The video profile
 */
@property (nonatomic) video_profile_t videoInProfile;

/**
 * The incoming video size for this contact. Replaces WeemoCall::getVideoProfile method.
 */
- (CGSize)getVideoInSize;


@end
