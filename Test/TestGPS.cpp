#include "../GPS.cpp"


class TestGPS : public SystemGPS {
	int numDataStringsRead = 0;
	String * testData = nullptr;
	String NoData = "";

public:

	TestGPS(String * testDataIn, int size) {
		testData = new String[size];
		numDataStringsRead = size;
		for (int i = 0; i < size; ++i) {
			testData[i] = testDataIn[i];
		}
	}
	String readData() {
		if (numDataStringsRead > 0) return testData[--numDataStringsRead];
		else return NoData;
	}
};
