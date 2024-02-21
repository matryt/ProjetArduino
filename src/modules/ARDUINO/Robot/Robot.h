// Robot.h
#ifndef PROJET_SYSTEME_H
#define PROJET_SYSTEME_H

#include <Arduino.h>
#include "../Capteur/Infrared.h"
#include "../Moteurs_Roue/Moteur.h"
#include "../constants.h"
#include "../Servomoteur/Servomoteur.h"


class Robot {
    Infrared capteur;
    Moteur gauche;
    Moteur droite;
    Servomoteur s;

public:
    void init();
    void config_speed(int speed,float offset);
    void speed_up(int speed, int target_speed, int increment);
    void slow_down(int speed, int target_speed, int increment);
    void config_spinning(char direction);
    void start();
    void stop();
    void halfturn();
    void straight_line();
    void journey();
    int main();
};

#endif // PROJET_SYSTEME_H
