#include "Date_Deal.h"

const std::vector<std::string> Date_Deal::vecMon{"Jan","Feb","Mar", "Apr", "May", "June", "July", "Aug", "Sept", "Oct", "Nov", "Dec"};
Date_Deal::Date_Deal(std::string strDate)
{
    std::string::size_type nPos = 0;
    // 处理不同的字符串 1.month day,year 2.mon/day/year 3.mon day year
    if (strDate.find(',') != std::string::npos) // 对应情况1
    {
        // 先找月份
        for (; strDate.find(vecMon[nPos]) < 0 && nPos<12;)
        {
            nPos++;
        }
        // 结束循环 找到了当前的月份 但是需要nPos再加一
        uMonth = ++nPos;
        // 再来找天数
        nPos = strDate.find_first_of(' ');
        ++nPos;
        std::string strDay;
        for (int i = 0; strDate[nPos] != ','; ++nPos,++i)
        {
            strDay[i] = strDate[nPos];
        }
        uDay = stoul(strDay);
        // 最后找年份
        nPos = strDate.find_first_of(',');
        ++nPos;
        std::string strYear;
        strYear.reserve(16);
        for (int i = 0; strDate[nPos] != '\0'&& nPos < strDate.size(); ++nPos, ++i)
        {
            //strYear[i] = strDate[nPos];  这种方式会抛出异常 out_of_range
            strYear.push_back(strDate[nPos]);
        }
        uYear = stoul(strYear);
    }
    else if (strDate.find('/') != std::string::npos) // 对应情况2
    {
        // 先找月份
        unsigned nPos_bf = nPos;
        nPos = strDate.find_first_of('/', nPos);
        std::string strMon;
        for (int i = 0; nPos_bf != nPos; ++i, ++nPos_bf)
        {
            // strMon[i] = strDate[nPos_bf];
            strMon.push_back(strDate[nPos_bf]);
        }
        unsigned umark = 0;
        while (strMon.find(vecMon[umark]) == std::string::npos)
        {
            ++umark;
        }
        uMonth = ++umark; nPos++;
        // 再找天数
        nPos_bf = nPos;
        nPos = strDate.find_first_of('/', nPos);
        std::string strDay;
        for (int i = 0; nPos_bf != nPos; ++i, ++nPos_bf)
        {
            // strDay[i] = strDate[nPos_bf];
            strDay.push_back(strDate[nPos_bf]);
        }
        uDay = stoul(strDay);
        nPos++;
        // 最后年份
        uYear = stoul(strDate.substr(nPos));
    }
    else // 对应情况3
    {
        // 先找月份
        unsigned nPos_bf = nPos;
        nPos = strDate.find_first_of(' ', nPos);
        std::string strMon;
        for (int i = 0; nPos_bf != nPos; ++i, ++nPos_bf)
        {
            // strMon[i] = strDate[nPos_bf];
            strMon.push_back(strDate[nPos_bf]);
        }
        unsigned umark = 0;
        while (strMon.find(vecMon[umark]) == std::string::npos)
        {
            ++umark;
        }
        uMonth = ++umark; nPos++;
        // 再找天数
        nPos_bf = nPos;
        nPos = strDate.find_first_of(' ', nPos);
        std::string strDay;
        for (int i = 0; nPos_bf != nPos; ++i, ++nPos_bf)
        {
            // strDay[i] = strDate[nPos_bf];
            strDay.push_back(strDate[nPos_bf]);
        }
        uDay = stoul(strDay);
        nPos++;
        // 最后年份
        uYear = stoul(strDate.substr(nPos));
    }
}

// 踩坑点  string要用push_back，下标会报异常，
// 还有find函数需要用std:;string::npos来判断是否找到，小于0的话其实是无法判断找没找到的