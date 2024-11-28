// /Users/<username>/.platformio/packages/framework-arduinoespressif32/cores/esp32/Arduino.h
#include <Arduino.h>
// define led according to pin diagram in article
const uint8_t led = D0;
const uint8_t button = D1;
bool buttonState = false;
uint8_t brightness = 0;
int16_t fadeAmount = 5;

void setup() {
    pinMode(led, OUTPUT);

    Serial.begin(115200);
    pinMode(button, INPUT_PULLUP);
}

void loop() {
    // set the brightness of pin 9:
    analogWrite(led, brightness);

    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;

    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 255) {
        fadeAmount = -fadeAmount;
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
}

void tmp() {
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
