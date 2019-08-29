//******************************************************//
// 6-axis Accelerometer / Gyro Sensor
// Sample Code 1
//                                      - Kyung-Sik Jang//
//******************************************************//

// Hardware Configuration
// Arduino    MPU 6050
//  VCC         VCC
//  GND         GND
//  SCL          A5
//  SDA          A4

#include<Wire.h>
#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>

const int MPU = 0x68;  // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

#define deviceID "dodit0D1566352364009"
#define authnRqtNo "g1s4dsarv"
#define extrSysID "OPEN_TCP_001PTL001_1000007609"

#define WIFI_SSID "ICT-LAB-2.4G" // SSID
#define WIFI_PASS "12345678" //psswd
//#define TAG_ID "GYRO2"
#define TAG_ACX, 
#define TAG_ACY, 
#define TAG_ACZ, 
#define TAG_TMP, 
#define TAG_GYX, 
#define TAG_GYY, 
#define TAG_GYZ

IoTMakers g_im;

void init_iotmakers()
{
  while (1)
  {
    Serial.print(F("Connect to AP..."));
    while (g_im.begin(WIFI_SSID, WIFI_PASS) < 0)
    {
      Serial.println(F("retrying"));
      delay(100);
    }

    Serial.println(F("Success"));

    g_im.init(deviceID, authnRqtNo, extrSysID);

    Serial.print(F("Connect to platform..."));
    while (g_im.connect() < 0)
    {
      Serial.println(F("retrying."));
      delay(100);
    }
    Serial.println(F("Success"));

    Serial.print(F("Auth..."));
    if (g_im.auth_device() >= 0)
    {
      Serial.println(F("Success..."));
      return;
    }
  }
}

void setup()
{
  Serial.begin(9600);
  init_iotmakers();

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  // gyro scale
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0xF8);
  Wire.endTransmission(true);

  // acc scale
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0xF8);
  Wire.endTransmission(true);
}

void loop()
{
  if (g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
  }

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);

  AcX = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  int xAxis = (AcX - 1090);
  int yAxis = (AcY - 930);
  int zAxis = (AcZ - 1000);

  Serial.print(xAxis);
  Serial.print(" ");
  Serial.print(yAxis);
  Serial.print(" ");
  Serial.print(zAxis);
  Serial.println(" ");

  //Gyro Value
  Serial.print("GyZ : " + String(GyX));
  Serial.print(" ");
  Serial.print("GyY : " + String(GyY));
  Serial.print(" ");
  Serial.println("GyZ : " + String(GyZ));

  //Gyro Temperature
  Serial.println("Temperature : " + String(Tmp));

  //String data = "xAxis " + String(xAxis) + " | yAxis " + String(yAxis) + " | zAxis " + String(zAxis);

  if (g_im.send_numdata(TAG_ID, (int)xAxis) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }

  delay(1000);
  g_im.loop();
}
