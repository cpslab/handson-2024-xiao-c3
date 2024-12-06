#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

#include <vector>

#include "WiFi.h"
#include "Wire.h"
#include "handson_xiao_board.hpp"
#include "secret.h"

// network setup
WiFiClientSecure net = WiFiClientSecure();

void connectWiFi() {
    delay(2000);  // シリアルモニタの表示が見やすくなるための遅延
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("Connecting to Wi-Fi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void setup() {
    Serial.begin(115200);
    connectWiFi();
}

void loop() {}
