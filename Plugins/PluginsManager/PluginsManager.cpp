#include "PluginsManager.h"
#include "PluginSpace.h"

#include <QReadLocker>
#include <QSharedPointer>
#include <QWriteLocker>

#include <QDebug>

QMap<QString, PluginsStatusPtr> g_golbalPluginsStatus;
QReadWriteLock PluginsManager::m_rwLock;
PluginsManager::PluginsManager(QObject *parent) : IBaseExport(parent) {}

PluginsManagerPtr PluginsManager::instance()
{
    static PluginsManagerPtr main = QSharedPointer<PluginsManager>(new PluginsManager);
    return main;
}

PluginsManager::~PluginsManager()
{
    // This function does nothing if the thread does not have an event loop.
    if (m_pluginCheck != nullptr) {
        m_pluginCheck->quit();
        m_pluginCheck->wait();
    }
    qDebug() << "析构~PluginsManager";
}

void PluginsManager::start()
{
    // 线程：重新更新状态库状态
    if (!isRunning()) {
        qDebug() << "PluginsManager 开始运行 操作";
        startCheck();
        // ...

        setStatus(LifeCycleStatus::RUNNING);
    }
}

void PluginsManager::stop()
{
    // 线程：处理库公共状态，重置为初始状态
    if (isRunning()) {
        stopCheck();
        qDebug() << "PluginsManager 结束运行 操作";
        // ...

        setStatus(LifeCycleStatus::FINISH);
    }
}

void PluginsManager::descripte()
{
    qDebug() << "PluginsManager::descripte";
}

void PluginsManager::updatePlugin(const QString &pluginNmae, PluginsStatusPtr &pluginStatus)
{

    if (g_golbalPluginsStatus.contains(pluginNmae)) {
        PluginsStatusPtr oldStatu = g_golbalPluginsStatus.value(pluginNmae);
        if (oldStatu->status() != pluginStatus->status()) {
            qDebug() << "Plugin status change:" << oldStatu->status() << "-->"
                     << pluginStatus->status();
        }
    }
    else {
        qDebug() << "add Plugin:" << pluginNmae;
    }

    {
        QWriteLocker lock(&m_rwLock);
        g_golbalPluginsStatus.insert(pluginNmae, pluginStatus);
    }
}

void PluginsManager::clear()
{
    QWriteLocker writeLocker(&m_rwLock);
    QMap<QString, PluginsStatusPtr>::iterator it = g_golbalPluginsStatus.begin();
    while (it != g_golbalPluginsStatus.end()) {
        if (it.value()->isUnInstalled()) {
            qDebug() << "remove plugin: " << it.key();
            it.value()->deleteLater();
            // it = g_golbalPluginsStatus.earse(it);
            g_golbalPluginsStatus.remove((it++).key());
        }
        else {
            ++it;
        }
    }
}

PluginsStatusPtr PluginsManager::getPlugin(const QString &pluginName)
{
    if (g_golbalPluginsStatus.contains(pluginName)) {
        QReadLocker lock(&m_rwLock);
        return g_golbalPluginsStatus.value(pluginName);
    }
    return QSharedPointer<PluginSpace::PluginStatus>();
}

void PluginsManager::startCheck()
{
    m_pluginCheck = new PluginsStatusCheck;
    connect(m_pluginCheck,
            &PluginsStatusCheck::signal_hasUninstallPlugin,
            this,
            &PluginsManager::slot_hasUninstallPlugin,
            Qt::QueuedConnection);

    connect(m_pluginCheck, &PluginsStatusCheck::finished, m_pluginCheck, &QObject::deleteLater);

    m_pluginCheck->start();
    m_pluginCheck->setRun(true);
}

void PluginsManager::stopCheck()
{
    m_pluginCheck->quit();
    m_pluginCheck->setRun(false);
    m_pluginCheck->wait();
    m_pluginCheck->deleteLater();
    m_pluginCheck = nullptr;
    qDebug() << "Plugins Check end！";
}

void PluginsManager::slot_hasUninstallPlugin()
{
    clear();
}

extern "C" PLUGINSMANAGER_EXPORT const void *Get()
{
    return static_cast<void *>(PluginsManager::instance().data());
}
