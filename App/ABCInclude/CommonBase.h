/******************************************************************************
 * Copyright (C) [2024] [github.com/babuge]
 *
 * [BBGProject] is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan
 * PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 * 文件名称 ：   CommonBase.h
 * 文件标识 ：
 * 摘 要 ：     兼容性通用头文件
 * 当前版本 ：   v0.01.0
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.0.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/12
 ******************************************************************************/
#pragma once

#include <stdlib.h>

// 扩展定义指针类型
typedef long int *PtrType;

// 释放内存
#define RELESE(p_TypeName)                                                                         \
    if (p_TypeName != nullptr) {                                                                   \
        delete p_TypeName;                                                                         \
        p_TypeName = nullptr;                                                                      \
    }

#define RELESEARR(p_ArrName)                                                                       \
    if (p_ArrName != nullptr) {                                                                    \
        delete[] p_ArrName;                                                                        \
        p_ArrName = nullptr;                                                                       \
    }
