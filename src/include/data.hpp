/***
 * @Description:这里定义了数据包，指示数据包中存在什么内容，可以将信息封装成数据包
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-05 16:34:46
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-05 16:34:54
 * @FilePath: /Socket_Computer_Network/src/include/data.hpp
 */

#pragma once

#include <stdio.h>
#include <string.h>

#include "type.h"

/***
 * @Description:
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @param {int32_t} _require_type 请求类型
 * @param {int32_t} _message_type 信息类型
 * @param {char} *msg 信息
 * @param {char} *pack 数据包
 * @return {*}
 */
void pack_data(int32_t _require_type, int32_t _message_type, char_t *_msg, int32_t _msg_len, char_t *pack)
{
    char_t _msg_len_str[5] = {0};
    snprintf(_msg_len_str, sizeof(_msg_len_str), "%d", _msg_len);
    for (int32_t i = 0; i < 200; i++) //数据包清零
        pack[i] = 'a';

    //数据包的头部和尾部
    for (int32_t i = 0; i < 10; i++)
        pack[i] = '1';

    for (int32_t i = 190; i < 200; i++)
        pack[i] = '9';

    for (int32_t i = 0; i < 5; i++)
        pack[i + 20] = _msg_len_str[i];

    for (int32_t i = 0; i < _msg_len; i++)
        pack[i + 30] = _msg[i];

    switch (_require_type)
    {
    case 1: //请求
        pack[10] = '1';
        if (_message_type == 1) //时间
        {
            pack[15] = '1';
        }
        if (_message_type == 2) //名称
        {
            pack[15] = '2';
        }
        if (_message_type == 3) //消息
        {
            pack[15] = '3';
        }
        if (_message_type == 4) //列表
        {
            pack[15] = '4';
        }
        break;
    case 2: //相应
        pack[10] = '1';
        if (_message_type == 1)
        {
            pack[15] = '1';
        }
        if (_message_type == 2) //名称
        {
            pack[15] = '2';
        }
        if (_message_type == 3) //消息
        {
            pack[15] = '3';
        }
        if (_message_type == 4) //列表
        {
            pack[15] = '4';
        }
        break;
    case 3: //指示
        pack[10] = '3';

        if (_message_type == 1) //消息
        {
            pack[15] = '1';
        }
        break;

    default:
        break;
    }
}

/***
 * @Description:
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @msg: None
 * @param {int32_t} _require_type
 * @param {int32_t} _message_type
 * @param {char_t} *_msg
 * @param {int32_t} _msg_len
 * @param {char_t} *pack
 * @return {*}
 */
bool_t unpack_data(int32_t &_require_type, int32_t &_message_type, char_t *_msg, int32_t &_msg_len, char_t *pack)
{
    for (int32_t i = 0; i < 10; i++)
        if (pack[i] != '1')
            return false;

    for (int32_t i = 190; i < 200; i++)
        if (pack[i] != '9')
            return false;

    _require_type = pack[10] - '0';
    _message_type = pack[15] - '0';

    char_t _msg_len_str[5] = {0};

    for (int32_t i = 0; i < 5; i++)
        if (pack[i + 20] != 'a')
            _msg_len_str[i] = pack[i + 20];

    int32_t muti = 1;

    _msg_len = 0;
    for (int32_t i = strlen(_msg_len_str) - 1; i >= 0; i--)
    {
        _msg_len += muti * (_msg_len_str[i] - '0');
        muti *= 10;
    }

    _msg = {0};

    for (int32_t i = 0; i < _msg_len; i++)
        _msg_len = pack[30 + i];

    return true;
}