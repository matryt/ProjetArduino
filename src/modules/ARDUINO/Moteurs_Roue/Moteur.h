// Moteur.h
#ifndef PROJET_MOTEUR_H
#define PROJET_MOTEUR_H

#include <Arduino.h>
#include "../constants.h"

class Moteur {
public:
    void init(int enable, int in1, int in2);
    void config_speed(int speed);
    void start();
    void stop();
    void config_spinning(char direction);

private:
    int EN;
    int in1;
    int in2;
};

#endif //PROJET_MOTEUR_H
