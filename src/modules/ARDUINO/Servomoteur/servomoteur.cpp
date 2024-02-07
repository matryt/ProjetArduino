//
// Created by mathi on 07/02/2024.
//

#include "Servomoteur.h"
#include <Servo.h>
#include "../constants.h"

Servo servo;

class Servomoteur {
    void init() {
        servo.attach(PINS::SERVO);
    }

    void write_angle(int angle) {
        servo.write(angle);
    }
};