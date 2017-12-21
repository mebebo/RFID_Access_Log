

void validateEntry(String key) {
  digitalWrite(relay, HIGH);
  writeLogSD(rtc.getDateStr(), rtc.getTimeStr(), key);

}

