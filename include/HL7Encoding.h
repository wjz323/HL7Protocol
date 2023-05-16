#pragma once

#include <string>
#include <sstream>
#include "HL7Exception.h"
class HL7Encoding
{
public:
	HL7Encoding();
	~HL7Encoding();
	std::string encode(const std::string& str);
	std::string decode(const std::string& str);

	char _fieldDelimiter = '|'; //F
	char _componentDelimiter = '^'; //S
	char _repetitionDelimiter = '~'; //R
	char _escapeCharacter = '\\'; //E
	char _subComponentDelimiter = '&'; //T
	std::string _segmentDelimiter = "\r"; //
	std::string _presentButNull="\"\""; //
	std::string allDelimiter() const;
	void evaluateDelimiters(const std::string delimiters);
	void evaluateSegmentDelimiter(const std::string message);
};




