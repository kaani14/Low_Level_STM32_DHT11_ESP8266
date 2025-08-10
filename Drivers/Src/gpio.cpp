#include "gpio.hpp"

GPIO::GPIO(GPIO_TypeDef* gpioPort) : gpio(gpioPort) {}

GPIO::~GPIO() {}

void GPIO::setMode(uint16_t pin, GPIOMode mode) {
    gpio->MODER &= ~(0x3U << (2 * pin));
    gpio->MODER |= (static_cast<uint32_t>(mode) << (2 * pin));
}

void GPIO::setAlternateFunction(uint16_t pin, GPIOAlternateFunction alternateFunction) {
    uint32_t afrIndex = pin / 8;
    uint32_t afrOffset = (pin % 8) * 4;
    
    gpio->AFR[afrIndex] &= ~(0xFU << afrOffset);
    gpio->AFR[afrIndex] |= (static_cast<uint32_t>(alternateFunction) << afrOffset);
}

void GPIO::setSpeed(uint16_t pin, GPIOSpeed speed) {
    gpio->OSPEEDR &= ~(0x3U << (2 * pin));
    gpio->OSPEEDR |= (static_cast<uint32_t>(speed) << (2 * pin));
}

void GPIO::setPullUpDown(uint16_t pin, GPIOPullUpDown pullUpDown) {
    gpio->PUPDR &= ~(0x3U << (2 * pin));
    gpio->PUPDR |= (static_cast<uint32_t>(pullUpDown) << (2 * pin)); 
}