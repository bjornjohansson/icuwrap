#pragma once

#include <unicode/unistr.h>
#include <string>

class UniStringException
{
public:
	UniStringException(const std::string& message)
		: message_(message)
		{}
	const std::string& GetMessage() { return message_; }
private:
	std::string message_;
}

class UniString
{
public:
	/*
	 * The input string is assumed to be UTF-8, if it can not properly
	 * be read as UTF-8 it will be considered as ISO-8859-1
	 */
	UniString(const std::string& input);

	std::string ToUtf8() const;
	
	UnicodeString& operator->() { return string_; }
	const UnicodeString& operator->() const { return string_; }
	
	UnicodeString& operator*() { return string_; }
	const UnicodeString& operator*() const { return string_; }
	
private:
	UnicodeString string_;
};
