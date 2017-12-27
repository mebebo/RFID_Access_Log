

void initRFID() {
  rfid.PCD_Init(rfidCSPin, rfidRstPin);
}

String getUID() {
  if (!rfid.PICC_ReadCardSerial()) return;
  String uid = ByteConvert::arrayToString(rfid.uid.size, rfid.uid.uidByte);
  uid = uid.substring(0, uid.length());

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  return uid;
}


















