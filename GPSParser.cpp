#ifndef GPS_CPP
#define GPS_CPP
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
//#include <assert.h> //TO REMOVE AFTER INITIAL TESTS!!!
//make north and south positive and negative...but then need to check zero


#include "OverrideableGPS.cpp"

#define UNDEFINED_COORDINATE -1.0f;
#define UNDEFINED_DIRECTION 'U';

//TODO: Add concept of degrees and radians!!!
struct GPSCoordinates {
	float latitude = UNDEFINED_COORDINATE;
	float longitude = UNDEFINED_COORDINATE;
	char northOrSouth = UNDEFINED_DIRECTION; //macros? for undefined north and south
	char westOrEast = UNDEFINED_DIRECTION;
	GPSCoordinates() { }
	GPSCoordinates(float lat, float lon, char NS, char WE) : latitude(lat), longitude(lon), northOrSouth(NS), westOrEast(WE) { }
};

//TODO BE: assert only one message per read and Add asserts nth != 0
class GPSParser {
public:
	GPSParser(OverrideableGPS * gpsIn) : gps(gpsIn) { }

	struct GPSCoordinates waitAndGetNextPosition() {
	   struct GPSCoordinates gpsCoordinates;
	   while (!successfullyGotAllFields(gpsCoordinates)) {
		   const char * nmeaSentence = gps->waitAndReadData();
		   if (isValidGPRMCNmeaMessage(nmeaSentence)) {
			   float latitude = getCSVEntry(nmeaSentence, IndexOfCommaForLatitude);
			   float longitude = getCSVEntry(nmeaSentence, IndexOfCommaForLongitude);
			   const char longitudeDirection = getCSVEntryChar(nmeaSentence, IndexOfCommaForNorthSouth);
			   const char lattitudeDirection = getCSVEntryChar(nmeaSentence, IndexOfCommaForWestOrEast);
			   gpsCoordinates = GPSCoordinates(latitude, longitude, longitudeDirection, lattitudeDirection);
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
		const char messageStatus = getCSVEntryChar(nmeaMessage, IndexOfCommaForMessageStatus);
		return ExpectedCommas == numCommas && OkayMessageStatus == messageStatus && strstr(nmeaMessage, "$GPRMC") != NULL;
	}

    float getCSVEntry(const char * csvRow, const int nth) const {
		const char * startingIndexOfEntry = findComma(csvRow, nth) + 1;
		const char * exclusiveEndingIndexOfEntry = findComma(csvRow, nth+1); //account for /n/r at end
		const int entrySize = exclusiveEndingIndexOfEntry - startingIndexOfEntry;
		if (entrySize != 0)  {
			char outputBuffer[entrySize];
			return atof(strncpy(outputBuffer, startingIndexOfEntry, entrySize));
		}
		else { return UNDEFINED_COORDINATE; }
	}

    char getCSVEntryChar(const char * csvRow, const int nth) const {
		const char * startingIndexOfEntry = findComma(csvRow, nth) + 1;
		const char * exclusiveEndingIndexOfEntry = findComma(csvRow, nth+1); //account for /n/r at end
		const int entrySize = exclusiveEndingIndexOfEntry - startingIndexOfEntry;
		return (entrySize != 0) ? startingIndexOfEntry[0] : UNDEFINED_DIRECTION;
	}

    const char * findComma(const char * csvRow, const int nth) const {
		int numOfCommasSeen = 0;
		for(const char * index = csvRow; index[0] != '\0'; ++index) { //see if this is how a message actually ends!! or if return carriage
			if (',' == index[0]) ++numOfCommasSeen;
			if (numOfCommasSeen == nth) return index;
		}
		return NULL; //handle
	}

    const bool successfullyGotAllFields(const struct GPSCoordinates gpsCoordinates) {
    	return -1.0f != gpsCoordinates.latitude && -1.0f != gpsCoordinates.longitude
    			&& isValidLatitudeDirection(gpsCoordinates.northOrSouth) && isValidLongitudeDirection(gpsCoordinates.westOrEast);
    }

    const bool isValidLatitudeDirection(const char direction) const { return 'N' == direction || 'S' == direction; }

    const bool isValidLongitudeDirection(const char direction) const { return 'W' == direction || 'E' == direction; }


	OverrideableGPS * gps = NULL;
	const int IndexOfCommaForMessageStatus = 2;
	const int IndexOfCommaForLatitude = 3;
	const int IndexOfCommaForNorthSouth = 4;
	const int IndexOfCommaForLongitude = 5;
	const int IndexOfCommaForWestOrEast = 6;
	const char OkayMessageStatus = 'A';
};

#endif
