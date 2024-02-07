#include "modules/ARDUINO/Capteur/Ultrasons.h"

Ultrasons capteur;

void setup() {
  // put your setup code here, to run once:
  capteur.init()
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(capteur.mesure());
  delay(150);
}
