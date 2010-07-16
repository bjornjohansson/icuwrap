#pragma once

#include <chardet.h>

#include <vector>
#include <string>

#include <boost/thread/mutex.hpp>

class CharsetDetector;

class CharsetDetectorImpl
{
public:
	typedef std::vector<std::string> CharsetCollection;
	typedef CharsetCollection::const_iterator CharsetIterator;
	
	virtual ~CharsetDetectorImpl();
	
	std::string GetCharsetName(const std::string& input);
private:
	CharsetDetectorImpl();
	CharsetDetectorImpl(const CharsetDetectorImpl&);
	CharsetDetectorImpl& operator=(const CharsetDetectorImpl&);
	
	boost::mutex detectorMutex_;

	chardet_t detector_;

	friend class CharsetDetector;
};
