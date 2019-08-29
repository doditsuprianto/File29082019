#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>

#define deviceID "dodit0D1566352364009"
#define authnRqtNo "g1s4dsarv"
#define extrSysID "OPEN_TCP_001PTL001_1000007609"

#define WIFI_SSID "ICT-LAB-2.4G" // SSID
#define WIFI_PASS "12345678" //psswd
#define TAG_ID "PIEZO"

#define VIB_SENSOR A0
#define TOUCH 1

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(VIB_SENSOR, INPUT);
  init_iotmakers();
}

void loop() {
  static unsigned long tick = millis();
  if (g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
  }

  if ((millis() - tick) > 200)
  {
    send_piezo();
    tick = millis();
  }
  g_im.loop();
}

int send_piezo() {
 // int isTouch = digitalRead(VIB_SENSOR);
  int data = analogRead(VIB_SENSOR);
  Serial.println(data);
  
  //if (isTouch == TOUCH) {
  //  Serial.println("TOUCH");
    if (g_im.send_numdata(TAG_ID, (double)data) < 0)
    {
      Serial.println(F("fail"));
      return -1;
    }

    return 0;
  //}
}
