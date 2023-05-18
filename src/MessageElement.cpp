#include "MessageElement.h"

HL7MessageElement::HL7MessageElement()
{

}

HL7MessageElement::~HL7MessageElement()
{
   //delete encoding;
  // encoding = nullptr;
}

std::string HL7MessageElement::getValue() const
{
    return _value==encoding->_presentButNull? nullptr:encoding->decode(_value);
}

std::string HL7MessageElement::getUndecodeValue() const
{
    return _value == encoding->_presentButNull? nullptr : _value;
}


void HL7MessageElement::setValue(const std::string& value)
{
    _value = value;
    this->processValue();
}
