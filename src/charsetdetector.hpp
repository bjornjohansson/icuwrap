#pragma once

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

class CharsetDetectorImpl;
typedef boost::shared_ptr<CharsetDetectorImpl> CharsetDetectorImplPtr;

class CharsetDetector
{
public:
	typedef std::vector<std::string> CharsetCollection;
	typedef CharsetCollection::const_iterator CharsetIterator;

	explicit CharsetDetector(const std::string& input);
	
	const std::string& GetCharsetName();
	const CharsetCollection& GetAllCharsetNames();
private:
	CharsetDetectorImplPtr impl_;
};
