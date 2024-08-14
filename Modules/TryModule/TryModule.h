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
 * 文件名称 ：   TryModule.h
 * 文件标识 ：
 * 摘 要 ：     临时模块
 * 当前版本 ：   v0.01.0
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.0.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/13
 ******************************************************************************/

#pragma once

#include "IBaseExport.h"
#include "TryModule_global.h"

#include <QObject>
#include <QReadWriteLock>

class TryModule;

using TryModulePtr = QSharedPointer<TryModule>;
class TRYMODULE_EXPORT TryModule : public IBaseExport
{
public:
    virtual ~TryModule() override;

    virtual void start() override;
    virtual void stop() override;
    virtual void descripte() override;

    static TryModulePtr instance();

    ResourceFreeType FreeType() const override;

private:
    explicit TryModule(QObject *parent = nullptr);

private:
    const ResourceFreeType m_freeType;
};
