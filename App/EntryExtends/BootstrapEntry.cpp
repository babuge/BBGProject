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
 * 文件名称 ：   BootstrapEntry.cpp
 * 文件标识 ：
 * 摘 要 ：     
 * 当前版本 ：   v0.01.1
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.01.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/12
 ******************************************************************************/
#include "BootstrapEntry.h"
#include "TryUtil.h"

#include "BussinessModule.h"
#include "ModulesManager.h"
#include "PluginsManager.h"
#include "ResourceManagerModule.h"
#include "TryModule.h"

#include <QJsonObject>
#include <QLibrary>
#include <QTime>
#include <QTimer>
#include <QVariantMap>

#include <QDebug>

BootstrapEntry::BootstrapEntry(QObject *parent)
    : QObject(parent)
{
    m_coreHandle.clear();
    m_coreLibs.clear();
    m_config.setCore({ "ResourceManagerModule", "ModulesManager" });  //, "PluginsManager" });
    m_config.setBussiness({});
}

BootstrapEntry::~BootstrapEntry()
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    QElapsedTimer elapsed;
#else
    QTime elapsed;
#endif
    elapsed.start();
    qDebug() << "析构~BootstrapEntry-start: 0 ms";
    if (isRunning()) {
        stop();
    }
    qDebug() << "析构~BootstrapEntry-end:" << elapsed.elapsed() << "ms";
}

void BootstrapEntry::start()
{
    if (!isRunning()) {
        setStatus(LifeCycleStatus::RUNNING);
        init();
    }
}

void BootstrapEntry::restart()
{
    stop();
    QTimer::singleShot(100, this, [=]() { start(); });
}

void BootstrapEntry::stop()
{
    if (isRunning()) {
        setStatus(LifeCycleStatus::FINISH);
        unInit();
    }
}

void BootstrapEntry::InitConfig()
{
    QString path = QDir::current().path() + QDir::separator() + ".config.json";
    QFile file(path);
    QJsonObject obj;
    if (file.exists()) {
        obj = TryUtil::ReadJson(path, obj);
        if (!obj.isEmpty()) {
        }
        qDebug() << "json: " << obj;
    }

    path = QDir::current().path() + QDir::separator()
           + QString(".config%1.json")
                 .arg(QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz"));
    if (TryUtil::WriteJson(path, obj)) {
        qDebug() << "WriteJson done!";
    }
    else {
        qDebug() << "WriteJson failed!";
    }

    if (!obj.empty()) {
        m_config.read(obj);
    }
    initBoostStrap();
}

void BootstrapEntry::initBoostStrap()
{
    QStringList cores = m_config.core();
    cores.removeDuplicates();
    m_coreLibs = cores.toVector();

    QMap<QString, int> mp_Module;
    QStringList array = m_config.bussiness();
    for (int i = 0; i < array.size(); ++i) {
        mp_Module.insert(array.at(i), static_cast<int>(ResourceType::MODULE));
    }
    if (!mp_Module.isEmpty()) {
        TryUtil::VectorUniqueAdd<QMap<QString, int>>(m_bussinessLibs, mp_Module);
    }
}

void BootstrapEntry::init()
{

    // 应用初始化核心列表并加载内部核心项
    {
        CoreType::const_iterator it = m_coreLibs.constBegin();
        while (it != m_coreLibs.constEnd()) {
            if (loadCore(*it))  // or :signal - concurrence
            {
                qDebug() << QString("loaded core: %1!").arg(*it);
            }
            ++it;
        }

        // debug 核心模块并运行
        QMap<QString, PtrType>::const_iterator item = m_coreHandle.constBegin();
        while (item != m_coreHandle.constEnd()) {
            if (auto pCore = getObjPtr<IBaseExport *>(item.key())) {
                pCore->start();
                pCore->descripte();
            }
            ++item;
        }
    }

    // 加载业务模块并存储到资源模块
    {
        if (auto resources = getObjPtr<ResourceManagerModule *>("ResourceManagerModule")) {
            BussinessType::const_iterator it = m_bussinessLibs.constBegin();
            while (it != m_bussinessLibs.constEnd()) {
                QMap<QString, int>::const_iterator subIt = it->constBegin();
                while (subIt != it->constEnd()) {
                    resources->descripte();
                    IResouceLoad *p_resources = resources;
                    if (p_resources->loadResource(subIt.key(),
                                                  static_cast<ResourceType>(subIt.value()))) {
                        qDebug() << QString("loaded bussiness: %1!").arg(subIt.key());
                    }
                    ++subIt;
                }
                ++it;
            }
        }

        // debug： 业务模块 并 运行
        if (auto resources = getObjPtr<ResourceManagerModule *>("ResourceManagerModule")) {
            BussinessType::const_iterator it = m_bussinessLibs.constBegin();
            while (it != m_bussinessLibs.constEnd()) {
                QMap<QString, int>::const_iterator subIt = it->constBegin();
                while (subIt != it->constEnd()) {
                    IResouceLoad *p_resources = resources;
                    if (auto module = p_resources->GetResource(
                            subIt.key(), static_cast<ResourceType>(subIt.value()))) {
                        IBaseExport *p_Export = reinterpret_cast<IBaseExport *>(module);
                        p_Export->descripte();
                        p_Export->start();
                    }
                    ++subIt;
                }
                ++it;
            }
        }
    }

    QTimer::singleShot(10000, this, [=]() { restart(); });
}

void BootstrapEntry::unInit()
{
    // 业务模块退出运行状态
    if (auto resources = getObjPtr<ResourceManagerModule *>("ResourceManagerModule")) {
        BussinessType::iterator it = m_bussinessLibs.begin();
        while (it != m_bussinessLibs.end()) {
            QMap<QString, int>::iterator subIt = it->begin();
            while (subIt != it->end()) {
                IResouceLoad *p_resources = resources;
                p_resources->freeResource(subIt.key(), static_cast<ResourceType>(subIt.value()));
                ++subIt;
            }
            ++it;
        }
    }

    // 核心模块退出运行状态
    {
        CoreType::iterator it = m_coreLibs.begin();
        while (it != m_coreLibs.end()) {
            QMap<QString, PtrType>::iterator item = m_coreHandle.find(*it);
            if (item != m_coreHandle.end()) {
                if (auto pCore = getObjPtr<IBaseExport *>(item.key())) {
                    pCore->stop();
                    m_coreHandle.remove(*it);
                }
            }
            ++it;
        }
    }
}

template <class T>
T BootstrapEntry::getObjPtr(const QString &name)
{
    if (m_coreHandle.contains(name) && m_coreHandle.value(name) != nullptr) {
        return reinterpret_cast<T>(m_coreHandle.value(name));
    }
    return static_cast<T>(nullptr);
}

bool BootstrapEntry::loadCore(const QString &name)
{
    PtrType ptr = nullptr;
    {
        QReadLocker mlock(&m_lock);
        if (m_coreHandle.contains(name)) {
            qDebug() << QString("%1 :core exist!").arg(name);
            return false;
        }
    }
    if (TryUtil::GetLibHandle(name, ptr)) {
        QWriteLocker mlock(&m_lock);
        m_coreHandle.insert(name, ptr);
        return true;
    }
    return false;
}
