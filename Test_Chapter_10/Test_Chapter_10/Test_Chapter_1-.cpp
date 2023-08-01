// Test_Chapter_1-.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// C++ Primer 泛型算法 第十章练习 37页 20230722 Saturday

#include <iostream>
#include <algorithm> // 算法头文件 经典算法的公共接口
#include <numeric> // 定义了数值泛型算法
#include <vector>
#include <string>
#include <list>
#include <iterator>
#include <functional>
#include <fstream>

// 这些泛型算法不直接操作容器 而是遍历两个迭代器指定的一个元素范围
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
// 10.4 错误  应该用0.0  10.5 错误 相当于比较两个char*类型，只有地址相等才相等

// 10.9 这里不能用list因为list的迭代器不支持加减操作。。。。大坑
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

// 10.13 partition算法
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

// 10.16  可沿用至10.25
void biggies(std::vector<std::string> svec, std::string::size_type sz)
{
    elimDups(svec);
    std::stable_sort(svec.begin(), svec.end(), [](const std::string &s1, const std::string &s2)
        {return s1.size() < s2.size(); });
    //auto iter = std::find_if(svec.begin(), svec.end(),
    //    [sz](const std::string& s) {return s.size() >= sz; });
    // 调用bind的形式
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

// 捕获列表的举例
void func_1()
{
    int size_t = 21;
    auto f = [size_t] {return size_t; };
    size_t = 0;
    int j = f();// j=21 返回的是size_t的拷贝
}

void func_2()
{
    int size_t = 21;
    auto f = [&size_t] {return size_t; };
    size_t = 0;
    int j = f();// j=0 因为捕获的是size_t的引用
}

// 隐式捕获与显式捕获混合使用
void biggies(std::vector<std::string> svec, const std::string::size_type sz, std::ostream& os, char ch = ' ')
{
    elimDups(svec);
    auto iter = std::partition(svec.begin(), svec.end(),
        [&sz](const std::string s) {return s.size() < sz; });
    auto size = svec.end() - iter;
    // 当我们混合使用隐式捕获和显式捕获时，捕获列表中的第一个元素必须是一个&或=。此符
    // 号指定了默认捕获方式为引用或值。
    // 
    // 隐式捕获os（引用）  显示捕获ch（值）
    std::for_each(svec.begin(), svec.end(),
        [&, ch](const std::string& str) {os << str << ch; });
    // 显式捕获os（引用）  隐示捕获ch（值）
    std::for_each(svec.begin(), svec.end(),
        [=, &os](const std::string& str) {os << str << ch; });
}

// 可变lambada
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

// 打印函数
void print_vec(const std::vector<std::string>& svec)
{
    std::for_each(svec.cbegin(), svec.cend(),
        [](const std::string& str) {std::cout << str << "\t"; });
}

// 打印函数
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

// 10.28(略)

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
   // find 算法 
    std::vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 8};
    int i = 9;
    auto result = std::find(ivec.begin(), ivec.end(), i); // 在ivec中寻找元素9
    std::cout << "The element " << i 
        << (result == ivec.end() ? "is not present" : "is present") << std::endl;
    // find也能在数组中查找元素 原理：指针类似于迭代器
    // find的工作是在一个未排序的元序序列中查找一个特定的序列
    // find不依赖于容器所保存的元素类型，只要有一个迭代器可以用来访问元素，find就不依赖于容器类型
    // 虽然迭代器领算法不依赖于容器，但算法缺依赖于元素类型的操作（比如==或者<等）

    // 关键概念
    // 泛型算法永远不会执行容器的操作，他们只会运行于迭代器之上，执行迭代器的操作
    // 这种特殊的属性导致了一个编程假定：算法永远不会改变底层容器的大小。算法可能改变容器中保存元素的
    // 值，也可能在容器内移动元素，但永远不会直接添加或删除元素（但可以依靠插入迭代器做到）
    
    // 只读算法
    // 一些算法只会读取其输入范围内的元素，从不改变元素，类似find
    // accumulate<numeric> accumulate(beg,end,init_value)
    // 第三个参数表示和的初值 返回的是所有元素的和
    // accumulate的第三个参数的类型决定了函数中使用哪个加法运算符以及返回值的类型
    std::vector<std::string> svec{"ABC", "DEF", "GHI"};
    // std::string str = std::accumulate(svec.begin(), svec.end(), "");
    // 上面是错误版本，第三个参数是const char*，没有定义+运算
    std::string str_acc = std::accumulate(svec.begin(), svec.end(), std::string(""));
    // 操作两个序列的算法 equal 返回值bool类型
    // 它将第一个序列中的每个元素与第二个序列中的对应元素进行比较
    // equal(a.cbegin(), a.cend(), b.cbegin())其中b至少应该与a中的元素一样多
    // 由于equal利用迭代器完成操作，因此我们可以通过调用equal来比较两个不同类型的
    // 容器中的元素。而且，元素类型也不必一样，只要我们能用一来比较两个元素类型即可

    // 写容器元素的算法
    // fill(v.begin(), v.end(), init_val) 讲容器中的值都置为init_val
    // 关键概念：迭代器参数  算法不检查写操作
    // fill_n(dest, size, init_val)  不适用于空容器  dest后size个元素都为init_val
    // 向目的位置迭代器写入数据的算法假定目的位置足够大，能容纳要写入的元素

    // back_inserter 插入迭代器 <iterator> 它是一个函数
    // back_inserter接受一个指向容器的引用，返回一个与该容器绑定的插入迭代器。
    // 当我们通过此迭代器赋值时，赋值运算符会调用push_back将一个具有给定值的元素添加到容器中
    std::vector<int> vec_ins, vec_ins1;
    // 类型为std::back_insert_iterator<std::vector<int>>  也可使用auto
    std::back_insert_iterator<std::vector<int>> iter = std::back_inserter(vec_ins);
    for (auto x = 0; x < 10; ++x)
        *iter = x;
    std::for_each(vec_ins.begin(), vec_ins.end(), 
        [&](int x) {std::cout << x << "\t"; });
    // 对于fill_n来说，使用back_inserter就更为保险了 对于一个空的vector
    std::fill_n(std::back_inserter(vec_ins1), 10, 0);
    std::cout << std::endl;
    // 拷贝算法 copy 返回值为目的地迭代器的值
    int a1[] = { 1,2,3,4,5,6,7,8,9 };
    int a2[sizeof(a1) / sizeof(a1[0])]; //确保a2大小==a1
    auto ret= std::copy(std::begin(a1), std::end(a1), a2);// a1中的内容拷贝给a2 ret指向a2尾元素之后的位置
    std::for_each(std::begin(a2), std::end(a2),
        [&](int x) {std::cout << x << "\t"; });
    std::cout << std::endl;
    // replace(iter1, iter2, old_val, new_val) 范围内搜索old_val并替换为new_val
    // 保留原序列不变 则用replace_copy
    // replace_copy(begin, end, iter_target, old_val, new_val) 范围内搜索old_val并替换为new_val

    // 10.6 
    std::list<int> ilist_f(std::begin(a1), std::end(a1));
    std::fill_n(ilist_f.begin(), ilist_f.size(), 0);
    std::for_each(ilist_f.begin(), ilist_f.end(),
        [&](int x) {std::cout << x << "\t"; });
    std::cout << std::endl;

    // 重排容器元素的算法 sort 利用<运算符实现的 (重排一个字符链表)
    // sort->unique->erease
    // unique 算法重排输入序列，将相邻的重复项“消除”, 并返回一个指向不重复值之后的迭代器
    // erase() P311 删除末尾重复的元素 unique返回的迭代器一直到end位置
    std::vector<std::string> svec_eli{"no", "one", "could", "or", "like", "the", "sun", "be", "the", "moon"};
    elimDups(svec_eli);
    std::for_each(svec_eli.begin(), svec_eli.end(),
        [&](std::string str) {std::cout << str << "\t"; });
    std::cout << std::endl;

    // 定制操作  要点  谓词  向算法传递函数
    // 重载sort的默认行为 sort的第二个版本 即三个参数的版本 第三个参数就是谓词
    // 个人理解谓词是指定的操作 是一个可调用的表达式 返回结果是一个能作为条件的值
    // 标准库所使用的谓词有两种 一元谓词和二元谓词 区别在于接收一个和两个参数
    // 接受谓词参数的算法对输入序列中的元素调用谓词 所以元素类型必须能转换为谓词的参数类型
    
    // 使用isShorter比较 短的返回真 就是短前长后
    // 按长度由短至长排序
    std::sort(svec_eli.begin(), svec_eli.end(), isShorter); // 使用isShorter比较 短的返回真 就是短前长后
    std::for_each(svec_eli.begin(), svec_eli.end(),
        [&](std::string str) {std::cout << str << "\t"; });
    std::cout << std::endl;
    // 字典序 stable_sort() 稳定排序算法维持相等元素的原有顺序
    svec_eli.push_back("about");
    svec_eli.push_back("above");
    svec_eli.push_back("abs");
    svec_eli.push_back("abt");
    svec_eli.push_back("abd");

    elimDups(svec_eli);// 按大小排序
    std::for_each(svec_eli.begin(), svec_eli.end(),
        [&](std::string str) {std::cout << str << "\t"; });
    std::cout << std::endl;

    std::sort(svec_eli.begin(), svec_eli.end(), isShorter);// 按长度排序
    std::for_each(svec_eli.begin(), svec_eli.end(),
        [&](std::string str) {std::cout << str << "\t"; });
    std::cout << std::endl;

    std::stable_sort(svec_eli.begin(), svec_eli.end(), isShorter);// 按照长度排序 且相同长度按照字典序
    std::for_each(svec_eli.begin(), svec_eli.end(),
        [&](std::string str) {std::cout << str << "\t"; });
    std::cout << std::endl;
    // 10.13
    OutFive(svec_eli);

    // Lambda表达式
    // 在参数的个数超出了谓词允许的范围时可以使用Lambda表达式
    // 我们可以向一个算法传递任何类别的可调用对象 一个对象或者一个表达式 
    // 可以对其使用调用运算符的 就称其为可调用的 比如e是一个可调用的表达式 则我们可以编写代码e(args)
    // args为参数列表（目前仅使用过两种可调用对象 函数和函数指针， 重载了函数调用运算符的类 以及 Lambda）
    // find_if算法 查找具有特定大小的元素

    // [capture lisr](parameter lisr)-> return type ( function body )
    //    捕获列表        参数列表        返回类型       函数体
    // 捕获列表是lambda所在函数中定义的局部变量的列表 通常为空
    // 可以忽略参数列表和返回类型
    // 如果忽略返回类型 lambda会根据函数体推断 
    // 如果函数体内只有一个return语句 则返回类型从返回的标识的类型推断而来
    // 否则 返回类型为void 
    // 即如果lambda的函数体包含任何单一return语句之外的内容，且未指定返回类型，则返回void
    // 捕获列表只用于局部非static变量，lambda可以直接使用局部static变量和在它所在函数之外声明的名字。
    // 

    // 10.14
    [](int i1, int i2) {return i1 + i2; };
    // 10.16
    biggies(svec_eli, 7);
    // 10.18
    biggies_other(svec_eli, 4);

    // lambda捕获和返回
    // 当定义一个lambda时，编译器生成一个与lambda对应的新的(未命名的)类类型
    // 可以这样理解 当向一个函数传递一个lambda时，同时定义了一个新类型和该类型的一个对象
    // 传递的参数就是此编译器定义的未命名的类类型对象
    // 变量的捕获方式也可以是值或者引用
    // 当以引用方式捕获一个变量时，必须保证在lambda执行时变量是存在的。
    // 隐式捕获 [&,=] 显式捕获[&val1,=val2]
    std::vector<std::string> svec_lambda{"love", "peace", "hello", "world", "fun", "sad", "mind"};
    biggies(svec_lambda, 5, std::cout);
    std::cout << std::endl;
    // 默认情况下，对于一个值拷贝的变量，lambda不会改变其值 如果我们希望改变一个被捕获的变量的值
    // 需要在参数列表首加上关键字mutable （可变lambda） 而引用捕获的变量取决于其是否为const
    func3();
    // 指定lambda返回类型
    std::vector<std::string> svec_accsz{"Spring", "Boot", "Money", "Zuul", "Cloud", "Authority"};
    unsigned utimes = 0;
    Acc_size(svec_accsz, 6, utimes);
    // 10.21 验证
    int nlval = 10;
    std::cout << "Before lambda_test val:" << nlval << std::endl;
    if (lambda_test(nlval))
        std::cout << "After lambda_test val:" <<nlval << std::endl;

    // 参数绑定
    // bind函数 <functional> 可以将bind函数看作一个通用的函数适配器
    // 它接受一个可调用对象，生成一个新的可调用对象来“适应”原对象的参数列表。
    // 一般形式：auto newCallable = bind(callable, arg_list);
    // arg_list中的参数可能包含形如_n的名字，其中n是一个整数。这些参数是“占位符”,
    // 表示newCallable的参数，它们占据了传递给newCallable的参数的“位置”
    // 数值n表示生成的可调用对象中参数的位置：_1为newCallable的第一个参数，2为第二个参数，依此类推。
    // 用Check_size函数展示bind  占位符在std::placeholders::中 
    // 10.22
    auto check6 = std::bind(Check_size, std::placeholders::_1, 6);
    if(check6(std::string("ccddeeffg"))) std::cout << "Beyond 6 words" << std::endl;
    // 使用placeholders名字 名字_n都定义在一个名为placeholders的命名空间中
    // bind的参数顺序  例如： f是一个有五个参数的可调用对象
    // auto g = bind(f,a,b,_2,c,_1);  则g是一个有两个参数的可调用对象  其实g(_1,_2);
    // 但是在调用时，比如g(x,y) 则x传到_1位置，y传到_2位置，实际的调用是f(a,b,y,c,x)
    
    // bind重排参数顺序
    // bind颠倒顺序
    std::vector<std::string> svec_bind{"Spring", "Boot", "Money", "Zuul", "Cloud", "Authority"};
    std::sort(svec_bind.begin(), svec_bind.end(), 
        std::bind(isShorter, std::placeholders::_2, std::placeholders::_1));
    print_vec(svec_bind);
    std::cout << std::endl;
    // 绑定引用参数
    // 默认情况下，那些不是占位符的参数背靠背到bind返回的可调用对象中
    // 如果要引用调用那些非占位符的参数  需要用到ref()函数
    // 绑定print函数
    auto print_new = std::bind(print, ref(std::cout), std::placeholders::_1, ' ');
    print_new(std::string("Hello World!"));
    std::cout << std::endl;
    //
    std::vector<int> ivec_24{1, 2, 3, 8, 9, 5, 4, 7, 6};
    std::string str_24{"hello"};
    find_First(ivec_24, str_24);
    
    // 再探迭代器
    // 除了为每个容器定义的迭代器之外，标准库在头文件中还定义了其他的迭代器
    // 插入迭代器  流迭代器  反向迭代器  移动迭代器（移动元素）
    // 先讲插入迭代器  1.back_inserter(push_back)  2.front_inserter(push_front)  3.inserter(insert)
    
    // iosteream迭代器 istream_iterator  ostream_iterrator
    // istream_iterator<T> in(is); in从输入流is读取类型为T的值
    // istream_iterator<T> end;  读取类型为T的值的istream_iterator迭代器，表示尾后位置
//    std::istream_iterator<int> in_iter(std::cin), eof;
//    while (in_iter != eof)
//        ivec_24.push_back(*in_iter++);
    // 使用算法操作流迭代器
//    std::istream_iterator<int> in(std::cin), eof1;
//    auto valii = std::accumulate(in_iter, eof, 0);
//    std::cout << valii << std::endl;
    // 必须将ostream_iterator绑定到一个指定的流，不允许空的或表示尾后位置的ostream iterator。
    // ostream_iterator<T> out(os);  out将类型为T的值写到输出流os中
    // ostream_iterator<T> out(os,d);  ut将类型为T的值写到输出流os中，每个值后面都输出一个d。d指向一个空字符结尾的字符数组
//    std::ostream_iterator<int> out_iter(std::cout, " ");
//    for (auto& ele : ivec_24)
//        *out_iter++ = ele;// 可以写成 out_iter=ele的形式 
    // *out, ++out, out++ 这些运算符是存在的，但不对out做任何事情。每个运算符都返回out
//    std::cout << std::endl;
    // 可以借用copy来输出
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
    // 10.32(略)
    // 10.33
    std::cin.clear();
    std::string str_src{"../Src.txt"}, str_eve{ "../Even.txt" }, str_odd{ "../Odd.txt" };
    Separate_EvenAndOdd(str_src, str_eve, str_odd);
    // 反向迭代器
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
    // 10.37 沿用vec_mon
    std::list<std::string> list_37{};
    auto ins_iter = std::front_inserter(list_37);
    for (auto iter = vec_mon.begin() + 3; iter != vec_mon.begin() + 7;)
    {
        *ins_iter = *iter++;
    }
    for (auto& x : list_37)
        std::cout << x << "\t";
    std::cout << std::endl;
    // 泛型算法结构
    // 算法所要求的迭代器操作可以分为5个迭代器类别
    // 输入迭代器    只读，不写；单遍扫描，只能递增
    // 输出迭代器    只写，不读：单遍扫描，只能递增
    // 前向迭代器    可读写；多遍扫描，只能递增
    // 双向迭代器    可读写；多遍扫描，可递增递减
    // 随机访问迭代器  可读写，多遍扫描，支持全部迭代器运算
    // 
    // 第二种算法分类的方式(如我们在本章开始所做的)是按照是否读、写或是重排序列中的元素来分类。
    // 


    // 1.输入迭代器  只用于顺序访问（istream_iterator）
    // 功能：比较迭代器的相等或不等
    //    推进迭代器的前置或者后置运算符
    //    读取元素的解引用运算以及箭头运算
    // 10.39 list上的迭代器属于双向迭代器  vector属于是随机访问迭代器
    // 10.40 copy前两个参数至少是输入迭代器，表示范围，第三个参数至少是一个输出迭代器
    // reverse要反向处理序列，两个参数至少是双向迭代器
    // unique顺序扫描元素，至少是前向迭代器

    // 算法形参模式
    // alg(beg, end, other args);
    // alg(beg, end, dest, other args);
    // alg(beg, end, beg2, other args);
    // alg(beg, end, beg2, end2, other args);

    // 10.41
    // replace(beg,end,old_val,new_val); 新值替换旧值
    // replace_if(beg,end,pred,new_val); 将满足条件的值替换为新值
    // replace_copy(beg,end,dest,old_val,new_val);  将新值替换旧值拷贝到dest位置（原容器内容不变）
    // replace_copy_if(beg,end,dest,pred,new_val); 满足条件的旧值替换为新值，拷贝到dest位置中（原容器内容不变）

    // list forward_list定义了几个成员函数形式的算法
    // sort merge remove reverse unique
    // splice成员 splice_after
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


