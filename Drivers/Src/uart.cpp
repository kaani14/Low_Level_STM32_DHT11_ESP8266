#include "uart.hpp"
#include "system_stm32f7xx.h"

UART::UART(USART_TypeDef* uart) : uart(uart) {
    // Constructor implementation
}

UART::~UART() {

}

void UART::setBaudrate(uint32_t clock, uint32_t baudRate) {

    disable();
    
    if (uart->CR1 & USART_CR1_OVER8) {
        uint32_t usartdiv = (2 * clock) / baudRate;
        uart->BRR = (usartdiv & 0xFFF0) | ((usartdiv & 0x000F) >> 1);
    } else {
        uint32_t usartdiv = clock / (baudRate);
        uart->BRR = usartdiv;
    }
}

void UART::transmit(const char *string) {
	while (*string){
		uart->TDR = (*string++);
		while (!(uart->ISR & USART_ISR_TXE));
	}
}

bool UART::isTransmitComplete(void) {
    return (uart->ISR & USART_ISR_TC);
}

void UART::transmitEnable(void) {
    uart->CR1 |= USART_CR1_TE;
}

void UART::receive(void) {

}

bool UART::isReceiveReady(void) {
    return (uart->ISR & USART_ISR_RXNE);
}

void UART::receiverEnable(void) {
    uart->CR1 |= USART_CR1_RE;
}

void UART::receiveInterruptEnable(void) {
    uart->CR1 |= USART_CR1_RE | USART_CR1_RXNEIE;
}

void UART::receiveInterruptHandler(uint8_t* buffer, volatile int& counter) {
    buffer[counter] = uart->RDR;
    counter++;
}

void UART::enable(void) {
    uart->CR1 |= USART_CR1_UE;
}

void UART::disable(void) {
    uart->CR1 &= ~USART_CR1_UE;
}