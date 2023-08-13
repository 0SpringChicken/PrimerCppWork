#include "stdafx.h"

void Message::save(Folder& f)
{
    folders.emplace(&f);
    f.addMsg(this);
}

void Message::remove(Folder& f)
{
    folders.erase(&f);
    f.remMsg(this);
}

void Message::add_to_Folders(const Message& m)
{
    for (auto f : m.folders)
        f->addMsg(this);
}

Message::Message(const Message& m):contents(m.contents),folders(m.folders)
{
    add_to_Folders(m);
}

void Message::remove_from_Folders()
{
    for (auto f : folders)
        f->remMsg(this);
}

Message::~Message()
{
    remove_from_Folders();
}

Message& Message::operator=(const Message& m)
{
    remove_from_Folders();
    folders = m.folders;
    contents = m.contents;
    add_to_Folders(m);
    return *this;
}

void swap(Message& lhs, Message& rhs)
{
    using std::swap;
    for (auto x : lhs.folders)
        x->remMsg(&lhs);
    for (auto x : rhs.folders)
        x->remMsg(&rhs);

    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);

    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}