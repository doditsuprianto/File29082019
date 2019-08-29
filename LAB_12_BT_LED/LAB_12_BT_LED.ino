#include <SoftwareSerial.h>

#define blueTx 2
#define blueRx 3
#define ledG 9
#define ledR 10
#define ledB 11

SoftwareSerial bluetooth(blueTx, blueRx);
String myString = "";

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(ledG, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledB, OUTPUT);
}
void loop()
{

  if (bluetooth.available()) {
    Serial.write(bluetooth.read());
  }
  if (Serial.available()) {
    bluetooth.write(Serial.read());
  }


  while (bluetooth.available()) {
    char myChar = (char)bluetooth.read();
    myString += myChar;
    delay(5);
  }

  //if (!myString.equals("")){
  //  Serial.println("Received : " + myString);
  //}

  if (bluetooth.available()) {
    if (!myString.equals("")) {
      Serial.println("Input value: " + myString);

      if (myString == "R") {
        Serial.println("RED LED ON");
        digitalWrite(ledR, HIGH);
      } else if (myString == "G") {
        Serial.println("GREEN LED ON");
        digitalWrite(ledR, HIGH);
      } else if (myString == "B") {
        Serial.println("BLUE LED ON");
        digitalWrite(ledR, HIGH);
      } else if (myString == "AUTO") {
        Serial.println("ALL LED ON");
        digitalWrite(ledR, HIGH);
        delay(500);
        digitalWrite(ledG, HIGH);
        delay(500);
        digitalWrite(ledB, HIGH);
        delay(500);

        Serial.println("ALL LED OFF");
        digitalWrite(ledR, LOW);
        digitalWrite(ledG, LOW);
        digitalWrite(ledB, LOW);
      }

      /*
        switch (myString) {
        case "R":
          Serial.println("RED LED ON");
          digitalWrite(ledR, HIGH);
          break;
        case "G":
          Serial.println("GREEN LED ON");
          digitalWrite(ledG, HIGH);
          break;
        case "B":
          Serial.println("BLUE LED ON");
          digitalWrite(ledB, HIGH);
          break;
        case "AUTO":
          Serial.println("ALL LED ON");
          digitalWrite(ledR, HIGH);
          delay(500);
          digitalWrite(ledG, HIGH);
          delay(500);
          digitalWrite(ledB, HIGH);
          delay(500);

          Serial.println("ALL LED OFF");
          digitalWrite(ledR, LOW);
          digitalWrite(ledG, LOW);
          digitalWrite(ledB, LOW);
          break;
        }
      */
    }
  }
}
