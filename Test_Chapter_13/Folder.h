#ifndef __FOLDER_H__
#define __FOLDER_H__

class Message;

class Folder
{
    friend class Message;
public:
    void addMsg(Message*);
    void remMsg(Message*);
private:
    std::set<Message*> msgs;
    void add_to_msg(const Folder&);
    void remove_from_msg();
};

inline
void Folder::addMsg(Message* m)
{
    msgs.insert(m);
}

inline
void Folder::remMsg(Message* m)
{
    msgs.erase(m);
}
#endif // ifndef __FOLDER_H__


