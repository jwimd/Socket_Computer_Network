/***
 * @Description: server类实现
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-03 20:33:10
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-04 10:19:00
 * @FilePath: /Socket_Computer_Network/src/server/server.cpp
 */
#include "server.h"

/***
 * @Description: Server类可使用的构造函数，执行初始化socket
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @param {int32_t} _domain
 * @param {int32_t} _type
 * @param {int32_t} _protocol
 * @param {string} _server_addr
 * @param {string} _server_port
 * @param {int32_t} _backlog
 * @return {*}
 */
Server::Server(int32_t _domain, int32_t _type, int32_t _protocol, std::string _server_addr, std::string _server_port, int32_t _backlog) : domain(_domain), type(_type), protocol(_protocol), server_addr(_server_addr), server_port(_server_port), backlog(_backlog)
{
    this->error_sign = false;

    int32_t file_description = -1;

    if ((file_description = socket(this->domain, this->type, this->protocol)) == -1) //生成socket句柄
    {
        this->error_sign = true;
        return;
    }

    this->sock_addr.sin_family = AF_INET;                                   // ipv4地址类型
    this->sock_addr.sin_addr.s_addr = inet_addr(this->server_addr.c_str()); //绑定地址
    this->sock_addr.sin_port = htons(stoi(this->server_port));              //绑定端口

    if (bind(file_description, (struct sockaddr *)&this->sock_addr, sizeof(struct sockaddr)) == -1) //绑定端口号和地址
    {
        this->error_sign = true;
        return;
    }

    if (listen(file_description, this->backlog) == -1)
    {
        this->error_sign = true;
        return;
    }

    this->main_thread_run(file_description);

    return;
}

/***
 * @Description: 启动服务端主线程
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @param {int32_t} _file_description
 * @return {*}
 */
void Server::main_thread_run(int32_t _file_description)
{
    this->main_thread = std::shared_ptr<Server_Thread>(new Server_Thread(_file_description)); //创建服务器线程类
    this->main_thread->run(*this, &Server::main_thread_process);                              //启动线程
    this->main_thread->join();                                                                //挂起主线程
    return;
}

/***
 * @Description: 主线程执行的函数
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
void Server::main_thread_process()
{
    while (1)
    {
        int32_t client_file_description = -1;
        struct sockaddr_in client_addr;
        socklen_t sock_len = sizeof(client_addr);

        if (client_file_description = accept(this->main_thread->get_file_description(), (sockaddr *)&client_addr, &sock_len) != -1) // accept接受客户端请求
        {
            std::cout << "get require!" << std::endl;
        }
    }

    return;
}

/***
 * @Description: Server类析构函数
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
Server::~Server()
{
    return;
}