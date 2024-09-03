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
 * 文件名称 ：   ModulesManager.h
 * 文件标识 ：
 * 摘 要 ：     模块管理，处理一般模块
 * 当前版本 ：   v0.01.0
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.0.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/13
 ******************************************************************************/
#pragma once

#include "IBaseExport.h"
#include "ModulesManager_global.h"

#include <QLibrary>
#include <QMap>
#include <QObject>
#include <QReadWriteLock>

#include <QDebug>

class ModulesManager;
using ModulesManagerPtr = QSharedPointer<ModulesManager>;

class MODULESMANAGER_EXPORT ModulesManager : public IBaseExport
{
    Q_OBJECT
public:
    explicit ModulesManager(QObject *parent = nullptr);

    static ModulesManagerPtr instance();
    virtual ~ModulesManager() override;

    void start() override;
    void stop() override;
    void descripte() override;

    bool loadModuleLibrary(const QString &moduleName);
    void *getModule(const QString &moduleName);

private:
    QReadWriteLock m_lock;
};
