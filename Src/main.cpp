#include "stm32f7xx.h"	// Device header.
#include <stdlib.h>
#include <stdio.h>
#include "clock.hpp"
#include "timer.hpp"
#include "dht11.hpp"
// PB7 - as timer 4, Ch2

#define LD3_MODE_OUT	(1 << 28)

volatile int j = 0;
void delay(int k);
volatile int delay_counter = 0;

DHT11Config cfg = {};
DHT11 dht11;

int main (void)
{
	enableGPIOClock(GPIOB);
	enableTimerClock(TIM4);
	enableTimerClock(TIM3);
	//RCC->APB1ENR |= (1 << 1);
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
       	
    }
	j=j+1;
	dht11.processData();

	if (j==2){

		GPIOB->PUPDR |= GPIO_PUPDR_PUPDR7_0;
		dht11.initReceive();
		dht11.receive();
		
		j = j+1;
	}

}

void delay(int k) {
	while (delay_counter <= k){
		while ((TIM3->SR | 0xFFFE) != 0xFFFF){	

		}	
	TIM3->SR &= ~(1 << 0 );	
	
	delay_counter++;
}
delay_counter = 0;

}