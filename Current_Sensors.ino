boolean brokenBeacon = false;


void checkMalfunction(Current lamp) {
  if (lamp.isError() && !brokenBeacon) {
    brokenBeacon = true;
    reportMalfunction("6", "00000", "0131313", "25525", lamp);
    //       reportFix("6", "00000", "0131313", "25525", lamp);
    Serial.println("CALISMIY");
  }

  else if (!lamp.isError() && brokenBeacon) {
    brokenBeacon = false;
    reportFix("6", "00000", "0131313", "25525", lamp);
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


