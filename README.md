# tiniest-analytics
Tiniest Analytics is a *very* simple to use, cross-platform (tested on win/osx/linux/ios/android) and basically *very tiny* analytics system written in C++ (less than 100 lines of code), made specifically for games. It uses libcurl to post events to your Google Analytics account.
<br />
<br />
Usage: call TAnalytics_Init("UA-12345678-1", uniqueId) at startup, call TAnalytics_Shutdown() when closing the app, and TAnalytics_Update() each frame. You also need libcurl in your project (ssl not needed).
<br />
There's only one function to use when posting an event, e.g.<br />
TAnalytics_Event("GameStart", "linux");<br />
TAnalytics_Event("WeaponClicked", "RocketLauncher");<br />
TAnalytics_Event("MapStarted", "SinglePlayer", "MapName.map");<br />
<br />
<br />
![alt text](https://user-images.githubusercontent.com/292486/33986723-206b0bc8-e0c7-11e7-9ac9-8f4f841385ed.jpg)
<br />
<br />
![alt text](https://user-images.githubusercontent.com/292486/33986724-20895b32-e0c7-11e7-8114-b203803867e4.jpg)
<br />
<br />
![alt text](https://user-images.githubusercontent.com/292486/33986722-204d395e-e0c7-11e7-8d1d-4f73cfcb577a.jpg)
<br />
<br />
Original authors:<br />
Mihai Dragomir - dmc@pixelshard.com<br />
Mihai Gosa - pintea@inthekillhouse.com or @gosamihai on twitter<br />
Initially developed for the 'Door Kickers' games.<br />
<br />
<br />
License: MIT
