#pragma once
#include "MessageElement.h"
#include <vector>
#include "Field.h"
#include "HL7Encoding.h"
class Segment:public HL7MessageElement
{
public:
	Segment();
	Segment(HL7Encoding *encoding);
	Segment(std::string name, HL7Encoding *encoding);

	void addEmptyField();
	void addNewField(std::string content, int position = -1);
	void addNewField(std::string content, bool isDelimiters);
	bool addNewField(HL7Field field, int position = -1);
	HL7Field fields(int position);
	std::vector<HL7Field> GetAllFields();
	int getSequenceNo();

	std::vector<HL7Field> fieldList;
	int sequenceNo;
	std::string name;

protected:
	void processValue() override;

};

