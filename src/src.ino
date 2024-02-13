#include "modules/ARDUINO/Capteur/Infrared.h"
#include "modules/ARDUINO/Robot/Robot.h"
#include "modules/ARDUINO/Bouton/Bouton.h"
#include "modules/ARDUINO/constants.h"

Infrared capteur;
//Robot robot;
Bouton bouton;

void setup() {
  // put your setup code here, to run once:
  capteur.init();
  bouton.init(PINS::BOUTON);
  Serial.begin(9600);
  //bouton.waitUntilPressed();
  //Robot.main();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(capteur.mesure());
  delay(150);
}
