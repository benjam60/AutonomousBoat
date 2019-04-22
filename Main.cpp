#include "Rudder.cpp"
#include "GPS.cpp"

//Servo myServo;
//Rudder * rudder;
//
//
//void setup() {
//  rudder = new Rudder(myServo); //must call in setup
//}
//
//void loop() {
//
//  for (int i = 90; i < 180; ++i) {
//        rudder->movePosition(i);
//  }
//
//}



// The serial connection to the GPS module
GPS * gps = NULL;

void setup(){
  gps = new GPS(1, 0);
}

void loop(){
	Serial.write("write on line");
	Serial.write(gps->readData().c_str());
	Serial.write(gps->readData().c_str());
//	Serial.write(gps->readData().c_str());
	while(1) { }
}
