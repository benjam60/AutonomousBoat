#ifndef AUTOPILOT_CPP
#define AUTOPILOT_CPP

#include "GPSParser.cpp"

class AutoPilot {
public:
	AutoPilot(GPSParser * gpsParserIn) : gpsParser(gpsParserIn) { }

	//void driveToDestination

private:
	GPSParser * gpsParser = NULL;


};
#endif
