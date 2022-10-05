/***
 * @Description:线程类定义
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-05 10:12:16
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-05 10:12:21
 * @FilePath: /Socket_Computer_Network/thread/include/thread.h
 */
#include <thread>

class Thread
{
public:
    Thread() = delete;
    virtual ~Thread() = 0; //抽象父基类

    std::thread* get_thread() { return &this->thread; }

protected:
    std::thread thread;
};

class Server_Thread: virtual public Thread
{
public:
    

protected:

};