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
 *
 * 文件名称 ：   IBaseExport.h
 * 文件标识 ：
 * 摘 要 ：     由于模块导出的抽象基类
 * 当前版本 ：   v0.01.0
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.0.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/13
 ******************************************************************************/

#pragma once

#include "FramWorkExtend.h"
#include <QObject>

#include <QDebug>

class IBaseExport : public QObject
{
protected:
    LIFECYCLE_STATUS
public:
    typedef enum class ResourceFreeType_ : int
    {
        AUTO = 0,
        EXTRA
    } ResourceFreeType;
    explicit IBaseExport(QObject *parent = nullptr)
        : QObject(parent)
    {
    }
    virtual ~IBaseExport() {}

    virtual void start()     = 0;
    virtual void stop()      = 0;
    virtual void descripte() = 0;

    virtual ResourceFreeType FreeType() const
    {
        return ResourceFreeType::AUTO;
    }
};
