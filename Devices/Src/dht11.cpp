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
}

void DHT11::processData() {

}