# Description

Sends Humidity data from DHT11 using HTTP request to Thingspeak using ESP8266 and STM32F767ZI. The project has low-level programming, and libraries have been created for each peripheral used in the project.

# Connections

**STM32F767ZI**  | **ESP-8266**
------------- | -------------
PC11  | Tx
PA0  | Rx
3.3V  | EN / CH_PD
PB7 | DHT11

# Implementation

## DHT11

The Output Compare of the timer peripheral in PWM mode is used to send the Wake Up signal. Then the pin changes its function to input capture, where it records the length of each pulse. This is collected in an array, and humidity and temperature are computed.

## ESP-8266

AT Commands are sent via UART to upload the humidity data to the ThingSpeak platform. 

## Sending Data to ThingSpeak

The data is sent to ThingSpeak periodically. A timer interrupt is used to achieve that.

# Future Updates

- Checksum for DHT11
- Addition of more sensors
- Sleep Mode
- Further power optimisation
