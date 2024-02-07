#include "modules/ARDUINO/Capteur/Infrared.h"
#include "modules/ARDUINO/Robot/Robot.h"

Infrared capteur;
Robot robot;

void setup() {
  // put your setup code here, to run once:
  capteur.init()
  Serial.begin(9600);
  Robot.main();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(capteur.mesure());
  delay(150);
}
