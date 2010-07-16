#include "uconverter.hpp"

#include <unicode/ucnv.h>

#include <vector>

IcuWrap::UConverter::UConverter(const std::string& codePage)
	: converter_(0)
	, errorCode_(U_ZERO_ERROR)
{
	converter_ = ucnv_open(codePage.c_str(), &errorCode_);
}

IcuWrap::UConverter::~UConverter()
{
	if (converter_ != 0)
	{
		ucnv_close(converter_);
	}
}

::UConverter* IcuWrap::UConverter::operator*()
{
	return converter_;
}

bool IcuWrap::UConverter::IsValid() const
{
	return U_SUCCESS(errorCode_);
}

std::string IcuWrap::UConverter::GetError() const
{
	return u_errorName(errorCode_);
}

std::string IcuWrap::UConverter::ConvertUnicodeString(const UnicodeString& str)
{
	int32_t size = UCNV_GET_MAX_BYTES_FOR_STRING(str.length(),
	                                             ucnv_getMaxCharSize(converter_));
	std::vector<char> buffer(size);
	int32_t length = ucnv_fromUChars(converter_, &buffer[0], buffer.size(),
	                                 str.getBuffer(), str.length(),
	                                 &errorCode_);
	return std::string(&buffer[0], length);
}
