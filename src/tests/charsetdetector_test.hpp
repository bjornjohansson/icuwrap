#pragma once

#include <cppunit/extensions/HelperMacros.h>

class CharsetDetectorTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( CharsetDetectorTest );

	CPPUNIT_TEST( TestDetection );

	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();

	void TestDetection();
};

