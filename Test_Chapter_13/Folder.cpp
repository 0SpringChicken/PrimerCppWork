#include "stdafx.h"

void Folder::add_to_msg(const Folder& f)
{
    for (auto m : f.msgs)
        m->addFldr(this);
}

void Folder::remove_from_msg()
{
    while (!msgs.empty())
        (*msgs.begin())->remove(*this);
}

Folder::Folder(const Folder& f) :msgs(f.msgs)
{
    add_to_msg(f);
}

Folder& Folder::operator=(const Folder& f)
{
    remove_from_msg();
    msgs = f.msgs;
    add_to_msg(f);
    return *this;
}

Folder::~Folder()
{
    remove_from_msg();
}