#ifndef TESTCOMPASS_CPP
#define TESTCOMPASS_CPP

#include "../OverrideableCompass.cpp"

class TestCompass : public OverrideableCompass {
	float headings[100];
	int headingsSize;
	int nextIndex = 0;

public:

	TestCompass(float headingsIn[], int headingsInSize) : headingsSize(headingsInSize){
		for (int i = 0; i < headingsInSize; ++i) {
			headings[i] = headingsIn[i];
		}
	}

	float getCurrentHeadingInDegrees() { return headings[nextIndex++]; }
};
#endif
