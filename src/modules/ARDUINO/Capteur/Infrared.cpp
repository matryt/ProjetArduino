// Infrared.cpp
#include <Arduino.h>
#include "Infrared.h"
#include "../constants.h"

float Infrared::distanceBrute() {
    return analogRead(PINS::INFRARED) / 1023.0 * 5.0;
}

int Infrared::convertirDistance(float raw) {
    if (raw < 1.0) {
        return -17143.0 * pow(raw, 5.0) + 57924.0 * pow(raw, 4.0) - 77112.0 * pow(raw, 3.0) + 50630.0 * pow(raw, 2.0) - 16509.0 * raw + 2211.7;
    }
    return 26.287 * pow(raw, -1.066);
}

void Infrared::init() {
    pinMode(PINS::INFRARED, INPUT);
}

int Infrared::mesure() {
    return convertirDistance(distanceBrute());
}
