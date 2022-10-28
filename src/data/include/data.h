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

void pack_data(int32_t _require_type, int32_t _message_type, char_t *_msg, int32_t _msg_len, char_t *pack);

bool_t unpack_data(int32_t &_require_type, int32_t &_message_type, char_t *_msg, int32_t &_msg_len, char_t *pack);