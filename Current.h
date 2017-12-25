#ifndef Current_h
#define Current_h

#include "Arduino.h"

class Current {
  public:
    Current(String _tag, int _pin);
    int readVal();
    boolean checkError();
    String tag;

  private:
    int pin;
    int currVal;
    int currCalib = 509;
    int currThreshold = 2;

    const int numReadings = 300;
};

#endif
