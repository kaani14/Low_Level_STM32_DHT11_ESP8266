#include "stm32f7xx.h"

void initSystem(void) {
    // enable FPU
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));
}
