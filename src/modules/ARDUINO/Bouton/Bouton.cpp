//
// Created by mathi on 13/02/2024.
//

#include "Bouton.h"
#include <Arduino.h>
#include "../constants.h"

void Bouton::init(int pin) {
    PIN = pin;
}

int Bouton::readValue() {
    return digitalRead(PIN);
}

bool Bouton::waitUntilPressed() {
    while (readValue() != BOUTON::TARGET_VALUE) {
        delay(BOUTON::DELAI_ATTENTE);
    }
    return true;
}