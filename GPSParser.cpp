#ifndef GPS_CPP
#define GPS_CPP
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "SystemGPS.cpp"

struct GPSCoordinates {
	float latitude = -1.0f;
	float longitude = -1.0f;
	char northOrSouth = 'U'; //macros? for undefined north and south
	char westOrEast = 'U';
	GPSCoordinates() { }
	GPSCoordinates(float lat, float longi, char nors, char eorw) : latitude(lat), longitude(longi), northOrSouth(nors), westOrEast(eorw) { }
};

//TODO BE: assert only one message per read and Add asserts nth != 0
class GPSParser {
public:
	GPSParser(SystemGPS * gpsIn) : gps(gpsIn) { }

	struct GPSCoordinates waitAndGetNextPosition() {
	   struct GPSCoordinates gpsCoordinates;
	   while (!successfullyGotAllFields(gpsCoordinates)) {
		   const char * nmeaSentence = gps->waitAndReadData();
		   if (isValidGPRMCNmeaMessage(nmeaSentence)) {
			   char * latitude = getCSVEntry(nmeaSentence, IndexOfCommaForLatitude);
			   char * longitude = getCSVEntry(nmeaSentence, IndexOfCommaForLongitude);
			   char * longitudeDirection = getCSVEntry(nmeaSentence, IndexOfCommaForNorthSouth); //clear memory
			   char * lattitudeDirection = getCSVEntry(nmeaSentence, IndexOfCommaForWestOrEast); //clear memory
			   gpsCoordinates = GPSCoordinates(atof(latitude), atof(longitude), longitudeDirection[0], lattitudeDirection[0]);
			   delete latitude;
			   delete longitude;
			   delete longitudeDirection;
			   delete lattitudeDirection;
		   }
	   }
	   return gpsCoordinates;
	}

private:
	const bool isValidGPRMCNmeaMessage(const char * nmeaMessage) const {
		int numCommas = 0;
		const int NmeaMessageLength = strlen(nmeaMessage);
		for (int i = 0; i < NmeaMessageLength; ++i) {
			if (nmeaMessage[i] == ',') { ++numCommas; }
		}
		const int ExpectedCommas = 12;
		char messageStatus = getCSVEntry(nmeaMessage, IndexOfCommaForMessageStatus)[0]; //DELETE
		return ExpectedCommas == numCommas && 'A' == messageStatus && strstr(nmeaMessage, "$GPRMC") != NULL;
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

    const bool successfullyGotAllFields(const struct GPSCoordinates gpsCoordinates) {
    	return -1.0f != gpsCoordinates.latitude && -1.0f != gpsCoordinates.longitude && isValidLatitudeDirection(gpsCoordinates.northOrSouth)
    	&& isValidLongitudeDirection(gpsCoordinates.westOrEast);
    }

    const bool isValidLatitudeDirection(const char direction) const { return 'N' == direction || 'S' == direction; }

    const bool isValidLongitudeDirection(const char direction) const { return 'W' == direction || 'E' == direction; }


//    const bool isAllAscii(const char * csvRow) const { doesn't fix anything
//    	const int NmeaMessageLength = strlen(csvRow);
//    	for (int i = 0; i < NmeaMessageLength; ++i) {
//    		if (isascii(csvRow[i]) == 0) { return false; }
//    	}
//    	return true;
//    }

	SystemGPS * gps = NULL;
	const int IndexOfCommaForMessageStatus = 2;
	const int IndexOfCommaForLatitude = 3;
	const int IndexOfCommaForNorthSouth = 4;
	const int IndexOfCommaForLongitude = 5;
	const int IndexOfCommaForWestOrEast = 6;
};

#endif
