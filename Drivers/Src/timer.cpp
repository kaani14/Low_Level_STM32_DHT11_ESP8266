#include "timer.hpp"

Timer::Timer(TIM_TypeDef* timerInstance) : tim(timerInstance) {}

Timer::~Timer() {}

void Timer::enable(){
    tim->CR1 |= TIM_CR1_CEN;
}
void Timer::setPrescaler(uint16_t prescaler){
    tim->PSC = prescaler;
}

void Timer::setAutoReload(uint16_t autoReload){
    tim->ARR = autoReload;
}

void Timer::setCompare(uint16_t compareValue){
    tim->CCR1 = compareValue;
}

void Timer::enableInterrupt(){
    TIM4->DIER |= TIM_DIER_CC2IE;
}
void Timer::outputCompareMode(){
    TIM4->CCMR1 |= TIM_CCMR1_OC2M_0 | TIM_CCMR1_OC2M_1;
	TIM4->CCER |= TIM_CCER_CC2E;
}

void Timer::startCounter(){
    tim->CR1 |= TIM_CR1_CEN;
}