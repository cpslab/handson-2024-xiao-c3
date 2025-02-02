#include <Arduino.h>

class Led {
    const uint8_t pin;
    int16_t brightness;
    int16_t fadeAmount;

   public:
    explicit Led(uint8_t pin) : pin(pin), brightness(255), fadeAmount(5) {
        pinMode(pin, OUTPUT);
    }
    auto on() -> void { analogWrite(pin, brightness); }
    auto off() -> void { analogWrite(pin, 0); }

    auto step_fade() -> void {
        analogWrite(pin, brightness);
        brightness = brightness + fadeAmount;
        if (brightness <= 0 || brightness >= 255) {
            fadeAmount = -fadeAmount;
        }
        delay(30);
    }

    auto set_brightness(uint8_t value) -> void { brightness = value; }
    auto get_brightness() -> uint8_t { return brightness; }
    auto set_fade_amount(int16_t value) -> void { fadeAmount = value; }
    auto get_fade_amount() -> int16_t { return fadeAmount; }
};

class Button {
    const uint8_t pin;
    bool state;

   public:
    explicit Button(uint8_t pin) : pin(pin), state(false) {
        pinMode(pin, INPUT_PULLUP);
    }

    auto is_pressed() -> bool { return !digitalRead(pin); }
};

class Handson_xiao_board {
    Led board_led;
    Button board_button;

   public:
    explicit Handson_xiao_board(uint8_t led, uint8_t button)
        : board_led(led), board_button(button) {};

    auto led() -> Led& { return board_led; }
    auto button() -> Button& { return board_button; }
};
