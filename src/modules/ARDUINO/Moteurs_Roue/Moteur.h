//
// Created by mathi on 07/02/2024.
//

#ifndef PROJET_MOTEUR_H
#define PROJET_MOTEUR_H


class Moteur {
    void init(int enable, int in1, int in2);
    void config_speed(int speed);
    void start();
    void stop();
    void config_spinning(char direction);
};


#endif //PROJET_MOTEUR_H
