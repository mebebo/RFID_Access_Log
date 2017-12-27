


// COMPONENTS
//
// RFID reader
// SMS Module
// Memory Card
// RTC Clock
// Current Sensors

// Piezo, RGB Led

// FUNCTIONS

// Working offline

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


// PROBLEMS
// No SD Card
// No GPRS Connection
// RFID Reading Error
// Date + Time Timezone Errors



// CURRENT SENSORS
#include "Current.h"

Current headlampL("Left Headlight", A0);
Current headlampR("Right Headlight", A1);
Current signalL("Left Signal Light", A2);
Current signalR("Right Signal Light", A3);
Current taillampL("Left Tail Light", A4);
Current taillampR("Right Tail Light", A5);
Current beacon("Beacon Light", 00000);

#include <SPI.h>

// RFID MODULE
#include <ByteConvert.hpp>
#include <MFRC522.h>
int rfidRstPin = 8;
int rfidCSPin = 4;

MFRC522 rfid(rfidCSPin, rfidRstPin);


// SD CARD MODULE
#include <SD.h>
File accessKeysFile;
File entryLogFile;
String accessKeys = "keys.txt";
String entryLog = "entryLog.txt";
int sdCSPin = 10;


// CLOCK MODULE
#include <DS1302.h>
int rsPin = 2, datPin = 3, clkPin = 00000;
DS1302 rtc(rsPin, datPin, clkPin);


// PINOUT
int relay = 00000;
int piezo = 6;                                    // PWM
int ledR = 00000, ledG = 00000, ledB = 00000;     // PWM * 3


boolean setDateNTime = false;


void setup() {
  Serial.begin(9600);
  SPI.begin();

  pinMode(relay, OUTPUT);
  pinMode(piezo, OUTPUT);

  pinMode(10, OUTPUT);
  pinMode(sdCSPin, OUTPUT);
  pinMode(rfidCSPin, OUTPUT);

  digitalWrite(sdCSPin, HIGH);
  digitalWrite(rfidCSPin, HIGH);
  digitalWrite(relay, LOW);

  initLedPins(ledR, ledG, ledB);
  initSD();
  initRFID();
  ledYellow();

  if (setDateNTime) {
    setRTCTime(__TIME__);
    setRTCDate(__DATE__);
  }
}


void loop() {



  if (rfid.PICC_IsNewCardPresent()) {
    String keyInput = getUID();

    Serial.print("Key Input: ");
    Serial.println(keyInput);

    boolean matchID = validateAccessSD(keyInput);

    if (matchID)    validateEntry(keyInput);
    else if (!matchID) rejectEntry(keyInput);
  }
}






