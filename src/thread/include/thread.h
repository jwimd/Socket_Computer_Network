/***
 * @Description:线程类定义
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-05 10:12:16
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-05 10:12:21
 * @FilePath: /Socket_Computer_Network/thread/include/thread.h
 */
#pragma once

#include <iostream>
#include <thread>
#include <memory>
#include <functional>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <termios.h>

#include "type.h"

#define MSG_LEN 200

class Server;
class Client;

typedef void (Server::*server_void_func)();
typedef void (Client::*client_void_func)();

class Thread
{
public:
    Thread() { return; };
    virtual ~Thread() = 0; //抽象父基类

    void run(Server &_server, server_void_func _func);
    void run(Client &_client, client_void_func _func);

    void join();

    inline std::shared_ptr<std::thread> get_thread() { return this->p_thread; }

protected:
    std::shared_ptr<std::thread> p_thread;
};

class Server_Thread : virtual public Thread
{
public:
    Server_Thread(int32_t _file_description);
    ~Server_Thread();

    int32_t get_file_description() { return this->file_description; }

protected:
    int32_t file_description; // 该线程所控制的socket文件描述符
};

class Client_Thread : virtual public Thread
{
public:
    Client_Thread(int32_t _file_description);
    ~Client_Thread();

    int32_t get_file_description() { return this->file_description; }

protected:
    int32_t file_description; // 该线程所控制的socket文件描述符
};

bool kbhit();