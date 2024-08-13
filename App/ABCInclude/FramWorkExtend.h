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

