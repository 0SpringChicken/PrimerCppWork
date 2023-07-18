// Test_Chapter_Eight.cpp : This file contains the 'main' function. Program execution begins and ends there.
// IO����ϰ

#include <iostream>
#include <fstream> // �ļ���д
#include <sstream> // string�����д
#include <string>
#include <vector>
#include <stdexcept>
#include <bitset>

// ��ȡ��Ϣ����
// �����һ������ĩβ����Ctrl+Z ��ᴥ��is.fail() ��Ҫ��������Ctrl+Z�Ż����
std::istream& func(std::istream& is)
{
    int v;
    while (is >> v, !is.eof())
    {
        if (is.bad())
            throw std::runtime_error("IO������");
        if (is.fail())
        {
            std::cerr << "���ݴ��������ԣ�" << std::endl;
            is.clear();
            is.ignore(100, '\n'); // ignore(num,ch) ��˼�Ǵ�cin����ȡ�ַ�������ȡ���ַ������ԣ�ÿ����һ���ַ�
                                  // ��Ҫ����������ch�Ƚϣ���������ﵽnum�����ַ���ch��ͬ����ֹͣ����
                                  // Ĭ�ϲ���Ϊcin.ignore(1, EOF)������EOFǰ��1���ַ����,û������EOF�����һ���ַ�Ȼ�������
            continue;
        }
        std::cout << v << std::endl;
    }
    is.clear();
    return is;
}

int main()
{
    wchar_t szV[] = L"�����л�";
    // ����״̬
    // iostate(��ʾ����״̬)��
    // badbit(������) failbit(IO����ʧ��) eofbit(���������ļ�����) goodbit(��δ���ڴ���״̬����ֵ��֤Ϊ0)
    // s.eof() ����s����eofbitλ�ã�����true
    // s.fail() ����ͬ��
    // s.bad() ����ͬ��
    // s.good() ����ͬ��
    // s.clear() ��������״̬��λ����������Ϊ��Ч ����void
    // s.clear(flags) ���ݸ�����flags�������ж�Ӧ����״̬λ��λ void
    // s.setstate(flags) ���ݸ�����flags������Ӧ������״̬λ��λ void
    // s.rdstate() ������s��ǰ��״̬ ����strm::iostate
    //

    //std::cout << "������һЩ���֣���Ctrl+Z����" << std::endl;
    //func(std::cin);
    
    // �������������  ���»���ˢ�µ�ԭ��
    // 1.������������ 2.��������ʱ 3.���ò��ݷ�����endl��ʾˢ�»����� 
    // 4.ÿ�����������֮�󣬿������ò��ݷ�unitbuf���������ڲ�״̬������ջ�����
    // Ĭ�������cerr������unitbuf�ģ�����cerr�����ݻᱻ����ˢ�³���
    // 5.һ����������ܱ���������һ������������£�����д����������ʱ�������������Ļ������ᱻˢ��
    // ���� Ĭ������� cerr��cin��������cout����˶�cin��дcerr���ᵼ��cout��������ˢ��
    // ����endl�Ĳ��ݷ� flush��������ݺ��ˢ�£� ends�����������һ�����ַ���ˢ�£�
    // 
    // 5�����ú���tieʵ�� ���������汾
    // һ����û�в����İ汾������ָ���������ָ�룬�����������һ�������������ָ����������ָ��
    // ������δ�������򷵻�һ����ָ��
    // �ڶ����汾����һ��ָ��ostream��ָ�룬���Լ���������ostream
    //

    std::cin.tie(&std::cout);
    // Old_tie��ָ����cout
    std::ostream* Old_tie = std::cin.tie(nullptr); // cin���ڹ���������
    std::cin.tie(&std::cerr); // cin������cerr����ȡcin��ˢ��cerr
    std::cin.tie(Old_tie); // cin������cout
    // ÿ����ͬʱ��������һ���� �����������ͬʱ������ͬһ��ostream

    // �ļ����������
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
        //// �ļ�ģʽ ÿ��������һ���������ļ�ģʽ ����ָ�����ʹ���ļ�
        //// in����ʽ�� outд��ʽ�� appÿ�β���ǰ����ζ���ļ�ĩβ
        //// ate���ļ���������λ��ĩβ trunc�ض��ļ� binary�Զ����Ʒ�ʽ����IO
        //outfile.open(szPath, std::ofstream::app);
        //outfile << "There is the first IO test file at 2023/07/09!" << std::endl;
        //outfile << "This is another line!" << std::endl;
        //outfile << "This is the last line!" << std::endl;

        //std::vector<std::string> Vec_str;
        //std::string strEg;
        //while( !infile.eof() )
        //{
        //    //getline(infile, strEg); // ���д洢
        //    infile >> strEg;          // �����ʴ洢
        //    Vec_str.push_back(strEg);
        //}
        infile.close();

        //auto iter = Vec_str.begin();
        //for (; iter != Vec_str.end(); ++iter)
        //{
        //    std::cout << *iter << std::endl;
        //}
    }
    // �о�cin��getline���÷�
    // 1.cin.getline(char[], BufferSize)
    infile.open(szPath, std::ofstream::in );
    char szValue[20] = { 0 };
    infile.getline(szValue, sizeof(szValue)); // ��ʾֻ��ȡǰ19���ַ�����20���ַ���Ҫ����'\0'
    std::cout << szValue << std::endl;
    infile.ignore(100, '\n');
    char szValues[20] = { 0 };
    infile.getline(szValues, sizeof(szValues), ' '); // �����ո���ֹͣ��ȡ �����������getline��������
                                                     // ʹ�ã������������ʾ
    std::cout << szValues << std::endl;
    // 2.getline(istream,string) ����else��֧�ڲ���Ϊ���÷�

}

// ���ͽ���
// 1.istream ostream ������ �����
// 1.1 cin cout cerr ��׼���� ��׼��� ������������Ϣ��д�뵽��׼����
// 2.>> << ����� ��istream/ostream��ȡ/д������
// 3.getline��������һ��������istream��ȡһ�����ݣ�����һ��������string������
// 
// Ϊ��֧�ֿ��ַ� ��׼�ⶨ����һ�����ͺͶ���������wchar_t���͵����� w��ͷ����
// ֪ʶ�㣺���ַ� �����ʽ
// ���ܿ���IO���� ���E���βλ��߷�����������Ϊ������ ���÷�ʽ���ݺͷ���������ȷ��
//