#ifndef MODULESMANAGER_H
#define MODULESMANAGER_H

#include "IBaseExport.h"
#include "ModulesManager_global.h"

#include <QLibrary>
#include <QMap>
#include <QObject>
#include <QReadWriteLock>

#include <QDebug>

class ModulesManager;
using ModulesManagerPtr = QSharedPointer<ModulesManager>;

class MODULESMANAGER_EXPORT ModulesManager : public IBaseExport
{
    Q_OBJECT
public:
    explicit ModulesManager(QObject *parent = nullptr);

    static ModulesManagerPtr instance();
    virtual ~ModulesManager() override;

    void start() override;
    void stop() override;
    void descripte() override;

    bool loadModuleLibrary(const QString &moduleName);
    void *getModule(const QString &moduleName);

private:
    QReadWriteLock m_lock;
};

#endif // MODULESMANAGER_H
