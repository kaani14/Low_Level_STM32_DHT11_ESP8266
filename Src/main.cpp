#include "stm32f7xx.h"	// Device header.
#include "stdlib.h"
#include "stdio.h"
#include "clock.hpp"
#include "timer.hpp"
// PB7 - as timer 4, Ch2

#define LD3_GPIO_PIN	(1 << 14) // PB14
#define LD3_MODE_OUT	(1 << 28)

volatile int j = 0;

int main (void)
{
	int test = 0;
	enableGPIOClock(GPIOB);
	enableTimerClock(TIM4);
	GPIOB->MODER |= LD3_MODE_OUT;
	GPIOB->MODER |= GPIO_MODER_MODER7_1;
	GPIOB->AFR[0] |= GPIO_AFRL_AFRL7_1;    

	Timer timer4(TIM4);
	timer4.setPrescaler(16000 - 1);
	timer4.setAutoReload(1000 - 1);
	timer4.setCompare(500);
	timer4.enableInterrupt();
	NVIC_EnableIRQ(TIM4_IRQn);
	timer4.outputCompareMode();
	timer4.startCounter();

	/*
	TIM4->ARR = 1000 - 1;
	TIM4->PSC |= 16000 - 1;
	TIM4->CCR2 = 500;

	TIM4->DIER |= TIM_DIER_CC2IE;
	NVIC_EnableIRQ(TIM4_IRQn);

	TIM4->CCMR1 |= TIM_CCMR1_OC2M_0 | TIM_CCMR1_OC2M_1;
	TIM4->CCER |= TIM_CCER_CC2E;
	
	TIM4->CR1 |= TIM_CR1_CEN;
	*/

while (1)
	{	

	}
}

extern "C" void TIM4_IRQHandler()
{
	GPIOB->ODR ^= ( LD3_GPIO_PIN);
	if (TIM4->SR & TIM_SR_CC2IF)
    {
        TIM4->SR &= ~TIM_SR_CC2IF;
        j=100;
    }
	j=100;
}