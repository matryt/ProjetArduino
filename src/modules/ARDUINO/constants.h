// constants.h
#ifndef PROJET_CONSTANTS_H
#define PROJET_CONSTANTS_H

namespace PINS {
    const int ENA =  3;
    const int ENB =  10;
    const int IN1 =  6;
    const int IN2 =  7;
    const int IN3 =  8;
    const int IN4 =  9;
    const int INFRARED =  0;
    const int SERVO =  13;
    const int BOUTON = 4;
}

namespace DIRECTION {
    const char AVANT = 'V';
    const char ARRIERE = 'R';
}

namespace MOTEUR {
    const int VITESSE_MIN =  65;
    const int VITESSE_MAX =  255;
    const int VITESSE_DEMI_TOUR =  100;
    const int DELAI_VARIATION_VITESSE = 20;
    const int DELAI_DEMI_TOUR = 1000;
    const int DELAI_LINEAIRE = 200;
    const int INCREMENT =  10;
    const int DISTANCE_FREINAGE = 50;
    const int DIFF_VITESSE_DEMITOUR = 50;
}

namespace SIDES {
    const char GAUCHE = 'L';
    const char DROITE = 'R';
}

namespace SERVO {
    const int INCREMENT =  5;
    const int MIN_ANGLE =  15;
    const int MAX_ANGLE =  90;
}

namespace BOUTON {
    const int TARGET_VALUE = 1;
    const int DELAI_ATTENTE = 200;
}

#endif //PROJET_CONSTANTS_H
