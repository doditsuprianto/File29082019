#include <SoftwareSerial.h>
 
int blueTx=2;
int blueRx=3;
SoftwareSerial bluetooth(blueTx, blueRx);
 
void setup() 
{
  Serial.begin(9600);
  bluetooth.begin(9600);
}
void loop()
{
  if (bluetooth.available()) {       
    Serial.write(bluetooth.read());  
  }
  if (Serial.available()) {         
    bluetooth.write(Serial.read());  
  }
}
