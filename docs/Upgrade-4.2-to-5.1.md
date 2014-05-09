## Overview

This section describes how to upgrade an application built using the
Weemo 4.2 iOS SDK Framework to the Weemo 5.1 iOS SDK Framework.

The upgrade process consists of two parts.  Weemo must upgrade your AppID to
support Version 5.x, and you must re-compile your application with the 5.1 iOS SDK.

## The libraries have changed

4.2 used speex 1.2 and vp8 1.1.0

5.1 uses opux 1.1 and vp8 1.1.0

## Weemo singleton creation

    [Weemo WeemoWithAppID:MOBILEAPPID andDelegate:self error:&err];

Nothing has changed.

## User authentication

In the weemoDidConnect:

was (in 3.2)

    [Weemo connectWithUserID:uid toDomain:domain]

is changed to (4.2, 5.1)

    [Weemo authenticateWithToken:token andType:userType]

## iOS-SDK-Helper

 - much of the program logic moved into a two new files:
    HomeViewController.m
    DataGroup.m
