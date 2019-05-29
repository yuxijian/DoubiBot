#include "TimeUtils.h"

TimeClient::TimeClient()
{
	timeClient = new NTPClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
	timeClient->begin();
}

void TimeClient::UpdateTime(TimeData& data)
{
	if (millis() - t > interval)
	{
		timeClient->update();

		data.day = timeClient->getDay();
		data.hours = timeClient->getHours();
		data.minutes = timeClient->getMinutes();
		data.seconds = timeClient->getSeconds();

		t = millis();
		last_sec = millis();
	}
	else
	{
		data.seconds += ((millis() - last_sec) / 1000);
		last_sec = millis();

		if (data.seconds > 59)
		{
			data.minutes++;
			data.seconds = 0;
		}

		if (data.minutes > 59)
		{
			data.hours++;
			data.minutes = 0;
		}

		if (data.hours > 23)
		{
			data.hours = 0;
		}
	}
}
