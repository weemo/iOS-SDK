# Content

This document comes in addition to the <a href='https://github.com/weemo/iOS-SDK/wiki'>SDK wiki</a> and <a href='http://docs.weemo.com/sdk/ios'>doxygen documentation</a> of the Weemo SDK for iOS project.

This sample project is provided with the usual disclaimer about how it comes `WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED`, as per the MIT License.

The goal of this sample project is to give developers a working example of how to start the Weemo singleton, connect and disconnect, authenticate on our network, and place an audio/video call, and to keep it simple.


# Global Architecture

This project is divided in two main classes:

* The `ViewController` is the controller for the rootView of the project. Its initialization and display starts the Weemo singleton and connects it to our network. It is a WeemoDelegate.
* The `CallViewController` is the view that appears when a call is placed/is started. It allows the user to change the video/audio source, to start/stop the outgoing audio[^1] and video, and of course hanging up the call. It is a WeemoCallDelegate.


## ViewController

The Weemo iOS-SDK initialization code is found in the `viewDidLoad:` method of the rootViewController:

	…
	NSError *err;
	[Weemo WeemoWithAPIKey:APIKEY andDelegate:self error:&err];
	…

Note that we don't keep a reference to the created Weemo singleton (which is available through the class method `+ (id)instance`), nor do we test the error this method can return (which is bad practice).

Authentication takes place in the action started by the `b_authenticate` UIButton, `authenticate:`.

	…
	if ([[Weemo instance]authenticateWithUserID:[[self tf_yourID]text]
								   toDomain:TECHDOMAIN])
	…

Contrary to what seems implied in this code, the connection is not done synchronously. The boolean returned by the authentication method depends on <a href=https://github.com/weemo/poc/wiki/Naming-rules>the correctness</a> of the UserID used.

If the Weemo singleton is connected, the `Authenticate` button is changed in a `Disconnect` button. The action called upon press is
	
	…
	[[Weemo instance] disconnect];
	…
This method disconnected the Weemo singleton from the network. The singleton is not destroyed. To reconnect, simply use the `WeemoWithAPIKey:andDelegate:error:`. The user have to re-authenticate afterwards.



### Delegate

All those methods are called by the Weemo singleton object and implemented in the sample application.

##### `weemoCallCreated:`

This method is called upon receiving a call (status is `CALLSTATUS_INCOMING`) or upon placing a call (another status `CALLSTATUS_PROCEEDING` or `CALLSTATUS_RINGING`). The call status tells which case applies.

##### `weemoDidConnect:`

On connection success or failure, the `weemoDidConnect:` method is called. In this code, the reaction is only about GUI changes.

##### `weemoDidAuthenticate:`

After authentication success or failure, this method is called. On success, the displayName is set. The error management is here reduced to its minimum: we display that there was a connection error.

##### `weemoDidDisconnect:`
After a disconnection attempt (or a remote disconnection), this method is called. In this sample code, we reinitialize the GUI and try to reconnect the SDK to the network if the disconnection was a user action.

##### `weemoContact:canBeCalled:`
This method is called after the user checks the availability of a contact. 

## CallViewController

Once a call has be created and returned to the application, or picked-up, this object's view is displayed on top of the root view controller.

The two UIViews used to display the video streams are set in the `viewWillAppear:` of this ViewController. 
	
	…
	[[self call]setViewVideoIn:[self v_videoIn]];
	[[self call]setViewVideoOut:[self v_videoOut]];
	…
	
Both data streams (audio and video) starts upon call start.
Each buttons of the View is linked to a WeemoCall action: pick-up/hang-up the call, switch Video source, start/stop video capture, start/stop audio capture.

### Delegate

##### `weemoCall:videoReceiving:`
This function is called when the remote client starts or stops its outgoing video stream, allowing you to adapt the GUI of the call view.

##### `weemoCall:videoSending:`
This function is the matching local function of the previous. The client starts or stops its outgoing video stream, allowing you to adapt the GUI of the call view.

##### `weemoCall:videoProfile:`
This function is called when the incoming video changes profile.

##### `weemoCall:videoSource:`
This function is called when the Video source changes.

##### `weemoCall:audioSending:`
This is called after a change in the audio capture. If YES, the client is sending what the microphone is capturing. If NO, the client sends empty audio frames.

##### `weemoCall:callStatus:`
This is called when the status of the call changed, allowing you to remove the callView from the application, using whatever means you want.


A function is not implemented in this example:

##### `weemoCall:audioRoute:`
Called when the audio route changes, upon headset connection.



[^1]: If you read the <a href='https://github.com/weemo/iOS-SDK/wiki'>wiki</a> carefully, you already know that the outgoing audio stream is never really stopped. `audioStop` allows the user to stop sending audio captured from the microphone, but the stream stays open, sending empty frames.