#include <vector>
#include "handson_xiao_board.hpp"
#include "secret.h"
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include "Wire.h"


//network setup
WiFiClientSecure net = WiFiClientSecure();

#if defined(ARDUINO_ARCH_AVR)
    #define debug  Serial

#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
    #define debug  SerialUSB
#else
    #define debug  Serial
#endif

void connectWiFi()
{
  delay(2000);//シリアルモニタの表示が見やすくなるための遅延
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println("Connecting to Wi-Fi");
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wi-Fi ちゃんと Connected!");
}

void setup() {
    debug.begin(115200);
    Wire.begin();
    connectWiFi();
}

void loop() {
    delay(1000);
}