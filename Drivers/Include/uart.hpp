#ifndef UART_HPP
#define UART_HPP

#include "stm32f7xx.h"

class UART {
public:
    UART(USART_TypeDef* uart);
    ~UART();

    void setBaudrate(uint32_t baudRate);
    void transmit(const char *string);
    void receive(void);
    bool isTransmitComplete(void);
    bool isReceiveComplete(void);
    void enable(void);
    void disable(void);

private:
    USART_TypeDef* uart;
};

#endif // UART_HPP