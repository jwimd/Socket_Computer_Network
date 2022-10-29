/***
 * @Description:这里定义了数据包，指示数据包中存在什么内容，可以将信息封装成数据包
 * @Author: jwimd chenjiewei@zju.edu.cn
 * @Date: 2022-10-05 16:34:46
 * @LastEditors: jwimd chenjiewei@zju.edu.cn
 * @LastEditTime: 2022-10-05 16:34:54
 * @FilePath: /Socket_Computer_Network/src/include/data.hpp
 */
#include "data.h"

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
    char_t _msg_len_str[MEG_LENGTH_AREA] = {0};
    snprintf(_msg_len_str, sizeof(_msg_len_str), "%d", _msg_len);
    for (int32_t i = PACK_BEGIN; i < PACK_LENGTH; i++) //数据包清零
        pack[i] = ZERO_SYM;

    //数据包的头部和尾部
    for (int32_t i = PACK_BEGIN; i < HEAD_LENGTH; i++)
        pack[i] = HEAD_SYM;

    for (int32_t i = PACK_LENGTH - TAIL_LENGTH; i < PACK_LENGTH; i++)
        pack[i] = TAIL_SYM;

    for (int32_t i = 0; i <  strlen(_msg_len_str); i++)
        pack[i + MEG_LENGTH_ADD] = _msg_len_str[i];

    for (int32_t i = 0; i < _msg_len; i++)
        pack[i + MEG_ADD] = _msg[i];

    switch (_require_type)
    {
    case 1: //请求
        pack[REQUIRE_ADD] = '1';
        if (_message_type == 1) //时间
        {
            pack[MEGTYPE_ADD] = '1';
        }
        if (_message_type == 2) //名称
        {
            pack[MEGTYPE_ADD] = '2';
        }
        if (_message_type == 3) //消息
        {
            pack[MEGTYPE_ADD] = '3';
        }
        if (_message_type == 4) //列表
        {
            pack[MEGTYPE_ADD] = '4';
        }
        break;
    case 2: //响应
        pack[REQUIRE_ADD] = '2';
        if (_message_type == 1)
        {
            pack[MEGTYPE_ADD] = '1';
        }
        if (_message_type == 2) //名称
        {
            pack[MEGTYPE_ADD] = '2';
        }
        if (_message_type == 3) //消息
        {
            pack[MEGTYPE_ADD] = '3';
        }
        if (_message_type == 4) //列表
        {
            pack[MEGTYPE_ADD] = '4';
        }
        break;
    case 3: //指示
        pack[10] = '3';

        if (_message_type == 1) //消息
        {
            pack[MEGTYPE_ADD] = '1';
        }

        if (_message_type == 2) //断开连接
        {
            pack[MEGTYPE_ADD] = '2';
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
    for (int32_t i = PACK_BEGIN; i < HEAD_LENGTH; i++)
        if (pack[i] != HEAD_SYM)
            return false;

    for (int32_t i = PACK_LENGTH-TAIL_LENGTH; i < PACK_LENGTH; i++)
        if (pack[i] != TAIL_SYM)
            return false;

    _require_type = pack[REQUIRE_ADD] - '0';
    _message_type = pack[MEGTYPE_ADD] - '0';

    char_t _msg_len_str[MEG_LENGTH_AREA] = {0};

    for (int32_t i = 0; i < MEG_LENGTH_AREA; i++)
        if (pack[i + MEG_LENGTH_ADD] != ZERO_SYM)
            _msg_len_str[i] = pack[i + MEG_LENGTH_ADD];

    int32_t _muti = 1;

    _msg_len = 0;
    for (int32_t i = strlen(_msg_len_str) - 1; i >= 0; i--)
    {
        _msg_len += _muti * (_msg_len_str[i] - '0');
        _muti *= 10;
    }

    for (int32_t i = 0; i < _msg_len; i++)
        _msg[i] = pack[MEG_ADD + i];

    return true;
}