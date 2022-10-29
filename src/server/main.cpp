/***
 * @Descripttion:
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-03 21:30:48
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-04 22:02:44
 * @FilePath: /Socket_Computer_Network/src/server/main.cpp
 */
/***
 * @Description: 服务器端主函数
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-03 21:30:48
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-04 10:12:25
 * @FilePath: /Socket_Computer_Network/src/server/main.cpp
 */

#include "server.h"

/***
 * @Description:服务端主函数
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @param {int32_t} argc
 * @param {char_t} *argv
 * @return {int32_t} 0
 */
int32_t main(int32_t argc, char_t *argv[])
{
    system("clear");

    Server my_server(AF_INET, SOCK_STREAM, 0, "127.0.0.1", "1205", 5); //启动socket服务
    Server *p_server = &my_server;

    if (p_server->is_error())
    {
        std::cout << "套接字创建异常!!" << std::endl;
        std::cout << strerror(errno) << std::endl;
        return 0;
    }

    return 0;
}