//
//  WeemoDelegate.h
//  sdk-helper
//
//  Created by Charles Thierry on 7/18/13.
//  Copyright (c) 2013 Weemo SAS. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol ControllerDelegate <NSObject>
@property (nonatomic) NSString* s_lastError;

- (void)statusChange:(int)newStatus from:(id)sender;
- (void)callStatusChange:(int)newStatus from:(id)sender;
- (void)displayNameChange:(NSString *)newDN from:(id)sender;

@end

@interface Controller: NSObject <WeemoDelegate, UIAlertViewDelegate>

@property (nonatomic) id<ControllerDelegate> delegate;
@property (nonatomic) int status;

@property (nonatomic) NSString *displayName;
@property (nonatomic) NSString *userName;
@property (nonatomic) WeemoCall *currentCall;

#pragma mark -
/**
 * Connect to the Weemo platforms, provisionning an account automaticaly using the APIKey.
 */
- (void)activate:(NSString *)APIKey;

- (void)authenticate:(NSString *)UID domain:(NSString *)techdomain;
- (void)disconnect;

- (void)call:(NSString*)remoteUID;

- (void)hangup;


@end
