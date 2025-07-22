#include "stm32f7xx.h"	// Device header.
#include <stdlib.h>
#include <stdio.h>
#include "clock.hpp"
#include "timer.hpp"
#include "dht11.hpp"
// PB7 - as timer 4, Ch2

#define LD3_GPIO_PIN	(1 << 14) // PB14
#define LD3_MODE_OUT	(1 << 28)

volatile int j = 0;
void delay(int k);
volatile int delay_counter = 0;
volatile int captureValue[100];
extern Timer timer4;
bool readStart = false;
volatile int edgeCount = 0;
bool dhtReply[40];
DHT11Config cfg = {};
DHT11 dht11;

uint8_t temperatureIntegral = 0;
uint8_t temperatureDecimal = 0;
uint8_t humidityIntegral = 0;
uint8_t humidityDecimal = 0;
uint8_t checkSum = 0;

int main (void)
{
	enableGPIOClock(GPIOB);
	enableTimerClock(TIM4);
	
	RCC->APB1ENR |= (1 << 1);		//Timer3 clock starts
	TIM3->CR1 |= 1 | (1<<2) | (1<<7);
	TIM3->ARR = 16;
	TIM3->PSC |= 999; 

	GPIOB->MODER |= LD3_MODE_OUT;
	GPIOB->MODER |= GPIO_MODER_MODER7_1;
	GPIOB->AFR[0] |= GPIO_AFRL_AFRL7_1;    
	delay(5000);

	dht11.initTransmit();
	dht11.transmit();

while (1)
	{

	}
}

extern "C" void TIM4_IRQHandler(){
	
	if (TIM4->SR & TIM_SR_CC2IF){
        TIM4->SR &= ~TIM_SR_CC2IF;	
       	j=j+1;
    }

	if (readStart == true){

		GPIOB->ODR ^= LD3_GPIO_PIN;
		captureValue[edgeCount] = TIM4->CCR2;
		edgeCount = edgeCount+1;
		TIM4->CNT = 0;

		if (edgeCount == 42){

			for (int i = 2; i < edgeCount; i++){

				if (captureValue[i] > 1500){
					dhtReply[i-2] = 1;
				}
				else{
					dhtReply[i-2] = 0;
				}
			}

			for (int i = 0; i < 8; i++){
				humidityIntegral    |= (dhtReply[i]      << (7 - i));
				humidityDecimal     |= (dhtReply[i + 8]  << (7 - i));
				temperatureIntegral |= (dhtReply[i + 16] << (7 - i));
				temperatureDecimal  |= (dhtReply[i + 24] << (7 - i));
				checkSum            |= (dhtReply[i + 32] << (7 - i));
			}
		}
	}

	if (j==2){
		GPIOB->ODR |= LD3_GPIO_PIN;
		GPIOB->PUPDR |= GPIO_PUPDR_PUPDR7_0;

		dht11.initReceive();
		dht11.receive();
		
		readStart = true;
		j = j+1;
	}

}

void delay(int k) 
{
while (delay_counter <= k)
{
		while ((TIM3->SR | 0xFFFE) != 0xFFFF)
	{	

	}	
	TIM3->SR &= ~(1 << 0 );	
	
	delay_counter++;
}
delay_counter = 0;

}