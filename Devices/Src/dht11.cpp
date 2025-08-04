#include "dht11.hpp"
#include "timer.hpp"

Timer timer4(TIM4);

DHT11::DHT11(const DHT11Config& config)
    : config(config) {}

DHT11::~DHT11() {}

void DHT11::initTransmit() {
    timer4.enable();
	timer4.setPrescaler(config.outputComparePrescaler);
	timer4.setAutoReload(config.outputCompareARR);
	timer4.setCounter(0);
	timer4.setCompare(20);
	timer4.generateUpdateEvent();
	timer4.enableInterrupt();
	NVIC_EnableIRQ(TIM4_IRQn);
	timer4.outputCompareMode(Timer::OutputCompareMode::ACTIVE_ON_MATCH);
}

void DHT11::transmit() {
    timer4.startCounter();
}

void DHT11::initReceive() {
	timer4.disable();
	timer4.ResetTimer();
	timer4.setPrescaler(config.inputCapturePrescaler);
	timer4.setAutoReload(config.inputCaptureARR);
	timer4.generateUpdateEvent();
	
	timer4.configureInputChannel();

	timer4.setFilter(config.filter);
	timer4.inputCaptureEdgeDetection(Timer::InputCaptureEdgeDetection::RISING_EDGE);

	timer4.setInputCapturePrescaler(config.alternateEdgeDetection);
	timer4.enableInterrupt();
}

void DHT11::receive() {
	timer4.startCounter();
	readStart = true;
}

void DHT11::processData() {

	if (readStart == true){

		captureValue[edgeCount] = timer4.readCaptureValue();
		edgeCount = edgeCount+1;
		TIM4->CNT = 0;

		if (edgeCount == 42){

			for (int i = 2; i < edgeCount; i++){
				if (captureValue[i] > 1500){
					dhtReply[i-2] = 1;
				}
				else{
					dhtReply[i-2] = 0;
				}
			}

			for (int i = 0; i < 8; i++){
				humidityIntegral    |= (dhtReply[i]      << (7 - i));
				humidityDecimal     |= (dhtReply[i + 8]  << (7 - i));
				temperatureIntegral |= (dhtReply[i + 16] << (7 - i));
				temperatureDecimal  |= (dhtReply[i + 24] << (7 - i));
				checkSum            |= (dhtReply[i + 32] << (7 - i));
			}
		}
	}
}