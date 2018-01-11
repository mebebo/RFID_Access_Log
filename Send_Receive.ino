void usbConnect() {
  while (Serial.available() <= 0) {
    Serial.print('A');
    delay(150);
  }
}


void logIn(String key) {
  digitalWrite(relay, HIGH);
  ledGreen();
  loggedIn = true;
  currUserID = key;

  beepAccept();
  writeLogSD(vehicleID, key, rtc.getDateStr(), rtc.getTimeStr(), true);
  //  Serial.println(F("Access GRANTED"));
}


void rejectAccess(String key) {
  //  Serial.println(F("Access DENIED"));
  int rejectInterval = 500;
  loggedIn = false;

  digitalWrite(relay, LOW);
  ledRed();
  beepReject();
  delay(rejectInterval);
  ledYellow();
}


void logOut(String key) {
  // digitalWrite(relay, LOW);        WHAT HAPPENS TO THE RELAY SWITCH???????????????
  loggedIn = false;
  ledYellow();

  beepReject();   // NEW BEEP OUT SOUND
  writeLogSD(vehicleID, key, rtc.getDateStr(), rtc.getTimeStr(), false);
  currUserID = "";
}

