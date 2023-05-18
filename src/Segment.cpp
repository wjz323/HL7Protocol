#include "Segment.h"

Segment::Segment()
{
}

Segment::Segment(HL7Encoding *encoding)
{
    this->fieldList = std::vector<HL7Field>();
    this->encoding = encoding;
}

Segment::Segment(std::string name, HL7Encoding *encoding)
{
    this->fieldList = std::vector<HL7Field>();
    this->name = name;
    this->encoding = encoding;
}

void Segment::addEmptyField()
{
    this->addNewField("");
}

void Segment::addNewField(std::string content, int position)
{
    this->addNewField(HL7Field(content, this->encoding), position);
}

void Segment::addNewField(std::string content, bool isDelimiters)
{
    HL7Field newField(this->encoding);
    if (isDelimiters)
        newField.isDelimitersField = true;
    newField.setValue(content);
    this->addNewField(newField, -1);
}

bool Segment::addNewField(HL7Field field, int position)
{
    try
    {
        if (position < 0)
        {
            this->fieldList.push_back(field);
        }
        else
        {
            position = position - 1;
            MsgHelper::addVector(this->fieldList, field, position, HL7Field("", field.encoding));
        }
        return true;
    }
    catch (...)
    {
        throw HL7Exception("Unable to add new field in segment");
    }
}

HL7Field Segment::fields(int position)
{
    position = position - 1;
    try
    {
        return this->fieldList[position];
    }
    catch (...)
    {
        throw HL7Exception("Field not available Error");
    }
}

std::vector<HL7Field> Segment::GetAllFields()
{
    return this->fieldList;
}

int Segment::getSequenceNo()
{
    return this->sequenceNo;
}

void Segment::processValue()
{
    char r=this->encoding->_fieldDelimiter;
    std::vector<std::string> allFields = MsgHelper::splitString(_value, std::string(1,this->encoding->_fieldDelimiter));
    allFields.erase(allFields.begin());
    for (size_t i = 0; i < allFields.size(); i++)
    {
        std::string strField = allFields[i];
        HL7Field field(this->encoding);

        if (this->name == "MSH" && i == 0)
            field.isDelimitersField = true; // special case

        field.setValue(strField);
        this->fieldList.push_back(field);
    }

    if (this->name == "MSH")
    {
        HL7Field field1(this->encoding);
        field1.isDelimitersField = true;
        std::string str= std::string(1,this->encoding->_fieldDelimiter);
        field1.setValue(str);
        this->fieldList.insert(fieldList.begin(),field1);//insert
    }
}
