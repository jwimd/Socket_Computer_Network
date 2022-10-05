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

#include <strings.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>

#include <netinet/in.h>

#include "type.h"
#include "thread.h"

class Server
{
public:
    Server() = delete;
    Server(int32_t _domain, int32_t _type, int32_t _protocol, std::string _server_addr, std::string _server_port, int32_t _backlog);
    ~Server();

    inline bool_t is_error() { return this->error_sign; }

    void main_thread_run(int32_t _file_description);

protected:
    int32_t domain;   //协议簇
    int32_t type;     //套接字类型
    int32_t protocol; //指定协议
    int32_t backlog;  //最多允许的并发数

    std::string server_addr; //服务地址
    std::string server_port; //端口

    sockaddr_in sock_addr;    // sockaddr结构体的指针'

    std::shared_ptr<Server_Thread> main_thread;                   //主线程
    std::vector<std::shared_ptr<Server_Thread>> sub_thread_group; //子线程

    bool_t error_sign; //指示Server类出现问题的标志

    void main_thread_process();
};
