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

