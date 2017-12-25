

void validateEntry(String key) {
  digitalWrite(relay, HIGH);
  ledGreen();
  writeLogSD(rtc.getDateStr(), rtc.getTimeStr(), key);

  beepAccept();
}


void rejectEntry(String key) {
  static unsigned long redTime;
  static boolean 
  digitalWrite(relay, LOW);

  beepReject();
}

