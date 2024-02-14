#include "modules/ARDUINO/Capteur/Infrared.h"
#include "modules/ARDUINO/Robot/Robot.h"
#include "modules/ARDUINO/Bouton/Bouton.h"
#include "modules/ARDUINO/constants.h"

Infrared capteur;
Robot robot;
Bouton bouton;

void setup() {
  // put your setup code here, to run once:
  capteur.init();
  bouton.init(PINS::BOUTON);
  Serial.begin(9600);
  //bouton.waitUntilPressed();
  robot.main();
}

void loop() {
}
