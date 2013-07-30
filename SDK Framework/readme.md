## How-To

This framework interacts with your application -- the Host App --  by means of the Objective-C Delegate/Protocol paradigm.

The WeemoDelegate is used to connect to and authenticate a user on our cloud service. Simply enter an available account name

A WeemoCallDelegate is instanciated everytime a call is created, either by receiving a call or starting a call.

It is used to control the call, start and stop the video, change the video source, start and stop the audio emission, change the audio route (if you want to use the speaker of your iPhone) and change the quality of the incoming video -- if you think your bandwidth can't cope with the quality.

For full SDK description please refert to our SDK online documentation : [http://docs.weemo.com/sdk/ios/](http://docs.weemo.com/sdk/ios/)



## Requirements

This framework requires an iPhone4S, an iPad2 or more recent.

This framework uses two open-source libraries: VP8 and Speex. Those two libraries can be found in a binary form in our repositories, section "3rd Party libraries".
