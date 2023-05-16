#pragma once
#include "MessageElement.h"
#include "HL7Encoding.h"
#include <vector>
#include "SubComponent.h"
#include <string>
class Component : public HL7MessageElement
{
	public:
		Component();
		Component(HL7Encoding* encoding,bool isDelimiter=false);
		Component(std::string pValue, HL7Encoding* encoding);
		~Component();
		std::vector<HL7SubComponent> subComponentList;
		std::vector<HL7SubComponent>  getSubComponents() const;
		void setSubComponents(const std::vector<HL7SubComponent>& subComponents); 
	    bool isSubComponentized = false;
		HL7SubComponent subComponents(int position);
		
	protected:
		void processValue() override;
	private:
		bool isDelimiter = false;
public:
		//std::vector<std::string> split(std::string str,char delimiter);



};

