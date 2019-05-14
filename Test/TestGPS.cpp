#ifndef TESTGPS_CPP
#define TESTGPS_CPP
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../SystemGPS.cpp"


class TestGPS : public SystemGPS {
public:
	TestGPS(char input[10][150], int numSentences) {
		for (int i = 0; i < numSentences; ++i) {
			strcpy(gpsInput[i], input[i]);
		}
	}

	char * waitAndReadData() {
		return gpsInput[numNmeaSentencesRead++];
	}
private:
	int numNmeaSentencesRead = 0;
	char gpsInput[10][150];
};

#endif
