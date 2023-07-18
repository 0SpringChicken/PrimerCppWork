#include "Date_Deal.h"

const std::vector<std::string> Date_Deal::vecMon{"Jan","Feb","Mar", "Apr", "May", "June", "July", "Aug", "Sept", "Oct", "Nov", "Dec"};
Date_Deal::Date_Deal(std::string strDate)
{
    std::string::size_type nPos = 0;
    // ����ͬ���ַ��� 1.month day,year 2.mon/day/year 3.mon day year
    if (strDate.find(',') != std::string::npos) // ��Ӧ���1
    {
        // �����·�
        for (; strDate.find(vecMon[nPos]) < 0 && nPos<12;)
        {
            nPos++;
        }
        // ����ѭ�� �ҵ��˵�ǰ���·� ������ҪnPos�ټ�һ
        uMonth = ++nPos;
        // ����������
        nPos = strDate.find_first_of(' ');
        ++nPos;
        std::string strDay;
        for (int i = 0; strDate[nPos] != ','; ++nPos,++i)
        {
            strDay[i] = strDate[nPos];
        }
        uDay = stoul(strDay);
        // ��������
        nPos = strDate.find_first_of(',');
        ++nPos;
        std::string strYear;
        strYear.reserve(16);
        for (int i = 0; strDate[nPos] != '\0'&& nPos < strDate.size(); ++nPos, ++i)
        {
            //strYear[i] = strDate[nPos];  ���ַ�ʽ���׳��쳣 out_of_range
            strYear.push_back(strDate[nPos]);
        }
        uYear = stoul(strYear);
    }
    else if (strDate.find('/') != std::string::npos) // ��Ӧ���2
    {
        // �����·�
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
        // ��������
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
        // ������
        uYear = stoul(strDate.substr(nPos));
    }
    else // ��Ӧ���3
    {
        // �����·�
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
        // ��������
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
        // ������
        uYear = stoul(strDate.substr(nPos));
    }
}

// �ȿӵ�  stringҪ��push_back���±�ᱨ�쳣��
// ����find������Ҫ��std:;string::npos���ж��Ƿ��ҵ���С��0�Ļ���ʵ���޷��ж���û�ҵ���