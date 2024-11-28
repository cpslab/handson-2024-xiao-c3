// /Users/<username>/.platformio/packages/framework-arduinoespressif32/cores/esp32/Arduino.h
#include <Arduino.h>
// define led according to pin diagram in article
const int led = D0;
const int button = D1;
bool buttonState = false;

void setup() {
    pinMode(led, OUTPUT);

    Serial.begin(115200);
    Serial.println("Hello World");
    pinMode(button, INPUT_PULLUP);
}

void loop() {
    // digitalWrite(led, HIGH);  // turn the LED on
    // delay(1000);              // wait for a second
    // digitalWrite(led, LOW);   // turn the LED off
    // delay(1000);              // wait for a second

    buttonState = !digitalRead(button);
    Serial.printf("buttonState: %d\n", buttonState);
    delay(1000);
}

int main() {
    setup();
    while (true) {
        loop();
    }
    return 0;
}
