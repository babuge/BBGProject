#ifndef BUSSINESSMODULE_H
#define BUSSINESSMODULE_H

#include "BaseExport.h"
#include "BussinessModule_global.h"

#include <QSharedPointer>

class BUSSINESSMODULE_EXPORT BussinessModule : public BaseExport
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

#endif // BUSSINESSMODULE_H
