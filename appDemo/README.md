#JabberClient

##Presentation
This is a basic integration of the SDK and helper code in an already existing application, namely a XMPP test client offering a basic chat functionality. While this application does provide basic chat functionality and contact availability using XMPP, it lacks everything else.


##Delegates
The `WeemoDelegate` is the same object as the application delegate.
The `WeemoCallDelegate` is the same CallViewController found in the `sdk-helper` application.


##Instantiating
The `Weemo` object is instantiated along the `XMPPStream` connection in the JabberClientAppDelegate `connect` method.

Once connected, authentication occurs when the `weemoDidConnect:` method of the delegate is called. 

The `DisplayName` is set when the authentication is validated, in the `weemoDidAuthenticate:` method of the `WeemoDelegate`.


##Background management
When the application goes to background, the AppDelegate `applicationDidEnterBackground:` method is called. We call the Weemo object `background` method at this time. While in a call, this suspends the video out stream and signals the remote client that the video stream stopped. It also set the Weemo object in background mode, dealing with the iOS 5&6 background mode.

On going to foreground, the AppDelegate `applicationWillEnterForeground:` is called. The Weemo object `foreground` method is called, setting the Weemo object to foreground mode, and restarting the video if the call is still ongoing.

If an ongoing call is terminated while the client is in background, the call is marked as terminated on going to foreground, leading to the `CallView` being removed.


##Calling and being called
Calling takes place in the SMChatViewController, when the method `call:` is called. 

This method creates a call to the contact whose chat window is displayed, by using the `createCall:` method of the `WeemoDelegate`.

Once created, this call is returned to the `WeemoDelegate` by the `weemoCallCreated:` callback method.

Receiving a call uses the same method: the incoming call is received by the `weemoCallCreated:` method of the delegate. The `callStatus` property of the `WeemoCall` informs the status (incoming or outgoing) of the call.

In this code, the user is notified of the call by a `UIAlertView` displayed on the view, and allowing the user to pick-up or dismiss the call.

##Call management

The `CallViewController` included presents a few methods to manage the call, which amounts to:

- to stop/start the outgoing video stream: `videoStart`/`videoStop`;
- to change the quality of the incoming video quality: `toggleVideoProfile`;
- to start and stop the emission of captured audio: `audioStart`/`audioStop`;
- to switch the video source: `toggleVideoSource`;
- and of course to hang-up the call: `hangup`.

Missing is the ability to switch the incoming audio output between loudspeaker and regular speaker, which is done with the `toggleAudioRoute` of the `WeemoCall` object.

##Terminating a call
To terminate a call, one just call the `hangup` method of the related `WeemoCall`. The `callStatus` is set to `CALLSTATUS_ENDED`.