#ifndef HL7MESSAGEELEMENT_H
#define HL7MESSAGEELEMENT_H

#include<string>
#include "HL7Encoding.h"
class HL7MessageElement
{

	public:
	HL7MessageElement();
	~HL7MessageElement();
	std::string getValue() const;
	std::string getUndecodeValue() const;
	void setValue(const std::string& value);
	HL7Encoding *encoding;
	protected:
	std::string _value = "";
	virtual void processValue()=0;

};



#endif
