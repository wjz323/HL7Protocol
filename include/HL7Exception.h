#pragma once 

#include <exception>
#include <string>
class HL7Exception : std::exception 
{

public:
	HL7Exception(const std::string& what):m_what(what) 
	{
	}

	virtual ~HL7Exception() throw () 
	{
	}

	virtual const char* what() const throw () 
	{
		return m_what.c_str();
	}
	std::string m_what;
};


