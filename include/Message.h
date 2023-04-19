#pragma once
#include "Component.h"
#include "Field.h"
#include <string>
#include <vector>
#include <map>

class Message:HL7MessageElement
{
public:
	Message();
	~Message();
	
private:
	std::vector<std::string> allSegemnts;
	//std::map<std::string,std::vector<>>
};
