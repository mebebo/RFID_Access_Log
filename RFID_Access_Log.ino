// COMPONENTS
//
// RFID reader
// SMS Module
// Memory Card
// RTC Clock

// FUNCTIONS

// Working offline

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






// CLOCK MODULE
#include <DS1302.h>
int rsPin = 2, datPin = 3, clkPin = 4;
DS1302 rtc(rsPin, datPin, clkPin);


// PINOUT
int relay = 7;
int piezo = 00000;
int ledR = 00000, ledG = 00000, ledB = 00000;




boolean setDateNTime = false;


void setup() {
  Serial.begin(9600);

  pinMode(relay, OUTPUT);
  pinMode(piezo, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);



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






