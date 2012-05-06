#include "unistring.hpp"
#include "uconverter.hpp"
#include "charsetdetector.hpp"
#include "charsetdetectorexception.hpp"

#include <vector>
#include <string>
#include <algorithm>

#include <iostream>

#include <unicode/ucnv.h>

UniString::UniString()
{
}

UniString::UniString(const std::string& input)
{
	try
	{
		CharsetDetector detector;

		string_ = detector.AsUnicode(input);
	}
	catch (const CharsetDetectorException& e)
	{
		throw UniStringException(e.GetMessage());
	}
}

UniString::UniString(const std::string& input, const std::string& encoding)
	: detectedCharset_(encoding)
{
	ConvertToCharset(input);
}

UniString::UniString(const UnicodeString& input)
	: string_(input)
{
}


void UniString::ConvertToCharset(const std::string& input)
{
	IcuWrap::UConverter converter(detectedCharset_);
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
