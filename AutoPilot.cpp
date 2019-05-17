#ifndef AUTOPILOT_CPP
#define AUTOPILOT_CPP

#include "GPSParser.cpp"
#include "OverrideableCompass.cpp"
#include "OverrideableRudder.cpp"
class AutoPilot {
public: //should i make these heap or stack?
	AutoPilot(GPSParser * gpsParserIn, OverrideableCompass * compassIn, OverrideableRudder * rudderIn) : gpsParser(gpsParserIn), compass(compassIn), rudder(rudderIn) { }
	void driveToWaypoint(float lattitude, char northOrSouth, float longitude, char eastOrWest) {
		rudder->movePosition(90);
	}

private:
	GPSParser * gpsParser = NULL;
	OverrideableCompass * compass = NULL;
	OverrideableRudder * rudder = NULL;

};
#endif
