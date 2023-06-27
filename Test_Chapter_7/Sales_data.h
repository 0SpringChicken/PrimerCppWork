#ifndef __SALES_DATA_H__
#define __SALES_DATA_H__

#include <iostream>
#include <string>

class Sales_data;

std::istream& operator>>(std::istream& datain, Sales_data& data);
std::ostream& operator<<(std::ostream& dataout, const Sales_data& data);

class Sales_data
{
public:
    friend std::istream& operator>>(std::istream& datain, Sales_data& data); 
    friend std::ostream& operator<<(std::ostream& dataout, const Sales_data& data);
public:
    Sales_data() = default;
    Sales_data(const std::string &s, unsigned n, double p):
        bookNo(s), units_solds(n), revenue(p*n){}
    Sales_data(const std::string &s):bookNo(s){}
    Sales_data(std::istream&);
    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);
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

#endif

// 引入const成员函数
// const关键字的作用其实是修改隐式this指针的类型 未修饰的this指针可以理解为 Sales_data* const 加入const关键字后变为 Sales_data const * const
// 这其实就是加入了顶层const属性  常量对象无法调用普通成员函数 所以常量对象以及常量对象的引用或者指针都只能调用常量成员函数

