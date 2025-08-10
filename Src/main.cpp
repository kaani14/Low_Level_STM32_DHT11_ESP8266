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
// PB7 - as timer 4, Ch2

extern Timer timer4;
volatile int timer4InterruptCounter = 0;
void delay(int k);
void uart_transmit(const char *string);


DHT11Config cfg = {};
DHT11 dht11;

std::string SSID = "SSID";
std::string password = "password";
std::string IP = "\"184.106.153.149\"";
std::string write_API_key = "\"API_KEY\"";

const int port = 80;
int sensor_output = 30.56;

esp8266 ESP;

int main (void)
{
	initClocks();
	initDelayTimer();

	ESP.initGPIO();
	GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER14_0;

	// UART
	UART4->BRR = 0x8A;				//Baud Rate: 16Mhz / 115200
	UART4->CR1 |= USART_CR1_UE | USART_CR1_TE;
	UART4->CR1 |= USART_CR1_RE | USART_CR1_RXNEIE;
	NVIC_SetPriority(UART4_IRQn, 0);
	NVIC_EnableIRQ(UART4_IRQn);

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
	ESP.rx_data[ESP.bufferCounter] = UART4->RDR;
	ESP.bufferCounter++;
}
