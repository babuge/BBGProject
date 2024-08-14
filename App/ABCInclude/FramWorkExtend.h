/******************************************************************************
 * Copyright (C) [2024] [github.com/babuge]
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * 文件名称 ：   FrameWorkExtend.h
 * 文件标识 ：
 * 摘 要 ：     应用程序框架扩展定义
 * 当前版本 ：   v0.01.0
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.0.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/12
 ******************************************************************************/
#pragma once

// 手动回收垃圾机制
#define EXPORT_EXTRA_GC(X)                                                                         \
    typedef class GC_                                                                              \
    {                                                                                              \
    public:                                                                                        \
        explicit GC_(X *p = nullptr) : m_p(p) {}                                                   \
        ~GC_()                                                                                     \
        {                                                                                          \
            if (m_p->isRunning()) {                                                                \
                m_p->stop();                                                                       \
                m_p->deleteLater();                                                                \
            }                                                                                      \
        }                                                                                          \
                                                                                                   \
    private:                                                                                       \
        X *m_p{ nullptr };                                                                         \
    } GC;

// 简单的生命周期定义
#define LIFECYCLE_STATUS                                                                           \
public:                                                                                            \
    typedef enum class RunningStatus_ : int                                                        \
    {                                                                                              \
        UNKNOW = 0,                                                                                \
        RUNNING,                                                                                   \
        FINISH                                                                                     \
    } LifeCycleStatus;                                                                             \
    bool isRunning()                                                                               \
    {                                                                                              \
        return m_status == LifeCycleStatus::RUNNING;                                               \
    }                                                                                              \
    void setStatus(const LifeCycleStatus &status)                                                  \
    {                                                                                              \
        m_status = status;                                                                         \
    }                                                                                              \
                                                                                                   \
private:                                                                                           \
    LifeCycleStatus m_status{ LifeCycleStatus::UNKNOW };

