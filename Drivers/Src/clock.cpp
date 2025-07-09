#include "clock.hpp"

void enableGPIOClock(GPIO_TypeDef* GPIOx) {
    if (GPIOx == GPIOA)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    else if (GPIOx == GPIOB)
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
}

void enableTimerClock(TIM_TypeDef* TIMx){
    if (TIMx == TIM1)
        RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    else if (TIMx == TIM2)
        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    else if (TIMx == TIM3)
        RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    else if (TIMx == TIM4)
        RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    else if (TIMx == TIM5)
        RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
}