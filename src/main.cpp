// /Users/<username>/.platformio/packages/framework-arduinoespressif32/cores/esp32/Arduino.h
#include <Arduino.h>
// define led according to pin diagram in article
const int led = D0;
const int button = D1;
bool buttonState = false;

void setup() {
    pinMode(led, OUTPUT);

    Serial.begin(115200);
    pinMode(button, INPUT_PULLUP);
}

void loop() {
    digitalWrite(led, LOW);
    Serial.printf("buttonState: %d\n", buttonState);
    if (buttonState = !digitalRead(button); buttonState) {
        digitalWrite(led, HIGH);
    }
}

int main() {
    setup();
    while (true) {
        loop();
    }
    return 0;
}
