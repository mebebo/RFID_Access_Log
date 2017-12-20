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




int relay = 00000;
int piezo = 00000;
int ledR = 00000, ledG = 00000, ledB = 00000;


boolean setDateNTime = true;

void setup() {
  Serial.begin(9600);

  pinMode(relay, OUTPUT);
  pinMode(piezo, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  if (setDateNTime) {
    setRTCTime(__TIME__);
    setRTCDate(__DATE__);
  }
}

void loop() {

rtc.getTimeStr();
rtc.getDateStr();  // DATE + TIME FORMAT CAN BE CHANGED

}
