/***
 * @Description:Client类实现
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-05 13:48:10
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-05 13:48:17
 * @FilePath: /Socket_Computer_Network/src/client/client.cpp
 */

#include "client.h"

/***
 * @Description: Client类可使用的构造函数，执行初始化socket
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
Client::Client(int32_t _domain, int32_t _type, int32_t _protocol, std::string _client_addr, std::string _client_port, int32_t _backlog) : domain(_domain), type(_type), protocol(_protocol)
{
    this->error_sign = false;

    int32_t file_description = -1;

    if ((file_description = socket(this->domain, this->type, this->protocol)) == -1) //生成socket句柄
    {
        this->error_sign = true;
        return;
    }

    this->is_connected = false;

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
void Client::main_thread_run(int32_t _file_description)
{
    this->main_thread = std::shared_ptr<Client_Thread>(new Client_Thread(_file_description)); //创建服务器线程类
    this->main_thread->run(*this, &Client::main_thread_process);                              //启动线程
    this->main_thread->join();                                                                //挂起主线程
    return;
}

/***
 * @Description: 主线程执行的函数
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
void Client::main_thread_process()
{
    while (1)
    {
        system("cls"); //清空输出

        if (this->is_connected)
        {
            std::cout << "当前状态：未连接服务端" << std::endl;
            std::cout << "操作:" << std::endl;
            std::cout << "[1] 连接服务端" << std::endl;
            std::cout << "[2] 断开连接" << std::endl;
            std::cout << "[3] 获取时间" << std::endl;
            std::cout << "[4] 获取名字" << std::endl;
            std::cout << "[5] 获取客户端列表" << std::endl;
            std::cout << "[6] 发送消息" << std::endl;
            std::cout << "[7] 退出客户端" << std::endl;

            int32_t opera_code = getchar() - '0';

            switch (opera_code)
            {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;

            default:
                std::cout << "未定义的输入！" << std::endl;
                break;
            }
        }

        else
        {
            std::cout << "当前状态：未连接服务端" << std::endl;
            std::cout << "操作:" << std::endl;
            std::cout << "[1] 连接服务端" << std::endl;
            std::cout << "[2] 退出客户端" << std::endl;

            char_t opera_code = getchar();

        }
    }

    return;
}

/***
 * @Description: Client类析构函数
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
Client::~Client()
{
    return;
}