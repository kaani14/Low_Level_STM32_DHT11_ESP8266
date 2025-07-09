#ifndef TIMER_HPP
#define TIMER_HPP

#include "stm32f7xx.h"

class Timer {

    public:
        Timer(TIM_TypeDef* timerInstance);
        ~Timer();
        void enable();
        void setPrescaler(uint16_t prescaler);
        void setAutoReload(uint16_t autoReload);
        void setCompare(uint16_t compareValue);
        void enableInterrupt();
        void outputCompareMode();
        void startCounter();

    private:
        TIM_TypeDef* tim;
};

#endif // TIMER_HPP