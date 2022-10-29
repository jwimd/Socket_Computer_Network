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
    this->exit_sign = false;

    int32_t _file_description = -1;

    if ((_file_description = socket(this->domain, this->type, this->protocol)) == -1) //生成socket句柄
    {
        this->error_sign = true;
        return;
    }

    this->file_description = _file_description;

    this->sock_addr.sin_family = AF_INET;                                   // ipv4地址类型
    this->sock_addr.sin_addr.s_addr = inet_addr(this->server_addr.c_str()); //绑定地址
    this->sock_addr.sin_port = htons(stoi(this->server_port));              //绑定端口

    if (bind(_file_description, (struct sockaddr *)&this->sock_addr, sizeof(struct sockaddr)) == -1) //绑定端口号和地址
    {
        this->error_sign = true;
        return;
    }

    if (listen(_file_description, this->backlog) == -1)
    {
        this->error_sign = true;
        return;
    }

    std::cout << "欢迎使用Jwimd Server套接字通信服务器" << std::endl;
    std::cout << "服务器成功启动！" << std::endl;

    std::cout << "服务器地址：" << this->server_addr << std::endl;
    std::cout << "服务器端口：" << this->server_port << std::endl;

    std::cout << std::endl;
    std::cout << "按[P]断开所有连接并关闭服务器" << std::endl;

    std::cout << std::endl;
    std::cout << "服务器消息：" << std::endl;

    std::shared_ptr<Server_Thread>
        new_thread(new Server_Thread(0)); //创建子线程
    new_thread->run(*this, &Server::thread_clean);

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

        if ((client_file_description = accept(this->main_thread->get_file_description(), (sockaddr *)&client_addr, &sock_len)) != -1) // accept接受客户端请求
        {
            std::shared_ptr<Server_Thread>
                new_thread(new Server_Thread(client_file_description)); //创建子线程
            new_thread->run(*this, &Server::server_sub_process);
            this->sub_thread_group[new_thread->get_thread()->get_id()] = new_thread; //写入类中
        }
    }

    return;
}

/***
 * @Description: 服务端子线程函数
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
void Server::server_sub_process()
{
    char_t msg[MSG_LEN] = {0};
    int32_t msg_len = MSG_LEN;

    int32_t _file_description = this->sub_thread_group[std::this_thread::get_id()]->get_file_description();

    sockaddr_in _client_addr;

    socklen_t addrlen = 0;

    if (getpeername(_file_description, (struct sockaddr *)&_client_addr, &addrlen) == -1)
    {
        std::cout << "获取信息时出现问题" << std::endl;
        std::cout << strerror(errno) << std::endl;
        return;
    }

    this->client_info_lock.lock();
    this->client_fd[std::this_thread::get_id()] = _file_description;
    this->client_addr[std::this_thread::get_id()] = _client_addr;
    this->client_info_lock.unlock();

    char_t _pack[MSG_LEN] = {0}; //数据包

    int32_t _require_type = 2;
    int32_t _message_type = 3;
    std::string _msg = "来自【服务端】的消息：你好!欢迎连接服务端!";

    pack_data(_require_type, _message_type, (char_t *)_msg.data(), _msg.length(), _pack);

    if (send(_file_description, _pack, MSG_LEN, 0) != -1)
        std::cout << "客户端" << std::this_thread::get_id() << "：成功连接！" << std::endl;
    else
    {
        std::cout << "客户端" << std::this_thread::get_id() << "：发送数据包失败！" << std::endl;
        std::cout << strerror(errno) << std::endl;
    }

    char_t _pack_fd[MSG_LEN] = {0}; //数据包

    _require_type = 3;
    _message_type = 3;
    _msg = std::to_string(_file_description);

    pack_data(_require_type, _message_type, (char_t *)_msg.data(), _msg.length(), _pack_fd);

    if (send(_file_description, _pack_fd, MSG_LEN, 0) != -1)
        std::cout << "客户端" << std::this_thread::get_id() << "：成功发送套接字！" << std::endl;
    else
    {
        std::cout << "客户端" << std::this_thread::get_id() << "：发送数据包失败！" << std::endl;
        std::cout << strerror(errno) << std::endl;
    }

    while (1)
    {
        bool_t is_close = false;

        char_t _re_pack[MSG_LEN] = {0}; //数据包
        if (recv(_file_description, _re_pack, msg_len, 0) == -1)
        {
            std::cout << "客户端" << std::this_thread::get_id() << "：接受数据包错误！" << std::endl;
            std::cout << strerror(errno) << std::endl;
            continue;
        }

        else
        {
            int32_t _msg_len = MSG_LEN;
            int32_t _require_type = 0;
            int32_t _message_type = 0;

            char_t _msg[MSG_LEN] = {0};
            char_t _pack[MSG_LEN] = {0};
            std::string _msg_str = "";

            if (unpack_data(_require_type, _message_type, _msg, _msg_len, _re_pack))
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
                        std::cout << "客户端" << std::this_thread::get_id() << "：请求客户端列表" << std::endl;

                        _require_type = 2;
                        _message_type = 4;

                        for (std::map<std::thread::id, std::shared_ptr<Server_Thread>>::iterator client = this->sub_thread_group.begin(); client != this->sub_thread_group.end(); client++)
                        {
                            std::thread::id _id = client->first;
                            _msg_str += std::to_string(this->client_fd[_id]);
                            _msg_str += 'j';
                            _msg_str += std::to_string(this->client_addr[_id].sin_addr.s_addr);
                            _msg_str += 'k';
                            _msg_str += std::to_string(this->client_addr[_id].sin_port);
                            _msg_str += 'l';
                        }

                        pack_data(_require_type, _message_type, (char_t *)_msg_str.data(), _msg_str.length(), _pack);

                        if (send(_file_description, _pack, MSG_LEN, 0) != -1)
                            std::cout
                                << "客户端" << std::this_thread::get_id() << "：成功收到客户端列表！" << std::endl;
                        else
                        {
                            std::cout
                                << "客户端" << std::this_thread::get_id() << "：发送数据包失败！" << std::endl;
                            std::cout << strerror(errno) << std::endl;
                        }
                    }
                    break;
                case 2: //响应
                    if (_message_type == 1)
                    {
                    }
                    if (_message_type == 2) //名称
                    {
                    }
                    if (_message_type == 3) //消息
                    {
                        std::cout << "客户端" << std::this_thread::get_id() << "：" << _msg << std::endl;
                    }
                    if (_message_type == 4) //列表
                    {
                    }
                    break;
                case 3: //指示

                    if (_message_type == 1) //消息
                    {
                        std::string _clid = "";
                        while (_msg_str.front() != '|')
                        {
                            _clid += _msg_str.front();
                            std::string::iterator itr = _msg_str.begin();
                            _msg_str.erase(itr);
                        }
                        std::string::iterator itr = _msg_str.begin();
                        _msg_str.erase(itr);

                        std::vector<int32_t> client_group;

                        for (std::map<std::thread::id, int32_t>::iterator client = this->client_fd.begin(); client != this->client_fd.end(); client++)
                            client_group.push_back(client->second);

                        std::vector<int32_t>::iterator it = find(client_group.begin(), client_group.end(), std::stoi(_clid));

                        if (it == client_group.end())
                        {
                            _require_type = 2;
                            _message_type = 3;
                            _msg_str = "来自【服务端】的消息：该客户端不存在，发送失败!";

                            pack_data(_require_type, _message_type, (char_t *)_msg_str.data(), _msg_str.length(), _pack);

                            if (send(_file_description, _pack, MSG_LEN, 0) != -1)
                                std::cout
                                    << "客户端" << std::this_thread::get_id() << "：成功收到提示！" << std::endl;
                            else
                            {
                                std::cout
                                    << "客户端" << std::this_thread::get_id() << "：发送数据包失败！" << std::endl;
                                std::cout << strerror(errno) << std::endl;
                            }
                        }

                        else
                        {
                            _require_type = 2;
                            _message_type = 3;
                            _msg_str = "来自【客户端" + std::to_string(_file_description) + "】的消息：" + _msg_str;

                            pack_data(_require_type, _message_type, (char_t *)_msg_str.data(), _msg_str.length(), _pack);

                            if (send(std::stoi(_clid), _pack, MSG_LEN, 0) != -1)
                                std::cout
                                    << "客户端" << std::stoi(_clid) << "：成功收到消息！" << std::endl;
                            else
                            {
                                std::cout
                                    << "客户端" << std::this_thread::get_id() << "：发送数据包失败！" << std::endl;
                                std::cout << strerror(errno) << std::endl;
                            }
                        }
                    }
                    if (_message_type == 2) //消息
                    {
                        close(_file_description);
                        is_close = true;
                        std::cout << "客户端" << std::this_thread::get_id() << "：socket连接关闭" << std::endl;
                    }
                    if (_message_type == 3) //套接字
                    {
                    }
                    break;

                default:
                    break;
                }
            }
            else
            {
                std::cout << "客户端" << std::this_thread::get_id() << "：收到一个非法数据包！" << std::endl;
                continue;
            }
        }

        if (is_close)
        {
            this->close_quene_mutex.lock();
            this->close_quene.push(std::this_thread::get_id());
            this->close_quene_mutex.unlock();

            break;
        }
    }

    return;
}

/***
 * @Description: 清除线程数据
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @return {*}
 */
void Server::thread_clean()
{
    while (1)
    {
        this->close_quene_mutex.lock();
        while (this->close_quene.size() > 0)
        {
            std::thread::id _id = this->close_quene.front();

            this->client_info_lock.lock();
            this->client_addr.erase(_id);
            this->client_fd.erase(_id);

            this->sub_thread_group[_id]->get_thread()->join();
            this->sub_thread_group.erase(_id);

            this->client_info_lock.unlock();
            this->close_quene.pop();

            std::cout << "客户端" << _id << "：成功断开连接并清除数据" << std::endl;
        }
        this->close_quene_mutex.unlock();

        if (kbhit())
        {
            char_t _opera_code = fgetc(stdin);

            if (_opera_code == 'p')
            {
                std::vector<std::thread::id> client_group;

                this->client_info_lock.lock();
                for (std::map<std::thread::id, std::shared_ptr<Server_Thread>>::iterator client = this->sub_thread_group.begin(); client != this->sub_thread_group.end(); client++)
                    client_group.push_back(client->first);

                for (std::vector<std::thread::id>::iterator cli_id = client_group.begin(); cli_id != client_group.end(); cli_id++)
                {
                    int32_t _file_description = this->sub_thread_group[*cli_id]->get_file_description();
                    std::thread::id _id = *cli_id;

                    char_t _pack[MSG_LEN] = {0}; //数据包

                    int32_t _require_type = 3;
                    int32_t _message_type = 2;
                    std::string _msg = "来自【服务端】的消息：服务端即将关闭，连接断开!";

                    pack_data(_require_type, _message_type, (char_t *)_msg.data(), _msg.length(), _pack);

                    if (send(_file_description, _pack, MSG_LEN, 0) != -1)
                        std::cout << std::endl
                                  << "客户端" << std::this_thread::get_id() << "：成功收到断开请求！" << std::endl;
                    else
                    {
                        std::cout << std::endl
                                  << "客户端" << std::this_thread::get_id() << "：发送数据包失败！" << std::endl;
                        std::cout << strerror(errno) << std::endl;
                    }
                }
                this->client_info_lock.unlock();

                this->exit_sign = true;
            }
        }
        if (this->exit_sign && this->sub_thread_group.size() == 0)
        {
            std::cout << std::endl
                      << "所有客户端都已经断开，服务器关闭!" << std::endl;
            exit(1);
        }
    }
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