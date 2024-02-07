//
// Created by mathi on 07/02/2024.
//

#ifndef PROJET_CONSTANTS_H
#define PROJET_CONSTANTS_H

struct PINS {
    int ENA = 10;
    int ENB = 3;
    int IN1 = 9;
    int IN2 = 8;
    int IN3 = 7;
    int IN4 = 6;
};

struct DIRECTION {
    char AVANT = "V";
    char ARRIERE = "R",
};

struct MOTEUR {
    int VITESSE_MIN = 60;
    int VITESSE_MAX = 255;
    int DELAI_VARIATION_VITESSE = 20;
};

struct SIDES {
    char GAUCHE = "L";
    char DROITE = "R";
};

#endif //PROJET_CONSTANTS_H
