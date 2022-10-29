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
#include <map>
#include <queue>
#include <mutex>

#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>

#include <netinet/in.h>

#include "type.h"
#include "thread.h"

#include "data.h"

#define LIST_WIDTH 30

class Client
{
public:
    Client() = delete;
    Client(int32_t _domain, int32_t _type, int32_t _protocol);
    ~Client();

    inline bool_t is_error() { return this->error_sign; }

protected:
    int32_t domain;   //协议簇
    int32_t type;     //套接字类型
    int32_t protocol; //指定协议

    int32_t file_description; //文件描述符
    int32_t con_file_description;

    std::string server_addr; //服务地址
    std::string server_port; //端口

    sockaddr_in sock_addr; // sockaddr结构体的指针

    bool_t is_connected; //是否与服务端建立连接

    std::shared_ptr<Client_Thread> main_thread;                                 //主线程
    std::map<std::thread::id, std::shared_ptr<Client_Thread>> sub_thread_group; //子线程

    bool_t error_sign; //指示Client类出现问题的标志

    std::queue<std::string> message_quene; //通信队列
    std::mutex message_quene_mutex;        //线程锁

    std::thread::id connent_thread_id; //接受数据包的线程id

    bool_t close_sign;

    void main_thread_run(int32_t _file_description);

    void main_thread_process();

    void connect_to_server();

    void client_receive_process();

    void print_process();

    void meum_print();

    void close_connent();
};