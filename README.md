# tiniest-analytics
Tiniest Analytics is VERY simple to use, cross-platform (tested on win/osx/linux/ios/android) and basically *very tiny* analytics system written in C++ (about 100 lines of code). It uses libcurl to post events to your Google Analytics account.
<br />

<br />
There's only one function to use, e.g.<br />
TAnalytics::Event("GameStart", "linux");<br />
TAnalytics::Event("WeaponClicked", "RocketLauncher");<br />
TAnalytics::Event("MapStarted", "SinglePlayer", "MapName.map");<br />


Original authors:<br />
Mihai Dragomir - dmc@pixelshard.com<br />
Mihai Gosa - pintea@inthekillhouse.com or @gosamihai on twitter<br />
<br />
License: MIT
