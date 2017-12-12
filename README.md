# tiniest-analytics
VERY simple cross-platform C++ analytics for games (using Google Analytics)

Tiniest Analytics is a multi-platform (tested on win/osx/linux/ios/android), very simple to use and basically *very tiny* analytics system written in C++ (about 100 lines of code). It uses libcurl to post events on your Google Analytics account.

There's only one function to use, e.g.
TAnalytics::Event("GameStart", "linux");
TAnalytics::Event("WeaponClicked", "RocketLauncher");
TAnalytics::Event("MapStarted", "SinglePlayer", "MapName.map");

Original authors:
Mihai Dragomir - dmc@pixelshard.com
Mihai Gosa - pintea@inthekillhouse.com or @gosamihai on twitter

License: MIT
