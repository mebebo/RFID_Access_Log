//stop sag sol
//far sag sol
//sinyal sag sol
//beacon tepe


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


// Access Keys In SD Card
// RFID Read
// SD Card Access Key Check
// Validate || Reject
//      Relay HIGH.LED Green.PiezoSUCCESS || Decline & Relay LOW.LED Red.PiezoFAIL

// LOG Entry to SD Card


// SD Card
// 1 - Access Keys
// 2 - Log Entry



// Online updates - Transmit & Receive

// Set date + time

// SD Card
// Sync Access Keys
// Sync Log Entries

// PROBLEMS
// No SD Card
// No GPRS Connection


// CURRENT SENSORS
#include "Current.h"

Current headlampL("Left HeadLight", A0);


// CLOCK MODULE
#include <DS1302.h>
int rsPin = 2, datPin = 3, clkPin = 4;
DS1302 rtc(rsPin, datPin, clkPin);


// PINOUT
int relay = 7;
int piezo = 6;
int ledR = 00000, ledG = 00000, ledB = 00000;




boolean setDateNTime = false;


void setup() {
  Serial.begin(9600);

  pinMode(relay, OUTPUT);
  pinMode(piezo, OUTPUT);

  initLedPins(ledR, ledG, ledB);



  initSD();

  if (setDateNTime) {
    setRTCTime(__TIME__);
    setRTCDate(__DATE__);
  }
}

void loop() {


  String keyInput = "";
  while (Serial.available()) {
    keyInput = Serial.readString();
    keyInput = keyInput.substring(0, keyInput.length());

    Serial.print("Key Input: ");
    Serial.println(keyInput);

    boolean matchID = validateAccessSD(keyInput);
    Serial.println(matchID);
  }

}






