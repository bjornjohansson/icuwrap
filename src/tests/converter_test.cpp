#include "converter_test.hpp"

#include "../converter.hpp"

#include <string>

CPPUNIT_TEST_SUITE_REGISTRATION( ConverterTest );

void ConverterTest::setUp()
{}

void ConverterTest::tearDown()
{}

void ConverterTest::TestConversion()
{
	std::string iso88591 = "R\xE4ven raskar \xF6ver den bl\xE5 isen.";
	std::string utf8 = "R\xC3\xA4ven raskar \xC3\xB6ver den bl\xC3\xA5 isen.";

	UnicodeString unicode = ConvertString(iso88591);
	CPPUNIT_ASSERT_EQUAL(utf8, AsUtf8(unicode));
	unicode = ConvertString(utf8);
	CPPUNIT_ASSERT_EQUAL(utf8, AsUtf8(unicode));

	UnicodeString aring = ConvertString("\xE5");
	CPPUNIT_ASSERT_EQUAL(std::string("\xC3\xA5"), AsUtf8(aring));

	UnicodeString auml = ConvertString("\xE4");
	CPPUNIT_ASSERT_EQUAL(std::string("\xC3\xA4"), AsUtf8(auml));

	UnicodeString ouml = ConvertString("\xF6");
	CPPUNIT_ASSERT_EQUAL(std::string("\xC3\xB6"), AsUtf8(ouml));
}
