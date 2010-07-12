#include "unistring_test.hpp"

#include "../unistring.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( UniStringTest );

void UniStringTest::setUp()
{}

void UniStringTest::tearDown()
{}

void UniStringTest::TestConstructor()
{
	CPPUNIT_ASSERT_NO_THROW(UniString());
	std::string testString = "This is my test string.";
	CPPUNIT_ASSERT_NO_THROW(UniString(testString));
}

void UniStringTest::TestCopyConstruction()
{
	std::string testString = "This is my test string.";

	UniString uniString(testString);
	CPPUNIT_ASSERT_EQUAL(uniString.ToUtf8(), testString);
	UniString copy(uniString);
	CPPUNIT_ASSERT_EQUAL(copy.ToUtf8(), testString);
	std::string oldTestString = testString;
	testString = "I modified my test string.";
	CPPUNIT_ASSERT_EQUAL(uniString.ToUtf8(), oldTestString);
	CPPUNIT_ASSERT_EQUAL(copy.ToUtf8(), oldTestString);

	uniString->append(65);  // Append the letter 'A'
	CPPUNIT_ASSERT_EQUAL(copy.ToUtf8(), oldTestString);
}


void UniStringTest::TestDetection()
{
	std::string latin1 = "Räven raskar över den blå isen.";
	std::string utf8 = "R\xc3\xa4ven raskar \xc3\xb6ver den bl\xc3\xa5 isen.";
	
	UniString fromLatin1(latin1);
	
	CPPUNIT_ASSERT_EQUAL(utf8, fromLatin1.ToUtf8());

	UniString fromUtf8(utf8);
	CPPUNIT_ASSERT_EQUAL(std::string("UTF-8"), fromUtf8.GetDetectedCharset());
	CPPUNIT_ASSERT_EQUAL(utf8, fromUtf8.ToUtf8());
	
	latin1 = "RÄVEN RASKAR ÖVER DEN BLÅ ISEN.";
	utf8 = "R\xc3\x84VEN RASKAR \xc3\x96VER DEN BL\xc3\x85 ISEN.";

	fromLatin1 = UniString(latin1);
	CPPUNIT_ASSERT_EQUAL(utf8, fromLatin1.ToUtf8());

	fromUtf8 = UniString(utf8);
	CPPUNIT_ASSERT_EQUAL(utf8, fromUtf8.ToUtf8());
}
