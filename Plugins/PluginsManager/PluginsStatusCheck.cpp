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
 * 文件名称 ：   PluginsStatusCheck.cpp
 * 文件标识 ：
 * 摘 要 ：     
 * 当前版本 ：   v0.01.1
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.01.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/12
 ******************************************************************************/
#include "PluginsStatusCheck.h"

#include <QDebug>
using PluginsStatusPtr = QSharedPointer<PluginSpace::PluginStatus>;
extern QMap<QString, PluginsStatusPtr> g_golbalPluginsStatus;

PluginsStatusCheck::PluginsStatusCheck(QObject *parent) : QThread(parent)
{
    setObjectName("PluginManager_qt_thread");
}

void PluginsStatusCheck::run()
{
    while (m_running) {
        QThread::msleep(1000);
        if (!m_running) {
            break;
        }
        bool hasModify = false;
        // check
        {
            QMap<QString, PluginsStatusPtr>::const_iterator it = g_golbalPluginsStatus.constBegin();
            while (it != g_golbalPluginsStatus.constEnd()) {
                if (it.value()->isUnInstalled()) {
                    hasModify = true;
                    break;
                }
                ++it;
            }
        }

        m_count++;
        qDebug() << objectName() << m_count;

        // handle
        if (hasModify) {
            // signal
            emit signal_hasUninstallPlugin();
        }
    }
}

void PluginsStatusCheck::setRun(const bool flag)
{
    m_running = flag;
}
