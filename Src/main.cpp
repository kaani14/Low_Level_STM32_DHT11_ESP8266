#include "stm32f7xx.h"	// Device header.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <cstdio>
#include "initClock.hpp"
#include "timer.hpp"
#include "dht11.hpp"
#include "delay.hpp"
#include "gpio.hpp"
#include "esp8266.hpp"
#include "uart.hpp"
// PB7 - as timer 4, Ch2

extern Timer timer4;
volatile int timer4InterruptCounter = 0;
void delay(int k);

DHT11Config cfg = {};
DHT11 dht11;

std::string SSID = "SSID";
std::string password = "Password";
std::string IP = "\"184.106.153.149\"";
std::string write_API_key = "key";

const int port = 80;
int sensor_output = 30.56;

esp8266 ESP;
extern UART uart4;

int main (void)
{
	initClocks();
	initDelayTimer();

	ESP.initGPIO();
	ESP.initUART();
	GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER14_0;

	//dht11.initGPIO();
	delay(5000);
	//dht11.initTransmit();
	//dht11.transmit();

	ESP.ESP8266_Test();
	ESP.ESP8266_WiFiSetup(SSID, password);
	ESP.ESP8266_Connection_Type();
	ESP.TS_Write(IP, port, write_API_key, sensor_output);

while (1)
	{

	}
}

extern "C" void TIM4_IRQHandler(){

	timer4.clearCC2InterruptFlag();
	timer4InterruptCounter += 1;
	
	dht11.processData();

	if (timer4InterruptCounter == 2){
		dht11.initReceive();
		dht11.receive();
	}
}

// interrupt for receiving
extern "C" void UART4_IRQHandler()
{
    ESP.ESP8266_Read();
}
