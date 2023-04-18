cmake_minimum_required(VERSION 3.0.0)

project(swap VERSION 0.1.0)

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

add_library(swap SHARED ${SRC_LIST})