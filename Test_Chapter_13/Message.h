#ifndef __MESSAGE_H__
#define __MESSAGE_H__

class Folder;

class Message
{
    friend class Folder;
    friend void swap(Message&, Message&);
public:
    // folders被隐式初始化为空集合
    explicit Message(const std::string& str = ""):contents(str){}
    // 拷贝控制成员  用来管理指向本Message的指针
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();
    // 从给定Folders集合中添加/删除本Message
    void save(Folder&);
    void remove(Folder&);
private:
    std::string contents;
    std::set<Folder*> folders; // 本Message指向的Folder集合
    // 拷贝构造函数、拷贝赋值运算符和析构函数使用的工具函数
    // 本Message添加到指定的Folder中
    void add_to_Folders(const Message&);
    // 从folders中的每个Folder中删除本Message
    void remove_from_Folders();
    void addFldr(Folder* f) { folders.insert(f); }
};
#endif // ifndef __MESSAGE_H__


