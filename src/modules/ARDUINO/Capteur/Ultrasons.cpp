//
// Created by mathi on 07/02/2024.
//

#include "Ultrasons.h"
#include "../constants.h"

class Ultrasons {
    void init() {
        pinMode(PINS::ULTRASONS, INPUT);
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