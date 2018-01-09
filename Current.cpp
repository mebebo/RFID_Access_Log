#include "Arduino.h"
#include "Current.h"

Current::Current(int _tag, int _pin) {
  tag = _tag;
  pin = _pin;
}

boolean Current::isError() {

  int total = 0;
  for (int i = 0; i < numReadings; i++) {
    int curVal = analogRead(pin) - currCalib;
    total += curVal;
  }

  float average = total / numReadings;

  // Check against threshold
  if (average <= currThreshold && millis() > 3000) return true;
  else return false;
}


void Current::state(boolean out) {
  broken = out;
}












