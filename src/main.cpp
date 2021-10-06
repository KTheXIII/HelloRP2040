#include <Arduino.h>
#include <cstdint>

constexpr int32_t LED_PIN = 13;

int32_t value    = 0;
int32_t fadeStep = 5;

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    analogWrite(LED_PIN, value);
    value += fadeStep;
    if (value <= 0 || value >= 255)
        fadeStep = -fadeStep;
    delay(30);
}

