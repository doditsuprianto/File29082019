#include <SoftwareSerial.h>
#define BT_TX 2
#define BT_RX 3

SoftwareSerial mySerial(BT_TX, BT_RX);
String myString = "";

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  while (mySerial.available()) {
    char myChar = (char)mySerial.read();
    myString += myChar;
    delay(5);
  }

  if (!myString.equals("")) {
    Serial.println("Received : " + myString);
    myString = "";
  }
}
