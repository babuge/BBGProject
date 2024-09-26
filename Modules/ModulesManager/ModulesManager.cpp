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
 * 文件名称 ：   ModulesManager.cpp
 * 文件标识 ：
 * 摘 要 ：
 * 当前版本 ：   v0.01.1
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.01.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/12
 ******************************************************************************/
#include "ModulesManager.h"
#include "TryUtil.h"

#include <QReadLocker>
#include <QWriteLocker>

static QMap<QString, void *> g_golbalLibraryMap;

ModulesManager::ModulesManager(QObject *parent)
    : IBaseExport(parent)
{
}

ModulesManager::~ModulesManager()
{
    qDebug() << "free~ModulesManager";
}

ModulesManagerPtr ModulesManager::instance()
{
    static ModulesManagerPtr main = QSharedPointer<ModulesManager>(new ModulesManager);
    return main;
}

void ModulesManager::start()
{
    // 线程：重新更新状态库状态
    if (!isRunning()) {
        qDebug() << "ModulesManager Strat Runing Operator";
        // ...
        setStatus(LifeCycleStatus::RUNNING);
    }
}

void ModulesManager::stop()
{
    // 线程：处理库公共状态，重置为初始状态
    if (isRunning()) {
        qDebug() << "ModulesManager Stop Runing Operator";
        // ...
        setStatus(LifeCycleStatus::FINISH);
    }
}

void ModulesManager::descripte()
{
    qDebug() << "ModulesManager::descripte";
}

bool ModulesManager::loadModuleLibrary(const QString &moduleName)
{
    PtrType ptr = nullptr;
    if (TryUtil::GetLibHandle(moduleName, ptr)) {
        QWriteLocker lock(&m_lock);
        g_golbalLibraryMap.insert(moduleName, ptr);
        qDebug() << g_golbalLibraryMap;
        return true;
    }
    return false;
}

void *ModulesManager::getModule(const QString &moduleName)
{
    if (g_golbalLibraryMap.contains(moduleName)) {
        QReadLocker lock(&m_lock);
        return g_golbalLibraryMap.value(moduleName);
    }
    return nullptr;
}

extern "C" MODULESMANAGER_EXPORT const void *Get()
{
    return static_cast<void *>(ModulesManager::instance().data());
}
