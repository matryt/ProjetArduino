//
// Created by mathi on 07/02/2024.
//

#ifndef PROJET_CONSTANTS_H
#define PROJET_CONSTANTS_H

struct PINS {
    int ENA = 3;
    int ENB = 10;
    int IN1 = 6;
    int IN2 = 7;
    int IN3 = 8;
    int IN4 = 9;
    int ULTRASONS = 0;
    int SERVO = 13;
};

struct DIRECTION {
    char AVANT = "V";
    char ARRIERE = "R",
};

struct MOTEUR {
    int VITESSE_MIN = 65;
    int VITESSE_MAX = 255;
    int VITESSE_DEMI_TOUR = 100;
    int DELAI_VARIATION_VITESSE = 20;
    int DELAI_DEMI_TOUR = 1000;
    int DELAI_LINEAIRE = 500;
};

struct SIDES {
    char GAUCHE = "L";
    char DROITE = "R";
};

#endif //PROJET_CONSTANTS_H
