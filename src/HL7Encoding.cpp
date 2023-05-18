#include "HL7Encoding.h"

HL7Encoding::HL7Encoding()
{
}


std::string HL7Encoding::encode(const std::string& str)
{
	//�ж�str�Ƿ�Ϊnull
	if (str.empty())
	{
		return _presentButNull;
	}
	std::string result="";
	for (int i = 0; i < str.length(); i++)
	{
		char c=str[i];
		bool continueFlag = true;
		if (c == '<')
		{
			continueFlag = false;
			// special case <B>
			if (str.length() >= i + 3 && str[i + 1] == 'B' && str[i + 2] == '>')
			{
				result += _escapeCharacter + "H";
				result += _escapeCharacter;
				i += 2;
			}
			// special case </B>
			else if (str.length() >= i + 4 && str[i + 1] == '/' && str[i + 2] == 'B' && str[i + 3] == '>')
			{
				result += _escapeCharacter + "N";
				result += _escapeCharacter;
				i += 3;
			}
			//special case <BR>
			else if (str.length() >= i + 4 && str[i + 1] == 'B' && str[i + 2] == 'R' && str[i + 3] == '>')
			{
				result += _escapeCharacter + ".br";
				result += _escapeCharacter;
				i += 3;
			}
			else
				continueFlag = true;			
		}
		if (continueFlag)
		{
			if (c == _componentDelimiter)
			{
				result += _escapeCharacter;
				result += "S";
				result += _escapeCharacter;
			}
			else if (c == _escapeCharacter)
			{
				result += _escapeCharacter;
				result += "E";
				result += _escapeCharacter;
			}
			else if (c == _fieldDelimiter)
			{
				result += _escapeCharacter;
				result += "F";
				result += _escapeCharacter;
			}
			else if (c == _repetitionDelimiter)
			{
				result += _escapeCharacter;
				result += "R";
				result += _escapeCharacter;
			}
			else if (c == _subComponentDelimiter)
			{
				result += _escapeCharacter;
				result += "T";
				result += _escapeCharacter;
			}
			else if (c == 10 || c == 13)
			{
				//������ת����16�����ַ���
				std::ostringstream oss;
				oss<<std::hex<<c;
				std::string v = oss.str();

				if ((v.length() % 2) != 0)
					v = "0" + v;
				result += _escapeCharacter;
				result += "X";
				result += v;
				result += _escapeCharacter;
			}
			else
				result += c;
		}
	}

	return result;
}

std::string HL7Encoding::decode(const std::string& str)
{
	//�ж� str�Ƿ�Ϊ��
	if (str.empty())
	{
		return "";
	}
	std::string result="";
	for (int i = 0; i < str.length(); i++)
	{
		char c=str[i];
		if (c != _escapeCharacter)
		{
			result += c;
			continue;
		}
		i++;
		//��ȡ�ַ���index
		int index = str.find(_escapeCharacter, i);

		if (index == -1)
		{
			//throw HL7Exception("Escape character not found in message");
			result+=_escapeCharacter;
			result+=str[i];
			continue;
		}
		std::string seq = str.substr(i, index - i);
		i = index;
		if (seq.length() == 0)
			continue;
		// Start higlighting
		if (seq == "H")
		{
			result += "<B>";
		}
		// Stop highlighting
		else if (seq == "N")
		{
			result += "</B>";
		}
		// New line
		else if (seq == ".br")
		{
			result += "<BR>";
		}
		// Field delimiter
		else if (seq == "F")
		{
			result += _fieldDelimiter;
		}
		// Component delimiter
		else if (seq == "S")
		{
			result += _componentDelimiter;
		}
		// Escape character
		else if (seq == "E")
		{
			result += _escapeCharacter;
		}
		// Repetition delimiter
		else if (seq == "R")
		{
			result += _repetitionDelimiter;
		}
		// Subcomponent delimiter
		else if (seq == "T")
		{
			result += _subComponentDelimiter;
		}
		// Hexadecimal character
		else if (seq[0] == 'X')
		{
			std::string hex = seq.substr(1);
			//���ַ���ת��������
			int v = std::stoi(hex, nullptr, 16);
			result += (char)v;
		}
		else
		{
			result += seq;
		}

		
	}
	return result;
}

std::string HL7Encoding::allDelimiter() const
{
	return "" + _fieldDelimiter + _componentDelimiter + _repetitionDelimiter + _escapeCharacter + _subComponentDelimiter;
}

void HL7Encoding::evaluateDelimiters(const std::string delimiters)
{
	_fieldDelimiter = delimiters[0];
	_componentDelimiter = delimiters[1];
	_repetitionDelimiter  =delimiters[2];
	_escapeCharacter  =delimiters[3];
	_subComponentDelimiter  =delimiters[4];
}

void HL7Encoding::evaluateSegmentDelimiter(const std::string message)
{	
	std::string delimiters[]= { "\r\n", "\n\r", "\r", "\n" };
	for (int i = 0; i < 4; i++)
	{
		//message���Ƿ�����ַ���
		if (message.find(delimiters[i]) != std::string::npos)
		{
			_segmentDelimiter = delimiters[i];
			return;
		}
		throw HL7Exception("Segment delimiter not found in message");///�޷�ʶ��Ķ���ֹ��
	}
}
