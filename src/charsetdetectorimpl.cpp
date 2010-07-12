#include "charsetdetectorimpl.hpp"
#include "charsetdetectorexception.hpp"

CharsetDetectorImpl::CharsetDetectorImpl(const std::string& input)
	: detector_(0)
	, input_(input.begin(), input.end())
	, inputSize_(input.size())
{
	if (chardet_create(&detector_) != CHARDET_RESULT_OK)
		throw CharsetDetectorException(
			"Could not create character detector, out of memory");
}

CharsetDetectorImpl::~CharsetDetectorImpl()
{
	if (detector_ != 0)
		chardet_destroy(detector_);
}

const std::string& CharsetDetectorImpl::GetCharsetName()
{
	if (detectedCharset_.size() > 0)
		return detectedCharset_;
	
	int err = chardet_handle_data(detector_, &input_[0], input_.size());
	if (err != CHARDET_RESULT_OK)
		throw CharsetDetectorException(
			"Could not feed data to charset detector");

	err = chardet_data_end(detector_);
	if (err != CHARDET_RESULT_OK)
		throw CharsetDetectorException(
			"Could not terminate data feed to charset detector");

	std::vector<char> buffer(CHARDET_MAX_ENCODING_NAME, 0);
	err = chardet_get_charset(detector_, &buffer[0], buffer.size());
	if (err != CHARDET_RESULT_OK)
		throw new CharsetDetectorException(
			"Could not get the charset for the given input");
	if (buffer[0] == 0)
		detectedCharset_ = "UTF-8";
	else
		detectedCharset_ = &buffer[0];
	return detectedCharset_;
}

const CharsetDetectorImpl::CharsetCollection&
CharsetDetectorImpl::GetAllCharsetNames()
{
	if (allDetectedCharsets_.size() == 0)
		allDetectedCharsets_.push_back(GetCharsetName());

	return allDetectedCharsets_;
}
