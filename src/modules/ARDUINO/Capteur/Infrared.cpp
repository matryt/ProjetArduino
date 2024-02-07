//
// Created by mathi on 07/02/2024.
//

#include "Infrared.h"
#include "../constants.h"

class Infrared {
    void init() {
        pinMode(PINS::INFRARED, INPUT);
    }

    int distanceBrute() {
        return analogRead(PINS::ULTRASONS);
    }

    int convertirDistance(int raw) {
        float Vout = float(raw) * 0.0048828125;
        int phys = 13 * pow(Vout, -1);
        return phys;
    }

    int mesure() {
        return convertirDistance(distanceBrute);
    }
};