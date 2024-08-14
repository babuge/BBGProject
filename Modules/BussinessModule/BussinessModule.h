#pragma once

#include "BussinessModule_global.h"
#include "IBaseExport.h"

#include <QSharedPointer>

class BUSSINESSMODULE_EXPORT BussinessModule : public IBaseExport
{
public:
    typedef QSharedPointer<BussinessModule> ptr;
    explicit BussinessModule(QObject *parent = nullptr);
    ~BussinessModule();

    virtual void start() final;
    virtual void stop() final;
    virtual void descripte() final;

    ResourceFreeType FreeType() const override final;

private:
    EXPORT_EXTRA_GC(BussinessModule)
private:
    const ResourceFreeType m_freeType;
    GC m_gc{ this };
};
