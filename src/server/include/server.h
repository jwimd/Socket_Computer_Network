/***
 * @Description: Server类头文件
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-03 21:19:15
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-04 10:19:56
 * @FilePath: /Socket_Computer_Network/src/server/include/server.h
 */

#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <map>
#include <queue>
#include <mutex>

#include <strings.h>
#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>

#include <netinet/in.h>

#include "type.h"
#include "thread.h"

#include "data.h"

class Server
{
public:
    Server() = delete;
    Server(int32_t _domain, int32_t _type, int32_t _protocol, std::string _server_addr, std::string _server_port, int32_t _backlog);
    ~Server();

    inline bool_t is_error() { return this->error_sign; }

protected:
    int32_t domain;   //协议簇
    int32_t type;     //套接字类型
    int32_t protocol; //指定协议
    int32_t backlog;  //最多允许的并发数

    int32_t file_description; //文件描述符

    std::string server_addr; //服务地址
    std::string server_port; //端口

    sockaddr_in sock_addr; // sockaddr结构体的指针'

    std::shared_ptr<Server_Thread> main_thread;                                 //主线程
    std::map<std::thread::id, std::shared_ptr<Server_Thread>> sub_thread_group; //子线程

    std::map<std::thread::id, int32_t> client_fd;
    std::map<std::thread::id, sockaddr_in> client_addr;
    std::mutex client_info_lock;        //线程锁

    std::queue<std::string> message_quene; //通信队列
    std::mutex message_quene_mutex;        //线程锁

    bool_t error_sign; //指示Server类出现问题的标志

    void main_thread_run(int32_t _file_description);

    void main_thread_process();

    void server_sub_process();
};
