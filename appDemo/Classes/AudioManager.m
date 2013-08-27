//
//  AudioManager.m
//  JabberClient
//
//  Created by alex zou on 13-4-6.
//
//

#import "AudioManager.h"
#import "SingletonSkelecton.h"

@implementation AudioManager

+(AudioManager *)sharedManager
{
  DEFINE_SHARED_INSTANCE_USING_BLOCK(^{
    return [[self alloc] init];
  });
}

-(id)init{

}

@end
