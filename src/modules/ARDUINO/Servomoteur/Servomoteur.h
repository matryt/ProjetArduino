// Servomoteur.h
#ifndef PROJET_SERVOMOTEUR_H
#define PROJET_SERVOMOTEUR_H

#include <Arduino.h>
#include <Servo.h>
#include "../constants.h"

class Servomoteur {
public:
    void init();
    void write_angle(int angle);

private:
    Servo servo;
};

#endif //PROJET_SERVOMOTEUR_H