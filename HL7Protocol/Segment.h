#ifndef SEGMENT_H
#define SEGMENT_H
#include "MessageElement.h"
#include <vector>
#include "Field.h"
#include "HL7Encoding.h"
class Segment:HL7MessageElement
{
public:
	Segment();
	Segment(HL7Encoding *encoding);
	Segment(std::string name, HL7Encoding *encoding);

	std::vector<HL7Field> fieldList;
	int sequenceNo;
	std::string name;

};

#endif
