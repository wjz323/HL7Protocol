// HL7Protocol.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include "include/Component.h"
#ifdef _DEBUG
#pragma comment(lib,"E:\\Code\\HL7Protocol\\HL7Protocol\\x64\\Debug\\ClassLibrary1")
#else
#pragma comment(lib,"..\\release\\PlusPlusTest.lib")
#endif
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
struct QCPoint
{
    float_t con;
    float_t vari;
    float_t upper_limit;
    float_t lower_limit;

};

struct CardInfo
{
    uint8_t device_id;//仪器型号，1个字节，0，1，2，3，4以代号的方式代表仪器型号
    uint32_t md_id; //项目代号，2个字节；支持大于255个项目；如果确定项目在255以内可以使用uint8_t
    ////中文名称，英文名称，单位
    uint8_t cali_type;//校准类型，2为两点校准，3为三点校准
    uint8_t md_mode;  //方法学模式，0一步法，1两步一分离，2两步两分离
    uint8_t fit_type; //拟合方式，4：4参数，10：样条函数
    //实验类型，校准还是样本
    uint8_t cali_mode;//校准模式，0定量 1定性
    uint8_t dilute_mode;//是否为稀释项目
    uint8_t dilute_kind;//稀释液种类，是不同稀释液还是相同的稀释液
    uint8_t ds1_volume;//第一步稀释样本加样量
    uint8_t dd1_volume;//第一步稀释稀释液加样量
    uint8_t d1_time;//第一步稀释后需要的孵育时间
    uint8_t ds2_volume;//第二步稀释样本加样量
    uint8_t dd2_volume;//第二步稀释稀释液加样量
    uint8_t d2_time;//第二步稀释后需要的孵育时间
    uint8_t con_precision;//浓度结果保留位数
    uint8_t reagent_count;//试剂组分个数，不包含稀释液
    uint8_t sp_volume;//样本加样量
    uint8_t first_add_name;//试剂加样顺序，第一个试剂名称为R1，R2还是R3
    uint8_t first_add_volume;//试剂加样量
    uint16_t first_add_icb_time;//孵育时间：
    uint8_t first_add_is_wash;//是否清洗
    uint8_t second_add_name;//试剂加样顺序，第二个试剂名称为R1，R2还是R3
    uint8_t second_add_volume;//试剂加样量
    uint16_t second_add_icb_time;//孵育时间：
    uint8_t second_add_is_wash;//是否清洗
    uint8_t third_add_name;//试剂加样顺序，第三个试剂名称为R1，R2还是R3
    uint8_t third_add_volume;//试剂加样量
    uint16_t third_add_icb_time;//孵育时间：
    uint8_t third_add_is_wash;//是否清洗
    uint8_t fourth_add_name;//试剂加样顺序，第四个试剂名称为R1，R2还是R3
    uint8_t fourth_add_volume;//试剂加样量
    uint16_t fourth_add_icb_time;//孵育时间：
    uint8_t fourth_add_is_wash;//是否清洗
    float_t con_upperlimit;
    float_t con_lowerlimit;
    uint8_t dilute_special;//是否连吸

    uint32_t lot_id; //批号
    uint32_t exp;//有效期

    uint8_t cali_curve_point_count;//定标点个数
    float_t cal0;
    float_t cal0_upp_limit;
    float_t cal0_low_limit;
    float_t cal1;
    float_t cal1_upp_limit;
    float_t cal1_low_limit;
    float_t cal2;
    float_t cal2_upp_limit;
    float_t cal2_low_limit;
    float_t con_array[15];
    uint32_t rlu_array[15];

    QCPoint qc1;
    QCPoint qc2;
    QCPoint qc3;

    uint16_t bottle_id;
    uint16_t test_count;

};



//int main()
//{
    
//    std::cout <<"CardInfo " << sizeof(CardInfo) << std::endl;
//    std::cout << "float " << sizeof(float_t) << std::endl;
//    std::cout << "uint8 " << sizeof(uint8_t) << std::endl;
//    std::cout << "uin16 " << sizeof(uint16_t) << std::endl;
//    std::cout << "uint32 " << sizeof(uint32_t) << std::endl;
    

//}





// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
