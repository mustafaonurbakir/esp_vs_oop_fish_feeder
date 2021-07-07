#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "Config.h"


class WifiCon {

    private:
        Stream *_streamRef;
    
    public:
        WifiCon();
        wl_status_t connectWifi();
        wl_status_t getConnectionStatus();
        bool isInternetAvailable();

        void setSerial(Stream *streamObject){
            _streamRef=streamObject;
        }
        void sendText(char *someText){
            _streamRef->println(someText);
        }
};