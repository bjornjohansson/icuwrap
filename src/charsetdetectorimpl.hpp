#pragma once

#include <chardet.h>

#include <vector>
#include <string>

class CharsetDetector;

class CharsetDetectorImpl
{
public:
	typedef std::vector<std::string> CharsetCollection;
	typedef CharsetCollection::const_iterator CharsetIterator;
	
	virtual ~CharsetDetectorImpl();
	
	const std::string& GetCharsetName();
	const CharsetCollection& GetAllCharsetNames();
private:
	CharsetDetectorImpl(const std::string& input);
	
	chardet_t detector_;

	std::vector<char> input_;
	size_t inputSize_;
	std::string detectedCharset_;
	CharsetCollection allDetectedCharsets_;

	friend class CharsetDetector;
};
