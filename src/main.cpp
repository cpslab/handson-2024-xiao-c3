#include <vector>

#include "handson_xiao_board.hpp"

Handson_xiao_board board(D0, D1);

void setup() {
    Serial.begin(115200);
    board.led().set_brightness(150);
    std::vector<bool> pattern = {1, 0, 1, 0, 1, 1, 0, 1};
    for (auto &&turn_on : pattern) {
        if (turn_on) {
            board.led().on();
            Serial.printf("LED ON\n");
        } else {
            board.led().off();
            Serial.printf("LED OFF\n");
        }
        delay(1000);
    }
    board.led().off();
}

void loop() {
    if (board.button().is_pressed()) {
        board.led().step_fade();
        Serial.printf("%d\n", board.led().get_brightness());
    } else {
        board.led().off();
    }
}
