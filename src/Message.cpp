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

    if (isValid)
    {
        try
        {
            if (this->allSegemnts.size() <= 0)
            {
                this->allSegemnts = MsgHelper::split(hl7Message, MsgHelper::lineSeparators, 1, 1);
            }
            int segSeqNo = 0;
            for (size_t i = 0; i < this->allSegemnts.size(); i++)
            {
                std::string strSegment = this->allSegemnts[i];
                if (strSegment == "" || strSegment == " ")
                    continue;
                Segment newSegment(this->encoding);
                newSegment.name = strSegment.substr(0, 3);
                newSegment.setValue(strSegment);
                this->addNewSegment(newSegment);
            }
            this->segmentCount = segSeqNo;
            std::string strSerializedMessage = "";
            try
            {
                strSerializedMessage = this->serializeMessage(false);
            }
            catch (...)
            {
                throw HL7Exception("Failed to serialize parsed message with error");
            }
            if (strSerializedMessage != "")
            {
                if (this->equals(strSerializedMessage))
                    isParsed = true;
            }
            else
            {
                throw HL7Exception("Unable to serialize to original message");
            }
        }
        catch (...)
        {
            throw HL7Exception("Failed to parse the message with error.");
        }
    }

    return isParsed;
}

std::string Message::serializeMessage(bool validate)
{
    if (validate && !this->validateMessage())
        throw HL7Exception("Failed to validate the updated message");
    std::string strMessage = "";
    std::string currentSegName = "";
    std::vector<Segment> _segListOrdered = getAllSegmentsInOrder();
    try
    {
        try
        {
            for (size_t i = 0; i < _segListOrdered.size(); i++)
            {
                currentSegName = _segListOrdered[i].name;
                strMessage += _segListOrdered[i].name;
                if (_segListOrdered[i].fieldList.size() > 0)
                    strMessage += encoding->_fieldDelimiter;
                int startField = currentSegName == "MSH" ? 1 : 0;
                for (size_t m = 0; m < _segListOrdered[i].fieldList.size(); m++)
                {
                    if (m > startField)
                        strMessage += encoding->_fieldDelimiter;
                    HL7Field field = _segListOrdered[i].fieldList[m];
                    if (field.isDelimitersField)
                    {
                        strMessage += field.getUndecodeValue();
                        continue;
                    }

                    if (field.hasRepetitions)
                    {
                        for (size_t n = 0; n < field.getRepetitionList().size(); n++)
                        {
                            if (n > 0)
                                strMessage += encoding->_repetitionDelimiter;
                            serializeField(field.getRepetitionList()[n], strMessage);
                        }
                    }
                    else
                        serializeField(field, strMessage);
                }

                strMessage += encoding->_segmentDelimiter;
            }
        }
        catch (...)
        {
            if (currentSegName == "MSH")
                throw HL7Exception("Failed to serialize the MSH segment with error -");
            else
                throw;
        }

        return strMessage;
    }
    catch (...)
    {
        throw HL7Exception("Failed to serialize the message with error");
    }
}

std::string Message::getValue(std::string strValueFormat)
{
    std::string segmentName = "";
    int segmentOccurrence = 0;
    int componentIndex = 0;
    int subComponentIndex = 0;
    std::string strValue = "";
    std::vector<std::string> allComponents = MsgHelper::split(strValueFormat, '.');
    int comCount = allComponents.size();
    bool isValid = validateValueFormat(allComponents);
    if (isValid)
    {
        std::smatch matches;
        std::regex r1(segmentRegex);
        std::regex_match(allComponents[0], matches, r1);
        if (matches.size() < 1)
            throw HL7Exception("Request format is not valid.");
        segmentName = matches[1]; // this is a point need test
        if (matches.size() > 3)
        {
            segmentOccurrence = std::stoi(matches[3]);
            segmentOccurrence--;
        }
        if (segmentList.count(segmentName))
        {
            Segment segment = segmentList[segmentName][segmentOccurrence];
            if (comCount == 4)
            {
                componentIndex = std::stoi(allComponents[2]);
                subComponentIndex = std::stoi(allComponents[3]);
                try
                {
                    HL7Field field = this->getField(segment, allComponents[1]);
                    strValue = field.componentList[componentIndex - 1].subComponentList[subComponentIndex - 1].getValue();
                }
                catch (...)
                {
                    throw new HL7Exception("SubComponent not available.");
                }
            }
            else if (comCount == 3)
            {
                componentIndex = std::stoi(allComponents[2]);
                try
                {
                    HL7Field field = this->getField(segment, allComponents[1]);
                    strValue = field.componentList[componentIndex - 1].getValue();
                }
                catch (...)
                {
                    throw HL7Exception("Component not available.");
                }
            }
            else if (comCount == 2)
            {
                try
                {
                    HL7Field field = this->getField(segment, allComponents[1]);
                    strValue = field.getValue();
                }
                catch (...)
                {
                    throw HL7Exception("Field not available.");
                }
            }
            else
            {
                try
                {
                    strValue = segment.getValue();
                }
                catch (...)
                {
                    throw HL7Exception("Segment value not available.");
                }
            }
        }
        else
            throw HL7Exception("Segment name not available.");
    }
    else
    {
        throw HL7Exception("Request format is not valid");
    }
    return this->encoding->decode(strValue);
}

bool Message::setValue(std::string strValueFormat, std::string strValue)
{
    bool isSet = false;
    std::string segmentName = "";
    int componentIndex = 0;
    int subComponentIndex = 0;
    std::vector<std::string> allComponents = MsgHelper::split(strValueFormat, '.');
    int comCount = allComponents.size();
    bool isValid = validateValueFormat(allComponents);
    if (isValid)
    {
        segmentName = allComponents[0];
        if (segmentList.count(segmentName))
        {
            for (size_t i = 0; i < segmentList[segmentName].size(); i++)
            {
                Segment segment = segmentList[segmentName][i];
                if (comCount == 4)
                {
                    componentIndex = std::stoi(allComponents[2]);
                    subComponentIndex = std::stoi(allComponents[3]);
                    try
                    {
                        HL7Field field = this->getField(segment, allComponents[1]);
                        field.componentList[componentIndex - 1].subComponentList[subComponentIndex - 1].setValue(strValue);
                        isSet = true;
                    }
                    catch (...)
                    {
                        throw HL7Exception("SubComponent not available.");
                    }
                }
                else if (comCount == 3)
                {
                    componentIndex = std::stoi(allComponents[2]);
                    try
                    {
                        HL7Field field = this->getField(segment, allComponents[1]);
                        field.componentList[componentIndex - 1].setValue(strValue);
                        isSet = true;
                    }
                    catch (...)
                    {
                        throw HL7Exception("Component not available");
                    }
                }
                else if (comCount == 2)
                {
                    try
                    {
                        HL7Field field = this->getField(segment, allComponents[1]);
                        field.setValue(strValue);
                        isSet = true;
                    }
                    catch (...)
                    {
                        throw HL7Exception("Field not available");
                    }
                }
                else
                {
                    throw HL7Exception("Cannot overwrite a segment value");
                }
            }
        }
        else
            throw HL7Exception("Segment name not available");
    }
    else
        throw HL7Exception("Request format is not valid");

    return isSet;
}

bool Message::isComponentized(std::string strValueFormat)
{
    bool isComponentized = false;
    std::string segmentName = "";
    std::vector<std::string> allComponents = MsgHelper::split(strValueFormat, '.');
    int comCount = allComponents.size();
    bool isValid = validateValueFormat(allComponents);
    if (isValid)
    {
        segmentName = allComponents[0];

        if (comCount >= 2)
        {
            try
            {
                Segment segment = segmentList[segmentName][0];
                HL7Field field = this->getField(segment, allComponents[1]);

                isComponentized = field.isComponentized;
            }
            catch (...)
            {
                throw HL7Exception("Field not available.");
            }
        }
        else
            throw HL7Exception("Field not identified in request");
    }
    else
        throw HL7Exception("Request format is not valid");

    return isComponentized;
}

bool Message::hasRepetitions(std::string strValueFormat)
{
    std::string segmentName = "";

    std::vector<std::string> allComponents = MsgHelper::split(strValueFormat, '.');
    int comCount = allComponents.size();
    bool isValid = validateValueFormat(allComponents);

    if (isValid)
    {
        segmentName = allComponents[0];
        Segment segment = segmentList[segmentName][0];

        if (comCount >= 2)
        {
            try
            {
                auto count = this->getFieldRepetitions(segment, allComponents[1]);
                return count > 1;
            }
            catch (...)
            {
                throw HL7Exception("Field not available.");
            }
        }
        else
            throw HL7Exception("Field not identified in request");
    }
    else
        throw HL7Exception("Request format is not valid");
}

bool Message::isSubComponentized(std::string strValueFormat)
{
    bool isSubComponentized = false;
    std::string segmentName = "";
    int componentIndex = 0;
    std::vector<std::string> allComponents = MsgHelper::split(strValueFormat, '.');
    int comCount = allComponents.size();
    bool isValid = validateValueFormat(allComponents);

    if (isValid)
    {
        segmentName = allComponents[0];

        if (comCount >= 3)
        {
            try
            {
                auto segment = segmentList[segmentName][0];
                auto field = this->getField(segment, allComponents[1]);

                componentIndex = std::stoi(allComponents[2]);
                isSubComponentized = field.componentList[componentIndex - 1].isSubComponentized;
            }
            catch (...)
            {
                throw HL7Exception("Component not available.");
            }
        }
        else
            throw HL7Exception("Component not identified in request");
    }
    else
        throw HL7Exception("Request format is not valid");

    return isSubComponentized;
}

Message Message::getACK(bool bypassValidation)
{
    return this->createAckMessage("AA", false, "", bypassValidation);
}

Message Message::getNACK(std::string code, std::string errMsg, bool bypassValidation)
{
    return this->createAckMessage(code, true, errMsg, bypassValidation);
}

bool Message::addNewSegment(Segment newSegment)
{
    try
    {
        newSegment.sequenceNo = segmentCount++;

        if (!segmentList.count(newSegment.name))
            segmentList[newSegment.name] = std::vector<Segment>();

        segmentList[newSegment.name].push_back(newSegment);
        return true;
    }
    catch (...)
    {
        segmentCount--;
        throw HL7Exception("Unable to add new segment. Error");
    }
}

bool Message::removeSegment(std::string segmentName, int index)
{
    try
    {
        if (!segmentList.count(segmentName))
            return false;

        auto list = segmentList[segmentName];
        if (list.size() <= index)
            return false;

        list.erase(list.begin() + index);
        segmentCount--;

        return true;
    }
    catch (...)
    {
        throw HL7Exception("Unable to add remove segment. Error");
    }
}

std::vector<Segment> Message::segments()
{
    return getAllSegmentsInOrder();
}

std::vector<Segment> Message::segments(std::string segmentName)
{
    std::vector<Segment> selectSegment;
    std::vector<Segment> allSegment1 = getAllSegmentsInOrder();
    for (size_t i = 0; i < allSegment1.size(); i++)
    {
        if (allSegment1[i].name == segmentName)
            selectSegment.push_back(allSegment1[i]);
    }
    return selectSegment;
}

Segment Message::defaultSegment(std::string segmentName)
{
    std::vector<Segment> allSegment1 = getAllSegmentsInOrder();
    for (size_t i = 0; i < allSegment1.size(); i++)
    {
        if (allSegment1[i].name == segmentName)
            return allSegment1[i];
    }
}

void Message::addSegmentMSH(std::string sendingApplication, std::string sendingFacility, std::string receivingApplication, std::string receivingFacility, std::string security, std::string messageType, std::string messageControlID, std::string processingID, std::string version)
{
    auto dateString = MsgHelper::LongDateWithFractionOfSecond();
    auto delim = this->encoding->_fieldDelimiter;

    std::string response = "MSH" + this->encoding->allDelimiter() + delim +
                           sendingApplication + delim +
                           sendingFacility + delim +
                           receivingApplication + delim +
                           receivingFacility + delim +
                           this->encoding->encode(dateString) + delim +
                           (security != "" ? security : "") + delim +
                           messageType + delim +
                           messageControlID + delim +
                           processingID + delim +
                           version + this->encoding->_segmentDelimiter;

    auto message = Message(response);
    message.parseMessage();
    this->addNewSegment(message.defaultSegment("MSH"));
}

std::vector<char> Message::getMLLP(bool validate)
{
    std::vector<char> mllp;
    std::string hl7 = this->serializeMessage(validate);
    for (size_t i = 0; i < hl7.size(); i++)
    {
      mllp.push_back(toascii(hl7[i]));
    }
    mllp.insert(mllp.begin(),11);  //VT
    mllp.push_back(28);//FS
    mllp.push_back(13);//CR
    
    return mllp;
