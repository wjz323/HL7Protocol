#include "Component.h"

Component::Component()
{
    this->subComponentList = std::vector<HL7SubComponent>();
}

Component::Component(HL7Encoding* encoding, bool isDelimiter)
{
    this->isDelimiter = isDelimiter;
    this->encoding = encoding;
    this->subComponentList= std::vector<HL7SubComponent>();

}

Component::Component(std::string pValue, HL7Encoding* encoding)
{
    this->subComponentList= std::vector<HL7SubComponent>();
    this->encoding = encoding;
	this->setValue(pValue);
}

Component::~Component()
{
    
}

std::vector<HL7SubComponent> Component::getSubComponents() const
{
    return subComponentList;
}

void Component::setSubComponents(const std::vector<HL7SubComponent>& subComponents)
{
    this->subComponentList= subComponents;
}

HL7SubComponent Component::subComponents(int position)
{
    position = position - 1;
    return this->subComponentList[position];
}


void Component::processValue()
{
    std::vector<std::string> allSubComponents;
    if (this->isDelimiter)
    {
		allSubComponents.push_back(this->getValue());
	}
    else
    {
        allSubComponents = MsgHelper::splitString(this->getValue(),std::string(1,this->encoding->_subComponentDelimiter));
	}
    if (allSubComponents.size() > 1)
        this->isSubComponentized = true;
    for (int i = 0; i < allSubComponents.size(); i++)
    {
        this->subComponentList.push_back(HL7SubComponent(allSubComponents[i], this->encoding));
    }
   
}

// std::vector<std::string> Component::split(std::string str, char delimiter)
// {
//     std::string::size_type pos;
//     std::vector<std::string> tokens;
//     int size = str.size();
//     for (int i = 0; i < size; i++)
//     {
// 		pos = str.find(delimiter, i);
//         if (pos <size)
//         {
// 			tokens.push_back(str.substr(i, pos-i));	
//             i = pos;
// 		}      
// 	}
//     return tokens;
// }
