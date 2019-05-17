#ifndef GPS_CPP
#define GPS_CPP

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WString.h>

#include "OverrideableGPS.cpp"


class GPS : public OverrideableGPS {
public:
	GPS(int rx, int tx) : softwareSerial(SoftwareSerial(rx,tx)) {
		Serial.begin(BaudRate);
		softwareSerial.begin(BaudRate);
	}


	char * waitAndReadData() { return softwareSerial.readString().c_str(); }

private:
	const int BaudRate = 9600;
	SoftwareSerial softwareSerial;
};

#endif
