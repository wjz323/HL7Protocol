#pragma once

#include <vector>
#include <string>
namespace MsgHelper
{
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
    std::vector<std::string> split(std::string str, T delimiter,bool removeEmpty=0)
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
            if(subStr==""&&removeEmpty)
            {}
            else
			    tokens.push_back(subStr);	
            i = pos;
		}      
	}
    return tokens;
    }
}

