#include <Arduino.h>
#include <EEPROM.h>
#include "Led.h"
#include "Lcd.h"
#include "WifiCon.h"
#include "TelegramOp.h"
#include "FishFeeder.h"

#define LED_1_PIN 2
#define FISH_FEEDER_PIN 13
#define REMAINING_TIME_EEPROM_ADDRESS 1
#define INITIALIZE_BEFORE_EEPROM_ADDRESS 2
#define FEED_ROUTINE 10 // minutes


// Objects and variables
Led led1(LED_1_PIN);
Lcd *Lcd::instance = 0;
Lcd *display = display->getInstance(); //Singleton for Display
WifiCon wifiCon;
TelegramOp telegramOp;
FishFeeder fishFeeder;

wl_status_t wifiStatus = WL_DISCONNECTED;
bool netAvailable = false;

//timer
unsigned long lastSecondControlTime = 0;
unsigned long lastMinuteControlTime = 0;
unsigned long lastFeedControlTime = 0;
int remainingFeedingTime = FEED_ROUTINE;


void resetTimer() {
	lastFeedControlTime = lastMinuteControlTime = millis();
	remainingFeedingTime = FEED_ROUTINE;
	display->setTimerVal(remainingFeedingTime);
}

void setup() {
	Serial.begin(115200);

	//EEPROM
	EEPROM.begin(12);
	remainingFeedingTime = EEPROM.read(REMAINING_TIME_EEPROM_ADDRESS);
  	if(remainingFeedingTime < 0 || remainingFeedingTime > FEED_ROUTINE) {
    	remainingFeedingTime = FEED_ROUTINE;
    	EEPROM.write(REMAINING_TIME_EEPROM_ADDRESS, remainingFeedingTime);
		EEPROM.commit();
  	}

	// display
	display->setSerial(&Serial);
	Adafruit_SSD1306 myDisplay(OLED_RESET);
	display->setup(myDisplay);
	display->setTimerVal(remainingFeedingTime);

	//wifi
	wifiCon.setSerial(&Serial);
	wifiStatus = wifiCon.connectWifi();
	netAvailable = wifiCon.isInternetAvailable();
	
	//telegram
	telegramOp.setSerial(&Serial);

	//fish feeder
	fishFeeder.setup(FISH_FEEDER_PIN);
	display->setHoleNo(fishFeeder.getHoleNo());
}

void loop() {
	if(millis() - lastSecondControlTime > 1000){
		lastSecondControlTime = millis();
		Commands com = telegramOp.checkMessage();

		switch (com){
			case LED_ON:
				led1.on();
				display->setLedStatus(true);
				break;
			case LED_OFF:
				led1.off();
				display->setLedStatus(false);
				break;
			case LED_STATUS:
				telegramOp.setAnswer(LED_STATUS, led1.getStatus() ? "ON": "OFF");
				break;
			case FEED_FISH:
				fishFeeder.nextHole();
				display->setHoleNo(fishFeeder.getHoleNo());
				resetTimer();
				break;
			case GET_HOLE_NO:
				telegramOp.setAnswer(GET_HOLE_NO, String(fishFeeder.getHoleNo()));
				break;
			case RESET_FEEDER:
				fishFeeder.resetDevice();
				display->setHoleNo(fishFeeder.getHoleNo());
				EEPROM.commit();
				resetTimer();
				break;
			case RESET_TIMER:
				resetTimer();
				break;
			case GET_REMAINING:
				telegramOp.setAnswer(GET_REMAINING, String(remainingFeedingTime));
				break;
			default:
				break;
		}
	}

	//every minute
	if(millis() - lastMinuteControlTime > 1000 * 60) {
		lastMinuteControlTime = millis();
		remainingFeedingTime-- ;
		EEPROM.write(REMAINING_TIME_EEPROM_ADDRESS, remainingFeedingTime);
		EEPROM.commit();
	  	display->setTimerVal(remainingFeedingTime);
	}

	// every feed
	if(millis() - lastFeedControlTime > 1000 * 60 * FEED_ROUTINE) {
		lastFeedControlTime = millis();
		fishFeeder.nextHole();
		resetTimer();
		display->setHoleNo(fishFeeder.getHoleNo());
		Serial.println("Feeding...");
		Serial.println("New hole no: " + String(fishFeeder.getHoleNo()));
	}
}

