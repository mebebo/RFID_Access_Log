String vehicleID = "HARLAN-07";

// Shift register needed for outputs?
// log out
// current sensor
// arduino memory to eeprom
// saat dilimi greenwich
// active session id variable -> Log Out ID

// SIM MODULE ADDITION
//  HTML UPDATE FUNCTION

//  Logged in behaviour
// Log Out?


// FUNCTIONS

// Working offline

// FLOWCHART =============================================================================================
//1 - ON
//2 - STANDBY
//      - LED yellow
//3 - CARD INPUT
//      - READING CARD - LED yellow blink (nonblocking, while reading rfid and searching sd card for match)
//  3a - ACCEPT ENTRY
//          - LED green
//          - RELAY on
//          - PIEZO yes
//          - SD LOG WRITE
//  3b - REJECT ENTRY
//          - LED red
//          - PIEZO no
//
//          - REVERT to STANDBY
//4 - RUNNING
//      - LED green
//      - RELAY on

// SECRET BYPASS SWITCH


// Online updates - Transmit & Receive

// Set date + time

// SD Card
// Sync Access Keys
// Sync Log Entries

// Ability to remotely change server info


// POSSIBLE PROBLEMS
// No SD Card           -  Check database online, blink yellow while checking
// No GPRS Connection
// RFID Reading Error
// Date + Time Timezone Errors



// CURRENT SENSORS
//#include "Current.h"
//
//Current headlampL("Left Headlight", A0);
//Current headlampR("Right Headlight", A1);
//Current signalL("Left Signal Light", A2);
//Current signalR("Right Signal Light", A3);
//Current taillampL("Left Tail Light", A4);
//Current taillampR("Right Tail Light", A5);
//Current beacon("Beacon Light", 00000);

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


// PINOUT
int relay = 8;
int piezo = 3;                                    // PWM
int ledR = 5, ledG = 6, ledB = 00000;     // PWM * 3

//2 CLK1
//3o PIEZO
//4 CLK2
//5o LED R
//6o LED G
//7 CLK3
//8 RELAY
//9o
//10 CS SD
//11 SPI
//12 SPI
//13 SPI
//18 RES RFID
//19 CS RFID
//
//14
//15
//16
//17


//
//Shiftables: RELAY, ledR, ledG, ledB


boolean setDateNTime = true;

boolean loggedIn = false;

String currUserID = "";

void setup() {
  Serial.begin(9600);
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

  initLedPins(ledR, ledG, ledB);
  initSD();
  initRFID();

  if (setDateNTime) {
    setRTCTime(__TIME__);
    setRTCDate(__DATE__);
  }
}


void loop() {

  if (rfid.PICC_IsNewCardPresent()) {
    String keyInput = getUID();
//    Serial.print("Current Input: ");
//    Serial.println(keyInput);
    boolean matchID;

    if (!loggedIn) {
      matchID = validateAccessSD(keyInput);
      Serial.print(F("Match ID "));
      Serial.println(matchID);

      if (matchID) logIn(keyInput);
      else rejectAccess(keyInput);
    }

    else if (loggedIn) {
      matchID = validateLogOutSD(keyInput);
      Serial.print(F("Match ID "));
      Serial.println(matchID);

      if(matchID) logOut(keyInput);
      else ;
    }
  }
}






