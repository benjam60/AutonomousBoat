#ifndef OVERRIDEABLERUDDER_CPP
#define OVERRIDEABLERUDDER_CPP

class OverrideableRudder {
public:
	virtual void movePosition(int positionInDegrees) = 0;
	virtual ~OverrideableRudder() { }
};
#endif
