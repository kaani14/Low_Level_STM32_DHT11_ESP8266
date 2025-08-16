#ifndef UART_HPP
#define UART_HPP

#include "stm32f7xx.h"

class UART {
public:
    UART(USART_TypeDef* uart);
    ~UART();
    
    void enable(void);
    void disable(void);
    void setBaudrate(uint32_t clock, uint32_t baudRate);

    /*
    Transmit
    */
    void transmit(const char *string);
    bool isTransmitComplete(void);
    void transmitEnable(void);

    /*
    Receive
    */
    void receive(void);
    bool isReceiveReady(void);
    void receiverEnable(void);
    void receiveInterruptEnable(void);
    void receiveInterruptHandler(uint8_t* buffer, volatile int& counter);

private:
    USART_TypeDef* uart;
};

#endif // UART_HPP