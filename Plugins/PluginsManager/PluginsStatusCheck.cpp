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
