// Test_Chapter_9.cpp : This file contains the 'main' function. Program execution begins and ends there.
// �ھ��� ˳������

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <deque>
#include <array>
#include <sstream>
#include <algorithm>
#include <forward_list>
#include <stdexcept>
#include <stack>
#include "Date_Deal.h"

template <class T>
T Find_number(T beg, T end, int val)
{
    while (beg != end)
    {
        if (*beg == val) return beg;
        ++beg;
    }
    return end;
}

struct Person {
    std::string Name;
    std::vector<std::string> phone;
};

void pluralize(size_t cnt, std::string& word)
{
    if (cnt > 1)
        word.push_back('s');
}

void test_and_insert(std::forward_list<std::string> &strfl, std::string &str_1, std::string &str_2)
{
    auto iter = strfl.begin(), iter_bf = strfl.before_begin();
    while (iter != strfl.end())
    {
        if( *iter == str_1 ) break;
        ++iter;
        ++iter_bf;
    }
    if (iter == strfl.end())
    {
        strfl.insert_after(iter_bf, str_2);
    }
    else
    {
        strfl.insert_after(iter, str_2);
    }
}

// 9.43
void replace_string(std::string& s, const std::string& oldVal, const std::string& newVal)
{
    auto l = oldVal.size();
    if (!l) 
        return;
    auto iter = s.begin();
    while (iter <= s.end() - 1)
    {
        auto iter1 = iter;
        auto iter2 = oldVal.begin();
        while (*iter1 == *iter2 && iter2 != oldVal.end())
        {
            ++iter1;
            ++iter2;
        }
        if (iter2 == oldVal.end())          // ��ȫƥ��
        {
            iter = s.erase(iter, iter1);    // ɾ����ƥ����ַ��������ڲ����µ��ַ���
            if (newVal.size())              // �滻�Ӵ��Ƿ�Ϊ��
            {
                iter2 = newVal.end();       // �ɺ���ǰ���β����ַ�
                do {
                    iter2--;
                    iter = s.insert(iter, *iter2);
                } while (iter2 > newVal.begin());
            }
            iter += newVal.size();          // iter��λ��ָ������ַ���֮��ĵ�һ���ַ�
        }
        else iter++;
    }
}

// 9.44
void replace_string_editin2(std::string& s, const std::string& oldVal, const std::string& newVal)
{
    auto len = oldVal.size();
    if (!len) return;

    auto iter = s.begin();auto iter2 = oldVal.begin();
    int n = 0;
    while (iter != s.end())
    {
        auto iter1 = iter;
        auto iter2 = oldVal.begin();
        while (iter2 != oldVal.end() && *iter1 == *iter2)
        {
            iter1++;
            iter2++;
        }
        if (iter2 == oldVal.end())
        {
            if (newVal.size())
            {
                s.replace(n, oldVal.size(),newVal);
                iter += newVal.size();
            }
        }
        else { iter++; n++; }
    }
}
// 9.51
std::ostream& operator<<(std::ostream& os, const Date_Deal& claDate)
{
    os << claDate.uYear << "--"
        << claDate.uMonth << "--"
        << claDate.uDay << "--"
        << std::endl;
    return os;
}

int main()
{
    // �ڰ���ʾ������ cin��ȡperson����
    std::string line, word;
    std::vector<Person> people;
    // ���ж�ȡ����
    // �����ǵ�ĳЩ�����Ƕ������ı����д���������һЩ�����Ǵ������ڵĵ�������ʱ
    // ͨ������ʹ��istringstream��
    while (getline(std::cin, line))
    {
        Person info;
        std::istringstream record(line);
        record >> info.Name;
        while (record >> word)
            info.phone.push_back(word);
        people.push_back(info);
    }
    
    // ����
    // ����������ӻ��������ɾ��Ԫ�صĴ���  ��˳�����������Ԫ�صĴ���
    // ���ࣺvector �ɱ��С���� deque ˫�˶��� list ˫������ 
    // forward_list �������� array �̶������С string ��vector����
    // ����vector��string�������洢 list��forward_list�ǲ�֧��������ʵģ��ڴ濪����
    // 
    // �����������1.ĳЩ����ʱ�����������Ͷ��ṩ�� 2.����һЩ���������˳��������������������������
    // 3.����һЩ����ֻ������һС��������
    // difference_type �������������ͣ��㹻��������������֮��ľ���
    // value_type Ԫ������
    // reference Ԫ�ص���ֵ���� ��value_type&������ͬ
    // const reference
    // size() max_size() empty()
    // insert(args) ��args�е�Ԫ�ؿ��������øú����Ķ��� emplace(inits) ʹ��inits���� 
    // erase(args) ɾ��argsָ����Ԫ��
    //
    std::list<std::deque<int>> ndeque_list;
    // forward_list��������֧�ֵݼ�--����
    std::vector<int> vec{ 1,2,3,4,5,11 };
    if (Find_number(vec.begin(), vec.end(), 5) != vec.end())
    {
        std::cout << "Find the goat" << std::endl;
    }
    else
    {
        std::cout << "No Results" << std::endl;
    }
    // list�ĵ�������֧��<���� ԭ����list���������� �޷��Ƚ�ָ��Ĵ�С
    std::cout << typeid(std::vector<int>::value_type).name() << std::endl;
    // array ��׼��array����й̶��Ĵ�С
    std::array<int, 42> arr;//������42��intԪ�ص�array
/*    arr[0] = 10;*/
    // list<int> ��ʼ��һ��vector<double>
//     std::list<int> ilist{ 1,2,3,4 };
//     std::vector<double> dVec(ilist.begin(), ilist.end());

    // ��ֵ��swap
    // array��ֵʱ���������ͬ������ ��array<type,num> ����type��num��ֵ��Ҫ��ͬ������ʹ�ø�ֵ=�����
    // swap(c1,c2)��c1.swap(c2)��˼��ͬ�����ǽ���c1��c2�е����ݣ�swap�ٶȿ죬�ȴ�c2��c1����Ԫ�ؿ�Ķ�

    // ����������array������assign����
    // seq.assign(b,e)��seq�е�Ԫ���滻Ϊ������b��e����ʾ��Χ�е�Ԫ�أ�b��e����ָ��seq�е�Ԫ��
    // seq.assign(il) ��seq�е�Ԫ���滻Ϊ��ʼ���б�il�е�Ԫ��
    // seq.assign(n,t)��seq�е�Ԫ���滻Ϊn��ֵΪt��Ԫ��

    // �ص㣺��ֵ����ᵼ��ָ����������ڲ��ĵ����������ú�ָ��ʧЧ����swap�����򲻻ᣨarray��string���⣩
//     std::list<std::string> liStrNames;
//     std::vector<char*> oldStyle;
    // liStrNames = oldStyle; ���Ͳ�ƥ���Ǵ����
/*    liStrNames.assign(oldStyle.cbegin(), oldStyle.cend());*/// assign֧�����ݵ����͸�ֵ

    // swapԭ��Ԫ�ر���δ������ֻ�ǽ����������������ڲ����ݽṹ  ʱ�临�Ӷȣ�������
    // ���Ƕ�arrayʹ��swap�������ĵ�������array֮���Ԫ��
//     std::vector<std::string> VecStr;
//     VecStr.assign(oldStyle.cbegin(), oldStyle.cend());

    // ������С����
    //std::vector<int>::size_type stype = VecStr.max_size();
    //std::cout << std::hex << stype << std::endl;

    // ˳����������
    // ��˳������ ��Ӳ���
    // ��array�⣬���б�׼�ⶼ�ṩ�����ڴ��������ʱ���Զ�̬����ӻ�ɾ��Ԫ�����ı������Ĵ�С
    // forward_list���Լ��汾��insert��emplace�����Ҳ�֧��push_back�Լ�emplace_back
    // vector��string��֧��push_front��emplace_front
    // c.push_back(t) c.emplace_back(args) c��β�����ֵΪt��Ԫ�أ�������args������Ԫ��
    // c.push_front(t) c.emplace_front(args) ͬ�ϣ�ֻ�����˲������ͷ��
    // c.insert(p,t) c.emplace(p,args) �ڵ�����pָ���Ԫ��֮ǰ����һ��ֵΪt������args����Ԫ�أ�����ָ��
    // ��Ԫ�صĵ�����
    // c.insert(p,n,t) ������p֮ǰ����n��ֵΪt��Ԫ�أ�����ָ���¼ӵĵ�һ��Ԫ�صĵ�������nΪ0�򷵻�p
    // c.insert(p,b,e) ������b��eָ���ķ�Χ�ڵ�Ԫ�ز��뵽������pָ���Ԫ��֮ǰ��b��e����ָ��c�е�Ԫ��
    // ����ָ������ӵĵ�һ��Ԫ�صĵ�����������ΧΪ�գ��򷵻�p
    // c.insert(p,il) il��һ��������{}��Χ��Ԫ��ֵ�б�����Щ����ֵ���뵽������p֮ǰ������ָ�������
    // �ĵ�һ��Ԫ�صĵ��������б�Ϊ�գ��򷵻�p
    // 
    // ��һ��string��vector��deque����Ԫ�ػ�ʹ����ָ�������ĵ����������ú�ָ��ʧЧ
    //

    // �ص㣺��������һ����������ʼ��һ���������߽�һ��������뵽������ʱ��ʵ���Ϸ����������Ƕ���Ŀ���
    // �����е�Ԫ�����ṩ��ֵû���κεĹ���������������Ԫ�ص��κθı䶼����Ӱ�쵽ԭʼ���󣬷�֮��Ȼ 
    // 

    // list,forward_list,deque֧��push_frontͷ������
    
    // ʹ��insert�ķ���ֵ  
    // ������ͷ������ֵ
    //std::vector<int> nVec; int nValue;
    //auto iter = nVec.begin();
    //while (std::cin >> nValue)
    //    iter = nVec.insert(iter, nValue);
    // �±�׼������������Ա emplace emplace_front emplace_back
    // �ڵ���push����insert��Ա����ʱ ���ǽ�Ԫ�����͵Ķ��󴫵ݸ����� ��Щ���󱻿�����������
    // ������emplace��Ա����ʱ�����ǽ��������ݸ�Ԫ�����͵Ĺ��캯�� 
    // emplace��Աʹ����Щ����������������ڴ�ռ���ֱ�ӹ���Ԫ�أ������Դ������б�

    // ����Ԫ��
    // at���±� �������� string��vector��deque��array
    // back��������forward_list
    // back()����βԪ�ص����� front()��Ԫ�ص����� [n]�����±�Ϊn��Ԫ�ص����ã�n>c.size()������Ϊδ����
    // c.at(n)�����±�Ϊn��Ԫ�ص����� ��Խ�磬���׳�out_of_range�쳣
    // 

    // ɾ��Ԫ��
    // pop_back() ɾ��βԪ��  pop_front()ɾ����Ԫ��  ������void
    // erase(p) ɾ��������p����Ԫ�أ�����һ����ɾ��Ԫ��֮��ĵ���������pΪβԪ���򷵻�β�����������p��β���������������Ϊδ����
    // erase(b,e)ɾ��b��e��ָ����Χ�ڵ�Ԫ�أ�����һ��e֮��ĵ���������eΪβ���������ԭ������
    // clear()ɾ������Ԫ�� ����void
    // 
    // deque�г���β֮����κ�Ԫ��ɾ������ʹ���еĵ����������ú�ָ��ʧЧ
    // vector��stringɾ����֮��λ�õĵ����������ú�ָ�붼��ʧЧ
    // 
    // ����ɾ��Ԫ�صĳ�Ա��������������������ɾ��Ԫ��֮ǰ������Ա����ȷ�������Ǵ��ڵ�
    // ͬvector��string�಻֧��push_frontһ��������������Ҳ��֧��pop_front����������forward_listҲ��֧��pop_back����

    std::list<int> nlist = { 1,2,3,4,5,6,7,8,9,10 };
    auto it = nlist.begin();
    while (it != nlist.end())
    {
        if (*it % 2)
        {
            it++;
        }
        else // ɾ��ż��
        {
            it = nlist.erase(it);
        }
    }
    // lambda���ʽ�ع� for_each()
    std::for_each(nlist.begin(), nlist.end(), [&](int ele) {std::cout << ele << std::endl; });

    // ɾ����Χ��Ԫ��
    std::list<int> nlist_2 = { 1,2,3,4,5,6,7,8,9,10 };
    auto it1 = nlist_2.begin(); auto it2 = nlist_2.begin();
    it2++; it2++; it2++; it2++; it2++;
    std::cout << *it2 << std::endl;
    nlist_2.erase(it1, it2);
    std::cout << *nlist_2.begin() << std::endl;
    // erase(b,e)ɾ������[b,e)�����ڵ�Ԫ��
    // it1 = nlist_2.erase(it1, it2); ִ����Ϻ�� it1 == it2

    // �����forward_list���� ����汾����Ӻ�ɾ������  ����������
    // ��ӻ�ɾ��Ԫ��ʱ��ɾ�������Ԫ��֮ǰ���Ǹ�Ԫ�صĺ�̻ᷢ���ı� 
    // forward_list��δ����insert erase emplace���� ���Ƕ����� insert_after emplace_after erase_after����
    // ��Ҳ������before_begin() ��ǰԪ�صĵ�����
    // lst.insert_after(p,t) ��p�����t������ָ�����һ������Ԫ�صĵ�������pΪβ��������Ļ�����Ϊδ����
    // lst.insert_after(p,n,t) lst.insert_after(p,b,e) lst.insert_after(p,il)
    // emplace_after(p, args)
    // erase_after(p), erase_after(b,e)����e����p֮���ָ��
    //
//     9.27
    std::forward_list<int> nflist{ 1,2,3,4,5,6,7,8,9,10 };
    auto iter_bf = nflist.before_begin(), iter_b = nflist.begin();
    while (iter_b != nflist.end())
    {
        if (*iter_b % 2 == 0)
        {
            iter_bf = iter_b;
            ++iter_b;
        }
        else
        {
            iter_b = nflist.erase_after(iter_bf);
        }
    }
    std::for_each(nflist.begin(), nflist.end(), [&](int ele) {std::cout << ele << std::endl; });
    // 9.28
    std::forward_list<std::string> strfl{ "hello", "world", "man", "woman", "love"};
    std::for_each(strfl.begin(), strfl.end(), [&](std::string ele) {std::cout << ele << " "; });
    std::cout << std::endl;
    std::string str1 = "love", str2 = "and", str3 = "peace";
    test_and_insert(strfl, str2, str3);
    test_and_insert(strfl, str1, str2);
    std::for_each(strfl.begin(), strfl.end(), [&](std::string ele) {std::cout << ele << " "; });

    // �ı�������С resize->size reverse->capacity
    // array��֧��resize ��ǰ��С����resize��С���������󲿵�Ԫ�ػᱻɾ������ǰ��СС��resize��С���Ὣ��Ԫ����ӵ�������
    // ���resize��С��������ָ��ɾ��Ԫ�صĵ�������ָ�룬���ö���ʧЧ����vector string deque����resize���ܵ��µ�������ָ�롢����ʧЧ
    //

    // ������������ʹ������ʧЧ  ��Ϊ���Ԫ�غ�ɾ��Ԫ��������� ���ȿ����Ԫ�أ�
    // 1.vector string ���洢�ռ䱻���·��� ��ʧЧ ���û�����·��䣬�����Ԫ��֮ǰ��û��ʧЧ��֮���ʧЧ
    // 2.deque ������β֮����κ�λ�ö��ᵼ��ʧЧ����λλ�����Ԫ�أ����ᵼ�µ�����ʧЧ
    // 3.list��forward_list ��Ȼ��Ч
    // ɾ��Ԫ�أ�
    // 1.list forward_list��Ȼ��Ч
    // 2.deque ��β֮����κ�λ��ɾ������ʧЧ��ɾ��deque��βԪ�أ���β�������Ҳ��ʧЧ��������ʧЧ��ɾ����Ԫ�أ���������Ӱ��
    // 3.vector string ֮ǰ��Ԫ�ز���Ӱ��
    // ע�⣺ɾ��Ԫ��ʱ��β����������ǻ�ʧЧ
    // list��forward_list������������������ͬ���ǣ����������֧�ּӼ����㣬��Ҫ��++��ʵ��ͬ���Ĺ��ܣ�����ԭ����
    // �������ڴ��еĿռ䲻�������ģ��޷�ͨ����ַ�Ӽ���Ԫ�ؼ��ƶ�
    // 9.31
    std::list<int> nlist11{ 1,2,3,4,5,6,7,8,9,10 };
    std::forward_list<int> nflist11{ 1,2,3,4,5,6,7,8,9,10 };
    auto iter_lis = nlist11.begin();
    auto iter_flis = nflist11.begin(), iter_flibs = nflist11.before_begin();
    while (iter_lis != nlist11.end())
    {
        if (*iter_lis % 2)
        {
            iter_lis = nlist11.insert(iter_lis, *iter_lis);
            iter_lis++;
            iter_lis++;
        }
        else
        {
            iter_lis = nlist11.erase(iter_lis);
        }
    }
    while (iter_flis != nflist11.end())
    {
        if (*iter_flis % 2)
        {
            iter_flis = nflist11.insert_after(iter_flis, *iter_flis);
            iter_flibs = iter_flis;
            iter_flis++;
        }
        {
            iter_flis = nflist11.erase_after(iter_flibs);
        }
    }
    std::for_each(nlist11.begin(), nlist11.end(), [&](int x) {std::cout << x << " "; });
    std::cout << std::endl;
    std::for_each(nflist11.begin(), nflist11.end(), [&](int x) {std::cout << x << " "; });

    // vector����ʱ���������
    // capacity �����������ڴ�ռ������¿������ɶ��ٸ�Ԫ��
    // reserve֪ͨ������Ӧ��׼��������ٸ�Ԫ��
    // shrink_to_fit ֻ������vector string deque
    // c.shrink_to_fit() capacity()���ٵ�size()��ͬ��С
    // c.capacity()
    // c.reserve(n) ��������������n��Ԫ�ص��ڴ�ռ� ��������СС�ڵ�ǰ���� ��ʲôҲ����
    // 
    // size��ʾ����Ŀǰ������Ԫ������ capacity��ʾ�����ڲ�����
    //
    std::vector<int> ivec(24, 40);
    std::cout << ivec.size() << std::endl;
    std::cout << ivec.capacity() << std::endl;
    ivec.reserve(64);
    std::cout << ivec.capacity() << std::endl;

    std::vector<int> ivecs;
    for (std::vector<int>::size_type x = 0; x < 32; ++x)
        ivecs.push_back(x);
    // �����󿴴�С
    std::cout << ivecs.size() << std::endl;
    std::cout << ivecs.capacity() << std::endl;
    std::cout << "-------------" << std::endl;
    while (ivecs.size() != ivecs.capacity())
        ivecs.push_back(1000);
    // ��ǰcapaci() == size()
    std::cout << ivecs.size() << std::endl;
    std::cout << ivecs.capacity() << std::endl;
    std::cout << "��ǰvector��ַ��" << std::hex << &ivecs << std::endl;
    std::cout << "-------------" << std::endl;
    // �ٴ�push_back��۲�size() capacity()�Ĵ�С
    ivecs.push_back(1000);
    std::cout << std::dec << ivecs.size() << std::endl;
    std::cout << ivecs.capacity() << std::endl;
    std::cout << "��ǰvector��ַ��" << std::hex << &ivecs << std::endl;
    std::cout << "-------------" << std::endl;
    // ִ��shrink_to_fit
    ivecs.shrink_to_fit();
    std::cout << std::dec << ivecs.size() << std::endl;
    std::cout << ivecs.capacity() << std::endl;
    std::cout << "��ǰvector��ַ��" << std::hex << &ivecs << std::endl;
    std::cout << "-------------" << std::endl;
    // ִ��reserve
    ivecs.reserve(10000);
    std::cout << std::dec << ivecs.size() << std::endl;
    std::cout << ivecs.capacity() << std::endl;
    std::cout << "��ǰvector��ַ��" << std::hex << &ivecs << std::endl;
    std::cout << "-------------" << std::endl;
    // ִ��resize
    ivecs.resize(10000);
    std::cout << std::dec << ivecs.size() << std::endl;
    std::cout << ivecs.capacity() << std::endl;
    std::cout << "��ǰvector��ַ��" << std::hex << &ivecs << std::endl;
    std::cout << "-------------" << std::endl;

    // �����string����
    // ���˹��캯�� �� �Ѿ����ܹ��ļ��ַ��� ������������
    // string s(cp,n) cpָ���������ǰn���ַ��Ŀ��������ٰ���n���ַ�
    // string s(s2,pos2) s��s2���±�pos2��ʼ���ַ��Ŀ��� ��pos2>s2.size()����Ϊδ����
    // string s(s2,pos2,len2) s��s2���±�s2��ʼlen2���ַ��Ŀ���������len2ֵ���٣�s֮�࿽��s2.size()-pos���ַ�
    // 
    const char* cp = "Hello World!!!";
    char sz[] = { 'C', 'H'};
    std::string s1(cp);
    std::string s2(cp, 6);
    try
    {
        std::string s3(sz); // sz������\0��β���ᷢ��δ�������Ϊ
        std::cout << s3 << std::endl;
        std::string s4(s1, 16); // �׳�out_of_range�쳣
    }
    catch (std::out_of_range)
    {
        std::cout << "out_of_range" << std::endl;
    }
    // substr���� 
    // ����һ��string ��ԭʼstring��һ���ֻ���ȫ���Ŀ��� ���Ը�substr����һ����ѡ�Ŀ�ʼλ�õļ���ֵ
    // s.substr(pos,n) ��pos��ʼ�Ժ��n���ַ��Ŀ��� nĬ��Ϊs.size()-pos ��ȡ�ַ���
    // 9.41
    std::vector<char> cvec{ 'a','b','c','d','e','f' };
    //std::string s(cvec.begin(), cvec.end()); ������ĳ�ʼ����ʽ
    std::string s(cvec.data(), cvec.size()); 
    // data() �� C++ �е� STL��������һ��ָ���ڴ������ֱ��ָ�룬���ڴ������������ڲ����ڴ洢��ӵ�е�Ԫ�ء�
    std::cout << s << std::endl;
    // �ı�string����������
    // �����insert��erase�汾 �����±�İ汾  ���µ�s.size() = 6,����s[6]ǰ���룬��\0ǰ����
    s.insert(s.size(), 5, '!');//��sĩβ����5����̾��
    std::cout << s << std::endl;
    s.erase(s.size() - 5, 5); //��sɾ�����5���ַ�
    std::cout << s << std::endl;
    // ��׼��string���ͻ��ṩ�˽���C����ַ������insert��assign�汾
    const char* cp1 = "Stately,plump Buck";
    s.assign(cp1, 7); // s =="Stately"
    std::cout << s << std::endl;
    s.insert(s.size(), cp1 + 7);// s =="Stately,plump Buck"
    std::cout << s << std::endl;
    // append(ĩβ����)��replace����(�滻)
    // string����������
    // string���ṩ��6����ͬ���������� ÿ����������4�����ذ汾 ÿ��������һ��size_typeֵ����ʾƥ����±�
    // �������ʧ�� ����һ����Ϊstring::npos��ststic��Ա -1 
    // ��������ʱ��Сд���е�
    // s.find(args)
    // s.rfind(args)
    // s.find_first_of(args) �κ�һ���ַ�
    // s.find_last_of(args)  �κ�һ���ַ�
    // s.find_first_not_of(args)
    // s.find_last_not_of(args)
    // args����ʽ�������£�
    // c,pos s��λ��pos��ʼ�����ַ�c posĬ��0
    // s2,pos s��λ��pos��ʼ�����ַ���s2 posĬ��0
    // cp,pos cpΪC����ַ���
    // cp,pos,n s��posλ�ÿ�ʼ����ָ��cpָ��������ǰn���ַ���pos��nû��Ĭ��ֵ
    // 

    std::string numbers("0123456789"), name("r2d2");
    std::string::size_type pos = 0;
    // Ѱ�����ַ������ֵ�����λ��
    // name.find_first_of(numbers, pos) ÿ�ҵ�һ���Ӵ��͸���pos��λ��
    while ((pos = name.find_first_of(numbers, pos)) != std::string::npos)
    {
        std::cout << "found number at index: " << pos
            << " element is " << name[pos] << std::endl;
        ++pos;
    }
    // 9.47
    std::string strEg("ab2c3d7R4E6");
    pos = 0;
    while ((pos = strEg.find_first_of(numbers, pos)) != std::string::npos)
    {
        std::cout << "found number at index: " << pos
            << " element is " << strEg[pos] << std::endl;
        ++pos;
    }
    // find_first_not_of���ǲ����ų��� ��һ���ַ����������еĴ�СдӢ����ĸ
    // compare����  compare��6���汾
    // ��ֵת�� to_string(��������)  
//     std::string s22 = "pi = 3.14";
//     double d = stod(s22.substr(s22.find_first_of("+-0.123456789")));
//     std::cout << d << std::endl;
    // stoi(s, p, b) �Դ�Ϊ�� s��ʼ�Ӵ�����ֵ b��ʾת������ p��size_tָ�루����s�е�һ������ֵ�ַ����±꣬Ĭ��0���������������±꣩
    // stof(s, p)

    // ����������
    // ����˳�������⣬��׼�⻹����������˳��������������stack��queue��
    // priority_queue��������(adaptor)�Ǳ�׼���е�һ��ͨ�ø��
    // stack����������һ��˳������(��array��forward_list��),��ʹ�����������һ��stackһ����
    // Ĭ������£�stack��queue�ǻ���dequeʵ�ֵģ�priority queue����vector֮��ʵ�ֵġ�
    // ���ǿ����ڴ���һ��������ʱ��һ��������˳��������Ϊ�ڶ������Ͳ�����������Ĭ���������͡�
//     std::vector<std::string> svec;
//     //��vector��ʵ�ֵĿ�ջ
//     std::stack<std::string, std::vector<std::string>> str_stk;
//     // str_stk2��vector��ʵ�֣���ʼ��ʱ����svec�Ŀ���
//     std::stack<std::string, std::vector<std::string>> str_stk2(svec);
    
    std::string str11{ "Jan 1,1990" }, str22{ "Feb/2/1990" }, str33{"Apri 17 2023"};
    Date_Deal date1(str11),date2(str22),date3(str33);
    std::cout << date1;
    std::cout << date2;
    std::cout << date3;
}

