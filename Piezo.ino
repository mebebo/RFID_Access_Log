int beepInterval = 80;

void beepAccept() {
  tone(piezo, 523);
  delay(beepInterval);
  tone(piezo, 784);
  delay(beepInterval * 2);
  noTone(piezo);
}

void beepReject() {
  tone(piezo, 784);
  delay(beepInterval);
  tone(piezo, 523);
  delay(beepInterval * 2);
  noTone(piezo);
}

void beepAlert() {
  tone(piezo, 784);
  delay(beepInterval);
  noTone(piezo);
  delay(beepInterval);
  tone(piezo, 784);
  delay(beepInterval);
  noTone(piezo);
  delay(beepInterval);
  tone(piezo, 784);
  delay(beepInterval);
  noTone(piezo);
}



