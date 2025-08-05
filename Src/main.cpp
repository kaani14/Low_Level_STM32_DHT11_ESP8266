#include "stm32f7xx.h"	// Device header.
#include <stdlib.h>
#include <stdio.h>
#include "initClock.hpp"
#include "timer.hpp"
#include "dht11.hpp"
#include "delay.hpp"
#include "gpio.hpp"
// PB7 - as timer 4, Ch2

extern Timer timer4;
volatile int timer4InterruptCounter = 0;
void delay(int k);

DHT11Config cfg = {};
DHT11 dht11;

int main (void)
{
	initClocks();
	initDelayTimer();

	dht11.initGPIO();
	delay(5000);
	dht11.initTransmit();
	dht11.transmit();

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