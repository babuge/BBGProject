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
