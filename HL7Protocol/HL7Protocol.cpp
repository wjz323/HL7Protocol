// HL7Protocol.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Component.h"

void addVector(std::vector<int>& numList,int number,int position)
{
    int listCount=numList.size();
    position= position - 1;
    if (position < listCount)
    {
		numList[position] = number;
	}
    else
    {
        for (int i = listCount; i < position; i++)
        {
			numList.push_back(0);
		}
		numList.push_back(number);
	}
}

int main()
{
    ////int转换成string
    //int a = 13;
    //std::string str1 = "1|1|323|32131|3131|32131|";
    //int index = str1.find('^', 5);
    ////int 转换成16进制string
   
   
    //std::ostringstream oss;
    //oss << std::hex << a;
    //std::string v = oss.str();
    //std::cout <<v << std::endl;
    //std::string str = std::to_string(a);
    //std::cout << str << std::endl;
    //std::cout << "Hello World!\n";
    //std::cout << index;

    //string以某一字符分割成vector
    std::string str2 = "1|1|323|32131|3131|32131|";
    std::vector<std::string> v1;
     Component *test=new Component();

    v1=test->split(str2, '|');
    for (int i = 0; i < v1.size(); i++)
    {
		std::cout << v1[i] << std::endl;
	}
    delete test;

    //vector插入元素
    std::vector<int> nList = std::vector<int>();
    nList.push_back(1);
    nList.push_back(2);
    nList.push_back(3);
    addVector(nList,8,2);
    int wjz = 0;
}







// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
