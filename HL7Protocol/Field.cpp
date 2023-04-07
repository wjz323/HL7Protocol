#include "Field.h"

HL7Field::HL7Field()
{
    this->componentList= std::vector<Component>();
}

HL7Field::HL7Field(std::string pValue, HL7Encoding* encoding)
{
    this->componentList= std::vector<Component>();
	this->encoding = encoding;
	this->setValue(pValue);
}

HL7Field::HL7Field(HL7Encoding* encoding)
{
    this->componentList= std::vector<Component>();
	this->encoding = encoding;
}

HL7Field::~HL7Field()
{
}

std::vector<HL7Field> HL7Field::getRepetitionList() const
{
    if (_repetitionList.empty())
    {
		return std::vector<HL7Field>();
	}
    return _repetitionList;
}

void HL7Field::setRepetitionList(const std::vector<HL7Field>& repetitionList)
{
    this->_repetitionList= repetitionList;
}

bool HL7Field::addNewComponent(Component com)
{
    try
    {
		this->componentList.push_back(com);
		return true;
	}
    catch (...)
    {
        throw HL7Exception("Unable to add new component Error.");
	}
}

bool HL7Field::addNewComponent(Component com, int position)
{
    try
    {
        addVector(this->componentList,com,position);
        return true;
    }
    catch (...)
    {
        throw HL7Exception("Unable to add new component Error.");
    }
}

std::vector<Component> HL7Field::getComponents() const
{
    return componentList;
}

Component HL7Field::getComponent(int position) const
{
    position = position - 1;
    try
    {
        return componentList[position];
    }
    catch (...)
    {
        throw HL7Exception("Component not available Error.");
    }
}

bool HL7Field::removeEmptyTrailingComponents()
{
    try
    {
        int count = componentList.size();
        for (int i = count; i >= 0; i--)
        {
            if (componentList[i].getValue().empty())
            {
				componentList.erase(componentList.begin() + i);
			}
            else
            {
				break;
			}
		}
		return true;
	}
	catch (...)
    {
        throw HL7Exception("Error removing trailing comonents");
    }
}

void HL7Field::addRepeatingField(HL7Field field)
{
    if (!this->hasRepetitions)
    {
        throw HL7Exception("Repeating field must have repetions (HasRepetitions = true)");
    }
}

void HL7Field::addVector(std::vector<Component>& componentList, Component componet, int position)
{
    int listCount = componentList.size();
    position = position - 1;
    if (position < listCount)
    {
        componentList[position] = componet;
    }
    else
    {
        for (int i = listCount; i < position; i++)
        {
            componentList.push_back(Component(componet.encoding,false));
        }
        componentList.push_back(componet);
    }
}


void HL7Field::processValue()
{
}
