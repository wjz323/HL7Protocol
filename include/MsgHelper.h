#pragma once

#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <iostream>
#include <iomanip>
namespace MsgHelper
{

    static std::string lineSeparators[] = { "\r\n", "\n\r", "\r", "\n" };
    template <typename T>
    void addVector(std::vector<T> &itemList, T item, int position, T emptyItem)
    {
        int listCount = itemList.size();
        position = position - 1;
        if (position < listCount)
        {
            itemList[position] = item;
        }
        else
        {
            for (int i = listCount; i < position; i++)
            {
                itemList.push_back(emptyItem);
            }
            itemList.push_back(item);
        }
    }
    template <typename T>
    std::vector<std::string> split(std::string str, T delimiter,bool removeEmpty=0,bool removeWhiteSpace=0)
    {
    std::string::size_type pos;
    std::vector<std::string> tokens;
    int size = str.size();
    for (int i = 0; i < size; i++)
    {
		pos = str.find(delimiter, i);
        if (pos <size)
        {
            std::string subStr=str.substr(i, pos-i);
            if((subStr==""&&removeEmpty)||(subStr==" "&&removeWhiteSpace))
            {}
            else
			    tokens.push_back(subStr);	
            i = pos;
		}      
	}
    return tokens;
    }

    std::string LongDateWithFractionOfSecond()
    {
        auto t=std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::stringstream ss;
        ss<<std::put_time(std::localtime(&t),"%Y%m%d%H%M%S");
        
        return ss.str();

    }

    

}

