#define VIB_SENSOR A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(VIB_SENSOR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(analogRead(VIB_SENSOR));
  delay(100);
}
