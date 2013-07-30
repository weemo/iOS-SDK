# WeemoDriver iOS SDK and Sample Application

This is a sample application using WeemoDriver SDK for iOS. More information about WeemoDriver Mobile SDK on our Website [http://www.weemo.com/](http://www.weemo.com/)


The use cases have been minimized in order to reduce the integration effort while creating a functional model for the POC that covers most of the use cases for audio and video during 1:1 calls. 
Basic implemented functions into this example are: 

- Initialization and Cloud authentification
- Send or Receive a call by UID  
- Stop or Start video
- Mute or Unmute audio
- iOS 6 Multi-tasking support

For a full functionalities list, refer to our SDK documentation: [http://docs.weemo.com/sdk/ios/](http://docs.weemo.com/sdk/ios/)

## SDK Architecture

<img src="https://raw.github.com/weemo/iOS-SDK/master/img/SDK-arch.png?login=beuck&token=9e3ffaee07288fdd39ea208e71d01e11">

## About Weemo

The Weemo Video Cloud is a solution specifically targeted at application software vendors providing real-time video communications embedded within any web or mobile application. The solution is particularly well suited for social software applications such as Enterprise Social Networks, Social CRM, HCM, Customer Service, Education and E-learning, as well as for Contact Management and Collaboration.

Weemo relies on open-standard protocols such as SIP, XMPP and HTTPS. The solution provides constant interoperability with existing or future communication-oriented devices and infrastructures.

Weemo provides both the client technology and integration means and a worldwide cloud infrastructure. These building blocks are designed to work together as one easy-to-use solution. The application vendor, provider of the web application to be integrated with Weemo, will implement JavaScript commands in order to control local clients and, as needed, will have access to REST APIs to perform management tasks including provisioning named users.


## Hardware Requirements

Weemo SDK requires at least an iPhone4, an iPad2 or more recent.

## Important note

This is still an early version of the SDK, more functionnality to be added soon.


## Release notes


### 0.1-20130730
First release

#### SDK:
- Connection and authentication
- Autoreconnection in case of temporary connection failure
- Incoming and Outgoing call
- Call control
- Audio and Video control


#### Helper:
- User-specified username
- Call to a user-specified contact
- Pick-up/Hang-up incoming call
- Video displayed and captured
- Stop outgoing video
