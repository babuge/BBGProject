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

