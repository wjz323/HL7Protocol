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
    std::vector<std::string> splitMsg(std::string str1,T t)
    {

       std::vector<std::string> tokens;  // 存储拆分后的子串

        // 以每个分隔符为界，逐个提取子字符串
        size_t start_pos = 0;
        while (start_pos != std::string::npos) {
            // 在字符串中查找下一个分隔符
            size_t min_pos = std::string::npos;
            for (const auto& delimiter : lineSeparators) {
                const size_t pos = str1.find(delimiter, start_pos);
                if (pos != std::string::npos && pos < min_pos) {
                    min_pos = pos;
                }
            }

            // 如果未找到分隔符，则将剩余部分作为最后一个子串
            if (min_pos == std::string::npos) {
                tokens.emplace_back(str1.substr(start_pos, str1.size() - start_pos));
                break;
            }

            // 提取中间段的子串
            tokens.emplace_back(str1.substr(start_pos, min_pos - start_pos));
            start_pos = min_pos + 1;
        }
        for (auto iter=tokens.begin();iter!=tokens.end();++iter)
            {
                if (iter->empty())
                {
                    iter=tokens.erase(iter);
                    --iter;
                }
            }

        return tokens;
    }

    template <typename T>
    std::string LongDateWithFractionOfSecond(T t1)
    {
        auto t=std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::stringstream ss;
        ss<<std::put_time(std::localtime(&t),"%Y%m%d%H%M%S");

        return ss.str();

    }
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

   static std::vector<std::string> splitString(std::string str, std::string delimiter,bool removeEmpty=0,bool removeWhiteSpace=0)
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
        if(pos==std::string::npos)
        {
            std::string subStr=str.substr(i, str.size()-i);
            tokens.push_back(subStr);
            break;
        }
	}
    return tokens;
    }



    

}

