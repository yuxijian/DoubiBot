#include "WeatherUtils.h"
#include "TimeUtils.h"


const char* SSID = "pixel";				// 要连接的WiFi的名称
const char* PASSWORD = "299792458";		// 要连接的WiFi的密码
const char* CITY = "shanghai";


WeatherClient weatherClient;
WeatherData weatherData;

TimeClient timeClient;
TimeData timeData;

void setup()
{
	Serial.begin(115200);

	Serial.print("Connecting to ");
	Serial.println(SSID);

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
}


void loop()
{
	weatherClient.UpdateWeather(CITY, weatherData);
	timeClient.UpdateTime(timeData);

	Serial.print("City: ");
	Serial.print(weatherData.city);
	Serial.print("   Weather: ");
	Serial.print(weatherData.weather);
	Serial.print("   Temp: ");
	Serial.print(weatherData.temp);
	Serial.print("  ");
	Serial.print(timeData.hours);
	Serial.print(":");
	Serial.println(timeData.minutes);

	delay(5000);
}
