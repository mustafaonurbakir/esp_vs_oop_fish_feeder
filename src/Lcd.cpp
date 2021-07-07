#include "Lcd.h"

void Lcd::setup(Adafruit_SSD1306 display) {
    this->myDisplay = display;
    init();
}

void Lcd::init() {
    myDisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32);
    myDisplay.display();
    myDisplay.clearDisplay();
    myDisplay.display();
    }

void Lcd::clearDisplay(){
    myDisplay.clearDisplay();
}

void Lcd::showHoleInfo() {
    myDisplay.setTextColor(WHITE);
    myDisplay.setTextSize(2);
    myDisplay.setCursor(1,14);
    myDisplay.println(holeNo);
}

void Lcd::showOnOffInfo() {
    //myDisplay.setTextColor(WHITE);
    //myDisplay.setTextSize(2);
    //myDisplay.setCursor(1,12);
    //myDisplay.println(ledStatus? "ON": "OFF");
    
    unsigned char sun_icon16x16[] =
    {
        0b00000000, 0b00000000, //                 
        0b00000011, 0b11100000, //       #####     
        0b00000100, 0b00010000, //      #     #    
        0b00001000, 0b00001000, //     #       #   
        0b00010000, 0b00000100, //    #         #  
        0b00010000, 0b00000100, //    #         #  
        0b00010000, 0b00000100, //    #         #  
        0b00010000, 0b00000100, //    #         #  
        0b00010000, 0b00000100, //    #         #  
        0b00001000, 0b00001000, //     #       #   
        0b00000100, 0b00010000, //      #     #    
        0b00000011, 0b11100000, //       #####     
        0b00000010, 0b00100000, //       #   #     
        0b00000011, 0b11100000, //       #####     
        0b00000010, 0b00100000, //       #   #     
        0b00000011, 0b11100000, //       #####   
    };
    unsigned char empyt_icon[] =
    {
        0b00000000, 0b00000000, // 
        0b00000000, 0b00000000, // 
        0b00000000, 0b00000000, // 
        0b00000000, 0b00000000, // 
        0b00000000, 0b00000000, // 
        0b00000000, 0b00000000, // 
        0b00000000, 0b00000000, // 
        0b00000000, 0b00000000, // 
        0b00000000, 0b00000000, // 
        0b00000000, 0b00000000, // 
        0b00000000, 0b00000000, // 
        0b00000000, 0b00000000, // 
        0b00000000, 0b00000000, // 
        0b00000000, 0b00000000, // 
        0b00000000, 0b00000000, // 
        0b00000000, 0b00000000, // 
    };

    myDisplay.drawBitmap(112, 16, ledStatus? sun_icon16x16 : empyt_icon, 16, 16, 1);
}

void Lcd::showConnectionInfo() {
    myDisplay.println("Connect...");
}


void Lcd::showCounter() {        
    myDisplay.setTextColor(WHITE);
    myDisplay.setTextSize(2);
    myDisplay.setCursor(60,14);
    myDisplay.println(timerVal);
}

void Lcd::updateScreen(){
    clearDisplay();
    printMainTexts(true, true);
    showCounter();
    showOnOffInfo();
    showHoleInfo();

    myDisplay.display();
}


void Lcd::printMainTexts(boolean ledStatus, boolean timerStatus){
    if(ledStatus){
        myDisplay.setTextColor(WHITE);
        myDisplay.setTextSize(1);
        myDisplay.setCursor(1,0);
        myDisplay.println("Hole");
    }

    if(timerStatus){
        myDisplay.setTextColor(WHITE);
        myDisplay.setTextSize(1);
        myDisplay.setCursor(60,0);
        myDisplay.println("Timer");
    }

    static unsigned char wifi1_icon16x16[] =
    {
        0b00000000, 0b00000000, //                 
        0b00000111, 0b11100000, //      ######     
        0b00011111, 0b11111000, //    ##########   
        0b00111111, 0b11111100, //   ############  
        0b01110000, 0b00001110, //  ###        ### 
        0b01100111, 0b11100110, //  ##  ######  ## 
        0b00001111, 0b11110000, //     ########    
        0b00011000, 0b00011000, //    ##      ##   
        0b00000011, 0b11000000, //       ####      
        0b00000111, 0b11100000, //      ######     
        0b00000100, 0b00100000, //      #    #     
        0b00000001, 0b10000000, //        ##       
        0b00000001, 0b10000000, //        ##       
        0b00000000, 0b00000000, //                 
        0b00000000, 0b00000000, //                 
        0b00000000, 0b00000000, //                 
    };

    myDisplay.drawBitmap(112, 0, wifi1_icon16x16, 16, 16, 1);

}


