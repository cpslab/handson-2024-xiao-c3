#include <vector>
#include "handson_xiao_board.hpp"
#include "secret.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include "Wire.h"


int c = 0;
//MQTT setup
#define AWS_IOT_PUBLISH_TOPIC   "c3/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "c3/sub"

//network setup
WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

// LED pin setup
const int LED_PIN = 2; // LEDが接続されているピン番号（ボードに応じて変更してください）

#if defined(ARDUINO_ARCH_AVR)
    #define debug  Serial

#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
    #define debug  SerialUSB
#else
    #define debug  Serial
#endif

void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Incoming message: ");
  Serial.println(topic);
 
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  Serial.println(message);

  // メッセージに基づいてLEDを制御
  if (strcmp(message, "on") == 0) {
    digitalWrite(LED_PIN, HIGH); // LEDを点灯
  } else if (strcmp(message, "off") == 0) {
    digitalWrite(LED_PIN, LOW); // LEDを消灯
  }
}

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
  Serial.println("Connecting to Wi-Fi");
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
 
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
 
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
 
  // Create a message handler
  client.setCallback(messageHandler);
 
  Serial.println("Connecting to AWS IOT");
 
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }
 
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
 
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
 
  Serial.println("AWS IoT Connected!");
}

void publishMessage()
{
  Serial.println("Publish!");
  StaticJsonDocument<200> doc;
  doc["humidity"] = 100;
  doc["temperature"] = 100;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
 
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}
 

void setup() {

    debug.begin(115200);
    debug.println("MQTT test!");
    Wire.begin();
    pinMode(LED_PIN, OUTPUT);
    connectAWS();
}

void loop() {
  if(c==60){
    publishMessage();
    c = 0;
  }
    client.loop();
    delay(1000);
    c++;
}