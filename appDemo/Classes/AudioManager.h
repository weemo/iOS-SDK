//
//  AudioManager.h
//  JabberClient
//
//  Created by alex zou on 13-4-6.
//
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@interface AudioManager : NSObject
{
  AVAudioPlayer *player;
  AVAudioRecorder *recorder;
}
@end
