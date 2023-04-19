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

	char _fieldDelimiter = '|'; //�ֶηָ���
	char _componentDelimiter = '^'; //����ָ���
	char _repetitionDelimiter = '~'; //�ظ��ָ���
	char _escapeCharacter = '\\'; //ת���ַ�'
	char _subComponentDelimiter = '&'; //������ָ���
	std::string _segmentDelimiter = "\r"; //����ֹ��
	std::string _presentButNull="\"\""; //��ֵ
	std::string allDelimiter() const;
	void evaluateDelimiters(const std::string delimiters);
	void evaluateSegmentDelimiter(const std::string message);
};




