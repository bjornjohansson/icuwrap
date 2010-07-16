#include "converter.hpp"
#include "charsetdetector.hpp"
#include "uconverter.hpp"

#include <unicode/unistr.h>
#include <string>
#include <cstring>

UnicodeString ConvertString(const std::string& input)
{
	CharsetDetector detector;
	return UnicodeString(input.c_str(), detector.GetCharsetName(input).c_str());
}

UnicodeString ConvertString(const std::string& input, const std::string& encoding)
{
	return UnicodeString(input.c_str(), encoding.c_str());
}

std::string AsUtf8(const UnicodeString& input)
{
	IcuWrap::UConverter converter("UTF-8");
	return converter.ConvertUnicodeString(input);
}

UnicodeString AsUnicode(const std::string& input)
{
	return UnicodeString(input.c_str(), "UTF-8");
}
