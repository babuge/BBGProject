#ifndef PLUGINSTRUCT_H
#define PLUGINSTRUCT_H

#include <QObject>
#include <CommonBase.h>

namespace PluginSpace
{
#pragma pack(1)

class PluginStatus
{
private:
    typedef enum class LifeCycle_
    {
        UNKNOW = 0,
        INSTALLING,
        INSTALLED,
        UNINSTALLING,
        UNINSTALLED,
        ERROR
    } LifeCycle;

public:
    explicit PluginStatus(PtrType inPtr = nullptr) : m_status(LifeCycle::UNKNOW), m_ptr(inPtr) {}

    void deleteLater()
    {
        if (m_ptr != nullptr) {
            reinterpret_cast<QObject *>(m_ptr)->deleteLater();
        }
    }

    bool isUnknow() const
    {
        return m_status == LifeCycle::UNKNOW;
    }
    bool isInstalling() const
    {
        return m_status == LifeCycle::INSTALLING;
    }
    bool isInstalled() const
    {
        return m_status == LifeCycle::INSTALLED;
    }
    bool isUnInstalling() const
    {
        return m_status == LifeCycle::UNINSTALLING;
    }
    bool isUnInstalled() const
    {
        return m_status == LifeCycle::UNINSTALLED;
    }
    bool isError() const
    {
        return m_status == LifeCycle::ERROR;
    }

    template <class T>
    T getObjPtr() {
        return reinterpret_cast<T*>(m_ptr);
    }

    unsigned char status() const
    {
        return static_cast<unsigned char>(m_status);
    }


private:
    LifeCycle m_status;
    PtrType m_ptr = nullptr;
};

#pragma pack()

}  // namespace PluginSpace

#endif  // PLUGINSTRUCT_H
