/***
 * @Description:客户端的程序入口
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-03 20:34:07
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-04 10:14:37
 * @FilePath: /Socket_Computer_Network/src/client/main.cpp
 */

#include "type.h"
#include "client.h"

/***
 * @Descripttion: 客户端主函数
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @param {int32_t} argc
 * @param {char_t} *argv
 * @return {int32_t} 0
 */
int32_t main(int32_t argc, char_t *argv[])
{
    Client my_client(AF_INET, SOCK_STREAM, 0); //启动socket服务
    Client *p_client = &my_client;

    if (p_client->is_error())
    {
        std::cout << "套接字创建异常!" << std::endl;
        std::cout << strerror(errno) << std::endl;
        return 0;
    }

    return 0;
}