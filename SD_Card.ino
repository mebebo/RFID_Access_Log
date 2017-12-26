// SD MODULE
#include <SPI.h>
#include <SD.h>
File accessKeysFile;
File entryLogFile;
String accessKeys = "keys.txt";
String entryLog = "entryLog.txt";

String delimitor = ",";

void initSD() {
  if (SD.begin(csPinSD)) Serial.println("SD Card Initialized");
  else Serial.println("SD Card Initialization Failed");
}


boolean validateAccessSD(String key) {
  String line = "";
//  String reset = "reset";
//  reset = reset.substring(0, reset.length());

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

        if (key == line) {
          // ID MATCH HERE ====================================================================
          accessKeysFile.close();
          return true;
        }

//        else if (key == reset) {
//          digitalWrite(relay, LOW);
//          Serial.println("Resettened");
//        }

        line = "";
      }
    }
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

  //  Serial.print(_date);
  //  Serial.print(delimitor);
  //  Serial.print(_time);
  //  Serial.print(delimitor);
  //  Serial.println(_id);
}


