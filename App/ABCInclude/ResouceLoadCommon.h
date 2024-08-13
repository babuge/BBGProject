#pragma once

#include <QString>
#include "CommonBase.h"

namespace ResourceSpace
{

typedef enum class ResourceType_ : int
{
    UNKNOW = 0,
    MODULE,
    PLUGIN,
    ICON,
    COMPONENY,
    BINARYFILE,
    ERROR
} ResourceType;

}  // namespace ResourceSpace

using ResourceSpace::ResourceType;
class IResouceLoad
{
public:
    virtual bool loadResource(const QString &fileName, const ResourceType &type) = 0;
    virtual PtrType GetResource(const QString &fileName, const ResourceType &type) = 0;
    virtual void freeResource(const QString &moduleName, const ResourceType &type) = 0;
};
