/***
 * @Description: Server类头文件
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-03 21:19:15
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-04 10:19:56
 * @FilePath: /Socket_Computer_Network/src/server/include/server.h
 */

#pragma once

#include "type.h"

class Server
{
public:
    Server() = delete;
    Server(int32_t _famliy, int32_t _type, int32_t protocol);
    ~Server();

protected:
    int32_t famliy;     //协议簇
    int32_t type;       //套接字类型
    int32_t protocol;   //指定协议
};
