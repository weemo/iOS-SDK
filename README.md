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

<img src="http://docs.weemo.com/img/SDK-arch.png">


## Download
The SDK is available as a framework.

The project available in this repository sdk-helper folder is an application built around the SDK, as a limited demo. Its goal is to show the SDK in action, not an integration of the SDK in an existing application.

Clone the repository onto your Mac, start Xcode using the sdk-helper/sdk-helper.xcodeproj.
 
Add your APIKey to the sdk-helper/support/sdk-helper-Prefix.pch file.

Press Build & Run.



## Software Dependencies

The SDK is available as a framework thanks to the work of Karl Stenerud (https://github.com/kstenerud)

This SDK uses VP8 and Speex. The two libraries are distributed as binaries with the project. Licences can be found in the Library folder of the project, along the binaries.


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



## About Weemo

The Weemo Video Cloud is a solution specifically targeted at application software vendors providing real-time video communications embedded within any web or mobile application. The solution is particularly well suited for social software applications such as Enterprise Social Networks, Social CRM, HCM, Customer Service, Education and E-learning, as well as for Contact Management and Collaboration.

Weemo relies on open-standard protocols such as SIP, XMPP and HTTPS. The solution provides constant interoperability with existing or future communication-oriented devices and infrastructures.

Weemo provides both the client technology and integration means and a worldwide cloud infrastructure. These building blocks are designed to work together as one easy-to-use solution. The application vendor, provider of the web application to be integrated with Weemo, will implement JavaScript commands in order to control local clients and, as needed, will have access to REST APIs to perform management tasks including provisioning named users.
