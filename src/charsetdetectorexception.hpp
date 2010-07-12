#pragma once

#include <string>

class CharsetDetectorException
{
public:
	CharsetDetectorException(const std::string& message)
		: message_(message)
		{}
	inline const std::string& GetMessage() const { return message_; }
private:
	std::string message_;
};
