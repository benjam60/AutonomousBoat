#include <Arduino.h>
#include <SoftwareSerial.h>

class SystemGPS {
public:
	virtual String readData() = 0;
	virtual ~SystemGPS() { }
};


class GPS : public SystemGPS {
public:
	GPS(int rxPinNumber, int txPinNumber) {
		boolean hasInverseLogic = false;
		softwareSerial = new SoftwareSerial(rxPinNumber, txPinNumber, hasInverseLogic);
		Serial.begin(BaudRate);
		softwareSerial->begin(BaudRate);
	}

	String readData() {
		return softwareSerial->readString();
	}

private:
	const int BaudRate = 9600;
	SoftwareSerial * softwareSerial = NULL;
};
