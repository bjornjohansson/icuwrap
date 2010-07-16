#pragma once

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <unicode/unistr.h>

class CharsetDetectorImpl;
typedef boost::shared_ptr<CharsetDetectorImpl> CharsetDetectorImplPtr;

class CharsetDetector
{
public:
	typedef std::vector<std::string> CharsetCollection;
	typedef CharsetCollection::const_iterator CharsetIterator;

	CharsetDetector();

	UnicodeString AsUnicode(const std::string& input);
	std::string GetCharsetName(const std::string& input);
private:
	CharsetDetectorImplPtr impl_;
};
