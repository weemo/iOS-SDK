//
//  AppDelegate.h
//  sdk-helper
//
//  Created by Charles Thierry on 7/16/13.
//


#import <UIKit/UIKit.h>


@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@end


/**

 This app presents the use of the SDK in a minimalistic environment. No function related to contact listing or availability is dealt here. This app assumes the user knows the UID of the contact he wants to call throught this app.
 
 two objects are used here:
 
 - the ViewController is the controller who deals with the main/root interface. It allows the user to authenticate on our network, using the provided URLReferer. It also allows to call a contact, disconnect, hangup a proceeding call and pick an incoming call.
 
 - The CallViewController deals with the call itself. It allows to stop and start the camera, the microphone, to switch the camera (back and front) and to change the audio route.
 
 
*/