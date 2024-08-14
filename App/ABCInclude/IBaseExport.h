/******************************************************************************
 * Copyright (C) [2024] [github.com/babuge]
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
    explicit IBaseExport(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IBaseExport() {}

    virtual void start()     = 0;
    virtual void stop()      = 0;
    virtual void descripte() = 0;

    virtual ResourceFreeType FreeType() const
    {
        return ResourceFreeType::AUTO;
    }
};

