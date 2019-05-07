#ifndef TESTGPS_CPP
#define TESTGPS_CPP
#include "../SystemGPS.cpp"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

class TestGPS : public SystemGPS {
public:
	TestGPS(char ** input, int numSentences) {
		for (int i = 0; i < numSentences; ++i) {
			strcpy(gpsInput[i], input[i]);
//			gpsInput[i] = new char[strlen(input[i]) + 1];
//			strcpy(gpsInput[i], input[i]);
		}
	}

	const char * waitAndReadData() {
		return gpsInput[numNmeaSentencesRead++];
	}
private:
	int numNmeaSentencesRead = 0;
	char gpsInput[][150];
};

#endif
