//
// Created by mathi on 07/02/2024.
//

#include "Moteur.h"
#include "../constants.h"

class Moteur {
    int EN;
    int in1;
    int in2;
    void init(int enable, int in1, int in2) {
        pinMode(enable, OUTPUT);
        pinMode(in1, OUTPUT);
        pinMode(in2, OUTPUT);
        EN=enable;
        this->in1=in1;
        this->in2=in2;
    }

    void config_speed(int speed) {
        analogWrite(EN, spped)
    }

    void start() {
        config_speed(MOTEUR::VITESSE_MIN);
    }

    void stop() {
        config_speed(0);
    }

    void config_spinning(char direction) {
        bool isForward = (direction == DIRECTION::AVANT);
        digitalWrite(in1, isForward);
        digitalWrite(in3, not isForward);
    }
}


