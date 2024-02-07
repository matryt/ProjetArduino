//
// Created by mathi on 07/02/2024.
//

#include "Robot.h"
#include "../Capteur/Infrared.h"
#include "../Moteurs_Roue/Moteur.h"
#include "../constants.h"

Infrared capteur;
Moteur gauche;
Moteur droite;
Servomoteur s;
int angle = SERVO::MIN_ANGLE;

class Robot {
    void init() {
        capteur.init();
        gauche.init(PINS::ENA, PINS::IN1, PINS::IN2);
        droite.init(PINS::ENB, PINS::IN3, PINS::IN4);
    }

    void config_speed(int speed) {
        gauche.config_speed(speed);
        droite.config_speed(speed);
    }

    void speed_up(int speed, int target_speed, int increment) {
        while (speed < target_speed) {
            speed += increment;
            config_speed(speed);
            delay(MOTEUR::DELAI_VARIATION_VITESSE);
            process_next_angle();
            s.write_angle(angle);
        }
    }

    void slow_down(int speed, int target_speed, int increment) {
        while (speed < target_speed) {
            speed += increment;
            config_speed(speed);
            delay(MOTEUR::DELAI_VARIATION_VITESSE);
            process_next_angle();
            s.write_angle(angle);
        }
    }

    void config_spinning(char direction) {
        gauche.config_spinning(direction);
        droite.config_spinning(direction);
    }

    void start() {
        gauche.start();
        droite.start();
    }

    void stop() {
        gauche.stop();
        droite.stop();
    }

    void halfturn() {
        stop();
        config_spinning(DIRECTION::ARRIERE);
        start();
        droite.config_speed(MOTEUR::VITESSE_MIN + 50);
        delay(MOTEUR::DELAI_DEMI_TOUR);
        stop();
        config_spinning(DIRECTION::AVANT);
    }

    void straight_line() {
        config_spinning(DIRECTION::AVANT);
        start();
        speed_up(MOTEUR::VITESSE_MIN, MOTEUR::VITESSE_MAX, MOTEUR::INCREMENT);
        while (capteur.mesure() > 79) {
            delay(MOTEUR::DELAI_LINEAIRE);
            process_next_angle();
            s.write_angle(angle);
        }
        slow_up(MOTEUR::VITESSE_MAX, MOTEUR::VITESSE_MIN, MOTEUR::INCREMENT);
        stop();
    }

    void journey() {
        straight_line();
        halfturn();
        straight_line();
    }

    void process_next_angle() {
        if (angle < SERVO::ANGLE_MAX) {
            angle += SERVO::INCREMENT;
        }
        else {
            angle -= SERVO::INCREMENT;
        }
    }

    int main() {
        journey();
        return 0;
    }
};

