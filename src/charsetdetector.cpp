#include "charsetdetector.hpp"
#include "charsetdetectorimpl.hpp"

#include <chardet.h>

CharsetDetector::CharsetDetector()
	: impl_(new CharsetDetectorImpl)
{
}

std::string CharsetDetector::GetCharsetName(const std::string& input)
{
	return impl_->GetCharsetName(input);
}

UnicodeString CharsetDetector::AsUnicode(const std::string & input)
{
	return UnicodeString(input.c_str(), impl_->GetCharsetName(input).c_str());
}
