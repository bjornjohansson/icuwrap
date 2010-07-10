#pragma once

#include <string>

#include <unicode/ucnv_err.h>
#include <unicode/uenum.h>

namespace IcuWrap
{

	class UConverter
	{
	public:
		UConverter(const std::string& codePage);
		~UConverter();

		::UConverter* operator*();

		bool IsValid() const;
		std::string GetError() const;
	private:
		::UConverter* converter_;
		UErrorCode errorCode_;
	};
	
}
