#ifndef  MESSAGE_H
#define MESSAGE_H
#include "Component.h"
#include "Field.h"
#include <String>
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
#endif // ! MESSAGE_H
