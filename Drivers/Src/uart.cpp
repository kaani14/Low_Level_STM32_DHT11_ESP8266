#include "uart.hpp"

UART::UART(USART_TypeDef* uart) : uart(uart) {
    // Constructor implementation
}

UART::~UART() {

}

void UART::setBaudrate(uint32_t baudRate) {

    disable();

    uint32_t pclk = SystemCoreClock;
    
    if (uart->CR1 & USART_CR1_OVER8) {
        uint32_t usartdiv = (2 * pclk) / baudRate;
        uart->BRR = (usartdiv & 0xFFF0) | ((usartdiv & 0x000F) >> 1);
    } else {
        uint32_t usartdiv = pclk / (baudRate);
        uart->BRR = usartdiv;
    }
}

void UART::transmit(const char *string) {

	while (*string){
		uart->TDR = (*string++);
		while (!(uart->ISR & USART_ISR_TXE));
	}
}

void UART::receive(void) {

}

bool UART::isTransmitComplete(void) {

    return true;
}

bool UART::isReceiveComplete(void) {

    return true;
}

void UART::enable(void) {
    uart->CR1 |= USART_CR1_UE;
}

void UART::disable(void) {
    uart->CR1 &= ~USART_CR1_UE;
}