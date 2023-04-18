cmake_minimum_required(VERSION 3.0.0)

project(hl7 VERSION 0.1.0)

set(SRC_LIST 
        ./Component.cpp 
        ./Field.cpp 
        ./HL7Encoding.cpp 
        ./HL7Protocol.cpp 
        ./Message.cpp 
        ./MessageElement.cpp 
        ./Segment.cpp 
        ./Field.cpp 
        ./SubComponent.cpp) 

add_library(hl7 SHARED ${SRC_LIST})