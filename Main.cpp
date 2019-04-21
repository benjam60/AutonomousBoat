#include "Rudder.cpp"

Servo myServo;
Rudder * rudder;

void setup() {
  rudder = new Rudder(myServo); //must call in setup
}

void loop() {

  for (int i = 90; i < 180; ++i) {
        rudder->movePosition(i);
  }

}

