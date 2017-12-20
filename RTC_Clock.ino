#include <DS1302.h>

int rsPin = 2, datPin = 3, clkPin = 4;
DS1302 rtc(rsPin, datPin, clkPin);



void setRTCTime(String t) {
  // setRTCTime("hh:mm:ss")
  int h, m, s;

  h = t.toInt();
  t = t.substring(t.indexOf(':') + 1);
  Serial.println(t);
  m = t.toInt();
  t = t.substring(t.indexOf(':') + 1);
  s = t.toInt();

  rtc.setTime(h, m, s);
}

void setRTCDate(String t) {
  // setRTCDate("Mon dd yy")

  String m;
  int d, y;

  m = t.substring(0, t.indexOf(" "));
  t = t.substring(t.indexOf(" ") + 1);
  d = t.toInt();
  t = t.substring(t.indexOf(" ") + 1);
  y = t.toInt();

  rtc.setDate(d, monthStrNo(m), y);
}


int monthStrNo(String months) {
  if (months == "Jan") return 1;
  else if (months == "Feb") return 2;
  else if (months == "Mar") return 3;
  else if (months == "Apr") return 4;
  else if (months == "May") return 5;
  else if (months == "Jun") return 6;
  else if (months == "Jul") return 7;
  else if (months == "Aug") return 8;
  else if (months == "Sep") return 9;
  else if (months == "Oct") return 10;
  else if (months == "Nov") return 11;
  else if (months == "Dec") return 12;
  else return 0;
}

