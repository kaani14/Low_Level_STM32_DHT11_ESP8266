#ifndef INC_ESP8266_H_
#define INC_ESP8266_H_

#include "stm32f7xx.h"
#include <string.h>
#include <string>

class esp8266{

	public:
		esp8266();
		~esp8266();
		void initGPIO(void);
		void initUART(void);
		void ESP8266_Read(void);
		void ESP8266_Test(void);
		void ESP8266_Connection_Type(void);
		void ESP8266_WiFiSetup(std::string SSID, std::string password);
		void TS_Write(std::string IP, int port, std::string channel_write_key, int sensor_output);
	
	//private:
		uint8_t rxPin;
		uint8_t txPin;
		std::string SSID;
		std::string password;
		std::string IP;
		int port;
		std::string write_API_key;
		uint8_t rx_data[150];
		int bufferCounter=0;
		int APIrequest_size;
};

#endif /* INC_ESP8266_H_ */
