#include "initClock.hpp"
#include "clock.hpp"

void initClocks(void) {
    enableGPIOClock(GPIOA);
    enableGPIOClock(GPIOB);
    enableGPIOClock(GPIOC);

    enableTimerClock(TIM3);
    enableTimerClock(TIM4);

    enableUARTClock(UART4);
}
