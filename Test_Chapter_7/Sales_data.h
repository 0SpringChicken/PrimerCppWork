#ifndef __SALES_DATA_H__
#define __SALES_DATA_H__

#include <iostream>
#include <string>

class Sales_data;

// 友元函数还要提供独立的声明
std::istream& operator>>(std::istream& datain, Sales_data& data);
std::ostream& operator<<(std::ostream& dataout, const Sales_data& data);
std::istream& read(std::istream& is, Sales_data& item);
std::ostream& print(std::ostream& os, const Sales_data& item);

class Sales_data
{
public:
    friend std::istream& operator>>(std::istream& datain, Sales_data& data); 
    friend std::ostream& operator<<(std::ostream& dataout, const Sales_data& data);
    friend std::istream& read(std::istream& is, Sales_data& item);
    friend std::ostream& print(std::ostream& os, const Sales_data& item);
public:
    Sales_data(const std::string& s, unsigned n, double p) :
        bookNo(s), units_solds(n), revenue(p* n) {}
 //   Sales_data(std::istream&);
    // C++11 新标准  提出了委托构造函数
// 委托构造函数 使用它所属类的其他构造函数执行它自己的初始化过程，可以理解为
// 委托构造函数，把它自己的职责委托给了其他构造函数
// 构成：成员初始值的列表、一个函数体
    // 下面为委托构造函数举例
public:
    Sales_data() :Sales_data("", 0, 0) {} // 调用了Sales_data(const std::string &s, unsigned n, double p)
    Sales_data(std::string str) :Sales_data(str, 0, 0) {}
    Sales_data(std::istream& is) :Sales_data() { read(is, *this); }// 调用了 Sales_data(std::istream&);
    // 值得说明的是，上面接受std::istream&参数的构造函数，首先调用默认的构造函数，默认构造函数则去调用
    // 三参数构造函数，当委托的构造函数执行完毕后，接着执行std::istream&构造函数体的内容
    // 即为 read(is, *this)，将数据读取给已经构造好的类
public:
 //   Sales_data() = default;// =default要求编译器生成构造函数
    Sales_data(const std::string &s):bookNo(s){}
    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);
    // 转换构造函数  即只定义了一个参数的构造函数（隐式类型转换机制）
    // 只允许一步类类型转换  类类型转换不总是有效
    // explicit关键字  抑制隐式类型转换 仅能用在类内部的声明中
    //
private:
    double avg_price() const { return units_solds ? revenue / units_solds : 0; }
    std::string bookNo;
    unsigned units_solds = 0;
    double revenue = 0.0;
};

struct absInt {
    int operator()(int val) const {
        return val < 0 ? -val : val;
    }
};

// 引入const成员函数
// const关键字的作用其实是修改隐式this指针的类型 未修饰的this指针可以理解为 Sales_data* const 加入const关键字后变为 Sales_data const * const
// 这其实就是加入了顶层const属性  常量对象无法调用普通成员函数 所以常量对象以及常量对象的引用或者指针都只能调用常量成员函数

// 默认构造函数的作用 
// 默认初始化的发生情况：
// 1.块作用域内不使用任何初始值定义一个非静态变量或者数组 2.一个类含有类类型成员且使用合成的默认构造函数时
// 3.类类型的成员没有在构造函数初始值列表中显示的初始化
// 值初识化发生在以下情况
// 1.数组初始化过程中，提供的值的数量小于数组长度
// 2.不使用初始值定义一个局部静态变量
// 3.显示的请求值初始化
//

// 聚合类 用户可以直接访问其成员  并具有特殊的初始化语法形式
// 1. 所有成员都是public 2.没有定义任何构造函数 3.没有类内初始值 4.没有基类，无virtual函数
//


#endif

