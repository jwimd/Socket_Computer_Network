/***
 * @Descripttion:
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-03 20:33:10
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-04 22:00:26
 * @FilePath: /Socket_Computer_Network/src/server/server.cpp
 */
/***
 * @Description: server类实现
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-03 20:33:10
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-04 10:19:00
 * @FilePath: /Socket_Computer_Network/src/server/server.cpp
 */

#include <iostream>
#include <string>

#include <strings.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>

#include "server.h"
#include "type.h"

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

    if ((this->file_description = socket(this->domain, this->type, this->protocol)) == -1) //生成socket句柄
    {
        this->error_sign = true;
        return;
    }

    bzero(&this->sock_addr, sizeof(this->sock_addr));                       //清空结构体
    this->sock_addr.sin_family = AF_INET;                                   // ipv4地址类型
    this->sock_addr.sin_addr.s_addr = inet_addr(this->server_addr.c_str()); //绑定地址
    this->sock_addr.sin_port = htons(stoi(this->server_port));              //绑定端口

    if (bind(this->file_description, (struct sockaddr *)&this->sock_addr, sizeof(struct sockaddr)) == -1) //绑定端口号和地址
    {
        this->error_sign = true;
        return;
    }

    if (listen(this->file_description, this->backlog) == -1)
    {
        this->error_sign = true;
        return;
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