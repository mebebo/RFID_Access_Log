#ifndef Current_h
#define Current_h

#include "Arduino.h"

class Current {
  public:
    Current(int _tag, int _pin);
    boolean isError();
    void state(boolean out);
    int tag;

  private:
    int pin;
    const static int currCalib = 510;
    const static int currThreshold = 3;

    boolean broken = false;

    int total;
    static const int numReadings = 10;
};

#endif
