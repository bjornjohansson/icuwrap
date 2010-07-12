#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "../unistring.hpp"

class UniStringTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( UniStringTest );

	CPPUNIT_TEST( TestConstructor );
	CPPUNIT_TEST( TestCopyConstruction );
	CPPUNIT_TEST( TestDetection );
	
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
	
	void TestConstructor();
	void TestCopyConstruction();
	void TestDetection();
private:
};
