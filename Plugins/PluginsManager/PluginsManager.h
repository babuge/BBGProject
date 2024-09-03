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
 * 文件名称 ：   PluginsManager.h
 * 文件标识 ：
 * 摘 要 ：     插件管理模块，动态管理插件
 * 当前版本 ：   v0.01.0
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.0.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/13
 ******************************************************************************/
#pragma once

#include "IBaseExport.h"
#include "PluginsManager_global.h"
#include "PluginsStatusCheck.h"

#include <QMap>
#include <QObject>
#include <QReadWriteLock>
#include <QThread>

class PluginsManager;

using PluginsManagerPtr = QSharedPointer<PluginsManager>;

using PluginSpace::PluginStatus;
using PluginsStatusPtr = QSharedPointer<PluginSpace::PluginStatus>;

extern QMap<QString, PluginsStatusPtr> g_golbalPluginsStatus;

class PLUGINSMANAGER_EXPORT PluginsManager : public IBaseExport
{
    Q_OBJECT
public:
    static QReadWriteLock m_rwLock;
    static PluginsManagerPtr instance();

    virtual ~PluginsManager() override;

    virtual void start() override;
    virtual void stop() override;
    virtual void descripte() override;

    void updatePlugin(const QString &pluginNmae, PluginsStatusPtr &pluginStatus);
    PluginsStatusPtr getPlugin(const QString &pluginName);

    void startCheck();
    void stopCheck();

private slots:
    void slot_hasUninstallPlugin();

private:
    explicit PluginsManager(QObject *parent = nullptr);

    void clear();

private:
    PluginsStatusCheck *m_pluginCheck = nullptr;
};
