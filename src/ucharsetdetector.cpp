#include "ucharsetdetector.hpp"

#include <unicode/ucsdet.h>

IcuWrap::UCharsetDetector::UCharsetDetector(const std::string& input)
	: input_(input.begin(), input.end())
	, inputSize_(input.size())
	, detector_(0)
	, errorCode_(U_ZERO_ERROR)
{
	detector_ = ucsdet_open(&errorCode_);

	// Since ICU seems to want to probe for UTF32 we need the buffer
	// to be at least 4 bytes to avoid illegal reads.
	if (input_.size() < 4)
		input_.resize(4, 0);
	
	ucsdet_setText(detector_, &input_[0], inputSize_, &errorCode_);
}

IcuWrap::UCharsetDetector::~UCharsetDetector()
{
	if (detector_ != 0)
		ucsdet_close(detector_);
}

bool IcuWrap::UCharsetDetector::IsValid() const
{
	return detector_ != 0 && U_SUCCESS(errorCode_);
}

std::string IcuWrap::UCharsetDetector::GetError() const
{
	return u_errorName(errorCode_);
}

const std::string& IcuWrap::UCharsetDetector::GetCharsetName()
{
	if (detectedCharset_.size() > 0)
		return detectedCharset_;

	const UCharsetMatch* match = ucsdet_detect(detector_, &errorCode_);
	detectedCharset_ = ucsdet_getName(match, &errorCode_);
	return detectedCharset_;
}

const IcuWrap::UCharsetDetector::CharsetCollection&
IcuWrap::UCharsetDetector::GetAllCharsetNames()
{
	if (allDetectedCharsets_.size() > 0)
		return allDetectedCharsets_;

	int32_t numMatches = 0;
	const UCharsetMatch** matches = ucsdet_detectAll(detector_, &numMatches,
	                                                 &errorCode_);

	for(int currentMatch=0; currentMatch < numMatches; ++currentMatch)
	{
		std::string name = ucsdet_getName(matches[currentMatch],
		                                  &errorCode_);
		int32_t confidence = ucsdet_getConfidence(matches[currentMatch],
		                                          &errorCode_);
		allDetectedCharsets_.push_back(CharsetMatch(name, confidence));
	}
	return allDetectedCharsets_;
}
