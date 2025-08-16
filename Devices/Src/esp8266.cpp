#include "esp8266.hpp"
#include "delay.hpp"
#include "gpio.hpp"
#include "uart.hpp"

GPIO gpioA(GPIOA);
GPIO gpioC(GPIOC);
UART uart4(UART4);

esp8266::esp8266() {
    rxPin = 0;
    txPin = 11;
}

esp8266::~esp8266() {}

void esp8266::initGPIO(void) {

    // GPIO mode
    gpioA.setMode(rxPin, GPIO::GPIOMode::ALTERNATE);
    gpioC.setMode(txPin, GPIO::GPIOMode::ALTERNATE);

    // GPIO speed
    gpioA.setSpeed(rxPin, GPIO::GPIOSpeed::LOW);
    gpioC.setSpeed(txPin, GPIO::GPIOSpeed::LOW);

	// GPIO function
    gpioA.setAlternateFunction(rxPin, GPIO::GPIOAlternateFunction::AF8);
    gpioC.setAlternateFunction(txPin, GPIO::GPIOAlternateFunction::AF8);
}

void esp8266::initUART(void) {
    uart4.setBaudrate(16000000, 115200);
    uart4.enable();
    uart4.transmitEnable();
    uart4.receiveInterruptEnable();

    NVIC_SetPriority(UART4_IRQn, 0);
	NVIC_EnableIRQ(UART4_IRQn);
}

// If OK received, turn on the greed LED
// If error received, sent AT command once more
// If nothing is received or error is received twice, turn on red LED
void esp8266::ESP8266_Test(void) {
    const std::string ok = "OK\r\n";
    const std::string error = "ERROR\r\n";
    
    for (int k = 0; k < 2; k++) {
        uart4.transmit("AT\r\n");
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
    uart4.transmit("AT+CIPMUX=0\r\n");
	delay(500);
}

//Set to station mode and connect to WiFi
void esp8266::ESP8266_WiFiSetup(std::string SSID, std::string password) {
    uart4.transmit("AT+CWMODE=1\r\n");
	delay(500);
	bufferCounter = 0;

	std::string cmd = "AT+CWJAP=\"" + SSID + "\",\"" + password + "\"\r\n";
	uart4.transmit(cmd.c_str());
	delay(7000);
	bufferCounter = 0;
}

//HTTP request
void esp8266::TS_Write(std::string IP, int port, std::string channel_write_key, int sensor_output) {
    std::string cmd = "AT+CIPSTART=\"TCP\"," + IP + "," + std::to_string(port) + "\r\n";
    uart4.transmit(cmd.c_str());
    delay(1000);
    bufferCounter = 0;

    std::string APIrequest = "GET /update?api_key=" + channel_write_key + "&field1=" + std::to_string(sensor_output) + "\r\n";
    APIrequest_size = APIrequest.size();
    std::string AT_Command = "AT+CIPSEND=" + std::to_string(APIrequest_size) + "\r\n";
    uart4.transmit(AT_Command.c_str());
	delay(200);

	uart4.transmit(APIrequest.c_str());
	delay(5000);
	bufferCounter = 0;
}

void esp8266::ESP8266_Read(void) {
    uart4.receiveInterruptHandler(rx_data, bufferCounter);
}