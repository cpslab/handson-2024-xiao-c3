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
#define AWS_IOT_PUBLISH_TOPIC   "トピック名"//AWS側で設定したポリシーに合致した自分用トピック名
#define AWS_IOT_SUBSCRIBE_TOPIC "トピック名"//AWS側で設定したポリシーに合致した自分用トピック名

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
 void loop() {
    // 現在の時間を取得
    static unsigned long lastPublishTime = 0; // 最後にメッセージを送信した時間
    unsigned long currentMillis = millis();

    // 60秒ごとにメッセージを送信
    if (currentMillis - lastPublishTime >= 60000) { // 60秒 (60000ms)
        publishMessage();
        lastPublishTime = currentMillis; // 最後に送信した時間を更新
    }

    // MQTT クライアントの接続状態を維持
    if (!client.connected()) {
        connectAWS(); // 再接続処理
    }
    client.loop();
}

}