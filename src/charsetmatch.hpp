#pragma once

#include <string>

class CharsetDetectorImpl;

class CharsetMatch
{
public:
	inline const std::string& GetCharset() const { return charset_; }
	inline int GetConfidence() const { return confidence_; }

	inline bool operator==(const std::string& other) const
		{ return charset_ == other; }
private:
	CharsetMatch(std::string charset, int confidence)
		: charset_(charset), confidence_(confidence)
		{}
	
	std::string charset_;
	int confidence_;

	friend class CharsetDetectorImpl;
};
