#ifndef GPS_CPP
#define GPS_CPP
#include "SystemGPS.cpp"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct GPSCoordinates {
	float latitude;
};


class GPSParser {
	SystemGPS * gps;

public:
	GPSParser(SystemGPS * gpsIn) : gps(gpsIn) { }

	struct GPSCoordinates waitAndGetNextPosition() {
	   const char * gpsInput = gps->waitAndReadData();
	   char * gpsInput1 = new char[strlen(gpsInput) + 1];
	   strcpy(gpsInput1, gpsInput);
	   float latitude = atof(getCSVEntry(gpsInput1, 3));
	   struct GPSCoordinates gpsCoordinates;
	   gpsCoordinates.latitude = latitude;
	   return gpsCoordinates;
	}

	const char * getCSVEntry(char * csvRow, int nth) {
		const char * startingIndexOfEntry = getIndexOfComma(csvRow, nth); //if (nth == 0) 0 else
		const char * endingIndexOfEntry = getIndexOfComma(csvRow, nth+1); //account for /n/r at end
		int entrySize = endingIndexOfEntry - startingIndexOfEntry;
		char * outputBuffer = new char[entrySize];
		strncpy(outputBuffer, startingIndexOfEntry + 1, entrySize - 1); //handle minus and place one in case empty or 1 char
		return outputBuffer;
	}

    const char * getIndexOfComma(char * csvRow, int nth) {
		int numOfCommasSeen = 0;
		for(char * index = csvRow; (char)index[0] != '\n'; ++index) { //handle wrong input
			if (index[0] == ',') ++numOfCommasSeen;
			if (numOfCommasSeen == nth) return index;
		}
		return nullptr; //handle
	}
};

#endif
