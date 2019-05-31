#pragma once

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>


struct TimeData
{
	int day;
	int hours;
	int minutes;
	int seconds;
};


class TimeClient
{
public:
	TimeClient();

	void UpdateTime(TimeData& data);

private:
	long t = -600000;
	long last_sec = 0;

	long interval = 600000; // 10min

	const long utcOffsetInSeconds = 28800;

	WiFiUDP ntpUDP;
	NTPClient* timeClient;

	char daysOfTheWeek[7][12] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
};