#include "delay.hpp"
#include "timer.hpp"

Timer timer3(TIM3);

void initDelayTimer(){
    timer3.basicCounterMode();
    timer3.setPrescaler(999);
    timer3.setAutoReload(16);
    timer3.setCounter(0);
}

void delay(int milliseconds) {

    int delay_counter = 0;

    timer3.startCounter();
	while (delay_counter <= milliseconds){
    timer3.waitforUpdateInterrupt();
    timer3.clearUpdateInterruptFlag();

	delay_counter++;
    }
    delay_counter = 0;
}