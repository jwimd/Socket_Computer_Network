/***
 * @Description:Thread及其子类实现
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-05 10:12:00
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-05 10:42:17
 * @FilePath: /Socket_Computer_Network/src/thread/thread.cpp
 */

#include "thread.h"

/***
 * @Description: 启动server线程
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
void Thread::run(Server &_server, server_void_func _func)
{
    this->p_thread = std::shared_ptr<std::thread>(new std::thread(std::bind(_func, &_server)));
    return;
}

/***
 * @Description: 启动client线程
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
void Thread::run(Client &_client, client_void_func _func)
{
    this->p_thread = std::shared_ptr<std::thread>(new std::thread(std::bind(_func, &_client)));
    return;
}

/***
 * @Description: 线程join
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
void Thread::join()
{
    this->p_thread->join();
    return;
}

/*** 
 * @Description: 纯虚函数体
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
Thread::~Thread()
{
    return;
}

/*** 
 * @Description: 
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @param {int32_t} _file_description
 * @return {*}
 */
Server_Thread::Server_Thread(int32_t _file_description) : file_description(_file_description)
{
    return;
}

/*** 
 * @Description: 
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
Server_Thread::~Server_Thread()
{
    return;
}

/*** 
 * @Description: 
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @param {int32_t} _file_description
 * @return {*}
 */
Client_Thread::Client_Thread(int32_t _file_description) : file_description(_file_description)
{
    return;
}

/*** 
 * @Description: 
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
Client_Thread::~Client_Thread()
{
    return;
}