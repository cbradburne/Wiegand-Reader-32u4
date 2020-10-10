/*
 
  26 bit Wiegand code RFID Reader (PAC ONEPROX GS3-MT)
  For Arduino Leonardo 32u4 boards (Pro Micro)
  
  Use:
  pin 7 for LED
  pin 8 for D1
  pin 9 for D0
  Gnd to Gnd

  Library:
  https://github.com/paulo-raca/YetAnotherArduinoPcIntLibrary
  
*/

#include <YetAnotherPcInt.h>
#include <Keyboard.h>

volatile long reader1 = 0;
volatile int reader1Count = 0;
void reader1One(bool pinstate) {
  if (pinstate == LOW) {
    reader1Count++;
    reader1 = reader1 << 1;
    reader1 |= 1;
  }
}

void reader1Zero(bool pinstate) {
  if (pinstate == LOW) {
    reader1Count++;
    reader1 = reader1 << 1;
  }
}

void setup() {
  //Serial.begin(115200);
  Keyboard.begin();
  pinMode(7, OUTPUT);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  PcInt::attachInterrupt(8, reader1One, CHANGE);
  PcInt::attachInterrupt(9, reader1Zero, CHANGE);
  reader1 = 0;
  reader1Count = 0;
  digitalWrite(7, HIGH);
}

void loop() {
  if (reader1Count >= 26) {
    //Serial.println(reader1);
    Keyboard.println(reader1);
    digitalWrite(7, LOW);
    reader1 = 0;
    reader1Count = 0;
    delay(1000);
    digitalWrite(7, HIGH);
  }
}
