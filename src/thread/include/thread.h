/***
 * @Description:线程类定义
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-05 10:12:16
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-05 10:12:21
 * @FilePath: /Socket_Computer_Network/thread/include/thread.h
 */
#pragma once

#include <thread>
#include <memory>
#include <functional>

class Server;

typedef void (Server::*server_void_func)();

class Thread
{
public:
    Thread() = delete;
    virtual ~Thread() = 0; //抽象父基类

    void run(Server& _server, server_void_func _func);

    void join();

    inline std::shared_ptr<std::thread> get_thread() { return this->p_thread; }

protected:
    std::shared_ptr<std::thread> p_thread;
};

class Server_Thread: virtual public Thread
{
public:
    

protected:

};