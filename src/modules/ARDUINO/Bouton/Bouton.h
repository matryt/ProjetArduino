//
// Created by mathi on 13/02/2024.
//

#ifndef PROJET_BOUTON_H
#define PROJET_BOUTON_H

#include <Arduino.h>

class Bouton {
public:
    void init(int pin);
public:
    int PIN;
    int readValue();
    bool waitUntilPressed();
};


#endif //PROJET_BOUTON_H
