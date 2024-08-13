#ifndef BASEEXPORT_H
#define BASEEXPORT_H
#include "FramWorkExtend.h"
#include <QObject>

#include <QDebug>

class BaseExport : public QObject
{
protected:
    LIFECYCLE_STATUS
public:
    typedef enum class ResourceFreeType_ : int
    {
        AUTO = 0,
        EXTRA
    } ResourceFreeType;
    explicit BaseExport(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~BaseExport() {}

    virtual void start()     = 0;
    virtual void stop()      = 0;
    virtual void descripte() = 0;

    virtual ResourceFreeType FreeType() const
    {
        return ResourceFreeType::AUTO;
    }
};

#endif  // BASEEXPORT_H
