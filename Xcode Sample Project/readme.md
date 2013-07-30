# Requirements

To compile this project, you will need a valid APIKey!

Define APIKEY in the sdk-helper-Prefix.pch before the #ifndef APIKEY block.

As this project uses speex and vp8, you will need a set of the relevant libraries and to configure your project to use them. Those two libraries are available as binaries on the Weemo iOS-SDK github.


# Sample Project

## Description

This test app is buggy-ish.  This project deals with three classes:

* Controller
* ViewController
* CallViewController


## Controller
defined in Controller.mm

The Controller is the WeemoDelegate.  This object is notified by the Weemo singleton -- through the use of the delegate's function -- of the connection, authentication and creation of a call.

In this code you will find everything related to Weemo singleton initialization, authentication, disconnection and so on.

The delegate code linking this object to the ViewController allows mainly for GUI update.

## ViewController
defined in ViewController.mm

The ViewController class is the initial ViewController of the app.

It allows user to authenticate after the Weemo singleton is connected to our network, call another user using their name, disconnect from the network using the Controller.

## CallViewController
defined in CallViewController.mm

The CallViewController deals with video and audio. It is shown when a call is set active, either by starting to call from the app or receiving a call from a contact.

