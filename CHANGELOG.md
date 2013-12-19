# Weemo iOS SDK Changelog


## 4.2.0

**`18/11/2013`**


### New Features

- **SDK:** `WeemoCall` provides `getVideoInProfile` and `getVideoOutProfile` to get the fram size of each video view.


### Improvements

- **SDK:** `foreground` and `backgroud` are deprecated. This is now handle automaticaly by the SDK.


### Known issues


- ***MS-8***  
  **Description:** No Display Name sent during a call creation.  
  **Workaround:** Manage DisplayName by Host application


- ***MS-11***  
  **Description:** Connecting a new device with same credentials force the authentication, the first device could not be contacted  
  **Workaround:** Manage accounts by host application

