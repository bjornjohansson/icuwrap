#pragma once

#include "../converter.hpp"


#include <cppunit/extensions/HelperMacros.h>

class ConverterTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( ConverterTest );

	CPPUNIT_TEST( TestConversion );

	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();

	void TestConversion();
private:
};
