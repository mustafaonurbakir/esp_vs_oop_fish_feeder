#include <Arduino.h>

class Led {
	private:
    	int pin;

  	public:
		Led(byte pin);
		void init();
		void on();
		void off();
		bool getStatus();
};