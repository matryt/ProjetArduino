// Servomoteur.cpp
#include <Arduino.h>
#include "Servomoteur.h"
#include <Servo.h>
#include "../constants.h"

Servo servo;

void Servomoteur::init() {
    servo.attach(PINS::SERVO);
}

void Servomoteur::write_angle(int angle) {
    servo.write(angle);
}
