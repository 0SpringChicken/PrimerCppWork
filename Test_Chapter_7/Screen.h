#pragma once
#include <iostream>
#include <string>
#include <vector>

//7.32����һ��Windows_mgr�� ����clear()ΪScreen�����Ԫ
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
    {}//contents���Ǻ���ht*wd��c���ַ���
    char get() const // ��ʽ����
    {
        return contents[cursor];
    }
    inline char get(pos ht, pos wd) const; // ��ʾ����
    Screen& move(pos r, pos c); // Ҳ����֮������Ϊ����
    // ���������ڲ��ĳ�Ա�������Զ������ģ�Ҳ������inline�ؼ�����Ϊ������һ������ʾ��������Ա����
    // Ҳ�ܹ�������ⲿ��inline�ؼ������κ����Ķ���
    // ��Ȼ�����������Ͷ����ͬʱ˵��inline������ô��Ҳ�Ϸ���һ�������д�����⣬�������
    Screen& Set(char);
    Screen& Set(pos, pos, char);
    // ��ӡScreen������  
    // һ��������Ա������������õ���ʽ������*this�������ķ���������һ����������
    // ����const������  ͨ�����ֳ�Ա�����Ƿ���const��  ���ǿ��Զ����������
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

// mutable�ؼ���  �����ü�ʹ����const��Ա������  ����Ҳ�ܽ����޸�  �ɱ����ݳ�Ա
// Severity	Code	Description	Project	File	Line	Suppression State
// Error	LNK2019	unresolved external symbol "public: class Screen & __cdecl Screen::move(unsigned __int64,unsigned __int64)" (? move@Screen@@QEAAAEAV1@_K0@Z) referenced in function main	Test_Chapter_7	F : \C++ Primer\Chapter7\Test_Chapter_7\Test_Chapter_7.obj	1
// δ�������ⲿ����

// �����const�����ã�����ĳ��δ�ṩĬ�Ϲ��캯���������ͣ����Ǳ���ͨ�����캯����ʼֵ�б�Ϊ��Щ��Ա�ṩ��ʼֵ


