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
 * 文件名称 ：   ResourceManagerModule.cpp
 * 文件标识 ：
 * 摘 要 ：
 * 当前版本 ：   v0.01.1
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.01.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/12
 ******************************************************************************/
#include "ResourceManagerModule.h"
#include "TryUtil.h"

#include <QEventLoop>
#include <QLibrary>
#include <QReadLocker>
#include <QSharedPointer>
#include <QWriteLocker>

#include <QDebug>

ResourceManagerModule::ResourceManagerModule(QObject *parent)
    : IBaseExport(parent)
{
    m_resourceArr.resize(6);
    for (int i = 0; i < 6; ++i) {
        m_resourceArr[i] = QSharedPointer<StringPrtMapType>(new StringPrtMapType);
    }
}

ResourcesManagerPtr ResourceManagerModule::instance()
{
    static ResourcesManagerPtr main =
        QSharedPointer<ResourceManagerModule>(new ResourceManagerModule);
    return main;
}

ResourceManagerModule::~ResourceManagerModule()
{
    qDebug() << " free ~ResourceManagerModule";
}

void ResourceManagerModule::start()
{
    // 线程：重新更新状态库状态
    if (!isRunning()) {
        setStatus(LifeCycleStatus::RUNNING);
        qDebug() << "ResourceManagerModule Strat Runing Operator";
        // ...
    }
}

void ResourceManagerModule::stop()
{
    // 线程：处理库公共状态，重置为初始状态
    if (isRunning()) {
        setStatus(LifeCycleStatus::FINISH);
        qDebug() << "ResourceManagerModule Stop Runing Operator";
        // ...
    }
}

void ResourceManagerModule::descripte()
{
    qDebug() << "ResourceManagerModule::descripte";
}

extern "C" RESOURCEMANAGERMODULE_EXPORT const void *Get()
{
    return static_cast<void *>(ResourceManagerModule::instance().data());
}

bool ResourceManagerModule::loadResource(const QString &fileName, const ResourceType &type)
{
    switch (type) {
    case ResourceType::UNKNOW:
        return false;
    case ResourceType::MODULE:
        return loadModuleLibrary(fileName);
    case ResourceType::PLUGIN:
        return false;
    case ResourceType::COMPONENY:
        return false;
    case ResourceType::ICON:
        return false;
    case ResourceType::BINARYFILE:
        return false;
    default:
        return false;
    }
}

bool ResourceManagerModule::loadModuleLibrary(const QString &fileName)
{
    //    SharedVoidPtr ;
    ResourceTypePtr itemMap = m_resourceArr[static_cast<int>(ResourceType::MODULE)];
    {
        QReadLocker lock(&m_moduleLock);
        if (itemMap->contains(fileName)) {
            qDebug() << QString("exist %1!").arg(fileName);
            return false;
        }
    }

    PtrType ptr = nullptr;
    if (TryUtil::GetLibHandle(fileName, ptr)) {
        QWriteLocker lock(&m_moduleLock);
        itemMap->insert(fileName, ptr);
        qDebug() << fileName << " loaded success!";
        return true;
    }

    return false;
}

PtrType ResourceManagerModule::GetResource(const QString &moduleName, const ResourceType &type)
{
    if (m_resourceArr[static_cast<int>(type)]->contains(moduleName)) {
        return reinterpret_cast<PtrType>(m_resourceArr[static_cast<int>(type)]->value(moduleName));
    }
    return nullptr;
}

void ResourceManagerModule::freeResource(const QString &moduleName,
                                         const ResourceSpace::ResourceType &type)
{
    if (m_resourceArr[static_cast<int>(type)]->contains(moduleName)) {
        auto module = reinterpret_cast<IBaseExport *>(
            m_resourceArr[static_cast<int>(type)]->value(moduleName));
        if (module->isRunning()) {
            module->stop();
            if (module->FreeType() == ResourceFreeType::EXTRA) {
                // If deleteLater() is called after the main event loop has stopped(mean application
                // quit), the object will not be deleted.
                reinterpret_cast<IBaseExport *>(
                    m_resourceArr[static_cast<int>(type)]->value(moduleName))
                    ->deleteLater();
            }
        }
        m_resourceArr[static_cast<int>(type)]->remove(moduleName);
    }
}

void ResourceManagerModule::clear()
{
    while (m_resourceArr.length()) {
        ResourceTypePtr mpPtr = m_resourceArr.last();
        if (!mpPtr.isNull()) {
            while (mpPtr->size()) {
                QObject *q_obj = reinterpret_cast<QObject *>(mpPtr->take(mpPtr->lastKey()));
                if (q_obj) {
                    q_obj->deleteLater();
                }
            }
        }
        m_resourceArr.removeFirst();
    }
}
