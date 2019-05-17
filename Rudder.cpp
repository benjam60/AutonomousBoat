/*
 * Rudder.cpp
 *
 *  Created on: Apr 21, 2019
 *      Author: ben
 */
#ifndef RUDDER_CPP
#define RUDDER_CPP
#include <Arduino.h>
#include <Servo.h>


class Rudder { //make singleton because there is only one
   const int ArduinoPinNumber = 2;
   Servo rudderServo;
   int currentDirectionInDegrees = StraightAheadInDegrees;

   public:
   Rudder(Servo myServo) {
    rudderServo = myServo;
    rudderServo.attach(ArduinoPinNumber);
    rudderServo.write(StraightAheadInDegrees);
   }

   void movePosition(int positionInDegrees) { //TODO: Add input constraints
    rudderServo.write(positionInDegrees);
    const int requiredLatencyBetweenMoves = 10;
    delay(requiredLatencyBetweenMoves);
    currentDirectionInDegrees = positionInDegrees;
   }

   int getCurrentPosition() {
	   //rudderServo.read() should be equal, good test
	   //what if the servo fails-- how would you know?
	  return rudderServo.read();
   }

   const int StraightAheadInDegrees = 90;

};
#endif
