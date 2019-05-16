#include "TimeUtils.h"

TimeClient::TimeClient()
{
	timeClient = new NTPClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
	timeClient->begin();
}

void TimeClient::UpdateTime(TimeData& data)
{
	timeClient->update();

	data.day = timeClient->getDay();
	data.hours = timeClient->getHours();
	data.minutes = timeClient->getMinutes();
	data.seconds = timeClient->getSeconds();
}
