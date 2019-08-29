#include <SoftwareSerial.h>
#define BT_TX 4
#define BT_RX 5

SoftwareSerial mySerial(BT_TX, BT_RX);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  if (mySerial.available()){    
    Serial.write(mySerial.read());
  }

  if (Serial.available()){
    delay(5);
    mySerial.write(Serial.read());
  }
}
