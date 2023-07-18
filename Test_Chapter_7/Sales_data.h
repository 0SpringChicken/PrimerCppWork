#ifndef __SALES_DATA_H__
#define __SALES_DATA_H__

#include <iostream>
#include <string>

class Sales_data;

// ��Ԫ������Ҫ�ṩ����������
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
    // C++11 �±�׼  �����ί�й��캯��
// ί�й��캯�� ʹ������������������캯��ִ�����Լ��ĳ�ʼ�����̣��������Ϊ
// ί�й��캯���������Լ���ְ��ί�и����������캯��
// ���ɣ���Ա��ʼֵ���б�һ��������
    // ����Ϊί�й��캯������
public:
    Sales_data() :Sales_data("", 0, 0) {} // ������Sales_data(const std::string &s, unsigned n, double p)
    Sales_data(std::string str) :Sales_data(str, 0, 0) {}
    Sales_data(std::istream& is) :Sales_data() { read(is, *this); }// ������ Sales_data(std::istream&);
    // ֵ��˵�����ǣ��������std::istream&�����Ĺ��캯�������ȵ���Ĭ�ϵĹ��캯����Ĭ�Ϲ��캯����ȥ����
    // ���������캯������ί�еĹ��캯��ִ����Ϻ󣬽���ִ��std::istream&���캯���������
    // ��Ϊ read(is, *this)�������ݶ�ȡ���Ѿ�����õ���
public:
 //   Sales_data() = default;// =defaultҪ����������ɹ��캯��
    Sales_data(const std::string &s):bookNo(s){}
    std::string isbn() const { return bookNo; }
    Sales_data& combine(const Sales_data&);
    // ת�����캯��  ��ֻ������һ�������Ĺ��캯������ʽ����ת�����ƣ�
    // ֻ����һ��������ת��  ������ת����������Ч
    // explicit�ؼ���  ������ʽ����ת�� �����������ڲ���������
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

// ����const��Ա����
// const�ؼ��ֵ�������ʵ���޸���ʽthisָ������� δ���ε�thisָ��������Ϊ Sales_data* const ����const�ؼ��ֺ��Ϊ Sales_data const * const
// ����ʵ���Ǽ����˶���const����  ���������޷�������ͨ��Ա���� ���Գ��������Լ�������������û���ָ�붼ֻ�ܵ��ó�����Ա����

// Ĭ�Ϲ��캯�������� 
// Ĭ�ϳ�ʼ���ķ��������
// 1.���������ڲ�ʹ���κγ�ʼֵ����һ���Ǿ�̬������������ 2.һ���ຬ�������ͳ�Ա��ʹ�úϳɵ�Ĭ�Ϲ��캯��ʱ
// 3.�����͵ĳ�Աû���ڹ��캯����ʼֵ�б�����ʾ�ĳ�ʼ��
// ֵ��ʶ���������������
// 1.�����ʼ�������У��ṩ��ֵ������С�����鳤��
// 2.��ʹ�ó�ʼֵ����һ���ֲ���̬����
// 3.��ʾ������ֵ��ʼ��
//

// �ۺ��� �û�����ֱ�ӷ������Ա  ����������ĳ�ʼ���﷨��ʽ
// 1. ���г�Ա����public 2.û�ж����κι��캯�� 3.û�����ڳ�ʼֵ 4.û�л��࣬��virtual����
//


#endif

