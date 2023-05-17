#pragma once
#include "Component.h"
#include "Field.h"
#include <string>
#include <vector>
#include <map>
#include <regex>
#include "Segment.h"
class Message
{
public:
	Message();
	Message(std::string strMessage);
	~Message();
	std::map<std::string,std::vector<Segment>> segmentList;
	std::string hl7Message;
	std::string version;
	std::string messageStructure;
	std::string messageControlID;
	std::string processingID;
	int segmentCount;
	HL7Encoding *encoding;
	bool equals(std::string obj);
	bool parseMessage(bool bypassValidation = false);
	std::string serializeMessage(bool validate);
	std::string getValue(std::string strValueFormat);
	bool setValue(std::string strValueFormat, std::string strValue);
	bool isComponentized(std::string strValueFormat);
	bool hasRepetitions(std::string strValueFormat);
	bool isSubComponentized(std::string strValueFormat);
	Message getACK(bool bypassValidation = false);
	Message getNACK(std::string code, std::string errMsg, bool bypassValidation = false);
	bool addNewSegment(Segment newSegment);
	bool removeSegment(std::string segmentName, int index = 0);
	std::vector<Segment> segments();
	std::vector<Segment> segments(std::string segmentName);
	Segment defaultSegment(std::string segmentName);
	void addSegmentMSH(std::string sendingApplication, std::string sendingFacility, std::string receivingApplication, 
					   std::string receivingFacility,std::string security, std::string messageType, 
					   std::string messageControlID, std::string processingID, std::string version);
	std::vector<char> getMLLP(bool validate = false);
private:
	std::vector<std::string> allSegemnts;
	
	const std::string segmentRegex	=R"(^([A-Z][A-Z][A-Z1-9])([\(\[]([0-9]+)[\)\]]){0,1}$)";
    const std::string fieldRegex = R"(^([0-9]+)([\(\[]([0-9]+)[\)\]]){0,1}$)";
    const std::string otherRegEx = R"(^[1-9]([0-9]{1,2})?$)";
	Message createAckMessage(std::string code, bool isNack, std::string errMsg, bool bypassValidation);
	HL7Field getField(Segment segment, std::string index);
	int getFieldRepetitions(Segment segment, std::string index);
	bool validateMessage();
	void serializeField(HL7Field field, std::string& strMessage);
	std::vector<Segment> getAllSegmentsInOrder();
	bool validateValueFormat(std::vector<std::string> allComponents);
	

};
