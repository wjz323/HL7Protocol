#include "SubComponent.h"

HL7SubComponent::HL7SubComponent()
{
}

HL7SubComponent::HL7SubComponent(std::string val, HL7Encoding* _encoding)
{
	this->encoding=encoding;
	this->setValue(val);
}

HL7SubComponent::~HL7SubComponent()
{
}

void  HL7SubComponent::processValue()
{

}
