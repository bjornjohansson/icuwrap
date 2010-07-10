#pragma once

#include <unicode/ucsdet.h>

#include <string>
#include <vector>

namespace IcuWrap
{
	class UCharsetDetector
	{
	public:
		explicit UCharsetDetector(const std::string& input);
		~UCharsetDetector();
		
		bool IsValid() const;
		std::string GetError() const;

		const std::string& GetCharsetName();
		const std::vector<std::string>& GetAllCharsetNames();
	private:
		std::string input_;
		::UCharsetDetector* detector_;
		UErrorCode errorCode_;
		std::string detectedCharset_;
		std::vector<std::string> allDetectedCharsets_;
	};
}
