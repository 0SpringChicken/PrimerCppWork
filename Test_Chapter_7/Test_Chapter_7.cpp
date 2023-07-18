// Test_Chapter_7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Sales_data.h"
#include "Screen.h"

#define REC(A,B) (A)*(B)
#define RECS(A,B) ((A)*(B))


int main()
{
    Screen myScreen(5, 5, 'X');
    myScreen.move(4, 0).Set('#').display(std::cout);
    std::cout << "\n";
    myScreen.display(std::cout);
    std::cout << "\n";

    Windows_mgr win_self;
    win_self.clear();
}

// 重载运算符  选择成员与非成员的标准
// 1.赋值，下标，调用以及成员访问箭头必须是成员的
// 2.复合赋值运算符一般来说是成员，但非必须
// 3.改变对象状态的运算符或者与给定类型密切相关的运算符，如递增递减和解引用运算符，应该是成员
// 4.具有对称性的运算符可能转换任意一端的运算对象，例如算数、相等性、关系和位运算符等，通常为非成员函数


// 对输入输出运算符的重载 （输入输出必须在类外重载）
// （1）输出运算符<<
// 通常情况下 输出运算符的第一个形参是一个非常量ostream对象的引用（无法直接复制一个ostream对象）
// 第二个形参一般来说是一个常量引用，是我们需要打印的类型
// 输出运算应当减少格式化操作
// （2）输入运算符>>
// 输入运算符必须处理输入失败的情况，输出运算符则不用，
// 输入运算符检测输入出现问题的情形：
// 1.输入了错误的值 2.读取到了文件的末尾 
// 当读取操作发生错误时，输入运算符应该负责从错误中恢复

// 算术和关系运算符
// 通常情况下，算术和关系运算符定义成非成员函数，目的是为了使其可以对左侧或右侧的运算对象进行转换
// 算术运算符往往会在运算后得到一个有别于任意一个运算对象的新值
// 定义算术运算符的同时  会定义一个对应的复合赋值运算符（应设置为成员函数） 返回左侧运算对象的引用

// 赋值运算符
// 返回值应为其左侧运算对象的引用 必须设置为成员函数（initializer_list<type>）P198 6.2.6

// 下标运算符（必须成员函数）
// 如果一个类包含下标运算符  则它通常会定义两个版本  一个返回普通引用 另一个是类的常量成员并返回常量引用

// 递减和递增运算符 建议设定成员函数  前置版本和后置版本都要定义
// 那么怎么区分前置版本和后置版本呢  
// 为了解决上述的问题  后置版本接受一个额外的（不被使用的）int类型形参，编译器为该形参提供一个0当做实参
// 类似为string operator++(int) 这种

// 成员访问运算符 解引用（*）与箭头（->）

// 函数调用运算符  必须是成员的
// 例子：
//struct absInt {
//    int operator()(int val) const{
//        return val < 0 ? -val : val;
//    }
//};
// 上面就是一个函数调用运算符重载的例子 其功能是返回一个int型数据的绝对值
// 但是在上面的定义中abs也只是一个对象而非一个函数
// 一个类可以定义多个不同版本的调用运算符，衙门支架应该再参数数量或者类型上有所区别
// 如果一个类定义了调用运算符  那么该类的对象称作函数对象

    //float ftv = 111111.3333333333;
    //std::cout << std::setprecision(12) << ftv << std::endl;
    //double dtv = 111111.3333333333;
    //std::cout << std::setprecision(12) << dtv << std::endl;
    //int a = 1, b = 2, c = 3, d = 4;
    //int e = ~REC(a + b, c + d);
    //std::cout << "e value:" << e << std::endl;
    //int f = ~RECS(a + b, c + d);
    //std::cout << "f value:" << f << std::endl;

