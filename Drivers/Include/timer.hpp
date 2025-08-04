#ifndef TIMER_HPP
#define TIMER_HPP

#include "stm32f7xx.h"

class Timer {

    public:

    enum OutputCompareMode {
        FROZEN = 0,
        ACTIVE_ON_MATCH,
        INACTIVE_ON_MATCH,
        TOGGLE,
        FORCE_INACTIVE,
        FORCE_ACTIVE,
        PWM_MODE1,
        PWM_MODE2
    };

    enum InputCaptureEdgeDetection {
        RISING_EDGE = 0,
        FALLING_EDGE,
        RESERVED,
        BOTH_EDGES
    };

        Timer(TIM_TypeDef* timerInstance);
        ~Timer();
        void enable();
        void disable();
        void setPrescaler(uint16_t prescaler);
        void setAutoReload(uint16_t autoReload);
        void setCounter(uint16_t counterValue);
        void setCompare(uint16_t compareValue);
        void generateUpdateEvent();
        uint16_t readCaptureValue();
        void enableInterrupt();
        void ResetTimer();
        void configureInputChannel();
        void setFilter(int filter);
        void outputCompareMode(OutputCompareMode mode);
        void setInputCapturePrescaler(uint16_t prescaler);
        void inputCaptureEdgeDetection(InputCaptureEdgeDetection edge);
        void startCounter();

    private:
        TIM_TypeDef* tim;
};

#endif // TIMER_HPP