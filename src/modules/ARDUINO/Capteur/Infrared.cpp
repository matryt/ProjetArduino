// Infrared.cpp
#include <Arduino.h>
#include "Infrared.h"
#include "../constants.h"

int Infrared::distanceBrute() {
    return analogRead(PINS::INFRARED);
}

int Infrared::convertirDistance(int raw) {
    float Vout = float(raw) *  0.0048828125;
    int phys =  13 * pow(Vout, -1);
    return phys;
}

void Infrared::init() {
    pinMode(PINS::INFRARED, INPUT);
}

int Infrared::mesure() {
    return convertirDistance(distanceBrute());
}
