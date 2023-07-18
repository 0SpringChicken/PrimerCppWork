#pragma once
#include <string>
#include <vector>

class Date_Deal
{
    friend std::ostream& operator<<(std::ostream& os, const Date_Deal& claDate);
private:
    unsigned uYear;
    unsigned uMonth;
    unsigned uDay;
public:
    Date_Deal() = default;
    Date_Deal(std::string strDate);
    const static std::vector<std::string> vecMon;
};

