/*
Tiniest Analytics - v1.0 - public domain

Original authors:
Mihai Dragomir, email:dmc@pixelshard.com
Mihai Gosa, email:pintea@inthekillhouse.com  twitter: @gosamihai

*/

#pragma once

class TAnalytics
{
private:
	TAnalytics();
public:
	static TAnalytics& GetInstance();
	~TAnalytics();

	// usage: Init("UA-12345678-1", steamClientId)
	bool	Init(const char* trackingId, const char* uniqueClientId); // uniqueClientId should be unique for each user, e.g. the Steam UID

	void	Shutdown();

	// read this https://support.google.com/analytics/answer/1033068?hl=en
	// e.g. Event("GameStart", "linux")
	// e.g. Event("WeaponClicked", "RocketLauncher")
	// e.g. Event("MapStarted", "SinglePlayer", "MapName.map")
	void	Event(const char* category, const char* action);
	void	Event(const char* category, const char* action, const char* label);
	void	Event(const char* category, const char* action, const char* label, unsigned int value);

	// call once per frame
	void	Update();

private:
	bool	ExecuteCurlURL(const char* url, ...);

private:
	static TAnalytics m_instance;
	void*	m_pMultiHandle; // actually a CURLM*, but don't include curl.h here
	char	m_strServicePath[2048]; // includes clientID and trackingID
};

// helpers
inline void ANALYTICS_EVENT(const char* category, const char* action)											{ TAnalytics::GetInstance().Event(category, action); }
inline void ANALYTICS_EVENT(const char* category, const char* action, const char* label)						{ TAnalytics::GetInstance().Event(category, action, label); }
inline void ANALYTICS_EVENT(const char* category, const char* action, const char* label, unsigned int value)	{ TAnalytics::GetInstance().Event(category, action, label, value); }
