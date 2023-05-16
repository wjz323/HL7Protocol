#include "Segment.h"

Segment::Segment()
{
}

Segment::Segment(HL7Encoding *encoding)
{
    this->fieldList=std::vector<HL7Field>();
    this->encoding=encoding;
}

Segment::Segment(std::string name, HL7Encoding *encoding)
{
     this->fieldList=std::vector<HL7Field>();
     this->name=name;
     this->encoding=encoding;
}

void Segment::addEmptyField()
{
    this->addNewField("");
}



void Segment::addNewField(std::string content, int position)
{
    this->addNewField(HL7Field(content,this->encoding),position);
}

void Segment::addNewField(std::string content, bool isDelimiters)
{
    HL7Field newField(this->encoding);
    if(isDelimiters)
        newField.isDelimitersField=true;
    newField.setValue(content);
    this->addNewField(newField,-1);
}

bool Segment::addNewField(HL7Field field, int position)
{
    try
    {
        if(position<0)
        {
            this->fieldList.push_back(field);
        }
        else
        {
            position=position-1;
            MsgHelper::addVector(this->fieldList,field,position,HL7Field("",field.encoding));         
        }
         return true;
    }
    catch(...)
    {
       throw HL7Exception("Unable to add new field in segment");
    }  
}

HL7Field Segment::fields(int position)
{
   position=position-1;
   try
   {
    return this->fieldList[position];
   
   }
   catch(...)
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
