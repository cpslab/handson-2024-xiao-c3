#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

#include <vector>

#include "WiFi.h"
#include "Wire.h"
#include "cert/secret.h"
#include "handson_xiao_board.hpp"

// network setup
WiFiClientSecure net = WiFiClientSecure();

void connectWiFi() {
    delay(200);
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
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("WiFi connected");
}

void setup() {
    Serial.begin(115200);
    connectWiFi();
}

void loop() {}
