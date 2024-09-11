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
 * 文件名称 ：   PluginsStatusCheck.h
 * 文件标识 ：
 * 摘 要 ：     
 * 当前版本 ：   v0.01.1
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.01.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/12
 ******************************************************************************/
#pragma once

#include "PluginSpace.h"
#include <QMap>
#include <QObject>
#include <QThread>

using PluginSpace::PluginStatus;

class PluginsStatusCheck : public QThread
{
    Q_OBJECT
public:
    explicit PluginsStatusCheck(QObject *parent = nullptr);

    void setRun(const bool flag);

protected:
    virtual void run() override;
signals:
    void signal_hasUninstallPlugin();

private:
    bool m_running{ false };

    int m_count{ 0 };
};
