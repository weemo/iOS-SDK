# Weemo iOS SDK

This repository contains the Weemo iOS SDK. More information about Weemo SDKs can be found at [http://www.weemo.com/](http://www.weemo.com/)


The use cases have been minimized in order to reduce the integration effort while creating a functional model for the POC that covers most of the use cases for audio and video during 1:1 calls.
Basic implemented functions into this example are: 

- Initialization and Cloud authentification
- Send or Receive a call by UID  
- Stop or Start video
- Mute or Unmute audio
- iOS 6 Multi-tasking support

There are other pages to help your implementation:

- API Reference on [http://docs.weemo.com/release/5.1/sdk/ios/](http://docs.weemo.com/release/5.1/sdk/ios/)
- How to [Upgrade from 4.2 to 5.1](/docs/Upgrade-4.2-to-5.1.md)

## SDK Architecture

<p align="center">
<img src="http://docs.weemo.com/img/ios_00_arch.png" width="650px" />
</p>

## Supported Platforms

### Hardware
* iPhone 4S, 5 and more recent
* iPad Mini, 2, 3 and more recent

### Software
* iOS 5.1 or later

## Licences

The Weemo iOS SDK relies on open source software libraries for encoding/decoding voice and video. Binaries of those libraries and their licenses can be found in the Libraries folder.


## Note

- The SDK uses Objective-C Automatic Reference Counting and can't be used in the iPhone Simulator.
- The SDK was compiled using Xcode 4.6.
- To use this SDK on an iPhone or iPad, you need a valid Apple iOS Developer account.
- The `sdk-helper` project compiles under Xcode 4.6. It was not tested on any previous version of the IDE.

## Setup

The SDK public interface is available in Objective-C++ and requires the STL to compile. Some extra iOS frameworks are also needed in the Host App:

	AudioToolbox.framework
	CoreVideo.framework
	CoreMedia.framework
	QuartzCore.framework
	CFNetwork.framework
	AVFoundation.framework
	CoreGraphics.framework
	
The simplest way to add them to your project is to open the sample project `sdk-helper` with Xcode and copy the `Framework` folder to your application Xcode project explorer.

If adding Weemo software components to an existing app, it may be necessary to include the C++ runtime.  If C++ linkage errors are encountered, add the following library as a linked framework.

        libstdc++.dylib

Once connected to our cloud, the SDK has to stay connected for the application to receive calls. Your application's plist file should include a Key/Value to take that into account:

- Add the `Required Background Modes` key to your application's plist
- Add the `App plays audio` and `App provides Voice over IP services` values to this key

This will allow the application to receive calls and play the call sound while in background.

## Implementation

The first thing is to add the iOS-SDK framework to your application, the library dependencies along with the frameworks mentioned in the [Setup section](https://github.com/weemo/iOS-SDK_beta/wiki#wiki-setup) and modify the application plist.

* [Initialize Weemo](https://github.com/weemo/iOS-SDK_beta/wiki#wiki-initialization)
* [Create and Receive a call](https://github.com/weemo/iOS-SDK_beta/wiki#wiki-create-and-receive-a-call)
* [GUI Integration](https://github.com/weemo/iOS-SDK_beta/wiki#wiki-gui-integration)

##General application flow

1. The host application authenticates with its application server.
2. The host application creates the Weemo singleton. Every action related to the Weemo Cloud goes through Weemo objects, and every callback is sent through those objects.
3. The SDK singleton connects to our cloud. 
4. Once connected, the application tries to authenticate the user.
5. The verification of the authentication is not mandatory during the POC/trial phase.
6. Once connected, the application communicates with our cloud.

<img src="http://docs.weemo.com/img/ios_03_appflow.png">

## Initialization
#### Call Flow

This application uses a singleton to connect with Weemo cloud. This object is set on instantiation and <b>must</b> be called via the `[Weemo instance]` class method.

<img src="http://docs.weemo.com/img/ios_init_sdk.png">

#### Code


This singleton is instantiated using the Weemo-provided AppID and a delegate object. In the helper code supplied, the Weemo Delegate is the rootViewController.

##### Weemo singleton creation


	[Weemo WeemoWithAppID:@"appID"
			  andDelegate:self 
			        error:err];


After this instantiation, the WeemoDelegate is notified through the 


	- (void)weemoDidConnect:(NSError *)error


method of the result of the connection.


##### User authentication
User authentication takes place using the 


	[[Weemo instance]authenticateWithToken:@"myToken" andType:<ContactType>];


method of the singleton. The token <b>must</b> comply to the <a href=https://github.com/weemo/Weemo.js/wiki/WeemoDriver-Naming>Naming Rules</a>.

The WeemoDelegate is notified of the result of this operation by the use of the delegate's method


	- (void)weemoDidAuthenticate:(NSError *)e

After being authenticated, the HostApp <b>should</b> set a display name. This is a user friendly name, that will be presented to remote users when the user is calling said remote user.


	[[Weemo instance] setDisplayName:@"myUserName"];


##### Background management

Don't forget to add the Key/Value related to the background activity as explained in the [Setup section](https://github.com/weemo/iOS-SDK_beta/wiki#wiki-setup), in order to allow for continued activity while in background.


## Create and Receive a call
#### Call Flow

**Create a call:**

<img src="http://docs.weemo.com/img/ios_send_call_cf.png">

**Receive a call:**

<img src="http://docs.weemo.com/img/ios_receive_call_cf.png">

#### Code

Before creating an outgoing call, the remote user availability can be checked by using


	[[Weemo instance] getStatus:@"remoteContactID"];


which result is returned as parameters for the 


	- (void)weemoContact:(NSString*)contactID CanBeCalled:(BOOL)canBeCalled


method of the WeemoDelegate object.


The WeemoDelegate is alerted of the incoming call through the use of


	- (void)weemoCallCreated:(WeemoCall*)call

The `[call contactDisplayName];` allows the receiving user to get the display name of the remote user.  Note: It is not currently possible for a receiving user to get the contactID of the remote user (i.e., using `[call contactID];` returns the display name of the remote user).

For an outgoing call, the HostApp calls


	[[Weemo instance] createCall:@"remoteContactID"];


or 


	[[Weemo instance]createCall:@"remoteContactID" andSetDisplayName:@"remoteContactDisplayName"];



The created call is returned to the WeemoDelegate through the same method as the incoming  call (`- (void)weemoCallCreated:(WeemoCall*)call`).  The WeemoCall `callStatus` property indicates whether it is an outgoing or an incoming call.

The call created <b>should</b> be assigned a delegate as soon as possible, as this delegate will notify the HostApp of all relevant information regarding the call and potentially needed GUI updates.  However, this delegation is entirely optional.

The controls of the WeemoCall are self explanatory, except maybe the call pick-up function which is provided by the `- (void)resume` signal. Each change of the properties of a WeemoCall is answered by a call to the WeemoCallDelegate.

Both the Video and Audio streams are started upon call pickup.

## GUI Integration

The ViewController whose view displays the call controls is here called the `callVC`.

This `callVC` is entirely customizable as it is your responsibility to create it. You choose which controls and which views are available to the user.

The typical `callVC` implementation should provide at least  a button for hanging up the call by calling the `- (void)hangup` method and two UIViews:

- one as argument of the WeemoCall `- (void)setViewVideoIn:(UIView*) view;`. The incoming video will be displayed in this space; 
- another to display the video out feedback as argument of the WeemoCall `- (void)setViewVideoOut:(UIView*) view;`. The view is integrated directly as a Quartz `CALayer` in the UIView provided. Displaying this monitoring view is optional.

The WeemoCall object presents a few more controls:

- `- (void)videoStart/Stop`: the outgoing video stream can be stopped and started at will.
- `- (void)audioStart/Stop`: the outgoing audio stream is filled with empty audio frame (the stream as to be kept active).
- `- (void)toggleVideoSource`: two cameras are available on every supported device type and you can switch between them.
- `- (void)toggleAudioSource`: if a headset is connected, this affects both iPad and iPhone as the sound can be played through the headset or the loudspeaker. Without headset, only the iPhone is affected by this function -- the incoming audio can be streamed through the regular phone audio output or on speakers.

Each of this changes calls a function in the WeemoCallDelegate, if such functions are implemented in the delegate.

## Known Limitations

- Some features available in the JavaScript API are not currently available in the iOS version of the SDK. Such features include multi-party calls and screen sharing.
- The audio layer of the SDK causes an error to be logged on debug: `Error Domain=NSOSStatusErrorDomain Code=560557673 "The operation couldn’t be completed."`. This message should not affect functionality.
