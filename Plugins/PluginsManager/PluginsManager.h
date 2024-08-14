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
