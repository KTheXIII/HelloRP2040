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
int32_t fadeStep = 1;
Adafruit_NeoPixel* pixel;

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint8_t calcHue(float p, float q, float t) {
    if (t < 0) t += 1.0f;
    if (t > 1) t -= 1.0f;

    if (t < 1.0f/6.0f) return uint8_t((p + (q - p) * 6.0f * t) * 255.f);
    if (t < 1.0f/2.0f) return uint8_t(q * 255.0f);
    if (t < 2.0f/3.0f) return uint8_t((p + (q - p) * (2.0f/3.0f - t) * 6.0f) * 255.0f);
    return uint8_t(p * 255.0f);
}

uint32_t hsl2RGB(float h, float s, float l) {
    uint32_t rgb = 0x000000;

    if (s == 0.0f) {
        auto m = uint8_t(255.0f * l);
        rgb = (m << 16) | (m << 8) | (m << 0);
    } else {
        auto q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
        auto p = 2.0f * l - q;

        auto r = calcHue(p, q, (h / 360.f) + 1.0f/3.0f);
        auto g = calcHue(p, q, (h / 360.f));
        auto b = calcHue(p, q, (h / 360.f) - 1.0f/3.0f);

        rgb = (r << 16) | (g << 8) | (b << 0);
    }
    return rgb;
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pixel = new Adafruit_NeoPixel(1, RGB_PIN, NEO_GRB + NEO_KHZ800);
    pixel->begin();
    Serial.begin(115200);
}

void loop() {
    analogWrite(LED_PIN, value);
    pixel->show();

    value += fadeStep;
    if (value <= 0 || value >= 255)
        fadeStep = -fadeStep;

    Serial.println("Hello, World!\n");

    auto hue = mapFloat(value, 0, 255, 0, 1);
    pixel->setPixelColor(0, hsl2RGB(259, 1, 0.5));
    delay(16);
}

