#include "uconverter.hpp"

#include <unicode/ucnv.h>

#include <iostream>

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
