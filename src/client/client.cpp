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
Client::Client(int32_t _domain, int32_t _type, int32_t _protocol) : domain(_domain), type(_type), protocol(_protocol)
{
    this->error_sign = false;

    int32_t _file_description = -1;

    if ((_file_description = socket(this->domain, this->type, this->protocol)) == -1) //生成socket句柄
    {
        this->error_sign = true;
        return;
    }

    this->file_description = _file_description;

    this->server_addr = "";
    this->server_port = "";

    this->is_connected = false;

    this->main_thread_run(_file_description);

    return;
}

/***
 * @Description: 启动客户端主线程
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @param {int32_t} _file_description
 * @return {*}
 */
void Client::main_thread_run(int32_t _file_description)
{
    this->main_thread = std::shared_ptr<Client_Thread>(new Client_Thread(_file_description)); //创建客户端线程类
    this->main_thread->run(*this, &Client::main_thread_process);                              //启动线程
    this->main_thread->join();                                                                //阻塞主线程
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
    // std::shared_ptr<Client_Thread> new_thread(new Client_Thread(this->file_description)); //创建子线程
    // new_thread->run(*this, &Client::print_process);
    // this->sub_thread_group[new_thread->get_thread()->get_id()] = new_thread; //写入类中

    this->meum_print();

    while (1)
    {

        if (this->is_connected)
        {

            if (kbhit())
            {
                system("clear");

                int32_t _opera_code = 0;
                _opera_code = fgetc(stdin) - '0';

                switch (_opera_code)
                {
                case 1:
                    break;
                case 2:
                    this->close_connent();
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
                    this->meum_print();
                    break;
                }
            }
        }

        else
        {
            if (kbhit())
            {
                system("clear");

                int32_t _opera_code = 0;
                _opera_code = fgetc(stdin) - '0';

                switch (_opera_code)
                {
                case 1:
                    std::cout << "连接服务端" << std::endl;
                    std::cout << std::endl;

                    std::cout << "输入服务端地址：" << std::endl;
                    std::cin >> this->server_addr;
                    std::cout << "输入服务端端口：" << std::endl;
                    std::cin >> this->server_port;

                    this->connect_to_server();
                    break;
                case 2:
                    break;

                default:
                    this->meum_print();
                    break;
                }
            }
        }

        this->message_quene_mutex.lock();
        while (this->message_quene.size() > 0)
        {
            std::string _str = this->message_quene.front();
            std::cout << _str << std::endl;
            this->message_quene.pop();
            sleep(SLEEP_TIME);
        }
        this->message_quene_mutex.unlock();

        if (this->error_sign)
            break;

        // sleep(SLEEP_TIME);
    }

    return;
}

/***
 * @Description: 客户端连接服务端
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
void Client::connect_to_server()
{
    this->sock_addr.sin_family = AF_INET;                                   // ipv4地址类型
    this->sock_addr.sin_addr.s_addr = inet_addr(this->server_addr.c_str()); //绑定地址
    this->sock_addr.sin_port = htons(stoi(this->server_port));              //绑定端口

    if (connect(this->main_thread->get_file_description(), (struct sockaddr *)&this->sock_addr, sizeof(struct sockaddr)) == -1)
    {
        std::cout << "连接错误" << std::endl;
        std::cout << strerror(errno) << std::endl;
        sleep(SLEEP_TIME);
        this->meum_print();
        return;
    }

    else
    {
        std::cout << "成功连接" << std::endl;
        sleep(SLEEP_TIME);
        std::shared_ptr<Client_Thread> new_thread(new Client_Thread(this->file_description)); //创建子线程
        new_thread->run(*this, &Client::client_receive_process);
        this->sub_thread_group[new_thread->get_thread()->get_id()] = new_thread; //写入类中
        this->connent_thread_id = new_thread->get_thread()->get_id();
        this->is_connected = true;
        this->meum_print();
    }
}

/***
 * @Description: 客户端线程接收数据包的循环调用
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
void Client::client_receive_process()
{
    char_t _pack[MSG_LEN] = {0}; //数据包
    int32_t _msg_len = MSG_LEN;

    int32_t _file_description = this->sub_thread_group[std::this_thread::get_id()]->get_file_description();
    while (1)
    {

        if (recv(_file_description, _pack, _msg_len, 0) == -1)
        {
            std::cout << "在接收数据包时发生错误！" << std::endl;
            std::cout << strerror(errno) << std::endl;
            continue;
        }
        else
        {
            int32_t _require_type = 0;
            int32_t _message_type = 0;

            char_t _msg[MSG_LEN] = {0};
            this->is_connected = false;
            std::string _msg_str = "";

            if (unpack_data(_require_type, _message_type, _msg, _msg_len, _pack))
            {
                _msg_str = _msg;
                switch (_require_type)
                {
                case 1:                     //请求
                    if (_message_type == 1) //时间
                    {
                    }
                    if (_message_type == 2) //名称
                    {
                    }
                    if (_message_type == 3) //消息
                    {
                    }
                    if (_message_type == 4) //列表
                    {
                    }
                    break;
                case 2: //响应scanKeyboard
                    if (_message_type == 1)
                    {
                    }
                    if (_message_type == 2) //名称
                    {
                    }
                    if (_message_type == 3) //消息
                    {
                        this->message_quene_mutex.lock();
                        this->message_quene.push(_msg);
                        this->message_quene_mutex.unlock();
                    }
                    if (_message_type == 4) //列表
                    {
                    }
                    break;
                case 3: //指示

                    if (_message_type == 1) //消息
                    {
                    }
                    break;

                default:
                    break;
                }
            }
            else
            {
                std::string _msg = "收到一个非法数据包！";

                this->message_quene_mutex.lock();
                this->message_quene.push(_msg);
                this->message_quene_mutex.unlock();
                continue;
            }
        }
    }

    return;
}

/***
 * @Description: 打印输出的线程
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
void Client::print_process()
{
    while (1)
    {
        this->meum_print();
        sleep(15);
    }

    return;
}

/***
 * @Description: 关闭服务器连接，退出线程，创建一个新的socket，并发送给服务端指示自己将要断连
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
void Client::close_connent()
{
    std::shared_ptr<Client_Thread> _accept_thread = this->sub_thread_group[this->connent_thread_id];
    pthread_cancel(_accept_thread->get_thread()->native_handle());
    _accept_thread->get_thread()->join();
    this->sub_thread_group.erase(this->connent_thread_id);

    char_t _pack[MSG_LEN] = {0}; //数据包

    int32_t _require_type = 3;
    int32_t _message_type = 2;
    std::string _msg = "";

    pack_data(_require_type, _message_type, (char_t *)_msg.data(), _msg.length(), _pack);

    if (send(this->file_description, _pack, MSG_LEN, 0) != -1)
        std::cout << "成功向服务器请求断开" << std::endl;
    else
    {
        std::cout << "请求服务器失败" << std::endl;
        std::cout << strerror(errno) << std::endl;
        return;
    }

    close(this->file_description);

    this->error_sign = false;

    int32_t _file_description = -1;

    if ((_file_description = socket(this->domain, this->type, this->protocol)) == -1) //生成socket句柄
    {
        this->error_sign = true;
        return;
    }

    this->file_description = _file_description;

    this->server_addr = "";
    this->server_port = "";

    std::cout << "服务器连接已断开" << std::endl;
    sleep(SLEEP_TIME);

    this->meum_print();

    return;
}

void Client::meum_print()
{
    system("clear");
    if (this->is_connected)
    {
        std::cout << "当前状态：已连接服务端" << std::endl;
        std::cout << "地址:" << this->server_addr << std::endl;
        std::cout << "端口号:" << this->server_port << std::endl;
        std::cout << std::endl;
        std::cout << "操作:" << std::endl;
        std::cout << "[1] 连接服务端" << std::endl;
        std::cout << "[2] 断开连接" << std::endl;
        std::cout << "[3] 获取时间" << std::endl;
        std::cout << "[4] 获取名字" << std::endl;
        std::cout << "[5] 获取客户端列表" << std::endl;
        std::cout << "[6] 发送消息" << std::endl;
        std::cout << "[7] 退出客户端" << std::endl;
    }

    else
    {
        std::cout << "当前状态：未连接服务端" << std::endl;
        std::cout << std::endl;
        std::cout << "操作:" << std::endl;
        std::cout << "[1] 连接服务端" << std::endl;
        std::cout << "[2] 退出客户端" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "消息：" << std::endl;
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