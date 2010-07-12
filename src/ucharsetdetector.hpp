#pragma once

#include <unicode/ucsdet.h>

#include <string>
#include <vector>

namespace IcuWrap
{
	class CharsetMatch
	{
	public:
		CharsetMatch(std::string charset, int confidence)
			: charset_(charset), confidence_(confidence)
			{}
		inline const std::string& GetCharset() const { return charset_; }
		inline int GetConfidence() const { return confidence_; }

		inline bool operator==(const std::string& other) const
			{ return charset_ == other; }
	private:
		std::string charset_;
		int confidence_;
	};
	
	
	class UCharsetDetector
	{
	public:
		typedef std::vector<CharsetMatch> CharsetCollection;
		typedef CharsetCollection::const_iterator CharsetIterator;
		
		explicit UCharsetDetector(const std::string& input);
		~UCharsetDetector();
		
		bool IsValid() const;
		std::string GetError() const;

		const std::string& GetCharsetName();
		const CharsetCollection& GetAllCharsetNames();
	private:
		std::vector<char> input_;
		size_t inputSize_;
		::UCharsetDetector* detector_;
		UErrorCode errorCode_;
		std::string detectedCharset_;
		CharsetCollection allDetectedCharsets_;
	};
}
