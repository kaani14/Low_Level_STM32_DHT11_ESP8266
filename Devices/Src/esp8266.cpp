#include "esp8266.hpp"
#include "delay.hpp"
#include "gpio.hpp"

GPIO gpioA(GPIOA);
GPIO gpioC(GPIOC);

void uart_transmit(const char *string)
{
	while (*string)
	{
		UART4->TDR = (*string++);
		while (!(UART4->ISR & USART_ISR_TXE));
	}
}

esp8266::esp8266() {}

esp8266::~esp8266() {}

void esp8266::initGPIO(void) {

    // GPIO mode
    gpioA.setMode(0, GPIO::GPIOMode::ALTERNATE);
    gpioC.setMode(11, GPIO::GPIOMode::ALTERNATE);

    // GPIO speed
    gpioA.setSpeed(0, GPIO::GPIOSpeed::LOW);
    gpioC.setSpeed(11, GPIO::GPIOSpeed::LOW);

	// GPIO function
    gpioA.setAlternateFunction(0, GPIO::GPIOAlternateFunction::AF8);
    gpioC.setAlternateFunction(11, GPIO::GPIOAlternateFunction::AF8);
}

// If OK received, turn on the greed LED
// If error received, sent AT command once more
// If nothing is received or error is received twice, turn on red LED
void esp8266::ESP8266_Test(void) {
    const std::string ok = "OK\r\n";
    const std::string error = "ERROR\r\n";
    
    for (int k = 0; k < 2; k++) {
        uart_transmit("AT\r\n");
        delay(1000);
        
        std::string rx_string(reinterpret_cast<const char*>(rx_data));
        
        if (rx_string.find(ok) != std::string::npos) {
            bufferCounter = 0;
            GPIOB->ODR = GPIO_ODR_OD0;
            break;
        }
        else if (rx_string.find(error) != std::string::npos) {
            bufferCounter = 0;
        }
    }
    
    std::string rx_string(reinterpret_cast<const char*>(rx_data));
    if (rx_string.find(ok) == std::string::npos && rx_string.find(error) == std::string::npos) {
        GPIOB->ODR = GPIO_ODR_OD14;
    }
}

//Single connection
void esp8266::ESP8266_Connection_Type(void) {
    uart_transmit("AT+CIPMUX=0\r\n");
	delay(500);
}

//Set to station mode and connect to WiFi
void esp8266::ESP8266_WiFiSetup(std::string SSID, std::string password) {
    uart_transmit("AT+CWMODE=1\r\n");
	delay(500);
	bufferCounter = 0;

	std::string cmd = "AT+CWJAP=\"" + SSID + "\",\"" + password + "\"\r\n";
	uart_transmit(cmd.c_str());
	delay(7000);
	bufferCounter = 0;
}

//HTTP request
void esp8266::TS_Write(std::string IP, int port, std::string channel_write_key, int sensor_output) {
    std::string cmd = "AT+CIPSTART=\"TCP\"," + IP + "," + std::to_string(port) + "\r\n";
    uart_transmit(cmd.c_str());
    delay(1000);
    bufferCounter = 0;

    std::string APIrequest = "GET /update?api_key=" + channel_write_key + "&field1=" + std::to_string(sensor_output) + "\r\n";
    APIrequest_size = APIrequest.size();
    std::string AT_Command = "AT+CIPSEND=" + std::to_string(APIrequest_size) + "\r\n";
    uart_transmit(AT_Command.c_str());
	delay(200);

	uart_transmit(APIrequest.c_str());
	delay(5000);
	bufferCounter = 0;
}