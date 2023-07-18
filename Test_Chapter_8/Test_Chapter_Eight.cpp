// Test_Chapter_Eight.cpp : This file contains the 'main' function. Program execution begins and ends there.
// IO类练习

#include <iostream>
#include <fstream> // 文件读写
#include <sstream> // string对象读写
#include <string>
#include <vector>
#include <stdexcept>
#include <bitset>

// 读取信息函数
// 如果在一串数字末尾加上Ctrl+Z 则会触发is.fail() 需要单独输入Ctrl+Z才会结束
std::istream& func(std::istream& is)
{
    int v;
    while (is >> v, !is.eof())
    {
        if (is.bad())
            throw std::runtime_error("IO留错误");
        if (is.fail())
        {
            std::cerr << "数据错误，请重试！" << std::endl;
            is.clear();
            is.ignore(100, '\n'); // ignore(num,ch) 意思是从cin中提取字符，但提取的字符被忽略，每抛弃一个字符
                                  // 都要计数或者与ch比较，如果数量达到num或者字符与ch相同，则停止抛弃
                                  // 默认参数为cin.ignore(1, EOF)，即把EOF前的1个字符清掉,没有遇到EOF就清掉一个字符然后结束。
            continue;
        }
        std::cout << v << std::endl;
    }
    is.clear();
    return is;
}

int main()
{
    wchar_t szV[] = L"爱我中华";
    // 条件状态
    // iostate(表示流的状态)：
    // badbit(流崩溃) failbit(IO操作失败) eofbit(流到达了文件结束) goodbit(流未处于错误状态，此值保证为0)
    // s.eof() 若流s处于eofbit位置，返回true
    // s.fail() 道理同上
    // s.bad() 道理同上
    // s.good() 道理同上
    // s.clear() 所有条件状态复位，将流设置为有效 返回void
    // s.clear(flags) 根据给定的flags，将流中对应条件状态位复位 void
    // s.setstate(flags) 根据给定的flags，将对应的条件状态位置位 void
    // s.rdstate() 返回流s当前的状态 类型strm::iostate
    //

    //std::cout << "请输入一些数字，按Ctrl+Z结束" << std::endl;
    //func(std::cin);
    
    // 管理输出缓冲区  导致缓冲刷新的原因：
    // 1.程序正常结束 2.缓冲区满时 3.利用操纵符比如endl显示刷新缓冲区 
    // 4.每个输出操作符之后，可以利用操纵符unitbuf设置流的内部状态，来清空缓冲区
    // 默认情况下cerr是设置unitbuf的，所以cerr的内容会被立即刷新出来
    // 5.一个输出流可能被关联到另一个流，此情况下，当读写被关联的流时，关联到的流的缓冲区会被刷新
    // 比如 默认情况下 cerr和cin都关联到cout。因此读cin或写cerr都会导致cout缓冲区被刷新
    // 类似endl的操纵符 flush（输出内容后仅刷新） ends（输出并附加一个空字符再刷新）
    // 
    // 5可以用函数tie实现 他有两个版本
    // 一个是没有参数的版本，返回指向输出流的指针，本对象关联到一个输出流，返回指向该输出流的指针
    // 本对象未关联，则返回一个空指针
    // 第二个版本接受一个指向ostream的指针，将自己关联到该ostream
    //

    std::cin.tie(&std::cout);
    // Old_tie就指向了cout
    std::ostream* Old_tie = std::cin.tie(nullptr); // cin不在关联其他流
    std::cin.tie(&std::cerr); // cin关联到cerr，读取cin会刷新cerr
    std::cin.tie(Old_tie); // cin关联到cout
    // 每个流同时最多关联到一个流 但多个流可以同时关联到同一个ostream

    // 文件的输入输出
    char szPath[] = "./Writefile/haidong.log";
    std::ifstream infile(szPath);
    if (!infile.is_open())
    {
        std::cerr << "Open file failed! Because of " << std::bitset<sizeof(int)*8>(infile.rdstate()) 
            << " flags!" << std::endl;
    }
    else
    {
        //std::ofstream outfile;
        //// 文件模式 每个流都有一个关联的文件模式 用来指出如何使用文件
        //// in读方式打开 out写方式打开 app每次操作前均订味道文件末尾
        //// ate打开文件后立即定位到末尾 trunc截断文件 binary以二进制方式进行IO
        //outfile.open(szPath, std::ofstream::app);
        //outfile << "There is the first IO test file at 2023/07/09!" << std::endl;
        //outfile << "This is another line!" << std::endl;
        //outfile << "This is the last line!" << std::endl;

        //std::vector<std::string> Vec_str;
        //std::string strEg;
        //while( !infile.eof() )
        //{
        //    //getline(infile, strEg); // 按行存储
        //    infile >> strEg;          // 按单词存储
        //    Vec_str.push_back(strEg);
        //}
        infile.close();

        //auto iter = Vec_str.begin();
        //for (; iter != Vec_str.end(); ++iter)
        //{
        //    std::cout << *iter << std::endl;
        //}
    }
    // 研究cin与getline的用法
    // 1.cin.getline(char[], BufferSize)
    infile.open(szPath, std::ofstream::in );
    char szValue[20] = { 0 };
    infile.getline(szValue, sizeof(szValue)); // 表示只读取前19个字符，第20个字符需要填入'\0'
    std::cout << szValue << std::endl;
    infile.ignore(100, '\n');
    char szValues[20] = { 0 };
    infile.getline(szValues, sizeof(szValues), ' '); // 遇到空格则停止读取 但是与上面的getline不能连续
                                                     // 使用，否则无输出显示
    std::cout << szValues << std::endl;
    // 2.getline(istream,string) 上面else分支内部即为此用法

}

// 类型介绍
// 1.istream ostream 输入流 输出流
// 1.1 cin cout cerr 标准输入 标准输出 输出程序错误消息，写入到标准错误
// 2.>> << 运算符 从istream/ostream读取/写入数据
// 3.getline函数，从一个给定的istream读取一行数据，存入一个给定的string对象中
// 
// 为了支持宽字符 标准库定义了一组类型和对象来操纵wchar_t类型的数据 w开头即可
// 知识点：宽字符 编码格式
// 不能拷贝IO对象 不鞥将形参或者返回类型设置为流类型 引用方式传递和返回流是正确的
//