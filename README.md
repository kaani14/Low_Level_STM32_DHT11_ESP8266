# Description

This project reads humidity data from a DHT11 sensor and sends it to ThingSpeak using HTTP requests. The system is built on an STM32F767ZI microcontroller with an ESP8266 Wi-Fi module.

The firmware is written in low-level C, and custom libraries were developed for each peripheral used in the project.


# File Structure

Drivers: Device Drivers and MCU Peripherals
Devices: Sensor and ESP Interfacing
Src: Main.cpp

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
