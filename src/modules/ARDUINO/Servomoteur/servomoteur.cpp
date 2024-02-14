// Servomoteur.cpp
#include <Arduino.h>
#include "Servomoteur.h"
#include <Servo.h>
#include "../constants.h"

Servo servo;

void Servomoteur::init() {
    servo.attach(PINS::SERVO);
    int cpt = 0;
    int max = (SERVO::MAX_ANGLE - SERVO::MIN_ANGLE) * 2 / SERVO::INCREMENT;
}

void Servomoteur::write_angle(int angle) {
    servo.write(angle);
}

void Servomoteur::next() {
    int angle;
    cpt = cpt % 30;
    if (cpt >= max/2) {
        angle = (max - cpt) * SERVO::INCREMENT;
    }
    else {
        angle = cpt * SERVO::INCREMENT;
    }
    write_angle(SERVO::MIN_ANGLE + angle);
    cpt++;
}