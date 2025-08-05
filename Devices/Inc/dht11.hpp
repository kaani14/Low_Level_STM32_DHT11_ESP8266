#ifndef DHT11_HPP
#define DHT11_HPP

#include <cstdint>

struct DHT11Config {
    uint16_t outputCompareARR = 1000 - 1;
    uint16_t outputComparePrescaler = 16000 - 1;
    uint16_t inputCaptureARR = 0xFFFF;
    uint8_t filter = 8;
    uint16_t inputCapturePrescaler = 0;
    uint16_t alternateEdgeDetection = 0;
    uint16_t pin = 7;
};

class DHT11 {

    public:
        explicit DHT11(const DHT11Config& config = DHT11Config());
        ~DHT11();
        void initGPIO();
        void initTransmit();
        void transmit();
        void initReceive();
        void receive();
        void processData();

        uint8_t temperatureIntegral = 0;
        uint8_t temperatureDecimal = 0;
        uint8_t humidityIntegral = 0;
        uint8_t humidityDecimal = 0;
        uint8_t checkSum = 0;

    private:
        uint16_t filter = 0;
        volatile uint16_t captureValue[100];
        bool dhtReply[40];
        volatile int edgeCount = 0;
        bool readStart = false;
        DHT11Config config;
};

#endif // DHT11_HPP