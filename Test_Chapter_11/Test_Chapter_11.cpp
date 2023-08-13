// Test_Chapter_11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// C++ Primer 11�� ��������  20230801  Tuesday
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
    // ��������֧�ָ�Ч�Ĺؼ��ֲ��Һͷ��� ������Ҫ�Ĺ������� map set
    // map�е�Ԫ����һЩ�ؼ���-ֵ(key-value)��
    // set��ÿ��Ԫ��ֻ����һ���ؼ��� set֧�ָ�Ч�Ĺؼ��ֲ�ѯ�����������һ�������ؼ����Ƿ���set��
    // ��׼���ṩ��8���������������ǵĲ�ͬ��Ҫ����������ά����
    // ��1��������set������map ��2���Ƿ�����ؼ����ظ� ��3���Ƿ�˳�򱣴�
    // �����ظ��ؼ���-multi  ����-unordered  ���߿������
    
    // ͳ�Ƶ��ʳ��ֵĴ���
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
    // 11.4��֤
    vector<string> svec_4{"Example.", "Example!", "Example78", "exAmple", "ample", "examp", "!EXAMPLE"};
    Accu_word(word_count, svec_4);
    for (const auto& w : word_count)
        cout << w.first << " occurs" << w.second << (w.second > 1 ? " times" : " time") << endl;
    // ��������֧����ͨ������������֧��˳����������ز���
    // ����mapʱ��ͬʱָ��keyֵ��valueֵ ����setʱ��ֻ��ָ���ؼ�������
    // ����map��set���ԣ����ǵĹؼ��ֱ�����Ψһ��  ����multimap��multisetû�д�����
    // TEST��
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
    // map ��Ҫ���ڲ��Ҹ�����ֵ  set ���ֵ�Ƿ����
    // 11.6
    // ����Ԫ�� list �жϴ��� set
    
    // 11.7
    map<string, vector<string>> mapFamily;
    vector<string> f_vec{"father", "mother", "son"};
    string fstr_1 = "Jonny";
    // ���Ԫ��
    mapFamily[fstr_1] = f_vec;
    // ��ӳ�Ա
    mapFamily[fstr_1].emplace_back(string("daughter"));

    // �ؼ������͵�Ҫ��
    // ������������ؼ���������һЩ����  ������������map,set,multimap,multiset �ؼ��ֱ��붨��Ԫ�صıȽϷ���
    // �ڼ��������� �ؼ������;���Ԫ������  ��ӳ�������� �ؼ���������Ԫ�صĵ�һ��������

    // pair���� <utility>
    // һ��pair�����������ݳ�Ա pair��Ĭ�Ϲ��캯�������ݳ�Ա����ֵ��ʼ��

    // key_type set �ؼ������� map �ؼ�������
    // mapped_type ÿ���ؼ��ֵĹ������� ֻ������map
    // value_type set�е���key_type map�ж�Ӧpair<const key_type, mapped_type>

    // �������������������汾��erase
    // ����Ԫ�صĲ���
    // lower_bound �� upper_bound����������������  equal_range
    // �±��atֻ�����ڷ�const��map��unordered_map
    
    // ��map��unordered map���ͣ��±�������ṩ����򵥵���ȡԪ�صķ��������ǣ�
    // ������������ʹ���±������һ�����صĸ����ã�����ؼ��ֻ�δ��map�У��±����
    // �����һ�����и����ؼ��ֵ�Ԫ�ء� ���Կ�����find�����±����

    // lower_bound(k) ���ص�һ���ؼ��ֲ�С��k��Ԫ��  >=k
    // upper_bound(k) ���ص�һ���ؼ��ִ���k��Ԫ��    >k
    // equal_range(k) ����һ��������pair����ʾ�ؼ��ֵ���k��Ԫ�صķ�Χ��k�����ڣ���pair�ĳ�Ա��Ϊc.end
    // �����´���ʵ��
    multimap<string, string> authors;
    string search_item("Alain de Botton");
    auto entrise = authors.count(search_item);
    auto iter = authors.find(search_item); // ����һ��map<string,string>::iterator
    while (entrise)
    {
        cout << iter->second << endl;
        ++iter;
        --entrise;
    }

    system("pause");
}
