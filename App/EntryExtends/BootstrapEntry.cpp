#include "BootstrapEntry.h"
#include "TryUtil.h"

#include "BussinessModule.h"
#include "ModulesManager.h"
#include "PluginsManager.h"
#include "ResourceManagerModule.h"
#include "TryModule.h"

#include <QJsonObject>
#include <QLibrary>
#include <QTimer>
#include <QVariantMap>

#include <QDebug>

BootstrapEntry::BootstrapEntry(QObject *parent) : QObject(parent)
{
    m_coreHandle.clear();
    m_coreLibs.clear();
    m_config.setCore({ "ResourceManagerModule", "ModulesManager", "PluginsManager" });
    m_config.setBussiness({});
}

BootstrapEntry::~BootstrapEntry()
{
    qDebug() << "析构~BootstrapEntry";
    if (isRunning()) {
        stop();
    }
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

void BootstrapEntry::setConfig(const QJsonObject &json)
{
    if (!json.empty()) {
        m_config.read(json);
    }
    initBoostStrap();
}

void BootstrapEntry::initBoostStrap()
{
    QStringList cores = m_config.core();
    cores.removeDuplicates();
    m_coreLibs = cores.toVector();

    QMap<QString, int> moduleM;
    QStringList array = m_config.bussiness();
    for (int i = 0; i < array.size(); ++i) {
        moduleM.insert(array.at(i), static_cast<int>(ResourceType::MODULE));
    }
    if (!moduleM.isEmpty()) {
        TryUtil::VectorUniqueAdd<QMap<QString, int>>(m_bussinessLibs, moduleM);
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
