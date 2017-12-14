# tiniest-analytics
Tiniest Analytics is a *very* simple to use, cross-platform (tested on win/osx/linux/ios/android) and basically *very tiny* analytics system written in C++ (about 100 lines of code), made specifically for games. It uses libcurl to post events to your Google Analytics account.
<br />
<br />
You need libcurl in your project, after that just include TAnalytics.h, call Init("UA-12345678-1", uniqueId) before using, Shutdown() when closing your app, and Update() each frame.
<br />
There's only one function to use when posting an event, e.g.<br />
TAnalytics::Event("GameStart", "linux");<br />
TAnalytics::Event("WeaponClicked", "RocketLauncher");<br />
TAnalytics::Event("MapStarted", "SinglePlayer", "MapName.map");<br />
<br />
<br />
![alt text](https://user-images.githubusercontent.com/292486/33986464-4f0b6000-e0c6-11e7-83fe-790486ef7685.jpg)
<br />
![alt text](https://user-images.githubusercontent.com/292486/33986467-4f4974b2-e0c6-11e7-9cc4-56922337432e.jpg)
<br />
![alt text](https://user-images.githubusercontent.com/292486/33986466-4f2c4f18-e0c6-11e7-9c87-25fdf8e13420.jpg)
<br />
<br />
Original authors:<br />
Mihai Dragomir - dmc@pixelshard.com<br />
Mihai Gosa - pintea@inthekillhouse.com or @gosamihai on twitter<br />
<br />
<br />
License: MIT
