#include "Message.h"

Message::Message()
{
}

Message::Message(std::string strMessage)
{
}

Message::~Message()
{
}

bool Message::equals(std::string obj)
{
    std::vector<std::string> arr1 = MsgHelper::split(this->hl7Message, this->encoding->_segmentDelimiter, 1);
    std::vector<std::string> arr2 = MsgHelper::split(this->hl7Message, this->encoding->_segmentDelimiter, 1);
    return arr1 == arr2;
}

bool Message::parseMessage(bool bypassValidation)
{
    bool isValid = false;
    bool isParsed = false;
    try
    {
        if (!bypassValidation)
        {
            isValid = this->validateMessage();
        }
        else
        {
            isValid = true;
        }
    }
    catch (...)
    {
        throw HL7Exception("Unhandled Exception in validation.");
    }

    if(isValid)
    {
        
    }



    return isParsed;
}

std::string Message::serializeMessage(bool validate)
{
    return std::string();
}
