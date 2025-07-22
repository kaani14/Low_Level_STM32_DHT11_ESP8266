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
};

class DHT11 {

    public:
        explicit DHT11(const DHT11Config& config = DHT11Config());
        ~DHT11();
        void initTransmit();
        void transmit();
        void initReceive();
        void receive();
        void processData();

    private:
        uint16_t filter = 0;
        DHT11Config config;
};

#endif // DHT11_HPP