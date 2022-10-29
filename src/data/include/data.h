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

#define PACK_LENGTH 200
#define HEAD_LENGTH 10
#define TAIL_LENGTH 10
#define PACK_BEGIN 0

#define MEG_LENGTH_ADD 20
#define MEG_LENGTH_AREA 5

#define MEG_ADD 30

#define REQUIRE_ADD 10

#define MEGTYPE_ADD 15

#define ZERO_SYM 'a'
#define HEAD_SYM '1'
#define TAIL_SYM '9'

void pack_data(int32_t _require_type, int32_t _message_type, char_t *_msg, int32_t _msg_len, char_t *pack);

bool_t unpack_data(int32_t &_require_type, int32_t &_message_type, char_t *_msg, int32_t &_msg_len, char_t *pack);