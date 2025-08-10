#ifndef GPIO_HPP
#define GPIO_HPP

#include "stm32f7xx.h"

class GPIO {
    public:
        enum GPIOMode : uint32_t {
            INPUT = 0x0U,
            OUTPUT = 0x1U,
            ALTERNATE = 0x2U,
            ANALOG = 0x3U
        };

        enum GPIOPullUpDown : uint32_t {
            NONE = 0x0U,
            PULL_UP = 0x1U,
            PULL_DOWN = 0x2U
        };

        enum GPIOAlternateFunction : uint32_t {
            AF0 = 0x0U,
            AF1 = 0x1U,
            AF2 = 0x2U,
            AF3 = 0x3U,
            AF4 = 0x4U,
            AF5 = 0x5U,
            AF6 = 0x6U,
            AF7 = 0x7U,
            AF8 = 0x8U,
            AF9 = 0x9U,
            AF10 = 0xAU,
            AF11 = 0xBU,
            AF12 = 0xCU,
            AF13 = 0xDU,
            AF14 = 0xEU,
            AF15 = 0xFU
        };

        enum GPIOSpeed : uint32_t {
            LOW = 0x0U,
            MEDIUM = 0x1U,
            HIGH = 0x2U,
            VERY_HIGH = 0x3U
        };

        GPIO(GPIO_TypeDef* gpioPort);
        ~GPIO();
        void setMode(uint16_t pin, GPIOMode mode);
        void setAlternateFunction(uint16_t pin, GPIOAlternateFunction alternateFunction);
        void setPullUpDown(uint16_t pin, GPIOPullUpDown pullUpDown);
        void setSpeed(uint16_t pin, GPIOSpeed speed);
    private:
        GPIO_TypeDef* gpio;
};
#endif // GPIO_HPP