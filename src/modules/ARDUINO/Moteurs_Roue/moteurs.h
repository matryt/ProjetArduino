#ifndef PROJET_MOTEURS_H
#define PROJET_MOTEURS_H


void init_pins();

void config_capteur();

void start();

void stop();

void config_speed(int speed, char side);

void speed_up_one(int speed, int target_speed, int increment, char side);

void speed_up_all(int speed, int target_speed, int increment);

void slow_down_one(int speed, int target_speed, int increment, char side);

void slow_down_all(int speed, int target_speed, int increment);

void config_spinning_one(char direction, char side);

void config_spinning_all(char direction);

void demi_tour();

void ligne_droite();

void trajet();

#endif //PROJET_MOTEURS_H
