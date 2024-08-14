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
