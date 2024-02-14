#include "src/modules/ARDUINO/Capteur/Infrared.h"
#include <Arduino.h>
#include "src/modules/ARDUINO/Robot/Robot.h"

float m;

Infrared capteur;
Robot robot;

void setup() {
  // put your setup code here, to run once:
  capteur.init();
  Serial.begin(9600);
  robot.main();
}



void loop() {

}
