// Test_Chapter_9.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 第九章 顺序容器

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
        if (iter2 == oldVal.end())          // 完全匹配
        {
            iter = s.erase(iter, iter1);    // 删除相匹配的字符串，用于插入新的字符串
            if (newVal.size())              // 替换子串是否为空
            {
                iter2 = newVal.end();       // 由后向前依次插入字符
                do {
                    iter2--;
                    iter = s.insert(iter, *iter2);
                } while (iter2 > newVal.begin());
            }
            iter += newVal.size();          // iter归位，指向插入字符串之后的第一个字符
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
    // 第八章示例代码 cin获取person数据
    std::string line, word;
    std::vector<Person> people;
    // 逐行读取数据
    // 当我们的某些工作是对整行文本进行处理，而其他一些工作是处理行内的单个单词时
    // 通常可以使用istringstream。
    while (getline(std::cin, line))
    {
        Person info;
        std::istringstream record(line);
        record >> info.Name;
        while (record >> word)
            info.phone.push_back(word);
        people.push_back(info);
    }
    
    // 概述
    // 向容器中添加或从容器中删除元素的代价  非顺序访问容器中元素的代价
    // 分类：vector 可变大小数组 deque 双端队列 list 双向链表 
    // forward_list 单向链表 array 固定数组大小 string 与vector类似
    // 其中vector和string是连续存储 list和forward_list是不支持随机访问的，内存开销大
    // 
    // 容器库概览：1.某些操作时所有容器类型都提供的 2.另外一些操作仅针对顺序容器、关联容器或无需容器
    // 3.还有一些操作只适用于一小部分容器
    // difference_type 带符号整数类型，足够保存两个迭代器之间的距离
    // value_type 元素类型
    // reference 元素的左值类型 与value_type&含义相同
    // const reference
    // size() max_size() empty()
    // insert(args) 将args中的元素拷贝进调用该函数的对象 emplace(inits) 使用inits构造 
    // erase(args) 删除args指定的元素
    //
    std::list<std::deque<int>> ndeque_list;
    // forward_list迭代器不支持递减--操作
    std::vector<int> vec{ 1,2,3,4,5,11 };
    if (Find_number(vec.begin(), vec.end(), 5) != vec.end())
    {
        std::cout << "Find the goat" << std::endl;
    }
    else
    {
        std::cout << "No Results" << std::endl;
    }
    // list的迭代器不支持<操作 原因是list不是连续的 无法比较指针的大小
    std::cout << typeid(std::vector<int>::value_type).name() << std::endl;
    // array 标准的array类具有固定的大小
    std::array<int, 42> arr;//包含有42个int元素的array
/*    arr[0] = 10;*/
    // list<int> 初始化一个vector<double>
//     std::list<int> ilist{ 1,2,3,4 };
//     std::vector<double> dVec(ilist.begin(), ilist.end());

    // 赋值和swap
    // array赋值时必须具有相同的内容 即array<type,num> 其中type与num的值都要相同，才能使用赋值=运算符
    // swap(c1,c2)与c1.swap(c2)意思相同，都是交换c1和c2中的内容，swap速度快，比从c2向c1拷贝元素快的多

    // 关联容器和array不适用assign操作
    // seq.assign(b,e)将seq中的元素替换为迭代器b和e所表示范围中的元素，b和e不能指向seq中的元素
    // seq.assign(il) 将seq中的元素替换为初始化列表il中的元素
    // seq.assign(n,t)将seq中的元素替换为n个值为t的元素

    // 重点：赋值运算会导致指向左边容器内部的迭代器、引用和指针失效。而swap操作则不会（array和string除外）
//     std::list<std::string> liStrNames;
//     std::vector<char*> oldStyle;
    // liStrNames = oldStyle; 类型不匹配是错误的
/*    liStrNames.assign(oldStyle.cbegin(), oldStyle.cend());*/// assign支持相容的类型赋值

    // swap原理：元素本身并未交换，只是交换了两个容器的内部数据结构  时间复杂度：常数级
    // 但是对array使用swap会真正的调换两个array之间的元素
//     std::vector<std::string> VecStr;
//     VecStr.assign(oldStyle.cbegin(), oldStyle.cend());

    // 容器大小操作
    //std::vector<int>::size_type stype = VecStr.max_size();
    //std::cout << std::hex << stype << std::endl;

    // 顺序容器操作
    // 向顺序容器 添加操作
    // 除array外，所有标准库都提供灵活的内存管理，运行时可以动态的添加或删除元素来改变容器的大小
    // forward_list有自己版本的insert和emplace，并且不支持push_back以及emplace_back
    // vector和string不支持push_front和emplace_front
    // c.push_back(t) c.emplace_back(args) c的尾部添加值为t的元素，或者由args创建的元素
    // c.push_front(t) c.emplace_front(args) 同上，只不过此操作针对头部
    // c.insert(p,t) c.emplace(p,args) 在迭代器p指向的元素之前创建一个值为t或者由args创建元素，返回指向
    // 新元素的迭代器
    // c.insert(p,n,t) 迭代器p之前插入n个值为t的元素，返回指向新加的第一个元素的迭代器，n为0则返回p
    // c.insert(p,b,e) 迭代器b和e指定的范围内的元素插入到迭代器p指向的元素之前，b和e不能指向c中的元素
    // 返回指向新添加的第一个元素的迭代器；若范围为空，则返回p
    // c.insert(p,il) il是一个花括号{}包围的元素值列表，将这些给定值插入到迭代器p之前。返回指向新添加
    // 的第一个元素的迭代器；列表为空，则返回p
    // 
    // 向一个string，vector，deque插入元素会使所有指向容器的迭代器、引用和指针失效
    //

    // 重点：当我们用一个对象来初始化一个容器或者将一个对象插入到容器中时，实际上放入容器的是对象的拷贝
    // 容器中的元素与提供的值没有任何的关联，随后对容器重元素的任何改变都不会影响到原始对象，反之亦然 
    // 

    // list,forward_list,deque支持push_front头部插入
    
    // 使用insert的返回值  
    // 持续在头部插入值
    //std::vector<int> nVec; int nValue;
    //auto iter = nVec.begin();
    //while (std::cin >> nValue)
    //    iter = nVec.insert(iter, nValue);
    // 新标准引入了三个成员 emplace emplace_front emplace_back
    // 在调用push或者insert成员函数时 我们将元素类型的对象传递给他们 这些对象被拷贝到容器中
    // 当调用emplace成员函数时，则是将参数传递给元素类型的构造函数 
    // emplace成员使用这些参数在容器管理的内存空间中直接构造元素（即可以传参数列表）

    // 访问元素
    // at和下标 仅适用于 string，vector，deque，array
    // back不适用于forward_list
    // back()返回尾元素的引用 front()首元素的引用 [n]返回下标为n的元素的引用，n>c.size()则函数行为未定义
    // c.at(n)返回下标为n的元素的引用 若越界，则抛出out_of_range异常
    // 

    // 删除元素
    // pop_back() 删除尾元素  pop_front()删除首元素  都返回void
    // erase(p) 删除迭代器p处的元素，返回一个被删除元素之后的迭代器，若p为尾元素则返回尾后迭代器，若p是尾后迭代器，则函数行为未定义
    // erase(b,e)删除b和e所指定范围内的元素，返回一个e之后的迭代器，若e为尾后迭代器则原样返回
    // clear()删除所有元素 返回void
    // 
    // deque中除首尾之外的任何元素删除都会使所有的迭代器、引用和指针失效
    // vector和string删除点之后位置的迭代器、引用和指针都会失效
    // 
    // 由于删除元素的成员函数并不检查其参数，再删除元素之前，程序员必须确保它们是存在的
    // 同vector与string类不支持push_front一样，这两个容器也不支持pop_front操作，类似forward_list也不支持pop_back操作

    std::list<int> nlist = { 1,2,3,4,5,6,7,8,9,10 };
    auto it = nlist.begin();
    while (it != nlist.end())
    {
        if (*it % 2)
        {
            it++;
        }
        else // 删除偶数
        {
            it = nlist.erase(it);
        }
    }
    // lambda表达式回顾 for_each()
    std::for_each(nlist.begin(), nlist.end(), [&](int ele) {std::cout << ele << std::endl; });

    // 删除范围内元素
    std::list<int> nlist_2 = { 1,2,3,4,5,6,7,8,9,10 };
    auto it1 = nlist_2.begin(); auto it2 = nlist_2.begin();
    it2++; it2++; it2++; it2++; it2++;
    std::cout << *it2 << std::endl;
    nlist_2.erase(it1, it2);
    std::cout << *nlist_2.begin() << std::endl;
    // erase(b,e)删除的是[b,e)区间内的元素
    // it1 = nlist_2.erase(it1, it2); 执行完毕后得 it1 == it2

    // 特殊的forward_list操作 特殊版本的添加和删除操作  （单向链表）
    // 添加或删除元素时，删除或添加元素之前的那个元素的后继会发生改变 
    // forward_list并未定义insert erase emplace操作 而是定义了 insert_after emplace_after erase_after操作
    // 其也定义了before_begin() 首前元素的迭代器
    // lst.insert_after(p,t) 在p后插入t，返回指向最后一个插入元素的迭代器，p为尾后迭代器的话，行为未定义
    // lst.insert_after(p,n,t) lst.insert_after(p,b,e) lst.insert_after(p,il)
    // emplace_after(p, args)
    // erase_after(p), erase_after(b,e)返回e或者p之后的指针
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

    // 改变容器大小 resize->size reverse->capacity
    // array不支持resize 当前大小大于resize大小，则容器后部的元素会被删除，当前大小小于resize大小，会将新元素添加到容器后部
    // 如果resize缩小容器，则指向被删除元素的迭代器，指针，引用都会失效；对vector string deque进行resize可能导致迭代器、指针、引用失效
    //

    // 容器操作可能使迭代器失效  分为添加元素和删除元素两种情况 首先看添加元素：
    // 1.vector string 若存储空间被重新分配 则失效 如果没有重新分配，则添加元素之前的没有失效，之后的失效
    // 2.deque 插入首尾之外的任何位置都会导致失效，首位位置添加元素，仅会导致迭代器失效
    // 3.list和forward_list 仍然有效
    // 删除元素：
    // 1.list forward_list仍然有效
    // 2.deque 首尾之外的任何位置删除，则失效，删除deque的尾元素，则尾后迭代器也会失效，其他不失效，删除首元素，其他不受影响
    // 3.vector string 之前的元素不受影响
    // 注意：删除元素时，尾后迭代器总是会失效
    // list与forward_list与其他容器迭代器不同的是，其迭代器不支持加减运算，需要用++来实现同样的功能，具体原因是
    // 它们在内存中的空间不是连续的，无法通过地址加减在元素间移动
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

    // vector对象时如何增长的
    // capacity 容器不扩张内存空间的情况下可以容纳多少个元素
    // reserve通知容器它应该准备保存多少个元素
    // shrink_to_fit 只适用于vector string deque
    // c.shrink_to_fit() capacity()减少到size()相同大小
    // c.capacity()
    // c.reserve(n) 分配至少能容纳n个元素的内存空间 如果需求大小小于当前容量 则什么也不做
    // 
    // size表示容器目前包含的元素数量 capacity表示容器在不分配
    //
    std::vector<int> ivec(24, 40);
    std::cout << ivec.size() << std::endl;
    std::cout << ivec.capacity() << std::endl;
    ivec.reserve(64);
    std::cout << ivec.capacity() << std::endl;

    std::vector<int> ivecs;
    for (std::vector<int>::size_type x = 0; x < 32; ++x)
        ivecs.push_back(x);
    // 结束后看大小
    std::cout << ivecs.size() << std::endl;
    std::cout << ivecs.capacity() << std::endl;
    std::cout << "-------------" << std::endl;
    while (ivecs.size() != ivecs.capacity())
        ivecs.push_back(1000);
    // 当前capaci() == size()
    std::cout << ivecs.size() << std::endl;
    std::cout << ivecs.capacity() << std::endl;
    std::cout << "当前vector地址：" << std::hex << &ivecs << std::endl;
    std::cout << "-------------" << std::endl;
    // 再次push_back后观察size() capacity()的大小
    ivecs.push_back(1000);
    std::cout << std::dec << ivecs.size() << std::endl;
    std::cout << ivecs.capacity() << std::endl;
    std::cout << "当前vector地址：" << std::hex << &ivecs << std::endl;
    std::cout << "-------------" << std::endl;
    // 执行shrink_to_fit
    ivecs.shrink_to_fit();
    std::cout << std::dec << ivecs.size() << std::endl;
    std::cout << ivecs.capacity() << std::endl;
    std::cout << "当前vector地址：" << std::hex << &ivecs << std::endl;
    std::cout << "-------------" << std::endl;
    // 执行reserve
    ivecs.reserve(10000);
    std::cout << std::dec << ivecs.size() << std::endl;
    std::cout << ivecs.capacity() << std::endl;
    std::cout << "当前vector地址：" << std::hex << &ivecs << std::endl;
    std::cout << "-------------" << std::endl;
    // 执行resize
    ivecs.resize(10000);
    std::cout << std::dec << ivecs.size() << std::endl;
    std::cout << ivecs.capacity() << std::endl;
    std::cout << "当前vector地址：" << std::hex << &ivecs << std::endl;
    std::cout << "-------------" << std::endl;

    // 额外的string操作
    // 除了构造函数 和 已经介绍过的几种方法 还有如下三种
    // string s(cp,n) cp指向的数组中前n个字符的拷贝，至少包含n个字符
    // string s(s2,pos2) s是s2从下标pos2开始的字符的拷贝 若pos2>s2.size()则行为未定义
    // string s(s2,pos2,len2) s是s2从下标s2开始len2个字符的拷贝，不管len2值多少，s之多拷贝s2.size()-pos个字符
    // 
    const char* cp = "Hello World!!!";
    char sz[] = { 'C', 'H'};
    std::string s1(cp);
    std::string s2(cp, 6);
    try
    {
        std::string s3(sz); // sz不是以\0结尾，会发生未定义的行为
        std::cout << s3 << std::endl;
        std::string s4(s1, 16); // 抛出out_of_range异常
    }
    catch (std::out_of_range)
    {
        std::cout << "out_of_range" << std::endl;
    }
    // substr操作 
    // 返回一个string 是原始string的一部分或者全部的拷贝 可以给substr传递一个可选的开始位置的计数值
    // s.substr(pos,n) 从pos开始以后的n个字符的拷贝 n默认为s.size()-pos 截取字符串
    // 9.41
    std::vector<char> cvec{ 'a','b','c','d','e','f' };
    //std::string s(cvec.begin(), cvec.end()); 迭代其的初始化方式
    std::string s(cvec.data(), cvec.size()); 
    // data() 是 C++ 中的 STL，它返回一个指向内存数组的直接指针，该内存数组由向量内部用于存储其拥有的元素。
    std::cout << s << std::endl;
    // 改变string的其他方法
    // 额外的insert和erase版本 接受下标的版本  如下的s.size() = 6,即在s[6]前插入，在\0前插入
    s.insert(s.size(), 5, '!');//在s末尾插入5个感叹号
    std::cout << s << std::endl;
    s.erase(s.size() - 5, 5); //从s删除最后5个字符
    std::cout << s << std::endl;
    // 标准库string类型还提供了接受C风格字符数组的insert和assign版本
    const char* cp1 = "Stately,plump Buck";
    s.assign(cp1, 7); // s =="Stately"
    std::cout << s << std::endl;
    s.insert(s.size(), cp1 + 7);// s =="Stately,plump Buck"
    std::cout << s << std::endl;
    // append(末尾插入)和replace函数(替换)
    // string的搜索操作
    // string类提供了6个不同的搜索函数 每个函数都有4个重载版本 每个都返回一个size_type值，表示匹配的下标
    // 如果搜索失败 返回一个名为string::npos的ststic成员 -1 
    // 搜索操作时大小写敏感的
    // s.find(args)
    // s.rfind(args)
    // s.find_first_of(args) 任何一个字符
    // s.find_last_of(args)  任何一个字符
    // s.find_first_not_of(args)
    // s.find_last_not_of(args)
    // args的形式必须如下：
    // c,pos s中位置pos开始查找字符c pos默认0
    // s2,pos s中位置pos开始查找字符串s2 pos默认0
    // cp,pos cp为C风格字符串
    // cp,pos,n s中pos位置开始查找指针cp指向的数组的前n个字符。pos和n没有默认值
    // 

    std::string numbers("0123456789"), name("r2d2");
    std::string::size_type pos = 0;
    // 寻找子字符串出现的所有位置
    // name.find_first_of(numbers, pos) 每找到一次子串就更新pos的位置
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
    // find_first_not_of则是采用排除法 令一个字符串包含所有的大小写英文字母
    // compare函数  compare有6个版本
    // 数值转换 to_string(数字类型)  
//     std::string s22 = "pi = 3.14";
//     double d = stod(s22.substr(s22.find_first_of("+-0.123456789")));
//     std::cout << d << std::endl;
    // stoi(s, p, b) 以此为例 s起始子串的数值 b表示转换基数 p是size_t指针（保存s中第一个非数值字符的下标，默认0，即函数不保存下标）
    // stof(s, p)

    // 容器适配器
    // 除了顺序容器外，标准库还定义了三个顺序容器适配器：stack、queue和
    // priority_queue。适配器(adaptor)是标准库中的一个通用概念。
    // stack适配器接受一个顺序容器(除array或forward_list外),并使其操作起来像一个stack一样。
    // 默认情况下，stack和queue是基于deque实现的，priority queue是在vector之上实现的。
    // 我们可以在创建一个适配器时将一个命名的顺序容器作为第二个类型参数，来重载默认容器类型。
//     std::vector<std::string> svec;
//     //在vector上实现的空栈
//     std::stack<std::string, std::vector<std::string>> str_stk;
//     // str_stk2在vector上实现，初始化时保存svec的拷贝
//     std::stack<std::string, std::vector<std::string>> str_stk2(svec);
    
    std::string str11{ "Jan 1,1990" }, str22{ "Feb/2/1990" }, str33{"Apri 17 2023"};
    Date_Deal date1(str11),date2(str22),date3(str33);
    std::cout << date1;
    std::cout << date2;
    std::cout << date3;
}

