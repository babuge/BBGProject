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
 * 文件名称 ：   TryModule.cpp
 * 文件标识 ：
 * 摘 要 ：
 * 当前版本 ：   v0.01.1
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.01.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/12
 ******************************************************************************/
#include "TryModule.h"
#include <QSharedPointer>
#include <iostream>

#include <QDebug>

TryModule::TryModule(QObject *parent)
    : IBaseExport(parent)
    , m_freeType(ResourceFreeType::AUTO)
{
}

TryModule::~TryModule()
{
    qDebug() << "free~TryModule";
}

TryModulePtr TryModule::instance()
{
    static TryModulePtr main = QSharedPointer<TryModule>(new TryModule);
    return main;
}

void TryModule::start()
{
    // 线程：重新更新状态库状态
    if (!isRunning()) {
        qDebug() << "TryModule Strat Runing Operator" << this;
        // ...
        setStatus(LifeCycleStatus::RUNNING);
    }
}

IBaseExport::ResourceFreeType TryModule::FreeType() const
{
    return m_freeType;
}

void TryModule::stop()
{
    // 线程：处理库公共状态，重置为初始状态
    if (isRunning()) {
        qDebug() << "TryModule Stop Runing Operator" << this;
        // ...
        setStatus(LifeCycleStatus::FINISH);
    }
}

void TryModule::descripte()
{
    // std::cout << "cout output!" << std::endl;
    qDebug() << "TryModule::descripte!";
}

extern "C" TRYMODULE_EXPORT const void *Get()
{
    return static_cast<void *>(TryModule::instance().data());
}
