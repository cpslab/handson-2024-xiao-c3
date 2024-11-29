// /Users/<username>/.platformio/packages/framework-arduinoespressif32/cores/esp32/Arduino.h
#include <Arduino.h>
// define led according to pin diagram in article

class handson_xiao_board {
    const uint8_t led;
    const uint8_t button;
    bool buttonState;
    uint8_t brightness;
    int16_t fadeAmount;
    unsigned long lastDebounceTime;
    const unsigned long debounceDelay = 50;  // 50ms

   public:
    handson_xiao_board(uint8_t led, uint8_t button)
        : led(led),
          button(button),
          buttonState(false),
          brightness(0),
          fadeAmount(5),
          lastDebounceTime(0) {
        Serial.begin(115200);
        pinMode(led, OUTPUT);
        pinMode(button, INPUT_PULLUP);
    }

    auto pressed() -> bool {
        bool currentState = !digitalRead(button);
        if (currentState != buttonState) {
            lastDebounceTime = millis();
        }
        if ((millis() - lastDebounceTime) > debounceDelay) {
            buttonState = currentState;
        }
        return buttonState;
    }
    auto led_fade() -> void {
        analogWrite(led, brightness);
        brightness = brightness + fadeAmount;
        if (brightness == 0 || brightness >= 255) {
            fadeAmount = -fadeAmount;
        }
        delay(30);
    }
    auto led_off() -> void { analogWrite(led, 0); }
    auto led_on() -> void { analogWrite(led, brightness); }
    auto set_brightness(uint8_t value) -> void { brightness = value; }
    auto get_brightness() -> uint8_t { return brightness; }
    auto set_fade_amount(int16_t value) -> void { fadeAmount = value; }
};

handson_xiao_board xiao(D0, D1);

void setup() {
    xiao.set_brightness(255);
    Serial.begin(115200);
    Serial.printf("Brightness: %d\n", xiao.get_brightness());
}

void loop() {
    xiao.led_on();
    delay(1000);
    xiao.led_off();
    delay(1000);
}
