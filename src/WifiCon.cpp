#include "WifiCon.h"

WifiCon::WifiCon () {

}

wl_status_t WifiCon::connectWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    for (int i = 0; i < 5 && WiFi.status() != WL_CONNECTED; i++) {
        delay(1000);
        _streamRef->println("Connecting to WiFi..");
    }

    return WiFi.status();
}

wl_status_t WifiCon::getConnectionStatus(){
    return WiFi.status();
}

bool WifiCon::isInternetAvailable(){
    return WiFi.status() == WL_CONNECTED;
}