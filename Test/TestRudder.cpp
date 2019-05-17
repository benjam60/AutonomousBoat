#ifndef TESTRUDDER_CPP
#define TESTRUDDER_CPP

#include "../OverrideableRudder.cpp"

class TestRudder : public OverrideableRudder {
	const int TestSize = 100;
	int nextIndex = 0;
public:
	int recordedPositions[100];

	TestRudder() {
		for (int i = 0; i < TestSize; ++i) {
			recordedPositions[i] = -1;
		}
	}

	void movePosition(int positionInDegrees) {
			recordedPositions[nextIndex++] = positionInDegrees;
	}

	//int getPosition(int nth) { return recordedPositions[nth]; }
};

#endif
