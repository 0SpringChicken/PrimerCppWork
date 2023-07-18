#pragma once
#include <iostream>
#include <string>
#include <vector>

//7.32定义一个Windows_mgr类 其中clear()为Screen类的友元
class Windows_mgr
{
public:
    void clear();
};

class Screen
{
    friend void Windows_mgr::clear();
public:
    typedef std::string::size_type pos;
    Screen() = default;
    Screen(pos ht, pos wd) :height(ht), width(wd), contents(ht * wd, ' ') {}
    Screen(pos ht, pos wd, char c):height(ht),width(wd),contents(ht*wd,c)
    {}//contents就是含有ht*wd个c的字符串
    char get() const // 隐式内联
    {
        return contents[cursor];
    }
    inline char get(pos ht, pos wd) const; // 显示内联
    Screen& move(pos r, pos c); // 也能在之后被设置为内联
    // 定义在类内部的成员函数是自动内联的，也可以用inline关键字作为声明的一部分显示的声明成员函数
    // 也能够在类的外部用inline关键字修饰函数的定义
    // 虽然无须在声明和定义出同时说明inline，但这么做也合法，一般情况下写在类外，便于理解
    Screen& Set(char);
    Screen& Set(pos, pos, char);
    // 打印Screen的内容  
    // 一个常量成员函数如果以引用的形式返回了*this，则他的返回类型是一个常量引用
    // 基于const的重载  通过区分成员函数是否是const的  我们可以对其进行重载
    Screen& display(std::ostream &os)
    {
        do_display(os); 
        return *this;
    }
    const Screen& display(std::ostream& os) const
    {
        do_display(os);
        return *this;
    }

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    void do_display(std::ostream& os) const
    {
        os << contents << std::endl;
    }
};

// mutable关键字  可以让即使是在const成员函数内  数据也能进行修改  可变数据成员
// Severity	Code	Description	Project	File	Line	Suppression State
// Error	LNK2019	unresolved external symbol "public: class Screen & __cdecl Screen::move(unsigned __int64,unsigned __int64)" (? move@Screen@@QEAAAEAV1@_K0@Z) referenced in function main	Test_Chapter_7	F : \C++ Primer\Chapter7\Test_Chapter_7\Test_Chapter_7.obj	1
// 未解析的外部符号

// 如果是const、引用，或者某种未提供默认构造函数的类类型，我们必须通过构造函数初始值列表为这些成员提供初始值


