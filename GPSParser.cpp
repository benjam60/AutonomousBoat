#ifndef GPS_CPP
#define GPS_CPP
#include "SystemGPS.cpp"

class GPSParser {
	SystemGPS * gps;
public:
	GPSParser(SystemGPS * gpsIn) : gps(gpsIn) { }

	const char * waitAndGetNextNmeaSentence() {
		return gps->waitAndReadData();
	}
};
#endif
