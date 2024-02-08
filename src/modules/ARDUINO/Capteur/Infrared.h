// Infrared.h
#ifndef PROJET_ULTRASONS_H
#define PROJET_ULTRASONS_H

#include <Arduino.h>
#include "../constants.h"



class Infrared {
public:
    void init();
    int mesure();
    float distanceBrute();
    int convertirDistance(float raw);
};

#endif // PROJET_ULTRASONS_H
