#ifndef GPS_CPP
#define GPS_CPP
#include "SystemGPS.cpp"

struct GPSCoordinates {
	float latitude;
};


class GPSParser {
	SystemGPS * gps;
public:
	GPSParser(SystemGPS * gpsIn) : gps(gpsIn) { }

	struct GPSCoordinates waitAndGetNextNmeaSentence() {
	   const char * gpsInput = gps->waitAndReadData();
	   struct GPSCoordinates gpsCoordinates;
	   gpsCoordinates.latitude = 1.0f;
	   return gpsCoordinates;
	}
};

#endif
