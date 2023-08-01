// Test_Chapter_1-.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// C++ Primer �����㷨 ��ʮ����ϰ 37ҳ 20230722 Saturday

#include <iostream>
#include <algorithm> // �㷨ͷ�ļ� �����㷨�Ĺ����ӿ�
#include <numeric> // ��������ֵ�����㷨
#include <vector>
#include <string>
#include <list>
#include <iterator>
#include <functional>
#include <fstream>

// ��Щ�����㷨��ֱ�Ӳ������� ���Ǳ�������������ָ����һ��Ԫ�ط�Χ
//
bool Check_size(const std::string str, size_t sz)
{
    return str.size() > sz;
}

// 10.1
void find_elem(std::vector<int>& vec, int& target, std::istream& is)
{
    int ele = 0; int64_t num = 0;
    while (is >> ele)
    {
        vec.push_back(ele);
    }
    num = std::count(vec.begin(), vec.end(), target);
    std::cout << "The value " << target << "'s number is " << num << std::endl;
}
// 10.2
void find_elem(std::list <std::string>& strlist, std::string& target, std::istream& is)
{
    std::string str = ""; int64_t num = 0;
    while (is >> str)
    {
        strlist.push_back(str);
    }
    num = std::count(strlist.begin(), strlist.end(), target);
    std::cout << "The value " << target << "'s number is " << num << std::endl;
}
// 10.3
void Summation(std::vector<int>& vec, int& Sum)
{
    Sum = std::accumulate(vec.cbegin(), vec.cend(), 0);
}
// 10.4 ����  Ӧ����0.0  10.5 ���� �൱�ڱȽ�����char*���ͣ�ֻ�е�ַ��Ȳ����

// 10.9 ���ﲻ����list��Ϊlist�ĵ�������֧�ּӼ����������������
void elimDups(std::vector<std::string>& svec)
{
    std::sort(svec.begin(), svec.end());
    auto iter = std::unique(svec.begin(), svec.end());
    svec.erase(iter, svec.end());
}

bool isShorter(const std::string& str1, const std::string& str2)
{
    return str1.size() < str2.size();
}

bool isShorterThanFive(const std::string& s)
{
    return s.size() < 5;
}

// 10.13 partition�㷨
void OutFive(std::vector<std::string>& svec)
{
    auto iter = std::partition(svec.begin(), svec.end(), isShorterThanFive);
    std::for_each(iter, svec.end(), [&](std::string str) {std::cout << str << "\t"; });
    std::cout << std::endl;
}

// 10.15
void Summation(int& ival)
{
    auto sum = [ival](int ivall)->int {return ival + ivall; };
    std::cout << sum(10) << std::endl;
}

// 10.16  ��������10.25
void biggies(std::vector<std::string> svec, std::string::size_type sz)
{
    elimDups(svec);
    std::stable_sort(svec.begin(), svec.end(), [](const std::string &s1, const std::string &s2)
        {return s1.size() < s2.size(); });
    //auto iter = std::find_if(svec.begin(), svec.end(),
    //    [sz](const std::string& s) {return s.size() >= sz; });
    // ����bind����ʽ
    auto iter = std::find_if(svec.begin(), svec.end(),
        std::bind(Check_size, std::placeholders::_1, sz));
    auto size = svec.end() - iter;
    std::cout << "There " << (size > 1 ? "are " : "is ") << size
        << (size > 1 ? " words" : " word") << " longer than " << sz << std::endl;
}

// 10.18
void biggies_other(std::vector<std::string> svec, std::string::size_type sz)
{
    elimDups(svec);
    auto iter = std::partition(svec.begin(), svec.end(),
        [sz](const std::string s) {return s.size() < sz; });
    auto size = svec.end() - iter;
    std::cout << "There " << (size > 1 ? "are " : "is ") << size
        << (size > 1 ? " words" : " word") << " longer than " << sz << std::endl;
}

// �����б�ľ���
void func_1()
{
    int size_t = 21;
    auto f = [size_t] {return size_t; };
    size_t = 0;
    int j = f();// j=21 ���ص���size_t�Ŀ���
}

void func_2()
{
    int size_t = 21;
    auto f = [&size_t] {return size_t; };
    size_t = 0;
    int j = f();// j=0 ��Ϊ�������size_t������
}

// ��ʽ��������ʽ������ʹ��
void biggies(std::vector<std::string> svec, const std::string::size_type sz, std::ostream& os, char ch = ' ')
{
    elimDups(svec);
    auto iter = std::partition(svec.begin(), svec.end(),
        [&sz](const std::string s) {return s.size() < sz; });
    auto size = svec.end() - iter;
    // �����ǻ��ʹ����ʽ�������ʽ����ʱ�������б��еĵ�һ��Ԫ�ر�����һ��&��=���˷�
    // ��ָ����Ĭ�ϲ���ʽΪ���û�ֵ��
    // 
    // ��ʽ����os�����ã�  ��ʾ����ch��ֵ��
    std::for_each(svec.begin(), svec.end(),
        [&, ch](const std::string& str) {os << str << ch; });
    // ��ʽ����os�����ã�  ��ʾ����ch��ֵ��
    std::for_each(svec.begin(), svec.end(),
        [=, &os](const std::string& str) {os << str << ch; });
}

// �ɱ�lambada
void func3()
{
    size_t v1 = 42;
    auto f = [v1]()mutable {return ++v1; };
    size_t v2 = f();
    std::cout << v2 << std::endl;
}
// 10.20
void Acc_size(std::vector<std::string>& svec , const size_t& sz, unsigned &Times)
{
    Times = std::count_if(svec.begin(), svec.end(),
        [sz](std::string str) {return str.size() >= sz; });
    std::cout << "There " << (Times > 1 ? "are " : "is ") << Times << (Times > 1 ? " words " : " word ")
        << " longer than " << sz << std::endl;
}
// 10.21
bool lambda_test(int& nValue)
{
    auto f = [&nValue]()->bool
    {
        if (nValue > 0)
        {
            for (; nValue;)
                --nValue;
        }
        else return true; 
    };
    return f();
}

// ��ӡ����
void print_vec(const std::vector<std::string>& svec)
{
    std::for_each(svec.cbegin(), svec.cend(),
        [](const std::string& str) {std::cout << str << "\t"; });
}

// ��ӡ����
std::ostream& print(std::ostream& os, const std::string& str, char ch)
{
    return os << str << ch;
}

// 10.24
bool isBigger(size_t sz, int val)
{
    return val > sz;
}

void find_First(std::vector<int>& ivec, const std::string &str)
{
    size_t sz = str.size();
    std::sort(ivec.begin(), ivec.end());
    auto iter = std::find_if(ivec.begin(), ivec.end(), std::bind(isBigger, sz, std::placeholders::_1));
    std::cout << *iter << std::endl;
}

// 10.27
void inserter_list(const std::vector<int>& ivec, std::list<int>& ilist)
{
    std::unique_copy(ivec.begin(), ivec.end(), std::back_inserter(ilist));
}

// 10.28(��)

// 10.33
void Separate_EvenAndOdd(const std::string& Src, const std::string& Even, const std::string& Odd)
{
    std::ifstream infile(Src);
    if (infile)
    {
        std::ofstream out_Even(Even), out_Odd(Odd);
        if (!out_Even && !out_Odd)
        {
            std::cerr << "Wrong File Dest Path" << std::endl;
        }
        else
        {
            std::istream_iterator<int> inEle(infile), eof;
            std::ostream_iterator<int> out_EvEle(out_Even,"\n"), out_OddEle(out_Odd," ");
            while (inEle != eof)
            {
                if (*inEle % 2) out_OddEle = *inEle++;
                else out_EvEle = *inEle++;
            }
            infile.close();
            out_Even.close();
            out_Odd.close();
        }
    }
    else
    {
        std::cerr << "Wrong File Src Path" << std::endl;
    }
}

int main()
{
   // find �㷨 
    std::vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 8};
    int i = 9;
    auto result = std::find(ivec.begin(), ivec.end(), i); // ��ivec��Ѱ��Ԫ��9
    std::cout << "The element " << i 
        << (result == ivec.end() ? "is not present" : "is present") << std::endl;
    // findҲ���������в���Ԫ�� ԭ��ָ�������ڵ�����
    // find�Ĺ�������һ��δ�����Ԫ�������в���һ���ض�������
    // find�������������������Ԫ�����ͣ�ֻҪ��һ��������������������Ԫ�أ�find�Ͳ���������������
    // ��Ȼ���������㷨�����������������㷨ȱ������Ԫ�����͵Ĳ���������==����<�ȣ�

    // �ؼ�����
    // �����㷨��Զ����ִ�������Ĳ���������ֻ�������ڵ�����֮�ϣ�ִ�е������Ĳ���
    // ������������Ե�����һ����̼ٶ����㷨��Զ����ı�ײ������Ĵ�С���㷨���ܸı������б���Ԫ�ص�
    // ֵ��Ҳ�������������ƶ�Ԫ�أ�����Զ����ֱ����ӻ�ɾ��Ԫ�أ��������������������������
    
    // ֻ���㷨
    // һЩ�㷨ֻ���ȡ�����뷶Χ�ڵ�Ԫ�أ��Ӳ��ı�Ԫ�أ�����find
    // accumulate<numeric> accumulate(beg,end,init_value)
    // ������������ʾ�͵ĳ�ֵ ���ص�������Ԫ�صĺ�
    // accumulate�ĵ��������������;����˺�����ʹ���ĸ��ӷ�������Լ�����ֵ������
    std::vector<std::string> svec{"ABC", "DEF", "GHI"};
    // std::string str = std::accumulate(svec.begin(), svec.end(), "");
    // �����Ǵ���汾��������������const char*��û�ж���+����
    std::string str_acc = std::accumulate(svec.begin(), svec.end(), std::string(""));
    // �����������е��㷨 equal ����ֵbool����
    // ������һ�������е�ÿ��Ԫ����ڶ��������еĶ�ӦԪ�ؽ��бȽ�
    // equal(a.cbegin(), a.cend(), b.cbegin())����b����Ӧ����a�е�Ԫ��һ����
    // ����equal���õ�������ɲ�����������ǿ���ͨ������equal���Ƚ�������ͬ���͵�
    // �����е�Ԫ�ء����ң�Ԫ������Ҳ����һ����ֻҪ��������һ���Ƚ�����Ԫ�����ͼ���

    // д����Ԫ�ص��㷨
    // fill(v.begin(), v.end(), init_val) �������е�ֵ����Ϊinit_val
    // �ؼ��������������  �㷨�����д����
    // fill_n(dest, size, init_val)  �������ڿ�����  dest��size��Ԫ�ض�Ϊinit_val
    // ��Ŀ��λ�õ�����д�����ݵ��㷨�ٶ�Ŀ��λ���㹻��������Ҫд���Ԫ��

    // back_inserter ��������� <iterator> ����һ������
    // back_inserter����һ��ָ�����������ã�����һ����������󶨵Ĳ����������
    // ������ͨ���˵�������ֵʱ����ֵ����������push_back��һ�����и���ֵ��Ԫ����ӵ�������
    std::vector<int> vec_ins, vec_ins1;
    // ����Ϊstd::back_insert_iterator<std::vector<int>>  Ҳ��ʹ��auto
    std::back_insert_iterator<std::vector<int>> iter = std::back_inserter(vec_ins);
    for (auto x = 0; x < 10; ++x)
        *iter = x;
    std::for_each(vec_ins.begin(), vec_ins.end(), 
        [&](int x) {std::cout << x << "\t"; });
    // ����fill_n��˵��ʹ��back_inserter�͸�Ϊ������ ����һ���յ�vector
    std::fill_n(std::back_inserter(vec_ins1), 10, 0);
    std::cout << std::endl;
    // �����㷨 copy ����ֵΪĿ�ĵص�������ֵ
    int a1[] = { 1,2,3,4,5,6,7,8,9 };
    int a2[sizeof(a1) / sizeof(a1[0])]; //ȷ��a2��С==a1
    auto ret= std::copy(std::begin(a1), std::end(a1), a2);// a1�е����ݿ�����a2 retָ��a2βԪ��֮���λ��
    std::for_each(std::begin(a2), std::end(a2),
        [&](int x) {std::cout << x << "\t"; });
    std::cout << std::endl;
    // replace(iter1, iter2, old_val, new_val) ��Χ������old_val���滻Ϊnew_val
    // ����ԭ���в��� ����replace_copy
    // replace_copy(begin, end, iter_target, old_val, new_val) ��Χ������old_val���滻Ϊnew_val

    // 10.6 
    std::list<int> ilist_f(std::begin(a1), std::end(a1));
    std::fill_n(ilist_f.begin(), ilist_f.size(), 0);
    std::for_each(ilist_f.begin(), ilist_f.end(),
        [&](int x) {std::cout << x << "\t"; });
    std::cout << std::endl;

    // ��������Ԫ�ص��㷨 sort ����<�����ʵ�ֵ� (����һ���ַ�����)
    // sort->unique->erease
    // unique �㷨�����������У������ڵ��ظ��������, ������һ��ָ���ظ�ֵ֮��ĵ�����
    // erase() P311 ɾ��ĩβ�ظ���Ԫ�� unique���صĵ�����һֱ��endλ��
    std::vector<std::string> svec_eli{"no", "one", "could", "or", "like", "the", "sun", "be", "the", "moon"};
    elimDups(svec_eli);
    std::for_each(svec_eli.begin(), svec_eli.end(),
        [&](std::string str) {std::cout << str << "\t"; });
    std::cout << std::endl;

    // ���Ʋ���  Ҫ��  ν��  ���㷨���ݺ���
    // ����sort��Ĭ����Ϊ sort�ĵڶ����汾 �����������İ汾 ��������������ν��
    // �������ν����ָ���Ĳ��� ��һ���ɵ��õı��ʽ ���ؽ����һ������Ϊ������ֵ
    // ��׼����ʹ�õ�ν�������� һԪν�ʺͶ�Ԫν�� �������ڽ���һ������������
    // ����ν�ʲ������㷨�����������е�Ԫ�ص���ν�� ����Ԫ�����ͱ�����ת��Ϊν�ʵĲ�������
    
    // ʹ��isShorter�Ƚ� �̵ķ����� ���Ƕ�ǰ����
    // �������ɶ���������
    std::sort(svec_eli.begin(), svec_eli.end(), isShorter); // ʹ��isShorter�Ƚ� �̵ķ����� ���Ƕ�ǰ����
    std::for_each(svec_eli.begin(), svec_eli.end(),
        [&](std::string str) {std::cout << str << "\t"; });
    std::cout << std::endl;
    // �ֵ��� stable_sort() �ȶ������㷨ά�����Ԫ�ص�ԭ��˳��
    svec_eli.push_back("about");
    svec_eli.push_back("above");
    svec_eli.push_back("abs");
    svec_eli.push_back("abt");
    svec_eli.push_back("abd");

    elimDups(svec_eli);// ����С����
    std::for_each(svec_eli.begin(), svec_eli.end(),
        [&](std::string str) {std::cout << str << "\t"; });
    std::cout << std::endl;

    std::sort(svec_eli.begin(), svec_eli.end(), isShorter);// ����������
    std::for_each(svec_eli.begin(), svec_eli.end(),
        [&](std::string str) {std::cout << str << "\t"; });
    std::cout << std::endl;

    std::stable_sort(svec_eli.begin(), svec_eli.end(), isShorter);// ���ճ������� ����ͬ���Ȱ����ֵ���
    std::for_each(svec_eli.begin(), svec_eli.end(),
        [&](std::string str) {std::cout << str << "\t"; });
    std::cout << std::endl;
    // 10.13
    OutFive(svec_eli);

    // Lambda���ʽ
    // �ڲ����ĸ���������ν������ķ�Χʱ����ʹ��Lambda���ʽ
    // ���ǿ�����һ���㷨�����κ����Ŀɵ��ö��� һ���������һ�����ʽ 
    // ���Զ���ʹ�õ���������� �ͳ���Ϊ�ɵ��õ� ����e��һ���ɵ��õı��ʽ �����ǿ��Ա�д����e(args)
    // argsΪ�����б�Ŀǰ��ʹ�ù����ֿɵ��ö��� �����ͺ���ָ�룬 �����˺���������������� �Լ� Lambda��
    // find_if�㷨 ���Ҿ����ض���С��Ԫ��

    // [capture lisr](parameter lisr)-> return type ( function body )
    //    �����б�        �����б�        ��������       ������
    // �����б���lambda���ں����ж���ľֲ��������б� ͨ��Ϊ��
    // ���Ժ��Բ����б�ͷ�������
    // ������Է������� lambda����ݺ������ƶ� 
    // �����������ֻ��һ��return��� �򷵻����ʹӷ��صı�ʶ�������ƶ϶���
    // ���� ��������Ϊvoid 
    // �����lambda�ĺ���������κε�һreturn���֮������ݣ���δָ���������ͣ��򷵻�void
    // �����б�ֻ���ھֲ���static������lambda����ֱ��ʹ�þֲ�static�������������ں���֮�����������֡�
    // 

    // 10.14
    [](int i1, int i2) {return i1 + i2; };
    // 10.16
    biggies(svec_eli, 7);
    // 10.18
    biggies_other(svec_eli, 4);

    // lambda����ͷ���
    // ������һ��lambdaʱ������������һ����lambda��Ӧ���µ�(δ������)������
    // ����������� ����һ����������һ��lambdaʱ��ͬʱ������һ�������ͺ͸����͵�һ������
    // ���ݵĲ������Ǵ˱����������δ�����������Ͷ���
    // �����Ĳ���ʽҲ������ֵ��������
    // �������÷�ʽ����һ������ʱ�����뱣֤��lambdaִ��ʱ�����Ǵ��ڵġ�
    // ��ʽ���� [&,=] ��ʽ����[&val1,=val2]
    std::vector<std::string> svec_lambda{"love", "peace", "hello", "world", "fun", "sad", "mind"};
    biggies(svec_lambda, 5, std::cout);
    std::cout << std::endl;
    // Ĭ������£�����һ��ֵ�����ı�����lambda����ı���ֵ �������ϣ���ı�һ��������ı�����ֵ
    // ��Ҫ�ڲ����б��׼��Ϲؼ���mutable ���ɱ�lambda�� �����ò���ı���ȡ�������Ƿ�Ϊconst
    func3();
    // ָ��lambda��������
    std::vector<std::string> svec_accsz{"Spring", "Boot", "Money", "Zuul", "Cloud", "Authority"};
    unsigned utimes = 0;
    Acc_size(svec_accsz, 6, utimes);
    // 10.21 ��֤
    int nlval = 10;
    std::cout << "Before lambda_test val:" << nlval << std::endl;
    if (lambda_test(nlval))
        std::cout << "After lambda_test val:" <<nlval << std::endl;

    // ������
    // bind���� <functional> ���Խ�bind��������һ��ͨ�õĺ���������
    // ������һ���ɵ��ö�������һ���µĿɵ��ö���������Ӧ��ԭ����Ĳ����б�
    // һ����ʽ��auto newCallable = bind(callable, arg_list);
    // arg_list�еĲ������ܰ�������_n�����֣�����n��һ����������Щ�����ǡ�ռλ����,
    // ��ʾnewCallable�Ĳ���������ռ���˴��ݸ�newCallable�Ĳ����ġ�λ�á�
    // ��ֵn��ʾ���ɵĿɵ��ö����в�����λ�ã�_1ΪnewCallable�ĵ�һ��������2Ϊ�ڶ����������������ơ�
    // ��Check_size����չʾbind  ռλ����std::placeholders::�� 
    // 10.22
    auto check6 = std::bind(Check_size, std::placeholders::_1, 6);
    if(check6(std::string("ccddeeffg"))) std::cout << "Beyond 6 words" << std::endl;
    // ʹ��placeholders���� ����_n��������һ����Ϊplaceholders�������ռ���
    // bind�Ĳ���˳��  ���磺 f��һ������������Ŀɵ��ö���
    // auto g = bind(f,a,b,_2,c,_1);  ��g��һ�������������Ŀɵ��ö���  ��ʵg(_1,_2);
    // �����ڵ���ʱ������g(x,y) ��x����_1λ�ã�y����_2λ�ã�ʵ�ʵĵ�����f(a,b,y,c,x)
    
    // bind���Ų���˳��
    // bind�ߵ�˳��
    std::vector<std::string> svec_bind{"Spring", "Boot", "Money", "Zuul", "Cloud", "Authority"};
    std::sort(svec_bind.begin(), svec_bind.end(), 
        std::bind(isShorter, std::placeholders::_2, std::placeholders::_1));
    print_vec(svec_bind);
    std::cout << std::endl;
    // �����ò���
    // Ĭ������£���Щ����ռλ���Ĳ�����������bind���صĿɵ��ö�����
    // ���Ҫ���õ�����Щ��ռλ���Ĳ���  ��Ҫ�õ�ref()����
    // ��print����
    auto print_new = std::bind(print, ref(std::cout), std::placeholders::_1, ' ');
    print_new(std::string("Hello World!"));
    std::cout << std::endl;
    //
    std::vector<int> ivec_24{1, 2, 3, 8, 9, 5, 4, 7, 6};
    std::string str_24{"hello"};
    find_First(ivec_24, str_24);
    
    // ��̽������
    // ����Ϊÿ����������ĵ�����֮�⣬��׼����ͷ�ļ��л������������ĵ�����
    // ���������  ��������  ���������  �ƶ����������ƶ�Ԫ�أ�
    // �Ƚ����������  1.back_inserter(push_back)  2.front_inserter(push_front)  3.inserter(insert)
    
    // iosteream������ istream_iterator  ostream_iterrator
    // istream_iterator<T> in(is); in��������is��ȡ����ΪT��ֵ
    // istream_iterator<T> end;  ��ȡ����ΪT��ֵ��istream_iterator����������ʾβ��λ��
//    std::istream_iterator<int> in_iter(std::cin), eof;
//    while (in_iter != eof)
//        ivec_24.push_back(*in_iter++);
    // ʹ���㷨������������
//    std::istream_iterator<int> in(std::cin), eof1;
//    auto valii = std::accumulate(in_iter, eof, 0);
//    std::cout << valii << std::endl;
    // ���뽫ostream_iterator�󶨵�һ��ָ��������������յĻ��ʾβ��λ�õ�ostream iterator��
    // ostream_iterator<T> out(os);  out������ΪT��ֵд�������os��
    // ostream_iterator<T> out(os,d);  ut������ΪT��ֵд�������os�У�ÿ��ֵ���涼���һ��d��dָ��һ�����ַ���β���ַ�����
//    std::ostream_iterator<int> out_iter(std::cout, " ");
//    for (auto& ele : ivec_24)
//        *out_iter++ = ele;// ����д�� out_iter=ele����ʽ 
    // *out, ++out, out++ ��Щ������Ǵ��ڵģ�������out���κ����顣ÿ�������������out
//    std::cout << std::endl;
    // ���Խ���copy�����
//    std::copy(ivec_24.begin(), ivec_24.end(), out_iter);
//    std::cout << std::endl;
    // 10.29
    std::ifstream in_file("../words.txt");
    if (in_file)
    {
        std::istream_iterator<std::string> in_words(in_file), eof;
        std::vector<std::string> str_vec(in_words, eof);
        in_file.close();
        print_vec(str_vec);
    }
    // 10.30  10.31
    std::istream_iterator<int> in_num(std::cin), eof_30;
    std::vector<int> ivec_30;
    while (in_num != eof_30)
        ivec_30.push_back(*in_num++);
    std::sort(ivec_30.begin(), ivec_30.end());
    std::ostream_iterator<int> out_num(std::cout, " ");
    std::unique_copy(ivec_30.begin(), ivec_30.end(), out_num);
    std::cout << std::endl;
    // 10.32(��)
    // 10.33
    std::cin.clear();
    std::string str_src{"../Src.txt"}, str_eve{ "../Even.txt" }, str_odd{ "../Odd.txt" };
    Separate_EvenAndOdd(str_src, str_eve, str_odd);
    // ���������
    std::string str_ri{"FIRST,MIDDLE,LAST"};
    auto rcomma = std::find(str_ri.crbegin(), str_ri.crend(), ',');
    std::string str_tr(rcomma.base(), str_ri.cend());
    std::cout << str_tr << std::endl;
    // 10.34
    std::vector<std::string> vec_mon{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (auto iter = vec_mon.crbegin(); iter != vec_mon.crend();)
        std::cout << *iter++ << "\t";
    std::cout << std::endl;
    // 10.35
    auto iter_35 = vec_mon.end() - 1;
    for (; iter_35 != vec_mon.begin();)
        std::cout << *iter_35-- << "\t";
    std::cout << *iter_35 << "\t";
    std::cout << std::endl;
    // 10.36
    std::list<int> list_36{1, 2, 3, 0, 5, 4, 6};
    auto iter_36 = std::find(list_36.begin(), list_36.end(), 0);
    // 10.37 ����vec_mon
    std::list<std::string> list_37{};
    auto ins_iter = std::front_inserter(list_37);
    for (auto iter = vec_mon.begin() + 3; iter != vec_mon.begin() + 7;)
    {
        *ins_iter = *iter++;
    }
    for (auto& x : list_37)
        std::cout << x << "\t";
    std::cout << std::endl;
    // �����㷨�ṹ
    // �㷨��Ҫ��ĵ������������Է�Ϊ5�����������
    // ���������    ֻ������д������ɨ�裬ֻ�ܵ���
    // ���������    ֻд������������ɨ�裬ֻ�ܵ���
    // ǰ�������    �ɶ�д�����ɨ�裬ֻ�ܵ���
    // ˫�������    �ɶ�д�����ɨ�裬�ɵ����ݼ�
    // ������ʵ�����  �ɶ�д�����ɨ�裬֧��ȫ������������
    // 
    // �ڶ����㷨����ķ�ʽ(�������ڱ��¿�ʼ������)�ǰ����Ƿ����д�������������е�Ԫ�������ࡣ
    // 


    // 1.���������  ֻ����˳����ʣ�istream_iterator��
    // ���ܣ��Ƚϵ���������Ȼ򲻵�
    //    �ƽ���������ǰ�û��ߺ��������
    //    ��ȡԪ�صĽ����������Լ���ͷ����
    // 10.39 list�ϵĵ���������˫�������  vector������������ʵ�����
    // 10.40 copyǰ���������������������������ʾ��Χ������������������һ�����������
    // reverseҪ���������У���������������˫�������
    // unique˳��ɨ��Ԫ�أ�������ǰ�������

    // �㷨�β�ģʽ
    // alg(beg, end, other args);
    // alg(beg, end, dest, other args);
    // alg(beg, end, beg2, other args);
    // alg(beg, end, beg2, end2, other args);

    // 10.41
    // replace(beg,end,old_val,new_val); ��ֵ�滻��ֵ
    // replace_if(beg,end,pred,new_val); ������������ֵ�滻Ϊ��ֵ
    // replace_copy(beg,end,dest,old_val,new_val);  ����ֵ�滻��ֵ������destλ�ã�ԭ�������ݲ��䣩
    // replace_copy_if(beg,end,dest,pred,new_val); ���������ľ�ֵ�滻Ϊ��ֵ��������destλ���У�ԭ�������ݲ��䣩

    // list forward_list�����˼�����Ա������ʽ���㷨
    // sort merge remove reverse unique
    // splice��Ա splice_after
    // 10.42
    std::list<int> list_42{1, 1, 2, 3, 3, 4, 4, 5, 6, 7, 7, 7, 7, 8};
    std::cout << "Before unique, list value: " << std::endl;
    for (auto& x : list_42)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    list_42.unique();
    std::cout << "After unique, list value: " << std::endl;
    for (auto& x : list_42)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu


