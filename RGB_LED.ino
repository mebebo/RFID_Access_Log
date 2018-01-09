


void initLedPins(int r, int g, int b) {
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  ledYellow();
}

void ledRed() {
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
}

void ledGreen() {
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, LOW);
}

void ledYellow() {
  analogWrite(ledR, 130);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, LOW);
}

void ledOff() {
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
}


