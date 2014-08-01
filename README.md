# Weemo iOS SDK

This repository contains the Weemo iOS SDK. More information about Weemo SDKs can be found at [http://www.weemo.com/](http://www.weemo.com/)


The use cases have been minimized in order to reduce the integration effort while creating a functional model that covers most of the use cases for audio and video during 1:1 calls.
Basic implemented functions into this example are: 

- Initialization and Cloud authentification
- Send or Receive a call by UID  
- Stop or Start video
- Mute or Unmute audio
- iOS 6 Multi-tasking support

There are other pages to help your implementation:

- API Reference on [http://docs.weemo.com/release/5.1/sdk/ios/](http://docs.weemo.com/release/5.1/sdk/ios/)

## SDK Architecture

<p align="center">
<img src="http://docs.weemo.com/img/ios_00_arch.png" width="650px" />
</p>

## Supported Platforms

### Hardware
* iPhone 4S, 5 and more recent
* iPad Mini, 2, 3 and more recent

### Software
* iOS 6 or later

## Licences

The Weemo iOS SDK relies on open source software libraries for encoding/decoding voice and video. Binaries of those libraries and their licenses can be found in the Libraries folder.


## Note

- The SDK uses Objective-C Automatic Reference Counting and can't be used in the iPhone Simulator.
- The SDK was compiled using Xcode 4.6 or later.
- To use this SDK on an iPhone or iPad, you need a valid Apple iOS Developer account.
- The `sdk-helper` project compiles under Xcode 4.6 or later. It was not tested on any previous version of the IDE.

## Setup

The SDK public interface is available in Objective-C++ and requires the STL to compile. Some extra iOS frameworks are also needed in the Host App:

	AudioToolbox.framework
	CoreVideo.framework
	CoreMedia.framework
	CoreTelephony.framework
	CoreGraphics.framework
	QuartzCore.framework
	CFNetwork.framework
	AVFoundation.framework
	OpenGLES.framework
	GLKit.framework
	UIKit.framework
	Foundation.framework
	
The simplest way to add them to your project is to open the sample project `sdk-helper` with Xcode and copy all the Frameworks in the framework folder to your application Xcode project explorer. The `sdk-helper` can be download on [Github](https://github.com/weemo/iOS-SDK-Helper)

If adding Weemo software components to an existing app, it may be necessary to include the C++ runtime.  If C++ linkage errors are encountered, add the following library as a linked framework.

        libstdc++.dylib

Once connected to our cloud, the SDK has to stay connected for the application to receive calls. Your application's plist file should include a Key/Value to take that into account:

- Add the `Required Background Modes` key to your application's plist
- Add the `App plays audio` and `App provides Voice over IP services` values to this key

This will allow the application to receive calls and play the call sound while in background.

## Implementation

The first thing is to add the iOS-SDK framework to your application, the library dependencies along with the frameworks mentioned in the [Setup section](https://github.com/weemo/iOS-SDK_beta/wiki#wiki-setup) and modify the application plist.

* [Initialize Weemo](#initialization)
* [Create and Receive a call](#create-and-receive-a-call)
* [GUI Integration](#ui-integration)

##General application flow

1. The host application authenticates with its application server. In addition to your business use cases, the server backends gets a Token from the Weemo back office (5) and sends it to the client application.
2. The host application creates the Weemo singleton. Every action related to the Weemo Cloud goes through Weemo objects, and every callback is sent through those objects.
3. The SDK singleton connects to our cloud. 
4. Once connected, the application tries to authenticate the user.
6. Once connected, the application communicates with our cloud.

<img src="http://docs.weemo.com/img/ios_03_appflow.png">

## Initialization

#### Prerequisites

Make sure that your application has received a token from your backend server when starting the authentication process.
If you use one of our Authentication Client, the code returns you a json string containing the Token.
If you use our SDK helper that is on Github, it contains the code to retrieve a token calling directly an authentication Client stored on your backend.

#### Call Flow

This application uses a singleton to connect with Weemo cloud. This object is set on instantiation and <b>must</b> be called via the `[Weemo instance]` class method.

<img src="http://docs.weemo.com/img/ios_init_sdk.png">

#### Code


This singleton is instantiated using the Weemo-provided AppID and a delegate object. In the helper code supplied on Github, the Weemo Delegate is the weemoDelegate Class.

##### Weemo singleton creation

```obj-c
[Weemo WeemoWithAppID:@"appID"
		andDelegate:self 
		error:err];
```


After this instantiation, the WeemoDelegate is notified through the 

```obj-c
- (void)weemoDidConnect:(NSError *)error
```

method of the result of the connection.


##### User authentication
User authentication takes place using the 

```obj-c
[[Weemo instance] authenticateWithToken:@"myToken" andType:<ContactType>];
```

method of the singleton. The token is the Token returned by the Weemo Client to your backend server and that the backend server forwarded to your application.

The WeemoDelegate is notified of the result of this operation by the use of the delegate's method

```obj-c
- (void)weemoDidAuthenticate:(NSError *)e
```

After being authenticated, the HostApp <b>should</b> set a display name. This is a user friendly name, that will be presented to remote users when the user is calling said remote user.

```obj-c
[[Weemo instance] setDisplayName:@"myUserName"];
```

##### Background management

Don't forget to add the Key/Value related to the background activity as explained in the [Setup section](https://github.com/weemo/iOS-SDK_beta/wiki#wiki-setup), in order to allow for continued activity while in background.


## Create and Receive a call
#### Call Flow

**Create a call:**

<img src="http://docs.weemo.com/img/ios_send_call_cf.png">

**Receive a call:**

<img src="http://docs.weemo.com/img/ios_receive_call_cf.png">

#### Code

#### Outgoing call

To establish an outgoing call, the HostApp calls

```obj-c
[[Weemo instance] createCall:@"remoteContactID" andSetDisplayName:@"remoteContactDisplayName"];
```

The result of the Host App call, is returned as parameters of WeemoDelegate object method :

```obj-c
- (void)weemoContact:(NSString*)contactID CanBeCalled:(BOOL)canBeCalled
```

The WeemoDelegate is alerted of the incoming call through the use of

```obj-c
- (void)weemoCallCreated:(WeemoCall*)call
```

One the call is created, you can display the contact UID of the remote user, by using `[call contactDisplayName];` which contains the remote/caller contact UID.


#### Note: 
Prior to create a call, it’s also possible to check the remote user availability by using

```obj-c
[[Weemo instance] getStatus:@“remoteContactID"]; 
```


#### Incoming call

To allow the receiving user to get the display name of the remote user, use  `[call contactDisplayName];` which contains the remote/caller contact display name. 

As soon the receiver hangup the call, both the Video and Audio streams are started upon call pickup.

#### Note : 

The call created <b>should</b> be assigned a delegate as soon as possible, as this delegate will notify the HostApp of all relevant information regarding the call and potentially needed GUI updates. However, this delegation is entirely optional.


## UI Integration


You should implement a UIViewController to show the call while it is active. A typical implementation will provide at least one button for hanging up the call and will implement two child UIViews:

- one as argument of the WeemoCall `- (void)setViewVideoIn:(UIView*) view;`. The incoming video will be displayed in this space. Setting and displaying this view is optional; 
- another to display the video out feedback as argument of the WeemoCall `- (void)setViewVideoOut:(UIView*) view;` Setting and displaying this monitoring view is optional. 

The WeemoCall object presents a few more controls:

- `- (void)videoStart/Stop`: the outgoing video stream can be stopped and started at will;
- `- (void)audioStart/Stop`: the outgoing audio stream is filled with empty audio frame (the stream as to be kept active);
- `- (void)toggleVideoSource`: two cameras are available on every supported devices and you can switch between them;
- `- (void)toggleAudioSource`: if a headset is connected, this affects both iPad and iPhone as the sound can be played through the headset or the loudspeaker. Without headset, only the iPhone is affected by this function -- the incoming audio can be streamed through the regular phone audio output or on speakers.

A change to any of these controls will be observed in the WeemoCallDelegate where modifications to the GUI should be performed.

## Known Limitations

- Some features available in the JavaScript API are not currently available in the iOS version of the SDK. Such features include multi-party calls and screen sharing.
- The audio layer of the SDK causes an error to be logged on debug: `Error Domain=NSOSStatusErrorDomain Code=560557673 "The operation couldn’t be completed."`. This message should not affect functionality.
