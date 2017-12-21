// SD MODULE
#include <SPI.h>
#include <SD.h>
File accessKeysFile;
File entryLogFile;
String accessKeys = "keys.txt";
String entryLog = "entryLog.txt";

String delimitor = ",";

void initSD() {
  if (SD.begin()) Serial.println("SD Card Initialized");
  else Serial.println("SD Card Initialization Failed");
}


boolean validateAccessSD(String key) {
  String line = "";

  if (SD.exists(accessKeys)) {
    accessKeysFile = SD.open(accessKeys, FILE_READ);

    while (accessKeysFile.available()) {
      char ltr = accessKeysFile.read();

      if (ltr != '\n') {
        line += ltr;
      }
      else if (ltr == '\n') {
        line = line.substring(0, line.length() - 1);
        Serial.println(line);

        if (line == key) {
          // ID MATCH HERE ====================================================================
          Serial.println("Access GRANTED");
          accessKeysFile.close();

          return true;
        }
        line = "";
      }

      //      String line = accessKeysFile.readStringUntil('\n')+ "\0";
      //
      //      Serial.println(line);
      //      Serial.println(line == key);
      //
      //      if (line == key) {
      //        Serial.println("Access GRANTED");
      //        accessKeysFile.close();
      //        return true;
      //      }


      //      char ltr = accessKeysFile.read();
      //
      //      if (ltr != '\n') {
      //        line += ltr;
      //      }
      //      else if (ltr == '\n') {
      //        line += '\0';
      //        Serial.println(line);
      //        if (line == "fishes") {
      //          // ID MATCH HERE ====================================================================
      //          Serial.println("Access GRANTED");
      //          accessKeysFile.close();
      //
      //          return true;
      //        }
      //        line = "";
      //      }
    }
    Serial.println("Access DENIED");
    accessKeysFile.close();
  }
  else Serial.println("Access Keys File Not Found");
  return false;
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


