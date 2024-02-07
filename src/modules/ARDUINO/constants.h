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
    int INFRARED = 0;
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
    int INCREMENT = 10;
};

struct SIDES {
    char GAUCHE = "L";
    char DROITE = "R";
};

struct SERVO {
    int INCREMENT = 5;
    int MIN_ANGLE = 15;
    int MAX_ANGLE = 90;
};

#endif //PROJET_CONSTANTS_H
