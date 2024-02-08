#include "src/modules/ARDUINO/Capteur/Infrared.h"
#include <Arduino.h>
//#include "src/modules/ARDUINO/Robot/Robot.h"

float m;

Infrared capteur;
//Robot robot;

void setup() {
  // put your setup code here, to run once:
  capteur.init();
  Serial.begin(9600);
  //Robot.main();
}

float moyenne() {
  float somme = 0;
  for (int i = 0; i<30; i++) {
    somme += capteur.distanceBrute();
    delay(100);
  }
  return somme/30;
}

void loop() {
  // put your main code here, to run repeatedly:
  m = moyenne();
  Serial.println(m);
  Serial.println(capteur.convertirDistance(m));
  while (!(Serial.available())) {
    delay(100);
  }
  Serial.read();
}
