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
