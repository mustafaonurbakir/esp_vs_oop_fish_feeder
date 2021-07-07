#include "FishFeeder.h"

void FishFeeder::setup(int pin) {
	  servoM.attach(pin);

    currentHole = EEPROM.read(HOLE_NO_ADDRESS);
  	if(currentHole < 0 || currentHole > MAX_HOLE) {
        setHoleNo(0);
  	}
    setHoleNo(currentHole);
}

void FishFeeder::nextHole() {
    if (currentHole >= MAX_HOLE){
        smoothRun(currentHole, 0);
        setHoleNo(0);
    } else {
        smoothRun(currentHole, currentHole+1);
        setHoleNo(currentHole+1);
	  }
}

void FishFeeder::goToHole(int val) {
	if(val > MAX_HOLE) {
		smoothRun(currentHole, MAX_HOLE);
    setHoleNo(MAX_HOLE);
	} else {
		smoothRun(currentHole, val);
    setHoleNo(val);
	}
}

void FishFeeder::resetDevice() {
	smoothRun(currentHole, 0);
	setHoleNo(0);
}

void FishFeeder::smoothRun(int from_pos, int to_pos){
  int angle_begin = from_pos * ONE_STEP_ANGLE;
  int angle_end = angle_begin + (to_pos - from_pos) * ONE_STEP_ANGLE;

  if(angle_begin > angle_end) {
    for(; angle_begin > angle_end; angle_begin--) {
      servoM.write(angle_begin);
      delay(10);
    }
  } else {
    for(; angle_begin < angle_end; angle_begin++) {
      servoM.write(angle_begin);
      delay(10);
    }
  }

}

void FishFeeder::saveCurrentHole() {
    EEPROM.write(HOLE_NO_ADDRESS, currentHole);
}

int FishFeeder::getHoleNo() {
	return currentHole;
}

void FishFeeder::setHoleNo(int val) {
    currentHole = val;
    EEPROM.write(HOLE_NO_ADDRESS, val);
    EEPROM.commit();
}