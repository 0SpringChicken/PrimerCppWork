#include "Sales_data.h"


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
