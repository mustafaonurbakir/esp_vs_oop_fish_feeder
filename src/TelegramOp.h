#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   
#include <ArduinoJson.h>
#include "Commands.h"
#include "Config.h"


class TelegramOp {
    WiFiClientSecure client;
    UniversalTelegramBot bot = UniversalTelegramBot(BOTtoken, client);

    // Checks for new messages every 1 second.
    int botRequestDelay = 1000;
    unsigned long lastTimeBotRan;

    private:
        Stream *_streamRef;
        String chat_id;
    public:
        TelegramOp();
        Commands handleNewMessages(int numNewMessages);
        Commands checkMessage();
        void setAnswer(Commands command, String msg);

        void setSerial(Stream *streamObject){
            _streamRef=streamObject;
        }
        void sendText(char *someText){
            _streamRef->println(someText);
        }
};