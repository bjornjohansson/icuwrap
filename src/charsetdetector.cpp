#include "charsetdetector.hpp"
#include "charsetdetectorimpl.hpp"

#include <chardet.h>

CharsetDetector::CharsetDetector(const std::string& input)
	: impl_(new CharsetDetectorImpl(input))
{
}

const std::string& CharsetDetector::GetCharsetName()
{
	return impl_->GetCharsetName();
}

const CharsetDetector::CharsetCollection& CharsetDetector::GetAllCharsetNames()
{
	return impl_->GetAllCharsetNames();
}
