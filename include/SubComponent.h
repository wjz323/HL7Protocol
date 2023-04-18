
#ifndef HL7SUBCOMPONENT_H
#define HL7SUBCOMPONENT_H
#include "MessageElement.h"
#include <string>
class HL7SubComponent : public HL7MessageElement
{

public:
	HL7SubComponent();
	HL7SubComponent(std::string val,HL7Encoding* _encoding);
	~HL7SubComponent();
protected:
	void processValue() override;

};



#endif // !HL7SUBCOMPONENT_H

