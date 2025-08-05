#ifndef DELAY_HPP
#define DELAY_HPP

#include "stm32f7xx.h"

void initDelayTimer(void);
void delay(int milliseconds);

#endif // DELAY_HPP