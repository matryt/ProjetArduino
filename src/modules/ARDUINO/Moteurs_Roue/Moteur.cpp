// Moteur.cpp
#include <Arduino.h>
#include "Moteur.h"
#include "../constants.h"

void Moteur::init(int enable, int in1, int in2) {
    pinMode(enable, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    EN = enable;
    this->in1 = in1;
    this->in2 = in2;
}

void Moteur::config_speed(int speed) {
    analogWrite(EN, speed);
}

void Moteur::start() {
    config_speed(MOTEUR::VITESSE_MIN);
}

void Moteur::stop() {
    config_speed(0);
}

void Moteur::config_spinning(char direction) {
    bool isForward = (direction == DIRECTION::AVANT);
    digitalWrite(in1, isForward);
    digitalWrite(in2, !isForward);
}
