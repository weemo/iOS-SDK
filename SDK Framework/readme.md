## How-To

This framework interacts with your application -- the Host App --  by means of the Objective-C Delegate/Protocol paradigm.

The WeemoDelegate is used to connect to and authenticate a user on our cloud service. Simply enter an available account name

A WeemoCallDelegate is instanciated everytime a call is created, either by receiving a call or starting a call.

It is used to control the call, start and stop the video, change the video source, start and stop the audio emission, change the audio route (if you want to use the speaker of your iPhone) and change the quality of the incoming video -- if you think your bandwidth can't cope with the quality.

For full SDK description please refert to our SDK online documentation : [http://docs.weemo.com/sdk/ios/](http://docs.weemo.com/sdk/ios/)



## Requirements

This framework requires an iPhone4S, an iPad2 or more recent.

This framework uses two open-source libraries: VP8 and Speex. Those two libraries can be found in a binary form in our repositories, section "3rd Party libraries".

Speex version used: 1.2

VP8 version used: 1.1.0

## License

These two binaries are available with the following license ("BSD Style"):

Speex: Copyright (C) 2002-2006 Jean-Marc Valin

VP8: Copyright (C) 2010, Google Inc. All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, are permitted provided that
    the following conditions are met:
    * Redistributions of source code must retain the above copyright notice, this list of conditions and the
    following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
    following disclaimer in the documentation and/or other materials provided with the distribution.
    * Neither the name of the Xiph.org Foundation nor Google nor the names of its contributors may be used to endorse or 
    promote products derived from this software without specific prior written permission.
    
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ''AS IS'' AND ANY EXPRESS OR IMPLIED
    WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
    PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
    INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
    OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND 
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
