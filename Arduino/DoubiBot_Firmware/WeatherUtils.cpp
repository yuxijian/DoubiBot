#include "WeatherUtils.h"

WeatherClient::WeatherClient()
{
	client.setTimeout(HTTP_TIMEOUT);
}

void WeatherClient::UpdateWeather(const char* city, WeatherData& data)
{
	while (!client.connected())
	{
		if (!client.connect(host, 80))
		{
			Serial.println("connection....");
			delay(500);
		}
	}
	if (sendRequest(host, city, APIKEY) && skipResponseHeaders())
	{
		clrEsp8266ResponseBuffer();
		readReponseContent(response, sizeof(response));

		if (parseUserData(response, &data))
		{
			//printUserData(&data);
		}
	}
}

/**
* @发送请求指令
*/
bool WeatherClient::sendRequest(const char* host, const char* cityid, const char* apiKey)
{
	// We now create a URI for the request
	//心知天气
	String GetUrl = "/v3/weather/now.json?key=";
	GetUrl += apiKey;
	GetUrl += "&location=";
	GetUrl += cityid;
	GetUrl += "&language=";
	GetUrl += language;
	// This will send the request to the server
	client.print(String("GET ") + GetUrl + " HTTP/1.1\r\n" +
		"Host: " + host + "\r\n" +
		"Connection: close\r\n\r\n");
	/*Serial.println("create a request:");
	Serial.println(String("GET ") + GetUrl + " HTTP/1.1\r\n" +
		"Host: " + host + "\r\n" +
		"Connection: close\r\n");*/
	delay(1000);
	return true;
}

/**
* @Desc 跳过 HTTP 头，使我们在响应正文的开头
*/
bool WeatherClient::skipResponseHeaders()
{
	// HTTP headers end with an empty line
	bool ok = client.find("\r\n\r\n");
	if (!ok)
	{
		Serial.println("No response or invalid response!");
	}
	return ok;
}

/**
* @Desc 从HTTP服务器响应中读取正文
*/
void WeatherClient::readReponseContent(char* content, size_t maxSize)
{
	size_t length = client.readBytes(content, maxSize);
	delay(100);
	//Serial.println("Get the data from Internet!");
	content[length] = 0;
	//Serial.println(content);
	//Serial.println("Read data Over!");
	client.flush();//这句代码需要加上  不然会发现每隔一次client.find会失败
}

/**
 * @Desc 解析数据
 * 数据格式如下：
 * {
 *    "results": [
 *        {
 *            "location": {
 *                "id": "WX4FBXXFKE4F",
 *                "name": "北京",
 *                "country": "CN",
 *                "path": "北京,北京,中国",
 *                "timezone": "Asia/Shanghai",
 *                "timezone_offset": "+08:00"
 *            },
 *            "now": {
 *                "text": "多云",
 *                "code": "4",
 *                "temperature": "23"
 *            },
 *            "last_update": "2017-09-13T09:51:00+08:00"
 *        }
 *    ]
 *}
 */
bool WeatherClient::parseUserData(char* content, struct WeatherData* userData)
{
	//    -- 根据我们需要解析的数据来计算JSON缓冲区最佳大小
	//   如果你使用StaticJsonBuffer时才需要
	//    const size_t BUFFER_SIZE = 1024;
	//   在堆栈上分配一个临时内存池
	//    StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
	//    -- 如果堆栈的内存池太大，使用 DynamicJsonBuffer jsonBuffer 代替
	DynamicJsonBuffer jsonBuffer;

	JsonObject& root = jsonBuffer.parseObject(content);

	if (!root.success())
	{
		Serial.println("JSON parsing failed!");
		return false;
	}

	//复制我们感兴趣的字符串
	strcpy(userData->city, root["results"][0]["location"]["name"]);
	strcpy(userData->weather, root["results"][0]["now"]["text"]);
	userData->temp = atoi(root["results"][0]["now"]["temperature"]);
	strcpy(userData->udate, root["results"][0]["last_update"]);
	//  -- 这不是强制复制，你可以使用指针，因为他们是指向“内容”缓冲区内，所以你需要确保
	//   当你读取字符串时它仍在内存中
	return true;
}

// 打印从JSON中提取的数据
void WeatherClient::printUserData(const struct WeatherData* userData)
{
	Serial.println("Print parsed data :");
	Serial.print("City : ");
	Serial.print(userData->city);
	Serial.print(", \t");
	Serial.print("Weather : ");
	Serial.print(userData->weather);
	Serial.print(",\t");
	Serial.print("Temp : ");
	Serial.print(userData->temp);
	Serial.print(" C");
	Serial.print(",\t");
	Serial.print("Last Updata : ");
	Serial.print(userData->udate);
	Serial.println("\r\n");
}

// 关闭与HTTP服务器连接
void WeatherClient::stopConnect()
{
	Serial.println("Disconnect");
	client.stop();
}

void WeatherClient::clrEsp8266ResponseBuffer(void)
{
	memset(response, 0, MAX_CONTENT_SIZE);      //清空
}