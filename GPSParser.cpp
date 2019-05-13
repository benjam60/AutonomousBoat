#ifndef GPS_CPP
#define GPS_CPP
#include "SystemGPS.cpp"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct GPSCoordinates {
	float latitude = -1.0f;
};

//TODO BE: cleanup memory
//TODO BE: assert only one message per read
//TODO BE: Add asserts nth != 0
class GPSParser {
public:
	GPSParser(SystemGPS * gpsIn) : gps(gpsIn) { }

	struct GPSCoordinates waitAndGetNextPosition() {
	   struct GPSCoordinates gpsCoordinates;
	   while (gpsCoordinates.latitude == -1.0f) {
		   char * nmeaSentence = gps->waitAndReadData();
		   if ((strstr(nmeaSentence, "$GPRMC") != NULL) && gprmcNmeaMessageIsValid(nmeaSentence)) {
			   char * latitude = getCSVEntry(nmeaSentence, IndexOfCommaForLatitude);
			   gpsCoordinates.latitude = atof(latitude);
			   delete latitude;
		   }
	   }
	   return gpsCoordinates;
	}

private:
	bool gprmcNmeaMessageIsValid(const char * nmeaMessage) const {
		int numCommas = 0;
		for (int i = 0; i < strlen(nmeaMessage); ++i) { //TODO: do not go on forever
			if (nmeaMessage[i] == ',') { ++numCommas; }
		}
		const int ExpectedCommas = 12;
		return numCommas == ExpectedCommas;
	}

	char * getCSVEntry(char * csvRow, int nth) {
		const char * startingIndexOfEntry = findComma(csvRow, nth) + 1;
		const char * exclusiveEndingIndexOfEntry = findComma(csvRow, nth+1); //account for /n/r at end
		const int entrySize = exclusiveEndingIndexOfEntry - startingIndexOfEntry;
		if (entrySize != 0)  {
			char * outputBuffer = new char[entrySize];
			return strncpy(outputBuffer, startingIndexOfEntry, entrySize);
		}
		else {
			char * outputBuffer = new char[5];
			return strcpy(outputBuffer, "-1.0");
		}
	}

    const char * findComma(char * csvRow, int nth) {
		int numOfCommasSeen = 0;
		for(char * index = csvRow; (char)index[0] != '\0'; ++index) { //handle wrong input
			if ((char)index[0] == ',') ++numOfCommasSeen;
			if (numOfCommasSeen == nth) return index;
		}
		return NULL; //handle
	}

	SystemGPS * gps;
	const int IndexOfCommaForLatitude = 3;
};

#endif
