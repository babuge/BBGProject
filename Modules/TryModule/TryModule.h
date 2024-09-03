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
