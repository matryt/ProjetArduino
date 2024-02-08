// Infrared.h
#ifndef PROJET_ULTRASONS_H
#define PROJET_ULTRASONS_H

#include <Arduino.h>
#include "../constants.h"

class Infrared {
public:
    void init();
    int mesure();

private:
    int distanceBrute();
    int convertirDistance(int raw);
};

#endif // PROJET_ULTRASONS_H
