#include "stdafx.h"

using namespace std;

connection connect(destination* des)
{
    cout << "链接已打开" << endl;
    return connection();
}

void disconnect(connection& con)
{
    cout << "关闭连接" << endl;
}

void end_connection(connection* p)
{
    disconnect(*p);
    cout << "连接已释放" << endl;
}