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
	// Copy contruct a UnicodeString object
	explicit UniString(const UnicodeString& input);

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

	inline UniString SubString(int32_t start, int32_t length=INT32_MAX) const
		{
			UniString result;
			string_.extract(start,
			                length == INT32_MAX ? string_.length() : start+length,
			                result);
			return result;
		}

	inline int32_t Find(const UniString& text, int32_t start = 0) const
		{
			int32_t position = string_.indexOf(*text, start);
			if (position == -1)
				return INT32_MAX;
			return position;
		}

	inline int32_t Find(UChar c, int32_t start = 0) const
		{
			int32_t position = string_.indexOf(c, start);
			if (position == -1)
				return INT32_MAX;
			return position;
		}
	
private:
	void ConvertToCharset(const std::string& input);

	UnicodeString string_;
	std::string detectedCharset_;
};
