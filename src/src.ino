#include "modules/ESP32/LiveStream.cpp"

LiveStream live;
Hotspot hotspot;

void setup() {
  // put your setup code here, to run once:
  live.init();
  live.main();
}

void loop() {
  // put your main code here, to run repeatedly:

}
