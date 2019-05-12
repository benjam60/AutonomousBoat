#ifndef SYSTEMGPS_CPP
#define SYSTEMGPS_CPP

class SystemGPS {
public:
	virtual char * waitAndReadData() = 0;
	virtual ~SystemGPS() { }
};
#endif
