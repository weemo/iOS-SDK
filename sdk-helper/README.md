#Content

`sdk-helper` is a sample application which provides an implementation model to help developers integrate the Weemo iOS SDK. Refer to the <a href='https://github.com/weemo/iOS-SDK/wiki'>SDK wiki</a> and <a href='http://docs.weemo.com/sdk/ios'>API Reference</a> documentation for more detailed information.

The goal of this sample project is to give developers a working example of how to start the Weemo singleton, connect and disconnect, authenticate with the Weemo Real-Time Video cloud, and place an audio/video call.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#Global Architecture

This project is divided in two main classes:

* The `ViewController` is the controller for the rootView of the project. Its initialization and display starts the Weemo singleton and connects it to our network. It is a WeemoDelegate.
* The `CallViewController` is the view that appears when a call is placed/is started. It allows the user to change the video/audio source, to start/stop the outgoing audio and video, and of course hanging up the call. It is a WeemoCallDelegate.

Note: The outgoing audio stream is never really stopped. `audioStop` allows the user to stop sending audio captured from the microphone, but the stream stays open, only sending empty frames.

##ViewController
The `viewDidLoad` creates the Weemo singleton by the use of `[Weemo WeemoWithAPIKey:andDelegate:error]`.

When the Weemo singleton is connected to our network, the `weemoDidConnect:` signal of the delegate is called. 

From there, users authenticate themselves by using the `authenticateWithUserID:toDomain:` method called when the user presses the 'Authenticate' button, which is answered by the `weemoDidAuthenticate:` signal, if the UID is valid. Otherwise, the authenticate method returns a NO. 

After authentication, the application sets the userID as the display name with `setDisplayName:`.

Once authenticated on the Weemo cloud, users can start and receive calls.

Because this sample application does not provide any roster-like functionality, the user can enter a userID that is known to be valid and authenticated beforehand (on the same application running on another device) and press the 'Call' button to call.

The WeemoCall is created after the `createCall:` method is called. It is returned to the application by means of the `weemoCallCreated:` function, if any call is created. Otherwise, no call is sent to the delegate.

The availability of the contact can be checked with the `getStatus:` method of the Weemo singleton. The contact status is returned to the application by means of the `weemoContact:CanBeCalled:` delegate method.

When a call is received, a pop-up is displayed. The call can be picked up by calling the `resume` method of the call or denied by calling the `hangup` method.

##CallViewController

Once a call has been created and returned to the application, or picked-up, this object's view is displayed on top of the root view controller.

The two UIViews used to display the video streams are set in the `viewWillAppear` of this ViewController.

##Known Limitations

* The video frame may appear cropped on the mobile device. 
<br />Workaround: Change the orientation of the device. When the screen rotates, the entire video frame will appear.
* The authentication may not work, in this case the `SIP OK` does not appear.
<br />Workaround: Close and kill the app. Relaunch and it should work. If not repeat this manipulation.
* Toggling the HD/SD button does not work.
<br />Workaround: There is no workaround. The button toggles the video quality but the button label does not change.
