#pragma once

#include "MessageElement.h"
#include "Component.h"
#include <vector>
class HL7Field : public HL7MessageElement
{
public:
	HL7Field();
	HL7Field(std::string pValue, HL7Encoding* encoding);
	HL7Field(HL7Encoding* encoding);
	~HL7Field();
	std::vector<Component> componentList;
	bool isComponentized = false;
	bool hasRepetitions = false;
	bool isDelimitersField = false;
	std::vector<HL7Field> getRepetitionList() const;
	void setRepetitionList(const std::vector<HL7Field>& repetitionList);
	bool addNewComponent(Component com);
	bool addNewComponent(Component com,int position);
	std::vector<Component> getComponents() const;
	Component getComponent(int position) const;
	bool removeEmptyTrailingComponents();
	void addRepeatingField(HL7Field field);
	//void addVector(std::vector<Component>& componentList,Component componet,int position);

private:
	std::vector<HL7Field> _repetitionList;

protected:
	void processValue() override;


};

