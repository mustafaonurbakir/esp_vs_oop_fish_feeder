#include "Arduino.h"
#include <Servo.h>
#include <EEPROM.h>

#define HOLE_NO_ADDRESS 0
#define ONE_STEP_ANGLE 22
#define MAX_HOLE 8

class FishFeeder {
    Servo servoM;

    private:
        int currentHole = 0;
        void smoothRun(int from_pos, int to_pos);
        void saveCurrentHole();

    public:
        void setup(int pin);
        void nextHole();
        void goToHole(int val);
        void resetDevice();
        int getHoleNo();
        void setHoleNo(int val);
};
