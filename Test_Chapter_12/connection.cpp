#include "stdafx.h"

using namespace std;

connection connect(destination* des)
{
    cout << "�����Ѵ�" << endl;
    return connection();
}

void disconnect(connection& con)
{
    cout << "�ر�����" << endl;
}

void end_connection(connection* p)
{
    disconnect(*p);
    cout << "�������ͷ�" << endl;
}