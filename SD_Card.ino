

String delimitor = ",";

void initSD() {
  if (SD.begin(sdCSPin)) Serial.println("SD Card Initialized");
  else Serial.println("SD Card Initialization Failed");
}


boolean validateAccessSD(String key) {
  String line = "";
  char filename[accessKeys.length() + 1];
  accessKeys.toCharArray(filename, accessKeys.length() + 1);

  if (SD.exists(filename)) {
    accessKeysFile = SD.open(accessKeys, FILE_READ);
    if (accessKeysFile.available() <= 0) Serial.println("Access Keys File Error");
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
          //          Serial.println("MATCH");
          accessKeysFile.close();
          return true;
        }

        line = "";
      }
    }
    accessKeysFile.close();
  }
  else Serial.println("Access Keys File Not Found");
  return 0;
}


void writeLogSD(String _date, String _time, String _id) {
  entryLogFile = SD.open(entryLog, FILE_WRITE);
  if (entryLogFile) {
    entryLogFile.print(_date);
    entryLogFile.print(delimitor);
    entryLogFile.print(_time);
    entryLogFile.print(delimitor);
    entryLogFile.println(_id);
  }

  entryLogFile.close();

  Serial.print(_date);
  Serial.print(delimitor);
  Serial.print(_time);
  Serial.print(delimitor);
  Serial.println(_id);
}


void addAccessSD(String _key) {
  accessKeysFile = SD.open(accessKeys, FILE_READ);
  accessKeysFile.println(_key);
  accessKeysFile.close();
}




