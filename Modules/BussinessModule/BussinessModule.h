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
 * 文件名称 ：   BussinessModule.h
 * 文件标识 ：
 * 摘 要 ：     业务模块，处理特定业务逻辑
 * 当前版本 ：   v0.01.0
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.0.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/13
 ******************************************************************************/
#pragma once

#include "BussinessModule_global.h"
#include "IBaseExport.h"

#include <QSharedPointer>

class BUSSINESSMODULE_EXPORT BussinessModule : public IBaseExport
{
public:
    typedef QSharedPointer<BussinessModule> ptr;
    explicit BussinessModule(QObject *parent = nullptr);
    ~BussinessModule();

    virtual void start() final;
    virtual void stop() final;
    virtual void descripte() final;

    ResourceFreeType FreeType() const override final;

private:
    EXPORT_EXTRA_GC(BussinessModule)
private:
    const ResourceFreeType m_freeType;
    GC m_gc{ this };
};
