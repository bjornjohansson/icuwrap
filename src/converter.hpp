#pragma once

#include <unicode/unistr.h>
#include <string>

/**
 * Automatically detect the character encoding of the input string
 * and convert the string from that encoding to an ICU UnicodeString
 */
UnicodeString ConvertString(const std::string& input);

/**
 * Convert the input string from the supplied encoding to an ICU UnicodeString
 */
UnicodeString ConvertString(const std::string&, const std::string& encoding);

/**
 * Convert a UnicodeString to UTF-8 and return it as an std::string.
 */
std::string AsUtf8(const UnicodeString& input);

/**
 * Assume that the input string is UTF-8 and return a UnicodeString from that.
 */
UnicodeString AsUnicode(const std::string& input);
/*
template<class Stream>
Stream& operator<<(Stream& stream, const UnicodeString& str)
{
	stream<<AsUtf8(str);
	return stream;
}
*/
/*
size_t hash_value(const UnicodeString& s)
{
	return static_cast<size_t>(s.hashCode());
}
*/
