# Weemo iOS SDK Changelog


## 4.2.0

**`Nov 18 2013`**


### New Features

- **SDK:** `WeemoCall` provides `getVideoInProfile` and `getVideoOutProfile` to get the frame size of each video view.


### Improvements

- **SDK:** `foreground` and `background` are deprecated. This is now handled automatically by the SDK.


### Known issues


- ***MS-8***  
  **Description:** No Display Name sent during a call creation.  
  **Workaround:** Manage DisplayName by Host application


- ***MS-11***  
  **Description:** Connecting a new device with same credentials forces a re-authentication, the first device can no longer be contacted  
  **Workaround:** Manage account access by host application

