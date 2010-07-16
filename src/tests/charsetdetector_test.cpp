#include "charsetdetector_test.hpp"

#include "../charsetdetector.hpp"

#include <string>

CPPUNIT_TEST_SUITE_REGISTRATION( CharsetDetectorTest );

void CharsetDetectorTest::setUp()
{
}

void CharsetDetectorTest::tearDown()
{
}

void CharsetDetectorTest::TestDetection()
{
	std::string plAsIso = "pl \xF6:asdf";
	std::string plAsUtf8 = "pl \xC3\xB6:asdf";

	CharsetDetector detector;
	std::string isoCharset = detector.GetCharsetName(plAsIso);
	CPPUNIT_ASSERT_MESSAGE("Expected windows-1252 or ISO-8859-1 but got "+isoCharset, isoCharset == "windows-1252" || isoCharset == "ISO-8859-1");
	CPPUNIT_ASSERT_EQUAL(std::string("UTF-8"), detector.GetCharsetName(plAsUtf8));
}
