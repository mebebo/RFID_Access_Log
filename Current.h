#ifndef Current_h
#define Current_h

#include "Arduino.h"

class Current {
  public:
    Current(int _tag, int _pin);
    boolean isError();
    int tag;
    boolean broken;

  private:
    int pin;
    const static int currCalib = 512;
    const static int currThreshold = 2;

    int total;
    static const int numReadings = 10;
};

#endif
