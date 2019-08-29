#include <SoftwareSerial.h>
#define BT_TX 2
#define BT_RX 3
#define ledG 9
#define ledR 10
#define ledB 11

SoftwareSerial mySerial(BT_TX, BT_RX);
String myString = "";

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(ledG, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() {
  while (mySerial.available()) {
    char myChar = (char)mySerial.read();
    myString += myChar;
    delay(5);
  }

  if (!myString.equals("")) {
    Serial.println("Received : " + myString);
    LED();
    myString = "";
  }
}

void LED() {
  if (myString == "R") {
    Serial.println("RED LED ON");
    Light(255, 0, 0);
  } else if (myString == "G") {
    Serial.println("GREEN LED ON");
    Light(0, 255, 0);
  } else if (myString == "B") {
    Serial.println("BLUE LED ON");
    Light(0, 0, 255);
  } else if (myString == "AUTO") {
    Serial.println("ALL LED ON");
    delay(800);

    Light(0, 255, 255);
    delay(800);
    Light(0, 255, 0);
    delay(800);
    Light(0, 255, 255);
    delay(800);
    Light(0, 0, 0);
  }
}

void Light(int r, int g, int b) {
  analogWrite(ledR, 255 - r);
  analogWrite(ledG, 255 - g);
  analogWrite(ledB, 255 - b);
}
