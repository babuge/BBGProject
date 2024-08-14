#include "ModulesManager.h"
#include "TryUtil.h"

#include <QReadLocker>
#include <QWriteLocker>

static QMap<QString, void *> g_golbalLibraryMap;

ModulesManager::ModulesManager(QObject *parent) : IBaseExport(parent) {}

ModulesManager::~ModulesManager()
{
    qDebug() << "析构~ModulesManager";
}

ModulesManagerPtr ModulesManager::instance()
{
    static ModulesManagerPtr main = QSharedPointer<ModulesManager>(new ModulesManager);
    return main;
}

void ModulesManager::start()
{
    // 线程：重新更新状态库状态
    if (!isRunning()) {
        qDebug() << "ModulesManager 开始运行 操作";
        // ...
        setStatus(LifeCycleStatus::RUNNING);
    }
}

void ModulesManager::stop()
{
    // 线程：处理库公共状态，重置为初始状态
    if (isRunning()) {
        qDebug() << "ModulesManager 结束运行 操作";
        // ...
        setStatus(LifeCycleStatus::FINISH);
    }
}

void ModulesManager::descripte()
{
    qDebug() << "ModulesManager::descripte";
}

bool ModulesManager::loadModuleLibrary(const QString &moduleName)
{
    PtrType ptr = nullptr;
    if (TryUtil::GetLibHandle(moduleName, ptr)) {
        QWriteLocker lock(&m_lock);
        g_golbalLibraryMap.insert(moduleName, ptr);
        qDebug() << g_golbalLibraryMap;
        return true;
    }
    return false;
}

void *ModulesManager::getModule(const QString &moduleName)
{
    if (g_golbalLibraryMap.contains(moduleName)) {
        QReadLocker lock(&m_lock);
        return g_golbalLibraryMap.value(moduleName);
    }
    return nullptr;
}

extern "C" MODULESMANAGER_EXPORT const void *Get()
{
    return static_cast<void *>(ModulesManager::instance().data());
}
