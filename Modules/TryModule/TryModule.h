#ifndef TRYMODULE_H
#define TRYMODULE_H
#include "IBaseExport.h"
#include "TryModule_global.h"

#include <QObject>
#include <QReadWriteLock>

class TryModule;

using TryModulePtr = QSharedPointer< TryModule >;
class TRYMODULE_EXPORT TryModule : public IBaseExport {
public:
    virtual ~TryModule() override;

    virtual void start() override;
    virtual void stop() override;
    virtual void descripte() override;

    static TryModulePtr   instance();

    ResourceFreeType FreeType() const override;
private:
    explicit TryModule(QObject* parent = nullptr);
private:
    const ResourceFreeType m_freeType;
};

#endif // TRYMODULE_H
