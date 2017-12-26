#include "Arduino.h"
#include "Current.h"

Current::Current(String _tag, int _pin) {
  tag = _tag;
  pin = _pin;
}

int Current::readVal() {
  currVal = analogRead(pin);
  return currVal;
}

boolean Current::checkError() {
  // Take average of sampled data
  int total = 0;
  for (int i = 0; i < numReadings; i++) {
    total += analogRead(pin);
  }
  int average = int(total / numReadings);

  // Check against threshold
  currVal = average - currCalib;
  if (currVal >= currThreshold) return false;
  else if (currVal < currThreshold) {
    return true;
  }
}














