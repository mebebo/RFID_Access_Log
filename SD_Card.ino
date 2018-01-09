


void initSD() {
  if (SD.begin(sdCSPin)) Serial.println(F("SD Card Initialized"));
  else Serial.println(F("SD Card Initialization Failed"));
}

boolean validateAccessSD(String key) {
  String line = "";
  line.reserve(10);
  Serial.println(F("Stored Access Keys: "));

  if (SD.exists(accessKeys)) {
    accessKeysFile = SD.open(accessKeys, FILE_READ);
    if (accessKeysFile.available() <= 0) Serial.println(F("Access Keys File Error"));
    while (accessKeysFile.available()) {
      char ltr = accessKeysFile.read();

      if (ltr != '\n') {
        line += ltr;
      }
      else if (ltr == '\n') {
        line = line.substring(0, line.length() - 1);
        Serial.println(line);

        if (key == line) {
          // ID MATCH HERE ====================================================================
          //          Serial.println(F("MATCH"));
          accessKeysFile.close();
          return true;
        }

        line = "";
      }
    }
    accessKeysFile.close();
  }
  else Serial.println(F("Access Keys File Not Found"));
  return 0;
}


boolean validateLogOutSD(String key) {
  if (currUserID == key) {
    return true;
  }
  else return 0;
}


void writeLogSD(String _vehicle, String _user, String _date, String _time, boolean _start) {
  entryLogFile = SD.open(entryLog, FILE_WRITE);

  entryLogFile.print(_vehicle);
  entryLogFile.print(delimitor);
  entryLogFile.print(_user);
  entryLogFile.print(delimitor);
  entryLogFile.print(_date);
  entryLogFile.print(delimitor);
  entryLogFile.print(_time);
  entryLogFile.print(delimitor);
  if (_start) entryLogFile.println(_start); // CHANGE THESE TO LOG IN AND LOG OUT ENTRY INDICATORS TO HTTP POST =======================================================
  else if (!_start) entryLogFile.println(_start);

  entryLogFile.close();

  Serial.print(_vehicle);
  Serial.print(delimitor);
  Serial.print(_user);
  Serial.print(delimitor);
  Serial.print(_date);
  Serial.print(delimitor);
  Serial.print(_time);
  Serial.print(delimitor);
  Serial.print(_start);
  Serial.print(delimitor);
  Serial.println(F("$LOG"));
}


//void updateAccessKeys(String newKeys) {
//  if (SD.exists(tempLog)) {
//    SD.remove(tempLog);
//    tempLogFile = SD.open(tempLog, FILE_WRITE);
//
//  }
//  if (SD.exists(tempKeys)) {
//    tempKeysFile = SD.open(tempKeys, FILE_WRITE);
//  }
//}
//
//
//void writeTempSD(File tempFile, char temp[], String input) {
//  if (SD.exists(temp)) {
//    SD.remove(temp);
//  }
//  tempFile = SD.open(temp, FILE_WRITE);
//
//  tempFile.print(input);
//
//  tempFile.close();
//
//}
//
//
//void switchTemp(char file[], File tempFile, char temp[]) {
//  if (SD.exists(temp)) {
//    SD.remove(file);
//    tempFile = SD.open(temp, FILE_WRITE);
//    tempFile.rename(SD.vwd(), file);
//    tempFile.close();
//  }
//}

