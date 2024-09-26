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
 * 文件名称 ：   LoggerManager.h
 * 文件标识 ：
 * 摘 要 ：
 * 当前版本 ：   v0.01.1
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.01.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/09/27
 ******************************************************************************/
#pragma once

#include "IBaseExport.h"
#include "LoggerManager_global.h"
#include <QMutex>

class LoggerManagerPrivate;
class LOGGERMANAGER_EXPORT LoggerManager : public IBaseExport
{
public:
    enum LogOutType
    {
        LogOutConsole = 0x01,
        LogOutFile    = 0x02,
    };
    enum LogLevel
    {
        LogLevelTrace = 0,
        LogLevelDebug,
        LogLevelInfo,
        LogLevelWarning,
        LogLevelCritical,
        LogLevelFatal,
        LogLevelMax
    };

public:
    LoggerManager();
    virtual ~LoggerManager();

    virtual void start() override;
    virtual void stop() override;
    virtual void descripte() override;
    IBaseExport::ResourceFreeType FreeType() const override;

public:
    void initialize();
    void release();
    static LoggerManager *instance();
    static void
    handleMessage(QtMsgType type, const QMessageLogContext &context, const QString &message);

    void LoggerOutFile(QtMsgType type,
                       const QMessageLogContext &context,
                       const QString &message,
                       const QString &strDateTime);

    void LoggerOutConsole(QtMsgType type,
                          const QMessageLogContext &context,
                          const QString &message,
                          const QString &strDateTime);

    int LoggerOutType() const;

    void SetLoggerOutType(int outType = 0x03);

    bool IsFileterLevel(QtMsgType type);
    int LoggerOutLevel() const;
    void SetLoggerOutLevel(int outLevel = (int)LogLevelDebug);

private:
    static LoggerManager *m_pLogManaer;
    static QMutex m_MutexLogManaer;
    EXPORT_EXTRA_GC(LoggerManager)
private:
    Q_DISABLE_COPY(LoggerManager)
    Q_DECLARE_PRIVATE(LoggerManager)
    LoggerManagerPrivate *d_ptr;
};
