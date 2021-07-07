#include "TelegramOp.h"

TelegramOp::TelegramOp() {
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
}

Commands TelegramOp::checkMessage(){
  //if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    Commands com = OTHERS;

    while(numNewMessages) {
        _streamRef->println("got response");
        com = handleNewMessages(numNewMessages);
        numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
    return com;
  //}
}

// Handle what happens when you receive new messages
Commands TelegramOp::handleNewMessages(int numNewMessages) {
  _streamRef->println("handleNewMessages");
  _streamRef->println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Print the received message
    String text = bot.messages[i].text;
    _streamRef->println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control your outputs.\n\n";
      welcome += "/led_on to turn LED ON \n";
      welcome += "/led_off to turn LED OFF \n";
      welcome += "/state to request current LED state \n";
      welcome += "/feed_fish to turn the next hole \n";
      welcome += "/reset_feeder to turn the 0th hole \n";
      welcome += "/reset_timer to reset timer \n";
      welcome += "/get_remaining to get remaining time \n";
      welcome += "/get_hole_no to get current hole \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/led_on") {
      bot.sendMessage(chat_id, "LED state set to ON", "");
      return LED_ON;
    }
    
    if (text == "/led_off") {
      bot.sendMessage(chat_id, "LED state set to OFF", "");
      return LED_OFF;
    }
    
    if (text == "/state") {
      return LED_STATUS;
    }
    
    if (text == "/feed_fish") {
      bot.sendMessage(chat_id, "Fish feeder is going next hole...", "");
      return FEED_FISH;
    }
    
    if (text == "/get_hole_no") {
      return GET_HOLE_NO;
    }
    
    if (text == "/reset_feeder") {
      bot.sendMessage(chat_id, "Fish feeder is going 0th hole...", "");
      return RESET_FEEDER;
    }
    
    if (text == "/reset_timer") {
      bot.sendMessage(chat_id, "Timer is set to default time.", "");
      return RESET_TIMER;
    }
    
    if (text == "/get_remaining") {
      return GET_REMAINING;
    }
  }
}

void TelegramOp::setAnswer(Commands command, String msg) {
  switch (command){
    case LED_STATUS:
      bot.sendMessage(chat_id, "Led is " + msg, "");
      break;
    case GET_HOLE_NO:
      bot.sendMessage(chat_id, "Current hole of fish feeder is " + msg, "");
      break;
    case GET_REMAINING:
      bot.sendMessage(chat_id, "Remaining time is " + msg, "");
      break;
    default:
      break;
    }
}

