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
 * 文件名称 ：   BussinessModule.cpp
 * 文件标识 ：
 * 摘 要 ：
 * 当前版本 ：   v0.01.1
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.01.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/12
 ******************************************************************************/
#include "BussinessModule.h"

#include <QDebug>

BussinessModule::BussinessModule(QObject *parent)
    : IBaseExport(parent)
    , m_freeType(ResourceFreeType::EXTRA)
{
}

BussinessModule::~BussinessModule()
{
    qDebug() << "free~BussinessModule";
}

void BussinessModule::start()
{
    // 线程：重新更新状态库状态
    if (!isRunning()) {
        setStatus(LifeCycleStatus::RUNNING);
        qDebug() << "BussinessModule Strat Runing Operator" << this;
        // ...
    }
}

void BussinessModule::stop()
{
    // 线程：处理库公共状态，重置为初始状态
    if (isRunning()) {
        setStatus(LifeCycleStatus::FINISH);
        qDebug() << "BussinessModule Stop Runing Operator" << this;
        // ...
    }
}
void BussinessModule::descripte()
{
    qDebug() << "BussinessModule::descripte!";
}

IBaseExport::ResourceFreeType BussinessModule::FreeType() const
{
    return m_freeType;
}

extern "C" BUSSINESSMODULE_EXPORT const void *Get()
{
    return static_cast<void *>(new BussinessModule);
}
