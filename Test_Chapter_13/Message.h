#ifndef __MESSAGE_H__
#define __MESSAGE_H__

class Folder;

class Message
{
    friend class Folder;
    friend void swap(Message&, Message&);
public:
    // folders����ʽ��ʼ��Ϊ�ռ���
    explicit Message(const std::string& str = ""):contents(str){}
    // �������Ƴ�Ա  ��������ָ��Message��ָ��
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();
    // �Ӹ���Folders���������/ɾ����Message
    void save(Folder&);
    void remove(Folder&);
private:
    std::string contents;
    std::set<Folder*> folders; // ��Messageָ���Folder����
    // �������캯����������ֵ���������������ʹ�õĹ��ߺ���
    // ��Message��ӵ�ָ����Folder��
    void add_to_Folders(const Message&);
    // ��folders�е�ÿ��Folder��ɾ����Message
    void remove_from_Folders();
    void addFldr(Folder* f) { folders.insert(f); }
};
#endif // ifndef __MESSAGE_H__


