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
		   const char * nmeaSentence = gps->waitAndReadData();
		   if ((strstr(nmeaSentence, "$GPRMC") != NULL) && gprmcNmeaMessageIsValid(nmeaSentence)) {
			   char * latitude = getCSVEntry(nmeaSentence, IndexOfCommaForLatitude);
			   gpsCoordinates.latitude = atof(latitude);
			   delete latitude;
		   }
	   }
	   return gpsCoordinates;
	}

private:
	const bool gprmcNmeaMessageIsValid(const char * const nmeaMessage) const {
		int numCommas = 0;
		const int NmeaMessageLength = strlen(nmeaMessage);
		for (int i = 0; i < NmeaMessageLength; ++i) { //TODO: do not go on forever
			if (nmeaMessage[i] == ',') { ++numCommas; }
		}
		const int ExpectedCommas = 12;
		return ExpectedCommas == numCommas;
	}

	char * getCSVEntry(const char * csvRow, const int nth) const {
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

    const char * findComma(const char * csvRow, int nth) const { //TODO BE: find out if should be passing in const pointer
		int numOfCommasSeen = 0;
		for(const char * index = csvRow; (char)index[0] != '\0'; ++index) { //handle wrong input
			if (',' == index[0]) ++numOfCommasSeen;
			if (numOfCommasSeen == nth) return index;
		}
		return NULL; //handle
	}

	SystemGPS * gps;
	const int IndexOfCommaForLatitude = 3;
};

#endif
