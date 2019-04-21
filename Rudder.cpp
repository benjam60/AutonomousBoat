/*
 * Rudder.cpp
 *
 *  Created on: Apr 21, 2019
 *      Author: ben
 */
#include <Arduino.h>
#include <Servo.h>


class Rudder { //make singleton because there is only one
   const int StraightAheadInDegrees = 90;
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
    int requiredLatencyBetweenMoves = 10;
    delay(requiredLatencyBetweenMoves);
    currentDirectionInDegrees = positionInDegrees;
   }

   int getCurrentPosition() {
	  return currentDirectionInDegrees;
   }

};

