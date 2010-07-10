#include "unistring.hpp"
#include "uconverter.hpp"
#include "ucharsetdetector.hpp"

#define U_HAVE_STD_STRINGS

#include <unicode/ucnv.h>

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

UniString::UniString(const std::string& input)
{
	IcuWrap::UCharsetDetector detector(input);

	if (!detector.IsValid())
		throw std::exception();

	const std::vector<std::string>& sets = detector.GetAllCharsetNames();

	// By default we use ISO-8859-1
	std::string charsetToUse = "ISO-8859-1";
	// If we find UTF-8 but not ISO-8859-1 then we go with UTF-8
	if (std::find(sets.begin(), sets.end(), "UTF-8") != sets.end() &&
	    std::find(sets.begin(), sets.end(), "ISO-8859-1") == sets.end())
	{
		charsetToUse = "UTF-8";
	}
	
	IcuWrap::UConverter converter(charsetToUse);
	if (!converter.IsValid())
		throw UniStringException(std::string("Converter invalid: ")+
		                         converter.GetError());

	std::vector<UChar> buffer(input.size()*2+1, 0);
	int32_t bufferSize = static_cast<int32_t>(buffer.size());
	int32_t inputSize = static_cast<int32_t>(input.size());
	
	UErrorCode errorCode = U_ZERO_ERROR;
	int32_t length = ucnv_toUChars(*converter, &buffer[0], bufferSize,
	                               input.c_str(), inputSize, &errorCode);
	if (U_FAILURE(errorCode))
		throw UniStringException(std::string("Conversion failed: ")+
		                         u_errorName(errorCode));

	string_ = UnicodeString(&buffer[0], length);
}

std::string UniString::ToUtf8() const
{
	IcuWrap::UConverter converter("UTF-8");

	int32_t bufferSize = UCNV_GET_MAX_BYTES_FOR_STRING(string_.countChar32(),
	                                                   ucnv_getMaxCharSize(*converter));

	std::vector<char> buffer(bufferSize+1, 0);

	UErrorCode error = U_ZERO_ERROR;
	ucnv_fromUChars(*converter, &buffer[0], bufferSize,
	                string_.getBuffer(),
	                string_.countChar32(),
	                &error);
	
	if (U_FAILURE(error))
		throw UniStringException("Conversion to UTF-8 failed");

	return &buffer[0];
}
