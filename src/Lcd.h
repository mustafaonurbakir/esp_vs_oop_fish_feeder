#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 32  
#define LOGO16_GLCD_WIDTH  128 



class Lcd {
  static Lcd *instance;

  private:
    Adafruit_SSD1306 myDisplay;
    Stream *_streamRef;
    bool ledStatus = false;
    int timerVal = 0;
    int holeNo = 0;
    void updateScreen();
    void showOnOffInfo();
    void showHoleInfo();
    void showCounter();
    void printMainTexts(boolean lcdStatus, boolean timerStatus);

  public:
    static Lcd *getInstance() {
        if (!instance){
            instance = new Lcd;
        }
        return instance;
    }
    void init();
    void setup(Adafruit_SSD1306 myDisplay);
    void showConnectionInfo();
    void clearDisplay();
    void setTimerVal(int val) {
      timerVal = val;
      updateScreen();
    }
    void setLedStatus(bool val) {
      ledStatus = val;
      updateScreen();
    }
    void setHoleNo(int val) {
      holeNo = val;
      updateScreen();
    }
    

    void setSerial(Stream *streamObject){
      _streamRef=streamObject;
    }
    void sendText(char *someText){
      _streamRef->println(someText);
    }
};