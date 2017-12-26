int rejectInterval = 750;

void validateEntry(String key) {
  digitalWrite(relay, HIGH);
  ledGreen();

  Serial.println("Access GRANTED");
  beepAccept();
  writeLogSD(rtc.getDateStr(), rtc.getTimeStr(), key);
}


void rejectEntry(String key) {
  Serial.println("Access DENIED");

  unsigned long redTime = millis() + rejectInterval;
  while (redTime <= millis()) {
    ledRed();
    digitalWrite(relay, LOW);
    beepReject();
  }
  ledYellow();
}

