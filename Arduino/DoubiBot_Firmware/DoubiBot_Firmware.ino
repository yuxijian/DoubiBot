#include "Control.h"
#include "TimeUtils.h"
#include "WeatherUtils.h"

//#define DRAW_WEATHER
//#define DRAW_TIME


const char* SSID = "***";				// 要连接的WiFi的名称
const char* PASSWORD = "***";		// 要连接的WiFi的密码
const char* CITY = "shanghai";

Control control(12, 5, 14);

TimeClient timeClient;
TimeData timeData, lastTime, lastWeather;

WeatherClient weatherClient;
WeatherData weatherData;

void setup()
{
	// uncommet this to do calibration, code will be blocked here
	control.Calibrate();

	Serial.begin(115200);

	WiFi.mode(WIFI_STA);     //设置ESP8266工作模式
	WiFi.begin(SSID, PASSWORD);

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}

	Serial.println("\nWiFi connected");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	control.GoHome();
}

void loop()
{
	// Serial CMD check, run this as often as possible
	control.CmdRoutine();

	// Get time through internet
	timeClient.UpdateTime(timeData);

	Serial.print("Now the time is ");
	Serial.print(timeData.hours);
	Serial.print(":");
	Serial.println(timeData.minutes);

#ifdef DRAW_TIME
	// Draw time every minute
	if (timeData.minutes != lastTime.minutes || timeData.hours != lastTime.hours)
	{
		control.Lift(LIFT_STATE::ON_DRAW);

		control.Clear();
		control.DrawNumber(5, 30, timeData.hours / 10, 1);
		control.DrawNumber(19, 30, timeData.hours % 10, 1);
		control.DrawNumber(28, 30, 11, 0.9);
		control.DrawNumber(34, 30, timeData.minutes / 10, 1);
		control.DrawNumber(48, 30, timeData.minutes % 10, 1);

		control.Lift(LIFT_STATE::LIFTED);
		control.GoTo(74.2, 45.5);
		control.Lift(LIFT_STATE::BETWEEN_NUMS);

		lastTime = timeData;
	}
#endif

#ifdef DRAW_WEATHER
	// Get weather through internet
	if (true || timeData.hours != lastWeather.hours)
	{
		lastWeather.hours = timeData.hours;

		weatherClient.UpdateWeather(CITY, weatherData);
		Serial.print("City: ");
		Serial.print(weatherData.city);
		Serial.print("   Weather: ");
		Serial.print(weatherData.weather);
		Serial.print("   Temp: ");
		Serial.println(weatherData.temp);

		String weather_type(weatherData.weather);

		if (true || weather_type.indexOf("sunny") > -1)
		{
			control.Clear();

			control.DrawWeatherIcon(10, 26, 1, 1);
			control.Lift(LIFT_STATE::BETWEEN_NUMS);

			control.DrawNumber(39, 27, weatherData.temp / 10, 0.8);
			control.DrawNumber(53, 27, weatherData.temp % 10, 0.8);

			control.GoHome();
		}
		else if (weather_type.indexOf("cloudy") > -1)
		{
			// ToDo
		}
		// other...
	}
#endif

	delay(1000);
}
