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
 * 文件名称 ：   ResourceManagerModule.h
 * 文件标识 ：
 * 摘 要 ：     资源管理模块，统一处理所有模块插件加载卸载
 * 当前版本 ：   v0.01.0
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.0.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/13
 ******************************************************************************/
#pragma once

#include "IBaseExport.h"
#include "ResourceManagerModule_global.h"

#include <QReadWriteLock>

#include "CommonBase.h"
#include "ResouceLoadCommon.h"
#include <QMap>
#include <QSharedPointer>
#include <QVector>

class ResourceManagerModule;

using ResourcesManagerPtr = QSharedPointer<ResourceManagerModule>;
using StringPrtMapType    = QMap<QString, PtrType>;
using ResourceTypePtr     = QSharedPointer<StringPrtMapType>;
using ResourceVector      = QVector<ResourceTypePtr>;

class RESOURCEMANAGERMODULE_EXPORT ResourceManagerModule : public IBaseExport, public IResouceLoad
{
public:
    virtual ~ResourceManagerModule() override;

    virtual void start() override;
    virtual void stop() override;
    virtual void descripte() override;

    static ResourcesManagerPtr instance();

    virtual bool loadResource(const QString &fileName, const ResourceType &type) override final;
    virtual void freeResource(const QString &moduleName, const ResourceType &type) override final;
    virtual PtrType GetResource(const QString &fileName, const ResourceType &type) override final;

private:
    explicit ResourceManagerModule(QObject *parent = nullptr);
    bool loadModuleLibrary(const QString &fileName);
    void clear();

private:
    QReadWriteLock m_moduleLock;

    ResourceVector m_resourceArr;
};
