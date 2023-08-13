// Test_Chapter_11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// C++ Primer 11章 关联容器  20230801  Tuesday
//

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <cstring>

using namespace std;

// 11.4
void Change_word(string& str)
{
    string s;
    for (auto& x : str)
    {
        if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
            s.push_back(toupper(x));
    }
    str = s;
}
void Accu_word(map<string, size_t> &smap, vector<string> &s_vec)
{
    smap.clear();
    for (auto& w : s_vec)
    {
        Change_word(w);
        ++smap[w];
    }
}
//
pair<string, int> 
process(vector<string>& v)
{
    if (!v.empty())
        return { v.back(), v.back().size() };
    else
        return pair<string, int>();
}

int main()
{
    // 关联容器支持高效的关键字查找和访问 两个主要的关联容器 map set
    // map中的元素是一些关键字-值(key-value)对
    // set中每个元素只包含一个关键字 set支持高效的关键字查询操作——检查一个给定关键字是否在set中
    // 标准库提供了8个关联容器，它们的不同主要体现在三个维度上
    // （1）或者是set或者是map （2）是否允许关键字重复 （3）是否按顺序保存
    // 允许重复关键字-multi  无序-unordered  二者可以组合
    
    // 统计单词出现的次数
    map<string, size_t> word_count;
    string word;
    while (cin >> word)
        ++word_count[word];
    for (const auto& w : word_count)
        cout << w.first << " occurs" << w.second << (w.second > 1 ? " times" : " time") << endl; 
    //
    cin.clear();
    set<string> exclude{"the", "but", "and", "or", "a"};
    cin >> word;
    if (exclude.find(word) != exclude.end())
        cout << "Your input is inside this set" << endl;
    else
        cout << "Your input is outside this set" << endl;
    // 11.4验证
    vector<string> svec_4{"Example.", "Example!", "Example78", "exAmple", "ample", "examp", "!EXAMPLE"};
    Accu_word(word_count, svec_4);
    for (const auto& w : word_count)
        cout << w.first << " occurs" << w.second << (w.second > 1 ? " times" : " time") << endl;
    // 关联容器支持普通容器操作，不支持顺序容器的相关操作
    // 定义map时，同时指明key值和value值 定义set时，只需指定关键字类型
    // 对于map和set而言，它们的关键字必须是唯一的  但是multimap和multiset没有此限制
    // TEST：
    vector<int> ivec;
    for (auto i = 0; i < 10; ++i)
    {
        ivec.emplace_back(i);
        ivec.emplace_back(i);
    }       
    set<int> iset(ivec.cbegin(), ivec.cend());
    multiset<int> m_iset(ivec.cbegin(), ivec.cend());
    cout << "set size: " << iset.size() << endl;
    cout << "multiset size: " << m_iset.size() << endl;
    // 11.5
    // map 主要用于查找给定的值  set 检查值是否存在
    // 11.6
    // 访问元素 list 判断存在 set
    
    // 11.7
    map<string, vector<string>> mapFamily;
    vector<string> f_vec{"father", "mother", "son"};
    string fstr_1 = "Jonny";
    // 添加元素
    mapFamily[fstr_1] = f_vec;
    // 添加成员
    mapFamily[fstr_1].emplace_back(string("daughter"));

    // 关键字类型的要求
    // 关联容器对其关键字类型有一些限制  对于有序容器map,set,multimap,multiset 关键字必须定义元素的比较方法
    // 在集合类型中 关键字类型就是元素类型  在映射类型中 关键字类型是元素的第一部分类型

    // pair类型 <utility>
    // 一个pair保存两个数据成员 pair的默认构造函数对数据成员进行值初始化

    // key_type set 关键字类型 map 关键字类型
    // mapped_type 每个关键字的关联类型 只适用于map
    // value_type set中等于key_type map中对应pair<const key_type, mapped_type>

    // 关联容器定义了三个版本的erase
    // 查找元素的操作
    // lower_bound 和 upper_bound不适用于无序容器  equal_range
    // 下标和at只适用于非const的map和unordered_map
    
    // 对map和unordered map类型，下标运算符提供了最简单的提取元素的方法。但是，
    // 如我们所见，使用下标操作有一个严重的副作用：如果关键字还未在map中，下标操作
    // 会插入一个具有给定关键字的元素。 所以可以用find代替下标操作

    // lower_bound(k) 返回第一个关键字不小于k的元素  >=k
    // upper_bound(k) 返回第一个关键字大于k的元素    >k
    // equal_range(k) 返回一个迭代器pair，表示关键字等于k的元素的范围，k不存在，则pair的成员均为c.end
    // 有如下代码实例
    multimap<string, string> authors;
    string search_item("Alain de Botton");
    auto entrise = authors.count(search_item);
    auto iter = authors.find(search_item); // 返回一个map<string,string>::iterator
    while (entrise)
    {
        cout << iter->second << endl;
        ++iter;
        --entrise;
    }

    system("pause");
}
