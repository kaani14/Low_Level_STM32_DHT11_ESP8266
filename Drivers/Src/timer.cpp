#include "timer.hpp"

Timer::Timer(TIM_TypeDef* timerInstance) : tim(timerInstance) {}

Timer::~Timer() {}

void Timer::enable(){
    tim->CR1 |= TIM_CR1_CEN | TIM_CR1_OPM;
}

void Timer::disable(){
    tim->CR1 &= ~TIM_CR1_CEN;
}

void Timer::setPrescaler(uint16_t prescaler){
    tim->PSC = prescaler;
}

void Timer::setAutoReload(uint16_t autoReload){
    tim->ARR = autoReload;
}

void Timer:: setCounter(uint16_t counterValue){
    tim->CNT = counterValue;
}

void Timer::setCompare(uint16_t compareValue){
    tim->CCR2 = compareValue;
}

void Timer::enableInterrupt(){
    tim->DIER |= TIM_DIER_CC2IE;
}

void Timer::generateUpdateEvent(){
    tim->EGR |= TIM_EGR_UG;
}

void Timer::ResetTimer() {
    TIM4->CCER = 0;
    tim->SR = 0;
    tim->CCMR1 = 0;
}

void Timer::configureInputChannel() {
    tim->CCMR1 |= TIM_CCMR1_CC2S_0;
}

void Timer::setFilter(int filter) {
    switch (filter) {
        case 0:
            tim->CCMR1 &= ~(TIM_CCMR1_IC2F_0 | TIM_CCMR1_IC2F_1 | TIM_CCMR1_IC2F_2);
            break;
        case 8:
            tim->CCMR1 |= TIM_CCMR1_IC2F_0 | TIM_CCMR1_IC2F_1;
            tim->CCMR1 &= ~(TIM_CCMR1_IC2F_2);
            break;
    }
}

void Timer::outputCompareMode(Timer::OutputCompareMode mode){
    switch (mode){
    case Timer::OutputCompareMode::ACTIVE_ON_MATCH:
        tim->CCMR1 |= TIM_CCMR1_OC2M_0;
        break;

    case Timer::OutputCompareMode::PWM_MODE1:
        tim->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;  // Ton = Count till setCompare, Toff = Count till ARR
        break;

    default:
        break;
    }  
	tim->CCER |= TIM_CCER_CC2E;
}

void Timer::setInputCapturePrescaler(uint16_t prescaler) {
    switch (prescaler){
    case 0:
        tim->CCMR1 &= ~(TIM_CCMR1_IC2PSC_0 | TIM_CCMR1_IC2PSC_1);
        break;
    default:
        break;
    }
    tim->CCER |= TIM_CCER_CC2E;
}

void Timer::inputCaptureEdgeDetection(Timer::InputCaptureEdgeDetection edge) {
    switch (edge) {
        case Timer::InputCaptureEdgeDetection::RISING_EDGE:
            tim->CCER &= ~(TIM_CCER_CC2P | TIM_CCER_CC2NP);
            break;
        case Timer::InputCaptureEdgeDetection::FALLING_EDGE:
            tim->CCER |= TIM_CCER_CC2P;
            tim->CCER &= ~TIM_CCER_CC2NP;
            break;
        case Timer::InputCaptureEdgeDetection::BOTH_EDGES:
            tim->CCER |= TIM_CCER_CC2P | TIM_CCER_CC2NP;
            break;
        default:
            break;
    }
}

void Timer::startCounter(){
    tim->CR1 |= TIM_CR1_CEN;
}