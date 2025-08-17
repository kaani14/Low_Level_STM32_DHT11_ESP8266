#include "stm32f7xx.h"
#include <string>
#include "initSystem.hpp"
#include "initClock.hpp"
#include "dht11.hpp"
#include "delay.hpp"
#include "esp8266.hpp"

DHT11Config cfg = {};
DHT11 dht11;
esp8266 ESP;

std::string SSID = "SSID";
std::string password = "Password";
std::string IP = "\"184.106.153.149\"";
std::string write_API_key = "APIKEY";

const int port = 80;

int main (void)
{	
	initSystem();
	initClocks();
	initDelayTimer();

	ESP.initGPIO();
	ESP.initUART();

	dht11.initGPIO();
	delay(5000);
	dht11.initTransmit();
	dht11.transmit();

	ESP.ESP8266_Test();
	ESP.ESP8266_WiFiSetup(SSID, password);
	ESP.ESP8266_Connection_Type();
	ESP.TS_Write(IP, port, write_API_key, dht11.humidityIntegral);

while (1)
	{

	}
}
