/**
 * @file   main.cpp
 * @author Pratchaya Khansomboon (pratchaya.k.git@gmail.com)
 * @brief  Adafruit Feather RP2040 Example project with NeoPixel.
 * @date   2021-10-07
 *
 * @copyright Copyright (c) 2021
 */
#include <cstdint>
#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

constexpr int32_t LED_PIN = 13;
constexpr int32_t RGB_PIN = 16;

int32_t value    = 0;
int32_t fadeStep = 5;
Adafruit_NeoPixel* pixel;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pixel = new Adafruit_NeoPixel(1, RGB_PIN, NEO_GRB + NEO_KHZ800);
    pixel->begin();
}

void loop() {
    analogWrite(LED_PIN, value);
    pixel->show();

    value += fadeStep;
    pixel->setPixelColor(0, value, 0, value);
    if (value <= 0 || value >= 255)
        fadeStep = -fadeStep;
    delay(30);
}

