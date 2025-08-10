#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "stm32f7xx.h"

void enableGPIOClock(GPIO_TypeDef* GPIOx);
void enableTimerClock(TIM_TypeDef* TIMx);
void enableUARTClock(USART_TypeDef* USARTx);
#endif // CLOCK_HPP