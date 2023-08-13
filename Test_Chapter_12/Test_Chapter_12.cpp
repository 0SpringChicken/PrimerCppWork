// Test_Chapter_12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// 十二章 动态内存 20230808 Tuesday

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
    // 局部static在第一次使用前被创建，在程序结束时销毁
    // 标准库定义了两个智能指针类型管理动态分配的对象
    // 截至目前学习到的程序 只使用过静态内存或者栈内存 静态内存保存局部static变量，类中static变量以及
    // 任何定义在函数体之外的变量
    // 栈内存同来保存函数之内的非static对象
    // 以上两部分内存的中内容由编译器自动创建和销毁
    
    // 除了静态内存和栈内存 每个程序还拥有一个内存池 这部分内存被称为自由空间或堆(heap)
    // 程序用堆来存储动态分配的对象 动态对象的生存期由程序控制
    
    // 新标准库提供的两款智能指针区别在于管理底层指针的方式
    // shared_ptr允许多个指针指向同一个对象 unique_ptr则独占所指向的对象
    // 标准库还定义了一个名为weak_ptr的伴随类 它是一种弱引用 指向shared_ptr所管理的对象
    // 头文件 <memory>
    shared_ptr<string> p1;
    shared_ptr<list<int>> p2; // 默认初始化的智能指针中保存着一个空指针
    if (p1 && p1->empty())
        *p1 = "hi";
    // 支持的操作
    // 初始化： shared_ptr<T> sp; unique_ptr<T> up;
    // p.get() 返回p保存的指针，若智能指针释放了其对象，没返回的指针所指向的对象也就消失了
    // swap(p,q) p.swap(q) 交换p和q中的指针
    // make_shared<T>(args) 构造一个shared_ptr，指向类型T 值为args初始化
    // shared_ptr<T>p(q) p是q的拷贝，递增q中的计数器，q中的指针必须可以转换为T*
    // p=q p,q都是shared_ptr 所保存的指针可以互相转换 会递减p的引用计数 递增q的引用计数，若p的引用计数为0，则将其管理的原内存释放
    // p.unique() 计数为1 则true 否 false
    // p.use_count() 返回与p共享对象的智能指针的数量
    shared_ptr<int> p3 = make_shared<int>(55);
    shared_ptr<string> p4 = make_shared<string>(10, '9');
    // 当指向一个对象的最后一个shared_ptr被销毁时，shared_ptr会自动销毁此对象，通过析构函数销毁
    // 析构函数一般用来释放对象所分配的资源（释放内存） 两步走 1.销毁对象 2.释放内存

    // 使用动态内存的原因：
    // 1.程序不知道自己要是用多少对象（容器类）
    // 2.程序不知道所需对象的准确类型
    // 3.程序需要在对个对象间共享数据
    
    // 直接管理内存 new delete
    // 对于定义了自己的构造函数的类类型来说，要求值初始化是没有意义的：不管采用什么形式，对象都会通过
    // 默认构造函数来初始化，但对于内置类型来说，差异就比较大了 值初始化的内置类型对象有这良好定义的值
    // 但是默认初始化的对象的值则是未定义的 对于类中那些依赖于编译器喝成的默认构造函数的内置类型成员 如
    // 果他们再内类未被初始化 那么他们的值是未定义的
    // 出于与变量初始化相同的原因，对动态分配的对象进行初始化通常是个好主意
    // 如果我们提供了一个括号包围的初始化器，就可以使用auto从此初始化器来推断我们想要分配的对象的类型
    auto p5 = new auto(17); // p5推测为int类型 只有当括号中仅有单一初始化器时才可以使用auto
    delete p5;
    // 用new分配const对象是合法的
    const int* pci = new const int(22);
    delete pci;
    // 内存耗尽时  new失败  会抛出bad_alloc异常  我们可以改变new的使用方式阻止其抛出异常
    int* p6 = new (nothrow) int(1024); // 定位new
    delete p6;
    // 释放动态内存 delete
    // 两步操作 1.销毁给定的指针指向的对象 2.释放对应的内存
    // 动态对象的生存期直到被释放时为止 
    // 由内置指针(而不是智能指针)管理的动态内存在被显式释放前一直都会存在。
    int* p7 = nullptr;
    delete p7;// delete一个空指针总是没有错误的
    
    // delete之后要重置指针 虽然我们delete了一个指针，指针值就变为无效，但在很多机器上
    // 指针仍然保存着（已经释放了的）动态内存地址，delete之后指针就变为了 空悬指针
    // 即 指向一块曾经保存数据对象但现在已经无效的内存的指针
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
	// shared_ptr和new合使用
	// 可以用用new返回的指针初始化智能指针：
	shared_ptr<int> p8(new int(77)); 
	// 因为智能指针的构造函数是explicit的，因此我们不能讲一个内置的指针隐式转换为一个智能指针，必须使用直接初始化形式
	// shared_ptr<int> p9 = new int(88); 这种就不正确 其实是发生了隐式转换
	// 同理  一个返回shared_ptr的函数不能再其返回语句中隐式转换一个普通指针

    // 默认情况下，一个用来初始化智能指针的普通指针必须指向动态内存，智能指针默认使用delete释放
    // 它所关联的对象。可以将智能指针绑定到一个指向其他资源的指针上，但是需要提供自己的操作代替delete
    // shared_ptr<T> p(q) shared_ptr<T> p(unique_ptr) shared_ptr<T> p(q,d) shared_ptr<T> p(p2,d)
    // p.reset() p.reset(q) p.reset(q,d) 

    // p.get()返回一个内置指针
    // 此函数是为了这样一种情况而设计的：我们需要向不能使用智能指针的代码传递一个内置指针。
    // 使用get返回的指针的代码不能delete此指针。

    // 如果再new和delete之间发生了异常函数退出且异常未被捕获 则new出来的资源就不会释放
    // 但是智能指针就像局部对象一样 会被释放

    // 智能指针可以提供对动态分配的内存安全而又方便的管理，但这建立在正确使用的前提下。
    // 为了正确使用智能指针，我们必须坚持一些基本规范：
    // 1.不使用相同的内置指针初始化（或reset）多个智能指针
    // 2.不delete get() 返回的指针
    // 3.使用了get()返回的指针，记住当最后一个对应的智能指针销毁后，你爹指针就变为无效了
    // 4.如果使用智能指针管理的资源不是new分配的内存，记住传递给其一个删除器
    
    // unique_ptr 与shared_ptr不同，unique_ptr没有类似make_shared的标准库函数 只能绑定new返回的值
    // unique_ptr<T> u1;  unique_ptr<T, D> u2; D为释放方法  unique_ptr<T, D> u(d); 空指针
    // u.release() 放弃指针控制权 返回指针 并将u置空 
    
    // 不能拷贝unique_ptr的规则有一个例外，可以拷贝或者赋值一个将要被销毁的unique_ptr 比如函数返回值
    unique_ptr<int> u1(new int(15));
    // weak_ptr 指向一个由shared_ptr管理的对象

    // 动态数组 new allocator（分配和初始化分离）
    int* pa = new int[30] {1,2,3,4,5,6,7};
    // 动态数组并不是数组类型  而是一个指向数组元素的指针
    // 当我们用new分配一个大小为0的数组时，new返回一个合法的非空指针,类似于尾后指针
    delete[]pa;
    // 数组中的元素按逆序销毁 然后释放内存

    // 标准库提供了一个可以管理new分配的数组的unique_ptr
    unique_ptr<int[]> up( new int[10]());
    up.release();// 自动调用delete[]
    //
    shared_ptr<int[]> ups(new int[10], [](int* p) {delete[]p; });
    // 访问元素
    for (size_t i = 0; i < 10; ++i)
        *(ups.get() + i) = i;
    ups.reset(); // 若没有lambda表达式 则会调用delete p 行为未定义
    // 12.23 验证
    const char* cp1 = { "I love " };
    const char* cp2 = { "program" };
    char* cp3 = nullptr;
    strcat_t(cp1, cp2, &cp3);
    cout << cp3 << endl;
    delete cp3;

    // allocator类 memory 将内存分配和构造对象分离
    allocator<string> alloc; // 可以分配string的allocator对象
    auto const p = alloc.allocate(100); // 分配100个未初始化的string
    // allocator的操作 
    // allocator<T> a 
    // a.allocate(n) 
    // a.deallocate(p,n) 释放从指针p中地址开始的内存，这块内存保存了n个类型为T的对象；p必须是allocate
    // 返回的指针，n必须是p创建时所要求的的大小 调用前必须对每个对象调用deatroy
    // a.construct(p,args) 用args构造一个对象
    // a.destroy(p) 对p指向的对象执行析构函数
    auto q = p;
    alloc.construct(q++);
    alloc.construct(q++, 10, 'c');
    alloc.construct(q++, "program");
    //
    while (q != p)
        alloc.destroy(--q);
    alloc.deallocate(p, 100);
    // 标准库为allocator定义了两个伴随算法 可以再未初始化的内存中创建对象
    // uninitialized_copy(b,e,b2) uninitialized_copy_n(b,n,b2)
    // 迭代器b->e 拷贝到b2指向的为构造的原始内存----从迭代器b开始，拷贝n个元素去b2指向的为构造的内存
    // uninitialized_fill(b,e,t) uninitialized_fill_n(b,n,t)
    // 迭代器b->e（原始内存） 创建对象，均为t的拷贝----从迭代器b开始，创建n个对象，都为t

    // 使用标准库：文本查询程序
}
