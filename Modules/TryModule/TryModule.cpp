#include "TryModule.h"
#include <QSharedPointer>
#include <iostream>

#include <QDebug>

TryModule::TryModule(QObject *parent) : IBaseExport(parent), m_freeType(ResourceFreeType::AUTO) {}

TryModule::~TryModule()
{
    qDebug() << "析构~TryModule";
}

TryModulePtr TryModule::instance()
{
    static TryModulePtr main = QSharedPointer<TryModule>(new TryModule);
    return main;
}

void TryModule::start()
{
    // 线程：重新更新状态库状态
    if (!isRunning()) {
        qDebug() << "TryModule 开始运行 操作" << this;
        // ...
        setStatus(LifeCycleStatus::RUNNING);
    }
}

IBaseExport::ResourceFreeType TryModule::FreeType() const
{
    return m_freeType;
}

void TryModule::stop()
{
    // 线程：处理库公共状态，重置为初始状态
    if (isRunning()) {
        qDebug() << "TryModule 结束运行 操作" << this;
        // ...
        setStatus(LifeCycleStatus::FINISH);
    }
}

void TryModule::descripte()
{
    // std::cout << "cout output!" << std::endl;
    qDebug() << "TryModule::descripte!";
}

extern "C" TRYMODULE_EXPORT const void *Get()
{
    return static_cast<void *>(TryModule::instance().data());
}
