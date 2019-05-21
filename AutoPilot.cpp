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
		int heading =(int) compass->getCurrentHeadingInDegrees();
		if (!willInterceptWaypoint(currentPosition.latitude, wayPoint.latitude, heading)) {
			float hypotenuseDistanceInMeters = calculateDistanceHaversineInMeters(currentPosition, wayPoint);
			GPSCoordinates rightAngleCorner(0.0f, 1.0f, 'N', 'E');
			float oppositeSideDistanceInMeters = calculateDistanceHaversineInMeters(rightAngleCorner, currentPosition);
			int error = asin(oppositeSideDistanceInMeters/hypotenuseDistanceInMeters) * (180.0 / M_PI);
			printf("The error is %d\n", error);
			int newRudderAngle = 90 + (error/2);
			//calculate the error
			rudder->movePosition(newRudderAngle);
		}
		else {
			printf("here!");
			rudder->movePosition(heading);
		}
	}

private:
	//Haversine formula
	float calculateDistanceHaversineInMeters(GPSCoordinates currentPosition, GPSCoordinates wayPoint) { //assert divide by zero
		Radians relativeBearingLatitude = toRadians(currentPosition.latitude);
		Radians	wayPointLatitude = toRadians(wayPoint.latitude);
		Radians deltaLatitude = toRadians(wayPoint.latitude - currentPosition.latitude);
		Radians deltaLongitude = toRadians(wayPoint.longitude - currentPosition.longitude);

		Radians intermediate1 = sin(deltaLatitude/2.0) * sin(deltaLatitude/2.0) +
		cos(relativeBearingLatitude) * cos(wayPointLatitude) *
		sin(deltaLongitude/2.0) * sin(deltaLongitude/2.0);
		Radians intermediate2 = 2.0 * atan2(sqrt(intermediate1), sqrt(1.0-intermediate1));

		return (EarthsRadius * intermediate2)/ MetersInKilometer;
	}
	const bool willInterceptWaypoint(float currentLatitude, float wayPointLatitude, int heading) const { //add units to heading and latitude
		return currentLatitude == wayPointLatitude && heading == 90;

	}
	inline float toRadians(float degrees) { return degrees * (M_PI / 180.0); }
	const float EarthsRadius = 6371000.0f;
	const float MetersInKilometer = 1.0f;
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
