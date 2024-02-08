//
// Created by mathi on 07/02/2024.
//

#include <Arduino.h>
#include "Robot.h"
#include "../Capteur/Infrared.h"
#include "../Moteurs_Roue/Moteur.h"
#include "../constants.h"
#include "../Servomoteur/Servomoteur.h"

Robot::Robot() : angle(SERVO::MIN_ANGLE) {}

Robot::~Robot() {}

void Robot::init() {
    capteur.init();
    gauche.init(PINS::ENA, PINS::IN1, PINS::IN2);
    droite.init(PINS::ENB, PINS::IN3, PINS::IN4);
}

void Robot::config_speed(int speed) {
    gauche.config_speed(speed);
    droite.config_speed(speed);
}

void Robot::speed_up(int speed, int target_speed, int increment) {
    while (speed < target_speed) {
        speed += increment;
        config_speed(speed);
        delay(MOTEUR::DELAI_VARIATION_VITESSE);
        process_next_angle();
        s.write_angle(angle);
    }
}

void Robot::slow_down(int speed, int target_speed, int increment) {
    while (speed > target_speed) {
        speed -= increment;
        config_speed(speed);
        delay(MOTEUR::DELAI_VARIATION_VITESSE);
        process_next_angle();
        s.write_angle(angle);
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
    droite.config_speed(MOTEUR::VITESSE_MIN +  50);
    delay(MOTEUR::DELAI_DEMI_TOUR);
    stop();
    config_spinning(DIRECTION::AVANT);
}

void Robot::straight_line() {
    config_spinning(DIRECTION::AVANT);
    start();
    speed_up(MOTEUR::VITESSE_MIN, MOTEUR::VITESSE_MAX, MOTEUR::INCREMENT);
    while (capteur.mesure() >  79) {
        delay(MOTEUR::DELAI_LINEAIRE);
        process_next_angle();
        s.write_angle(angle);
    }
    slow_down(MOTEUR::VITESSE_MAX, MOTEUR::VITESSE_MIN, MOTEUR::INCREMENT);
    stop();
}

void Robot::journey() {
    straight_line();
    halfturn();
    straight_line();
}

void Robot::process_next_angle() {
    if (angle < SERVO::MAX_ANGLE) {
        angle += SERVO::INCREMENT;
    } else {
        angle -= SERVO::INCREMENT;
    }
}

int Robot::main() {
    journey();
    return  0;
}

