#include "moteurs.h"
#include "../constants.h"

#include "../Capteur/Ultrasons.h"

Ultrasons capteur;

void init_pins() {
    pinMode(PINS::ENA, OUTPUT);
    pinMode(PINS::ENB, OUTPUT);
    pinMode(PINS::IN1, OUTPUT);
    pinMode(PINS::IN2, OUTPUT);
    pinMode(PINS::IN3, OUTPUT);
    pinMode(PINS::IN4, OUTPUT);
}

void config_capteur() {
    capteur.init();
}

void start() {
    analogWrite(PINS::ENA, MOTEUR::VITESSE_MIN);
    analogWrite(PINS::ENB, MOTEUR::VITESSE_MIN)
}

void stop() {
    analogWrite(PINS::ENA, 0);
    analogWrite(PINS::ENB, 0);
}

void config_speed(int speed, char side) {
    switch (side) {
        case SIDES::GAUCHE {
            analogWrite(PINS::ENA, speed);
        }
        case SIDES::DROITE {
            analogWrite(PINS::ENB, speed);
        }
    }
}


void speed_up_one(int speed, int target_speed, int increment, char side) {
    while (speed < target_speed) {
        speed += increment;
        switch (side) {
            case SIDES::GAUCHE {
                analogWrite(PINS::ENA, speed);
            }
            case SIDES::DROITE {
                analogWrite(PINS::ENB, speed);
            }
        }
        delay(MOTEUR::DELAI_VARIATION_VITESSE);
    }
}

void speed_up_all(int speed, int target_speed, int increment) {
    speed_up_one(speed, target_speed, increment, SIDES::GAUCHE);
    speed_up_one(speed, target_speed, increment, SIDES::DROITE);
}

void slow_down_one(int speed, int target_speed, int increment, char side) {
    while (speed > target_speed) {
        speed -= increment;
        switch (side) {
            case SIDES::GAUCHE {
                        analogWrite(PINS::ENA, speed);
                }
            case SIDES::DROITE {
                        analogWrite(PINS::ENB, speed);
                }
        }
        delay(MOTEUR::DELAI_VARIATION_VITESSE);
    }
}

void slow_down_all(int speed, int target_speed, int increment) {
    slow_down_one(speed, target_speed, increment, SIDES::GAUCHE);
    slow_down_one(speed, target_speed, increment, SIDES::DROITE);
}

void config_spinning_one(char direction, char side) {
    bool isForward = (direction == DIRECTION::AVANT);
    switch (side) {
        case (SIDES::GAUCHE) {
            digitalWrite(BORNES::IN1, isForward);
            digitalWrite(bornes::IN2, not isForward);
            }
        case (SIDES::DROITE) {
            digitalWrite(BORNES::IN3, isForward);
            digitalWrite(bornes::IN4, not isForward);
        }
    }
}

void config_spinning_all(char direction) {
    config_spinning_one(direction, SIDES::GAUCHE);
    config_spinning_one(direction, SIDES::DROITE);
}

void demi_tour() {
    config_spinning_all(DIRECTION::ARRIERE);
    start();
    config_speed(MOTEUR::VITESSE_DEMI_TOUR, SIDES::GAUCHE);
    delay(MOTEUR::DELAI_DEMI_TOUR);
    stop();
    config_spinning_all(DIRECTION::AVANT);
}

void ligne_droite() {
    config_spinning_all(DIRECTION::AVANT);
    start();
    speed_up_all(MOTEUR::VITESSE_MIN, MOTEUR::VITESSE_MAX, 10);
    while (capteur.mesure() > 79) {
        delay(MOTEUR::DELAI_LINEAIRE);
    }
    slow_up_all(MOTEUR::VITESSE_MAX, MOTEUR::VITESSE_MIN, 10);
    stop();
}

void trajet() {
    ligne_droite();
    demi_tour();
    ligne_droite();
}