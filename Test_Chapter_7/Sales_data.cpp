#include "Sales_data.h"

// Sales_data::Sales_data(std::istream& is)
// {
//     read(is, *this);
// }

std::istream& operator>>(std::istream& datain, Sales_data& data)
{
    if (datain)
    {
        datain >> data.bookNo;
        datain >> data.units_solds;
    }
    return datain;
}

std::ostream& operator<<(std::ostream& dataout, const Sales_data& data)
{
    const char szV[] = "\t";
    dataout << data.bookNo << szV
        << data.units_solds << std::endl;
    return dataout;
}

Sales_data& Sales_data::combine(const Sales_data& rhs)
{
    units_solds += rhs.units_solds;
    revenue += rhs.revenue;
    return *this;
}

// 类相关非类成员函数
std::istream& read(std::istream& is, Sales_data& item)
{
    double price = 0;
    is >> item.bookNo >> item.units_solds >> price;
    item.revenue = item.units_solds * price;
    return is;
}

std::ostream& print(std::ostream& os, const Sales_data& item)
{
    const char ch = '\t';
    os << item.bookNo << ch
        << item.units_solds << ch
        << item.revenue << ch
        << item.avg_price() << std::endl;
    return os;
}