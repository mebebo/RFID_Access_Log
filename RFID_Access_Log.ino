// Shift register needed for outputs?
// to EEPROM. vehicle ID, parts broken booleans

// LED COLOR

// SIM MODULE ADDITION
//  HTML UPDATE FUNCTION

// SECRET BYPASS SWITCH


// Online updates - Transmit & Receive

// SD Card
// Sync Access Keys
// Sync Log Entries

// Ability to remotely change server info?


// POSSIBLE PROBLEMS
// No SD Card           -  Check database online, blink yellow while checking
// No GPRS Connection
// RFID Reading Error
// Date + Time Timezone Errors

//2 CLK1
//3o PIEZO
//4 CLK2
//5o LED R
//6o LED G
//7 CLK3
//8 RELAY
//9o BTN_ENGINE
//10 CS SD
//11 SPI
//12 SPI
//13 SPI
//18 RES RFID
//19 CS RFID
//
//14 CURR HEAD
//15 CURR STOP
//16 CURR SIGNAL
//17 BTN_LIGHTS

//Shiftables: RELAY, ledR, ledG, ledB, BTN_ENGINE, BTN_LIGHTS


String vehicleID = "6";

// CURRENT SENSORS
#include "Current.h"
//
Current headlight(1, A0);
Current stoplight(2, A1);
Current beacon(3, A2);
//Current signalL(4, 00000);
//Current signalR(5, 00000);


#include <SPI.h>

// RFID MODULE
#include <ByteConvert.hpp>
#include <MFRC522.h>
int rfidRstPin = 18;
int rfidCSPin = 19;

MFRC522 rfid(rfidCSPin, rfidRstPin);


// SD CARD MODULE
//#include <SD.h>
#include "SdFat.h"
SdFat SD;
File accessKeysFile;
File entryLogFile;
File tempKeysFile;
File tempLogFile;
const char accessKeys[] = "keys.txt";
const char entryLog[] = "entryLog.txt";
const char tempKeys[] = "tempKeys.txt";
const char tempLog[] = "tempLog.txt";
int sdCSPin = 10;


// CLOCK MODULE
#include <DS1302.h>
int rsPin = 2, datPin = 4, clkPin = 7;
DS1302 rtc(rsPin, datPin, clkPin);


// BUTTON CONTROL
int buttonEngine = 9;


// PINOUT
int relay = 8;
int piezo = 3;                            // PWM
int ledR = 5, ledG = 6, ledB = 00000;     // PWM * 3

boolean setDateNTime = false;

boolean loggedIn = false;
unsigned long buttonDebounceTime;
int buttonDebounce = 200;
String currUserID = "";
String delimitor = ",";

int errCheckInterval = 2000; // millisec
unsigned long errCheckTime = errCheckInterval;


void setup() {
  Serial.begin(9600);
  usbConnect();

  SPI.begin();

  pinMode(relay, OUTPUT);
  pinMode(piezo, OUTPUT);

  pinMode(10, OUTPUT);
  pinMode(sdCSPin, OUTPUT);
  pinMode(rfidCSPin, OUTPUT);
  pinMode(rfidRstPin, OUTPUT);

  digitalWrite(sdCSPin, HIGH);
  digitalWrite(rfidCSPin, HIGH);
  digitalWrite(relay, LOW);

  pinMode(buttonEngine, INPUT_PULLUP);

  initLedPins(ledR, ledG, ledB);
  initSD();
  initRFID();

  if (setDateNTime) {
    setRTCTime(__TIME__);
    setRTCDate(__DATE__);
  }

  currUserID.reserve(10);
}


void loop() {

  if (!loggedIn) {
    // CHECK RFID CARD ENTRY
    if (rfid.PICC_IsNewCardPresent()) {
      String keyInput = getUID();
      boolean matchID;

      if (!loggedIn) {
        matchID = validateAccessSD(keyInput);
        if (matchID) logIn(keyInput);
        else rejectAccess(keyInput);

        errCheckTime = millis() + errCheckInterval;
      }

      //    else if (loggedIn) {
      //      matchID = validateLogOutSD(keyInput);
      //      if (matchID) logOut(keyInput);
      //      else ;
      //    }
    }
  }

  // CHECK AND UPDATE LIGHTS MALFUNCTION
  else if (loggedIn) {
    if (errCheckTime < millis()) {
      errCheckTime = millis() + errCheckInterval;
      checkMalfunction(headlight);
      checkMalfunction(stoplight);
      checkMalfunction(beacon);
    }
  }

  if (digitalRead(buttonEngine) == LOW && buttonDebounceTime < millis()) {
    buttonDebounceTime = millis() + buttonDebounce;
    if (loggedIn) logOut(currUserID);
    digitalWrite(relay, LOW);
  }
}






