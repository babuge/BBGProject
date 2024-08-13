#pragma once

#include "FramWorkExtend.h"
#include <QObject>

#include <QDebug>

class IBaseExport : public QObject
{
protected:
    LIFECYCLE_STATUS
public:
    typedef enum class ResourceFreeType_ : int
    {
        AUTO = 0,
        EXTRA
    } ResourceFreeType;
    explicit IBaseExport(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IBaseExport() {}

    virtual void start()     = 0;
    virtual void stop()      = 0;
    virtual void descripte() = 0;

    virtual ResourceFreeType FreeType() const
    {
        return ResourceFreeType::AUTO;
    }
};

