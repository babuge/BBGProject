/******************************************************************************
 * Copyright (C) [2024] [github.com/babuge]
 *
 * [BBGProject] is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan
 * PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 * 文件名称 ：   PluginSpace.h
 * 文件标识 ：
 * 摘 要 ：     
 * 当前版本 ：   v0.01.1
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.01.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/12
 ******************************************************************************/
#pragma once

#include <CommonBase.h>
#include <QObject>

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
    T getObjPtr()
    {
        return reinterpret_cast<T *>(m_ptr);
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
