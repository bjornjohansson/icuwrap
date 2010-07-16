#include "charsetdetectorimpl.hpp"
#include "charsetdetectorexception.hpp"

#include <boost/thread/locks.hpp>

CharsetDetectorImpl::CharsetDetectorImpl()
	: detector_(0)
{
	boost::lock_guard<boost::mutex> lock(detectorMutex_);

	if (chardet_create(&detector_) != CHARDET_RESULT_OK)
		throw CharsetDetectorException(
			"Could not create character detector, out of memory");
}

CharsetDetectorImpl::~CharsetDetectorImpl()
{
	boost::lock_guard<boost::mutex> lock(detectorMutex_);

	if (detector_ != 0)
		chardet_destroy(detector_);
}

std::string CharsetDetectorImpl::GetCharsetName(const std::string& input)
{
	boost::lock_guard<boost::mutex> lock(detectorMutex_);

	int err = chardet_reset(detector_);
	if (err != CHARDET_RESULT_OK)
		throw CharsetDetectorException("Could not reset charset detector");
	
	err = chardet_handle_data(detector_, input.c_str(), input.size());
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
		return "UTF-8";

	return &buffer[0];
}
