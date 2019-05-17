#ifndef OVERRIDEABLECOMPASS_CPP
#define OVERRIDEABLECOMPASS_CPP

class OverrideableCompass {
public:
	virtual float getCurrentHeadingInDegrees() = 0;
	virtual ~OverrideableCompass() { }
};

#endif
