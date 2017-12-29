
void grantAccess(String key) {
  digitalWrite(relay, HIGH);
  ledGreen();

  Serial.println("Access GRANTED");
  beepAccept();
    writeLogSD(rtc.getDateStr(), rtc.getTimeStr(), key);
}


void rejectAccess(String key) {
  Serial.println("Access DENIED");
  int rejectInterval = 500;

  digitalWrite(relay, LOW);
  ledRed();
  beepReject();
  delay(rejectInterval);
  ledYellow();
}

