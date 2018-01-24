

void checkMalfunction(Current lamp) {

  if (lamp.isError() && lamp.broken == false) {
    changeLampStat(lamp, true);
    reportMalfunction(vehicleID, "00000", rtc.getDateStr(), rtc.getTimeStr(), lamp);
    Serial.println("CALISMIY");
  }

  else if (!lamp.isError() && lamp.broken == true) {
    changeLampStat(lamp, false);
    reportFix(vehicleID, "00000", rtc.getDateStr(), rtc.getTimeStr(), lamp);
    Serial.println("DUZELDI");
  }
}

void reportMalfunction(String _vehicle, String _sessionID, String _date, String _time, Current lamp) {

  Serial.print(_vehicle);
  Serial.print(delimitor);
  Serial.print(_sessionID);
  Serial.print(delimitor);
  Serial.print(_date);
  Serial.print(delimitor);
  Serial.print(_time);
  Serial.print(delimitor);
  Serial.print(lamp.tag);
  Serial.print(delimitor);
  Serial.println(F("$ERR"));
}

void reportFix (String _vehicle, String _sessionID, String _date, String _time, Current lamp) {

  Serial.print(_vehicle);
  Serial.print(delimitor);
  Serial.print(_sessionID);
  Serial.print(delimitor);
  Serial.print(_date);
  Serial.print(delimitor);
  Serial.print(_time);
  Serial.print(delimitor);
  Serial.print(lamp.tag);
  Serial.print(delimitor);
  Serial.println(F("$FIX"));
}


void changeLampStat(Current lamp, boolean broke) {
  switch (lamp.tag) {
    case 1:
      headlight.broken = broke;
      break;
    case 2:
      stoplight.broken = broke;
      break;
    case 3:
      beacon.broken = broke;
      break;
      //      case 4:
      //        signalL.broken = broke;
      //        break;
      //      case 5:
      //        signalR.broken = broke;
      //        break;
  }
}

