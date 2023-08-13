// Test_Chapter_12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// ʮ���� ��̬�ڴ� 20230808 Tuesday

#include "stdafx.h"

using namespace std;

// 12.6
vector<int>* Test_126_1(int val = 0)
{
    return new (nothrow) vector<int>(val);
}

void Test_126_2(vector<int> *pv)
{
    int v;
    while (cin >> v)
        pv->push_back(v);
}

void Test_126_3(vector<int>* pv)
{
    for (auto& x : *pv)
        cout << x << "  ";
    cout << endl;
}

// 12.7
shared_ptr<vector<int>> new_vector()
{
    return make_shared<vector<int>>();
}

void read_sptr(shared_ptr<vector<int>> spv)
{
    int val;
    while (cin >> val)
        spv->push_back(val);
}

void print_sptr(shared_ptr<vector<int>> spv)
{
    for (auto& x : *spv)
        cout << x << "  ";
    cout << endl;
}

// 12.14
void func_connectin(destination& des)
{
    connection con = connect(&des);
    shared_ptr<connection> sh_con = shared_ptr<connection>(&con, end_connection);
}

// 12.15
void func_connection_lam(destination& des)
{
    connection con = connect(&des);
    auto fun = [](connection *con) {disconnect(*con); };
    shared_ptr<connection> sh_con = shared_ptr<connection>(&con,fun);
}

// 12.23
void strcat_t(const char* cstr1, const char* cstr2, char** str)
{
    if (!str) return;
    size_t sz = strlen(cstr1) + strlen(cstr2) + 2;
    *(str) = new char[sz];
    memcpy(*(str), cstr1, strlen(cstr1)+1);
    memcpy(*(str)+ strlen(*(str)), cstr2, strlen(cstr2)+1);
}

int main()
{
    // �ֲ�static�ڵ�һ��ʹ��ǰ���������ڳ������ʱ����
    // ��׼�ⶨ������������ָ�����͹���̬����Ķ���
    // ����Ŀǰѧϰ���ĳ��� ֻʹ�ù���̬�ڴ����ջ�ڴ� ��̬�ڴ汣��ֲ�static����������static�����Լ�
    // �κζ����ں�����֮��ı���
    // ջ�ڴ�ͬ�����溯��֮�ڵķ�static����
    // �����������ڴ���������ɱ������Զ�����������
    
    // ���˾�̬�ڴ��ջ�ڴ� ÿ������ӵ��һ���ڴ�� �ⲿ���ڴ汻��Ϊ���ɿռ���(heap)
    // �����ö����洢��̬����Ķ��� ��̬������������ɳ������
    
    // �±�׼���ṩ����������ָ���������ڹ���ײ�ָ��ķ�ʽ
    // shared_ptr������ָ��ָ��ͬһ������ unique_ptr���ռ��ָ��Ķ���
    // ��׼�⻹������һ����Ϊweak_ptr�İ����� ����һ�������� ָ��shared_ptr������Ķ���
    // ͷ�ļ� <memory>
    shared_ptr<string> p1;
    shared_ptr<list<int>> p2; // Ĭ�ϳ�ʼ��������ָ���б�����һ����ָ��
    if (p1 && p1->empty())
        *p1 = "hi";
    // ֧�ֵĲ���
    // ��ʼ���� shared_ptr<T> sp; unique_ptr<T> up;
    // p.get() ����p�����ָ�룬������ָ���ͷ��������û���ص�ָ����ָ��Ķ���Ҳ����ʧ��
    // swap(p,q) p.swap(q) ����p��q�е�ָ��
    // make_shared<T>(args) ����һ��shared_ptr��ָ������T ֵΪargs��ʼ��
    // shared_ptr<T>p(q) p��q�Ŀ���������q�еļ�������q�е�ָ��������ת��ΪT*
    // p=q p,q����shared_ptr �������ָ����Ի���ת�� ��ݼ�p�����ü��� ����q�����ü�������p�����ü���Ϊ0����������ԭ�ڴ��ͷ�
    // p.unique() ����Ϊ1 ��true �� false
    // p.use_count() ������p������������ָ�������
    shared_ptr<int> p3 = make_shared<int>(55);
    shared_ptr<string> p4 = make_shared<string>(10, '9');
    // ��ָ��һ����������һ��shared_ptr������ʱ��shared_ptr���Զ����ٴ˶���ͨ��������������
    // ��������һ�������ͷŶ������������Դ���ͷ��ڴ棩 ������ 1.���ٶ��� 2.�ͷ��ڴ�

    // ʹ�ö�̬�ڴ��ԭ��
    // 1.����֪���Լ�Ҫ���ö��ٶ��������ࣩ
    // 2.����֪����������׼ȷ����
    // 3.������Ҫ�ڶԸ�����乲������
    
    // ֱ�ӹ����ڴ� new delete
    // ���ڶ������Լ��Ĺ��캯������������˵��Ҫ��ֵ��ʼ����û������ģ����ܲ���ʲô��ʽ�����󶼻�ͨ��
    // Ĭ�Ϲ��캯������ʼ��������������������˵������ͱȽϴ��� ֵ��ʼ�����������Ͷ����������ö����ֵ
    // ����Ĭ�ϳ�ʼ���Ķ����ֵ����δ����� ����������Щ�����ڱ������ȳɵ�Ĭ�Ϲ��캯�����������ͳ�Ա ��
    // ������������δ����ʼ�� ��ô���ǵ�ֵ��δ�����
    // �����������ʼ����ͬ��ԭ�򣬶Զ�̬����Ķ�����г�ʼ��ͨ���Ǹ�������
    // ��������ṩ��һ�����Ű�Χ�ĳ�ʼ�������Ϳ���ʹ��auto�Ӵ˳�ʼ�������ƶ�������Ҫ����Ķ��������
    auto p5 = new auto(17); // p5�Ʋ�Ϊint���� ֻ�е������н��е�һ��ʼ����ʱ�ſ���ʹ��auto
    delete p5;
    // ��new����const�����ǺϷ���
    const int* pci = new const int(22);
    delete pci;
    // �ڴ�ľ�ʱ  newʧ��  ���׳�bad_alloc�쳣  ���ǿ��Ըı�new��ʹ�÷�ʽ��ֹ���׳��쳣
    int* p6 = new (nothrow) int(1024); // ��λnew
    delete p6;
    // �ͷŶ�̬�ڴ� delete
    // �������� 1.���ٸ�����ָ��ָ��Ķ��� 2.�ͷŶ�Ӧ���ڴ�
    // ��̬�����������ֱ�����ͷ�ʱΪֹ 
    // ������ָ��(����������ָ��)����Ķ�̬�ڴ��ڱ���ʽ�ͷ�ǰһֱ������ڡ�
    int* p7 = nullptr;
    delete p7;// deleteһ����ָ������û�д����
    
    // delete֮��Ҫ����ָ�� ��Ȼ����delete��һ��ָ�룬ָ��ֵ�ͱ�Ϊ��Ч�����ںܶ������
    // ָ����Ȼ�����ţ��Ѿ��ͷ��˵ģ���̬�ڴ��ַ��delete֮��ָ��ͱ�Ϊ�� ����ָ��
    // �� ָ��һ�������������ݶ��������Ѿ���Ч���ڴ��ָ��
    vector<int>* pv = Test_126_1();
    if (!pv)
    {
        cout << "run out of memory" << endl;
        return -1;
    }
    Test_126_2(pv);
    Test_126_3(pv);

    delete pv;
    pv = nullptr;
	// shared_ptr��new��ʹ��
	// ��������new���ص�ָ���ʼ������ָ�룺
	shared_ptr<int> p8(new int(77)); 
	// ��Ϊ����ָ��Ĺ��캯����explicit�ģ�������ǲ��ܽ�һ�����õ�ָ����ʽת��Ϊһ������ָ�룬����ʹ��ֱ�ӳ�ʼ����ʽ
	// shared_ptr<int> p9 = new int(88); ���־Ͳ���ȷ ��ʵ�Ƿ�������ʽת��
	// ͬ��  һ������shared_ptr�ĺ����������䷵���������ʽת��һ����ָͨ��

    // Ĭ������£�һ��������ʼ������ָ�����ָͨ�����ָ��̬�ڴ棬����ָ��Ĭ��ʹ��delete�ͷ�
    // ���������Ķ��󡣿��Խ�����ָ��󶨵�һ��ָ��������Դ��ָ���ϣ�������Ҫ�ṩ�Լ��Ĳ�������delete
    // shared_ptr<T> p(q) shared_ptr<T> p(unique_ptr) shared_ptr<T> p(q,d) shared_ptr<T> p(p2,d)
    // p.reset() p.reset(q) p.reset(q,d) 

    // p.get()����һ������ָ��
    // �˺�����Ϊ������һ���������Ƶģ�������Ҫ����ʹ������ָ��Ĵ��봫��һ������ָ�롣
    // ʹ��get���ص�ָ��Ĵ��벻��delete��ָ�롣

    // �����new��delete֮�䷢�����쳣�����˳����쳣δ������ ��new��������Դ�Ͳ����ͷ�
    // ��������ָ�����ֲ�����һ�� �ᱻ�ͷ�

    // ����ָ������ṩ�Զ�̬������ڴ氲ȫ���ַ���Ĺ������⽨������ȷʹ�õ�ǰ���¡�
    // Ϊ����ȷʹ������ָ�룬���Ǳ�����һЩ�����淶��
    // 1.��ʹ����ͬ������ָ���ʼ������reset���������ָ��
    // 2.��delete get() ���ص�ָ��
    // 3.ʹ����get()���ص�ָ�룬��ס�����һ����Ӧ������ָ�����ٺ����ָ��ͱ�Ϊ��Ч��
    // 4.���ʹ������ָ��������Դ����new������ڴ棬��ס���ݸ���һ��ɾ����
    
    // unique_ptr ��shared_ptr��ͬ��unique_ptrû������make_shared�ı�׼�⺯�� ֻ�ܰ�new���ص�ֵ
    // unique_ptr<T> u1;  unique_ptr<T, D> u2; DΪ�ͷŷ���  unique_ptr<T, D> u(d); ��ָ��
    // u.release() ����ָ�����Ȩ ����ָ�� ����u�ÿ� 
    
    // ���ܿ���unique_ptr�Ĺ�����һ�����⣬���Կ������߸�ֵһ����Ҫ�����ٵ�unique_ptr ���纯������ֵ
    unique_ptr<int> u1(new int(15));
    // weak_ptr ָ��һ����shared_ptr����Ķ���

    // ��̬���� new allocator������ͳ�ʼ�����룩
    int* pa = new int[30] {1,2,3,4,5,6,7};
    // ��̬���鲢������������  ����һ��ָ������Ԫ�ص�ָ��
    // ��������new����һ����СΪ0������ʱ��new����һ���Ϸ��ķǿ�ָ��,������β��ָ��
    delete[]pa;
    // �����е�Ԫ�ذ��������� Ȼ���ͷ��ڴ�

    // ��׼���ṩ��һ�����Թ���new����������unique_ptr
    unique_ptr<int[]> up( new int[10]());
    up.release();// �Զ�����delete[]
    //
    shared_ptr<int[]> ups(new int[10], [](int* p) {delete[]p; });
    // ����Ԫ��
    for (size_t i = 0; i < 10; ++i)
        *(ups.get() + i) = i;
    ups.reset(); // ��û��lambda���ʽ ������delete p ��Ϊδ����
    // 12.23 ��֤
    const char* cp1 = { "I love " };
    const char* cp2 = { "program" };
    char* cp3 = nullptr;
    strcat_t(cp1, cp2, &cp3);
    cout << cp3 << endl;
    delete cp3;

    // allocator�� memory ���ڴ����͹���������
    allocator<string> alloc; // ���Է���string��allocator����
    auto const p = alloc.allocate(100); // ����100��δ��ʼ����string
    // allocator�Ĳ��� 
    // allocator<T> a 
    // a.allocate(n) 
    // a.deallocate(p,n) �ͷŴ�ָ��p�е�ַ��ʼ���ڴ棬����ڴ汣����n������ΪT�Ķ���p������allocate
    // ���ص�ָ�룬n������p����ʱ��Ҫ��ĵĴ�С ����ǰ�����ÿ���������deatroy
    // a.construct(p,args) ��args����һ������
    // a.destroy(p) ��pָ��Ķ���ִ����������
    auto q = p;
    alloc.construct(q++);
    alloc.construct(q++, 10, 'c');
    alloc.construct(q++, "program");
    //
    while (q != p)
        alloc.destroy(--q);
    alloc.deallocate(p, 100);
    // ��׼��Ϊallocator���������������㷨 ������δ��ʼ�����ڴ��д�������
    // uninitialized_copy(b,e,b2) uninitialized_copy_n(b,n,b2)
    // ������b->e ������b2ָ���Ϊ�����ԭʼ�ڴ�----�ӵ�����b��ʼ������n��Ԫ��ȥb2ָ���Ϊ������ڴ�
    // uninitialized_fill(b,e,t) uninitialized_fill_n(b,n,t)
    // ������b->e��ԭʼ�ڴ棩 �������󣬾�Ϊt�Ŀ���----�ӵ�����b��ʼ������n�����󣬶�Ϊt

    // ʹ�ñ�׼�⣺�ı���ѯ����
}
