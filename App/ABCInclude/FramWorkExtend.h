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
        explicit GC_(X *p = nullptr)                                                               \
            : m_p(p)                                                                               \
        {                                                                                          \
        }                                                                                          \
        ~GC_()                                                                                     \
        {                                                                                          \
            if (m_p != nullptr && m_p->isRunning()) {                                              \
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
