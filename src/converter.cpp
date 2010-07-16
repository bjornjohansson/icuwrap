#include "converter.hpp"
#include "charsetdetector.hpp"

#include <unicode/unistr.h>
#include <string>
#include <cstring>

class VectorByteSink : public ByteSink
{
public:
	void Append(const char* bytes, int32_t n);
	char* GetAppendBuffer(int32_t min_capacity, int32_t desired_capacity, char* scratch, int32_t scratch_capacity, int32_t* result_capacity);

	const std::vector<char> GetBuffer() const { return buffer_; }
private:
	std::vector<char> buffer_;
};

void VectorByteSink::Append(const char* bytes, int32_t n)
{
}

char* VectorByteSink::GetAppendBuffer(int32_t min_capacity, int32_t desired_capacity, char* scratch, int32_t scratch_capacity, int32_t* result_capacity)
{
	size_t oldSize = buffer_.size();
	buffer_.resize(oldSize + desired_capacity);
	*result_capacity = desired_capacity;
	return &buffer_[oldSize];
}


UnicodeString ConvertString(const std::string& input)
{
	CharsetDetector detector;
	return UnicodeString(input.c_str(), detector.GetCharsetName(input).c_str());
}

UnicodeString ConvertString(const std::string& input, const std::string& encoding)
{
	return UnicodeString(input.c_str(), encoding.c_str());
}

std::string AsUtf8(const UnicodeString& input)
{
	VectorByteSink sink;
	input.toUTF8(sink);
	const std::vector<char>& buffer = sink.GetBuffer();
	return std::string(&buffer[0]);
}

UnicodeString AsUnicode(const std::string& input)
{
	return UnicodeString(input.c_str(), "UTF-8");
}
