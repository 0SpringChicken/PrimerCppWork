#pragma once

//extern struct destination;
//extern struct connection;

struct destination {}; // Ŀ�ĵ�ַ
struct connection {}; // ������Ϣ

extern connection connect(destination*);
extern void disconnect(connection&);
extern void end_connection(connection*);