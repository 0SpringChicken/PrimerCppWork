#include "Screen.h"

char Screen::get(pos r, pos c) const
{
    pos row = r * width;
    return contents[row + c];
}


Screen& Screen::move(pos r, pos c)
{
    pos row = r * width;    // 计算行内位置
    cursor = row + c;       // 将光标移动到指定的列
    return *this;           // 左值形式返回对象
}


Screen& Screen::Set(char ch)
{
    contents[cursor] = ch;
    return *this;
}


Screen& Screen::Set(pos r, pos col, char ch)
{
    contents[r * width + col] = ch;
    return *this;
}

////////////////////////////////////////////////////////
void Windows_mgr::clear()
{
    Screen myScreen(10, 20, 'X');
    std::cout << "before clear The Screen show:" << std::endl;
    myScreen.display(std::cout);
    myScreen.contents.clear();
    std::cout << "after clear The Screen show:" << std::endl;
    myScreen.display(std::cout);
}
