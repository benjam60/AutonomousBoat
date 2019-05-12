#ifndef TESTGPS_CPP
#define TESTGPS_CPP
#include "../SystemGPS.cpp"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


class TestGPS : public SystemGPS {
public:
	TestGPS(char input[2][150], int numSentences) {
		for (int i = 0; i < numSentences; ++i) {
			strcpy(gpsInput[i], input[i]);
		}
	}

	char * waitAndReadData() {
		return gpsInput[numNmeaSentencesRead++];
	}
private:
	int numNmeaSentencesRead = 0;
	char gpsInput[2][150];
};

#endif
