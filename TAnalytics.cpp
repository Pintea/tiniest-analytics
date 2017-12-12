/*
Tiniest Analytics - v1.0 - public domain

Original authors:
Mihai Dragomir, email:dmc@pixelshard.com
Mihai Gosa, email:pintea@inthekillhouse.com  twitter: @gosamihai

*/

#include "TAnalytics.h"
#include "curl/curl.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

TAnalytics TAnalytics::m_instance;
TAnalytics& TAnalytics::GetInstance()
{
	return m_instance;
}

TAnalytics::TAnalytics()
{
	m_pMultiHandle = NULL;
	m_strServicePath[0] = '\0';
}

TAnalytics::~TAnalytics()
{
	Shutdown();
}

bool TAnalytics::Init(const char* trackingId, const char* uniqueClientId)
{
	curl_global_init(CURL_GLOBAL_ALL);
	m_pMultiHandle = curl_multi_init();
	if (!m_pMultiHandle)
		return false;

	sprintf(m_strServicePath, "http://www.google-analytics.com/collect?v=1&tid=%s&cid=%s", trackingId, uniqueClientId);
	return true;
}

void TAnalytics::Shutdown()
{
	if (!m_pMultiHandle)
		return;

	Update(); // one last update to remove handles from stack if they're ready
	curl_multi_cleanup((CURLM*)m_pMultiHandle);
	m_pMultiHandle = NULL;
}

static void ReplaceStrChar(char *s, const int len, const char what, const char with)
{
	for (int i = 0; i < len; ++i)
	{
		if (s[i] == what)
			s[i] = with;
	}
}

bool TAnalytics::ExecuteCurlURL(const char* url, ...)
{
	if (!m_pMultiHandle)
		return false;

	va_list argptr;
	va_start(argptr, url);
	char strAddr[2048] = {'\0'};
	int slen = vsprintf(strAddr, url, argptr);
	va_end(argptr);

	ReplaceStrChar(strAddr, slen, ' ', '+');

	CURL* pCurlHandle = curl_easy_init();
	curl_easy_setopt(pCurlHandle, CURLOPT_URL, strAddr);
	curl_easy_setopt(pCurlHandle, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(pCurlHandle, CURLOPT_TIMEOUT, 20);
	CURLMcode result = curl_multi_add_handle((CURLM*)m_pMultiHandle, pCurlHandle);
	return (result == CURLM_OK);
}

void TAnalytics::Event(const char* category, const char* action, const char* label, unsigned int value)
{
	ExecuteCurlURL("%s&t=event&ec=%s&ea=%s&el=%s&ev=%u&z=%d", m_strServicePath, category, action, label, value, rand());
}

void TAnalytics::Event(const char* category, const char* action, const char* label)
{
	ExecuteCurlURL("%s&t=event&ec=%s&ea=%s&el=%s&z=%d", m_strServicePath, category, action, label, rand());
}

void TAnalytics::Event(const char* category, const char* action)
{
	ExecuteCurlURL("%s&t=event&ec=%s&ea=%s&z=%d", m_strServicePath, category, action, rand());
}

void TAnalytics::Update()
{
	if (!m_pMultiHandle)
		return;

	int stillRunning = 0;
	curl_multi_perform((CURLM*)m_pMultiHandle, &stillRunning);

	CURLMsg* pMsg = NULL;
	do {
		int msgsInQueue = 0;
		pMsg = curl_multi_info_read((CURLM*)m_pMultiHandle, &msgsInQueue);
		if(pMsg && (pMsg->msg == CURLMSG_DONE))
		{
			long response_code;
			curl_easy_getinfo(pMsg->easy_handle, CURLINFO_RESPONSE_CODE, &response_code);
			if (response_code != 200)
			{
				const char *urlp;
				curl_easy_getinfo(pMsg->easy_handle, CURLINFO_EFFECTIVE_URL, &urlp);

				char strerr[2048];
				sprintf(strerr, "[Error] TAnalytics::Update() failed for URL '%s' with error %ld\n", urlp ? urlp : "?", response_code);
				assert(response_code == 200 && strerr);
			}
			curl_multi_remove_handle((CURLM*)m_pMultiHandle, pMsg->easy_handle);
			curl_easy_cleanup(pMsg->easy_handle);
		}
	} while (pMsg);
}
