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
class GPSParser {
	SystemGPS * gps;
	char NOENTRY[5] = "-1.0";
	const int NoEntrySize = 1;
public:
	GPSParser(SystemGPS * gpsIn) : gps(gpsIn) { }

	struct GPSCoordinates waitAndGetNextPosition() {
	   struct GPSCoordinates gpsCoordinates;
	   while (gpsCoordinates.latitude == -1.0f) {
		   char * gpsInput = gps->waitAndReadData();
		   if (strstr(gpsInput, "$GPRMC") != NULL) {
			   float latitude = atof(getCSVEntry(gpsInput, 3));
			   gpsCoordinates.latitude = latitude;
		   }
	   }
	   return gpsCoordinates;
	}

	char * getCSVEntry(char * csvRow, int nth) {
		const char * startingIndexOfEntry = getIndexOfComma(csvRow, nth); //if (nth == 0) 0 else
		const char * endingIndexOfEntry = getIndexOfComma(csvRow, nth+1); //account for /n/r at end
		int entrySize = endingIndexOfEntry - startingIndexOfEntry;
		if (entrySize == NoEntrySize) { return NOENTRY; }
		else {
			char * outputBuffer = new char[entrySize];
			strncpy(outputBuffer, startingIndexOfEntry + 1, entrySize - 1); //handle minus and place one in case empty or 1 char
			return outputBuffer;
		}
	}

    const char * getIndexOfComma(char * csvRow, int nth) {
		int numOfCommasSeen = 0;
		for(char * index = csvRow; (char)index[0] != '\n'; ++index) { //handle wrong input
			if ((char)index[0] == ',') ++numOfCommasSeen;
			if (numOfCommasSeen == nth) return index;
		}
		return nullptr; //handle
	}
};

#endif
