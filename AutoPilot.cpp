#ifndef AUTOPILOT_CPP
#define AUTOPILOT_CPP

#include <math.h>
#include "GPSParser.cpp"
#include "OverrideableCompass.cpp"
#include "OverrideableRudder.cpp"


typedef float Radians;

class AutoPilot {
public: //should i make these heap or stack?

	AutoPilot(GPSParser * gpsParserIn, OverrideableCompass * compassIn, OverrideableRudder * rudderIn) : gpsParser(gpsParserIn), compass(compassIn), rudder(rudderIn) { }

	void driveToWaypoint(GPSCoordinates wayPoint) {
		GPSCoordinates currentPosition;
		currentPosition = gpsParser->waitAndGetNextPosition();
		//get the direction
		float heading = compass->getCurrentHeadingInDegrees();
		float error = calculateError(currentPosition, wayPoint, heading);
		int newRudderAngle = 90 + (error/2);
		//calculate the error
		rudder->movePosition(newRudderAngle);
	}

private:
	float calculateError(GPSCoordinates currentPosition, GPSCoordinates wayPoint, float heading) { //assert divide by zero
		Radians relativeBearingLatitude = toRadians(currentPosition.latitude);
		Radians relativeBearingLongitude = toRadians(wayPoint.longitude);
		Radians	wayPointLatitude = toRadians(wayPoint.latitude);
		Radians wayPointLongitude = toRadians(wayPoint.longitude);
		Radians deltaLatitude = toRadians(wayPointLatitude - relativeBearingLatitude);
		Radians deltaLongitude = toRadians(wayPointLongitude - relativeBearingLongitude);

		float intermediate1 = sin(deltaLatitude/2.0) * sin(deltaLatitude/2.0) +
		cos(relativeBearingLatitude) * cos(wayPointLatitude) *
		sin(deltaLongitude/2.0) * sin(deltaLongitude/2.0);
		float intermediate2 = 2 * atan2(sqrt(intermediate1), sqrt(1-intermediate1));

		return EarthsRadius * intermediate2;
	}
	inline float toRadians(float degrees) { return degrees * (M_PI / 180.0); }
	const float EarthsRadius = 6371000.0f;
	GPSParser * gpsParser;
	OverrideableCompass * compass;
	OverrideableRudder * rudder;

};
#endif


/*
 * var R = 6371e3; // metres
var φ1 = lat1.toRadians();
var φ2 = lat2.toRadians();
var Δφ = (lat2-lat1).toRadians();
var Δλ = (lon2-lon1).toRadians();

var a = Math.sin(Δφ/2) * Math.sin(Δφ/2) +
        Math.cos(φ1) * Math.cos(φ2) *
        Math.sin(Δλ/2) * Math.sin(Δλ/2);
var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));

var d = R * c;
 *
 */
