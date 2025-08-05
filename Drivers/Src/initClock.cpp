#include "initClock.hpp"
#include "clock.hpp"

void initClocks(void) {
    enableGPIOClock(GPIOB);
    enableTimerClock(TIM4);
    enableTimerClock(TIM3);
}
