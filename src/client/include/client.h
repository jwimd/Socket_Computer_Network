/***
 * @Description:client类定义
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-05 11:29:13
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-05 11:29:42
 * @FilePath: /Socket_Computer_Network/src/client/include/client.h
 */

#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <strings.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>

#include <netinet/in.h>

#include "type.h"
#include "thread.h"

class Client
{
public:
    Client() = delete;
    Client(int32_t _domain, int32_t _type, int32_t _protocol, std::string _client_addr, std::string _client_port, int32_t _backlog);
    ~Client();

    inline bool_t is_error() { return this->error_sign; }

    void main_thread_run(int32_t _file_description);

protected:
    int32_t domain;   //协议簇
    int32_t type;     //套接字类型
    int32_t protocol; //指定协议

    std::shared_ptr<Client_Thread> main_thread;                   //主线程
    std::vector<std::shared_ptr<Client_Thread>> sub_thread_group; //子线程

    bool_t error_sign; //指示Client类出现问题的标志

    void main_thread_process();
};