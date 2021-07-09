# Fish Feeder with ESP32 and Telegram

With this application, an automatic fish feeding system can be established.


https://user-images.githubusercontent.com/23248283/124842529-68ba6080-df98-11eb-9b17-76dc6a402db4.mp4


### Necessary equipment ###

- 3D printed feeder system (https://www.thingiverse.com/thing:2089866)
- Espressif ESP32 board
- Adafruit 0.92" 128x32 i2c OLED display
- 9 gr servo (need custom frame for model)
- power adaptor and cable

### To use ###

- Create a bot with botfather from Telegram.
- Take token from botfather
- Find chatId
- Fill Config.h file 

### Connections ###

| Servo         | ESP32         |
| ------------- | ------------- |
| Brown         | GND           |
| Red           | Vin           |
| Orange        | D13           |


| LCD           | ESP32         |
| ------------- | ------------- |
| GND           | GND           |
| VCC           | 3v3           |
| SCL           | D22           |
| SDA           | D21           |



.
.
.

![image](https://user-images.githubusercontent.com/23248283/124842089-76bbb180-df97-11eb-81ff-67e5cf2468c9.png)
.
.
.

![image](https://user-images.githubusercontent.com/23248283/124842111-85a26400-df97-11eb-8391-683524c215ad.png)
