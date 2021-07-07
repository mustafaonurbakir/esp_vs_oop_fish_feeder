#include "Led.h"

Led::Led(byte pin) {
	this->pin = pin;
	init();
}

void Led::init() {
	Serial.println("led initializer");
	pinMode(pin, OUTPUT);
	off();
}

void Led::on() {
  	digitalWrite(pin, HIGH);
}

void Led::off() {
  	digitalWrite(pin, LOW);
}

bool Led::getStatus() {
  	return digitalRead(pin);
}

