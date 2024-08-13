#include "BussinessModule.h"

#include <QDebug>

BussinessModule::BussinessModule(QObject *parent)
    : IBaseExport(parent), m_freeType(ResourceFreeType::EXTRA)
{
}

BussinessModule::~BussinessModule()
{
    qDebug() << "析构~BussinessModule";
}

void BussinessModule::start()
{
    // 线程：重新更新状态库状态
    if (!isRunning()) {
        setStatus(LifeCycleStatus::RUNNING);
        qDebug() << "BussinessModule 开始运行 操作" << this;
        // ...
    }
}

void BussinessModule::stop()
{
    // 线程：处理库公共状态，重置为初始状态
    if (isRunning()) {
        setStatus(LifeCycleStatus::FINISH);
        qDebug() << "BussinessModule 结束运行 操作" << this;
        // ...
    }
}
void BussinessModule::descripte()
{
    qDebug() << "BussinessModule::descripte!";
}

IBaseExport::ResourceFreeType BussinessModule::FreeType() const
{
    return m_freeType;
}

extern "C" BUSSINESSMODULE_EXPORT const void *Get()
{
    return static_cast<void *>(new BussinessModule);
}
