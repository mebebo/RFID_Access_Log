// Greenwich Time

void setRTCTime(String t) {
  // setRTCTime("hh:mm:ss")
  int h, m, s;

  h = t.toInt();
  t = t.substring(t.indexOf(':') + 1);
  m = t.toInt();
  t = t.substring(t.indexOf(':') + 1);
  s = t.toInt();

  rtc.setTime(h, m, s);
}

void setRTCDate(String t) {
  // setRTCDate("Mon dd yyyy")
  String m;
  int d, y;

  m = t.substring(0, t.indexOf(" "));
  t = t.substring(t.indexOf(" ") + 1);
  t.trim();
  d = t.toInt();
  t = t.substring(t.indexOf(" ") + 1);
  y = t.toInt();

  rtc.setDate(d, monthStrNo(m), y);
}

//void formatTime(String t) {
//// Current time format: 00:19:59
//// Current date format: 05.01.2021
//// Output date time format: "2018-01-06 19:20:06.125254"
//
//}


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

