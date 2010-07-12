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
};

class UniString
{
public:
	UniString();
	// Read an input string and attempt to detect its encoding
	UniString(const std::string& input);
	// Read an input string using the supplied encoding
	UniString(const std::string& input, const std::string& encoding);

	std::string ToUtf8() const;
	
	UnicodeString* operator->() { return &string_; }
	const UnicodeString* operator->() const { return &string_; }
	
	UnicodeString& operator*() { return string_; }
	const UnicodeString& operator*() const { return string_; }

	operator UnicodeString&() { return string_; }
	operator const UnicodeString&() { return string_; }

	inline UniString& Append(const UniString& other)
		{ string_.append(*other); return *this; }
	inline UniString& Append(const UnicodeString& other)
		{ string_.append(other); return *this; }
	inline UniString Append(UChar c)
		{ string_.append(c); return *this;}

	inline const std::string& GetDetectedCharset() const
		{ return detectedCharset_; }
	
private:
	void ConvertToCharset(const std::string& input);

	UnicodeString string_;
	std::string detectedCharset_;
};
