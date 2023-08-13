#pragma once

//extern struct destination;
//extern struct connection;

struct destination {}; // 目的地址
struct connection {}; // 连接信息

extern connection connect(destination*);
extern void disconnect(connection&);
extern void end_connection(connection*);