#ifndef HL7ENCODING_H
#define HL7ENCODING_H

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

	char _fieldDelimiter = '|'; //字段分隔符
	char _componentDelimiter = '^'; //组件分隔符
	char _repetitionDelimiter = '~'; //重复分隔符
	char _escapeCharacter = '\\'; //转义字符'
	char _subComponentDelimiter = '&'; //子组件分隔符
	std::string _segmentDelimiter = "\r"; //段终止符
	std::string _presentButNull="\"\""; //空值
	std::string allDelimiter() const;
	void evaluateDelimiters(const std::string delimiters);
	void evaluateSegmentDelimiter(const std::string message);
};




#endif

