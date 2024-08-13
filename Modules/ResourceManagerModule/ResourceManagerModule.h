#pragma once

#include "BaseExport.h"
#include "ResourceManagerModule_global.h"

#include <QReadWriteLock>

#include <QMap>
#include <QSharedPointer>
#include <QVector>
#include "CommonBase.h"
#include "ResouceLoadCommon.h"

class ResourceManagerModule;

using ResourcesManagerPtr = QSharedPointer<ResourceManagerModule>;
using StringPrtMapType    = QMap<QString, PtrType>;
using ResourceTypePtr     = QSharedPointer<StringPrtMapType>;
using ResourceVector      = QVector<ResourceTypePtr>;

class RESOURCEMANAGERMODULE_EXPORT ResourceManagerModule : public BaseExport, public IResouceLoad
{

public:
    virtual ~ResourceManagerModule() override;

    virtual void start() override;
    virtual void stop() override;
    virtual void descripte() override;

    static ResourcesManagerPtr instance();

    virtual bool loadResource(const QString &fileName, const ResourceType &type) override final;
    virtual void freeResource(const QString &moduleName, const ResourceType &type) override final;
    virtual PtrType GetResource(const QString &fileName, const ResourceType &type) override final;

private:
    explicit ResourceManagerModule(QObject *parent = nullptr);
    bool loadModuleLibrary(const QString &fileName);
    void clear();

private:
    QReadWriteLock m_moduleLock;

    ResourceVector m_resourceArr;
};

