//
// Created by mathi on 07/02/2024.
//

#include <Arduino.h>
#include "Robot.h"
#include "../Capteur/Infrared.h"
#include "../Moteurs_Roue/Moteur.h"
#include "../constants.h"
#include "../Servomoteur/Servomoteur.h"

void Robot::init() {
    capteur.init();
    gauche.init(PINS::ENA, PINS::IN1, PINS::IN2);
    droite.init(PINS::ENB, PINS::IN3, PINS::IN4);
    s.init();
}

void Robot::config_speed(int speed,float offset) {
    gauche.config_speed(speed-offset);
    droite.config_speed(speed);
}

void Robot::speed_up(int speed, int target_speed, int increment) {
    int i=0;
    while (speed < target_speed) {
        speed += increment;
        config_speed(speed,MOTEUR::OFFSET +2.5*i);
        delay(MOTEUR::DELAI_VARIATION_VITESSE);
        s.next();
        i++;
    }
}

void Robot::slow_down(int speed, int target_speed, int increment) {
    int i=17;
    while (speed > target_speed) {
        speed -= increment;
        config_speed(speed,MOTEUR::OFFSET+2.5*i);
        delay(MOTEUR::DELAI_VARIATION_VITESSE);
        s.next();
        i--;
    }
}

void Robot::config_spinning(char direction) {
    gauche.config_spinning(direction);
    droite.config_spinning(direction);
}
void Robot::start() {
    gauche.start();
    droite.start();
}

void Robot::stop() {
    gauche.stop();
    droite.stop();
}

void Robot::halfturn() {
    stop();
    config_spinning(DIRECTION::ARRIERE);
    start();
    droite.config_speed(MOTEUR::VITESSE_MIN + MOTEUR::DIFF_VITESSE_DEMITOUR);
    delay(MOTEUR::DELAI_DEMI_TOUR);
    stop();
    config_spinning(DIRECTION::AVANT);
    s.next();
}

void Robot::straight_line() {
    config_spinning(DIRECTION::AVANT);
    start();
    speed_up(MOTEUR::VITESSE_MIN, MOTEUR::VITESSE_MAX, MOTEUR::INCREMENT);
    while (capteur.mesure() > MOTEUR::DISTANCE_FREINAGE) {
        delay(MOTEUR::DELAI_LINEAIRE);
        s.next();
    }
    slow_down(MOTEUR::VITESSE_MAX, MOTEUR::VITESSE_MIN, MOTEUR::INCREMENT);
    stop();
}

void Robot::journey() {
    straight_line();
    halfturn();
    straight_line();
}

int Robot::main() {
    journey();
    return 0;
}

