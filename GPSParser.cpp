#ifndef GPS_CPP
#define GPS_CPP
#include "SystemGPS.cpp"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct GPSCoordinates {
	float latitude = -1.0f;
	float longitude = -1.0f;
};

//TODO BE: assert only one message per read and Add asserts nth != 0
class GPSParser {
public:
	GPSParser(SystemGPS * gpsIn) : gps(gpsIn) { }

	struct GPSCoordinates waitAndGetNextPosition() {
	   struct GPSCoordinates gpsCoordinates;
	   while (-1.0f == gpsCoordinates.latitude || -1.0f == gpsCoordinates.longitude) {
		   const char * nmeaSentence = gps->waitAndReadData();
		   if ((strstr(nmeaSentence, "$GPRMC") != NULL) && gprmcNmeaMessageIsValid(nmeaSentence)) {
			   char * latitude = getCSVEntry(nmeaSentence, IndexOfCommaForLatitude);
			   char * longitude = getCSVEntry(nmeaSentence, IndexOfCommaForLongitude);
			   gpsCoordinates.latitude = atof(latitude);
			   gpsCoordinates.longitude = atof(longitude);
			   delete latitude;
			   delete longitude;
		   }
	   }
	   return gpsCoordinates;
	}

private:
	const bool gprmcNmeaMessageIsValid(const char * const nmeaMessage) const {
		int numCommas = 0;
		const int NmeaMessageLength = strlen(nmeaMessage);
		for (int i = 0; i < NmeaMessageLength; ++i) {
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

    const char * findComma(const char * csvRow, const int nth) const { //TODO BE: find out if should be passing in const pointer
		int numOfCommasSeen = 0;
		for(const char * index = csvRow; index[0] != '\0'; ++index) { //handle wrong input
			if (',' == index[0]) ++numOfCommasSeen;
			if (numOfCommasSeen == nth) return index;
		}
		return NULL; //handle
	}

	SystemGPS * gps = NULL;
	const int IndexOfCommaForLatitude = 3;
	const int IndexOfCommaForLongitude = 5;
};

#endif
