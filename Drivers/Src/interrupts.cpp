#include "timer.hpp"
#include "dht11.hpp"
#include "esp8266.hpp"

extern Timer timer4;
extern DHT11 dht11;
extern esp8266 ESP;
volatile int timer4InterruptCounter = 0;

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