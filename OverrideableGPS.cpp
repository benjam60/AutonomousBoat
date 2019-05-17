#ifndef OVERRIDEABLEGPS_CPP
#define OVERRIDEABLEGPS_CPP

class OverrideableGPS {
public:
	virtual char * waitAndReadData() = 0;
	virtual ~OverrideableGPS() { }
};
#endif
