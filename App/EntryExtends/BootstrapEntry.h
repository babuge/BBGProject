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
 * 文件名称 ：   BootstrapEntry.h
 * 文件标识 ：
 * 摘 要 ：     程序启动引导入口
 * 当前版本 ：   v0.01.0
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.0.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/12
 ******************************************************************************/
#pragma once

#include <QJsonObject>
#include <QMap>
#include <QObject>
#include <QReadWriteLock>
#include <QVector>

#include "CommonBase.h"
#include "FramWorkExtend.h"
#include "MainConfig.h"

class QJsonObject;

class BootstrapEntry : public QObject
{
    Q_OBJECT
    LIFECYCLE_STATUS
public:
    typedef QVector<QString> CoreType;
    typedef QVector<QMap<QString, int>> BussinessType;
    typedef QMap<QString, PtrType> CoreHandle;

    explicit BootstrapEntry(QObject *parent = nullptr);
    virtual ~BootstrapEntry();

    void InitConfig();

    void restart();
    void start();
    void stop();
signals:

public slots:
private:
    void initBoostStrap();
    void init();
    void unInit();
    bool loadCore(const QString &);

    template <class T>
    T getObjPtr(const QString &name);

private:
    CoreType m_coreLibs;
    CoreHandle m_coreHandle;

    BussinessType m_bussinessLibs;

    QReadWriteLock m_lock;

    MainConfig m_config;
};
