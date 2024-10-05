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
 * 文件名称 ：   LoggerManager.cpp
 * 文件标识 ：
 * 摘 要 ：
 * 当前版本 ：   v0.01.1
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.01.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/09/27
 ******************************************************************************/

#include "LoggerManager.h"

#include <QDateTime>
#include <QFileInfo>
#include <QHash>
#include <QTextStream>
#include <QtConcurrent/QtConcurrent>

namespace SPLogMgr
{
const QString str_ConstFormat("(%1)");
const QString str_LogFormat("%1:[%2][%3:%4]%5 %6\n");
const QString str_FileName("LoggerMessage");
const QString str_LogFormat_NonFunction("%1:[%2][%3:%4]: %6\n");
const QHash<int, QString> hash_TypeStr = {
    { QtDebugMsg, "Debug" },
    { QtWarningMsg, "Warning" },
    { QtCriticalMsg, "Critical" },
    { QtFatalMsg, "Fatal" },
};
const QHash<int, int> hash_TypeToLevel = {
    { -1, LoggerManager::LogLevelTrace },  // 无 trace
    { QtDebugMsg, LoggerManager::LogLevelDebug },
    { QtInfoMsg, LoggerManager::LogLevelInfo },
    { QtWarningMsg, LoggerManager::LogLevelWarning },
    { QtCriticalMsg, LoggerManager::LogLevelCritical },
    { QtFatalMsg, LoggerManager::LogLevelFatal },
};
}  // namespace SPLogMgr

class LoggerManagerPrivate
{
    Q_DECLARE_PUBLIC(LoggerManager)
public:
    explicit LoggerManagerPrivate(LoggerManager *qPtr);

    void OpenFile();
    void CloseFile();
    QString UpdateFileName();
    QString LogFormat(QtMsgType type,
                      const QMessageLogContext &context,
                      const QString &message,
                      const QString &strDateTime);

    void DoReNameLogFile();

private:
    LoggerManager *q_ptr;
    QFile *m_pFileLog;
    QMutex m_lock;
    int m_fileSize;
    int m_emOutType;
    int m_s32MaxFile;
    int m_s32Level;
    bool m_blFirstInit;
};

LoggerManagerPrivate::LoggerManagerPrivate(LoggerManager *qPtr)
    : q_ptr(qPtr)
    , m_pFileLog(nullptr)
    , m_fileSize(10 * 1024 * 1024)  // 10M
    , m_emOutType(0x03)
    , m_s32MaxFile(10)  // 10 * file 100M
    , m_s32Level((int)LoggerManager::LogLevelDebug)
    , m_blFirstInit(true)
{
}

void LoggerManagerPrivate::OpenFile()
{
    if (m_pFileLog != nullptr) {
        return;
    }
    // 打开日志文件
    QString str_FileName = UpdateFileName();
    m_pFileLog           = new QFile(str_FileName);
    if (!m_pFileLog->open(QIODevice::WriteOnly | QIODevice::Append)) {
        qWarning("Couldn't open log file");
        m_pFileLog->close();
        delete m_pFileLog;
        m_pFileLog = nullptr;
    }
}
void LoggerManagerPrivate::CloseFile()
{
    if (m_pFileLog != nullptr && m_pFileLog->isOpen()) {
        m_pFileLog->close();
        delete m_pFileLog;
        m_pFileLog = nullptr;
    }
}
QString LoggerManagerPrivate::UpdateFileName()
{
    QString str_File = "./" + SPLogMgr::str_FileName + ".log";
    QFileInfo fileInfo(str_File);
    if (fileInfo.exists()) {
        if (fileInfo.size() > (m_fileSize - 1024)) {
            DoReNameLogFile();
        }
    }
    return str_File;
}

void LoggerManagerPrivate::DoReNameLogFile()
{
    const QString str_Format("%1(%2).log");
    QStringList ls_FileName;
    ls_FileName << QString(SPLogMgr::str_FileName + ".log");
    for (int i = 1; i < m_s32MaxFile; ++i) {
        ls_FileName << str_Format.arg(SPLogMgr::str_FileName, QString::number(i));
    }
    for (int i = m_s32MaxFile - 1; i > 0; --i) {
        QFile file("./" + ls_FileName.at(i));
        if (file.exists()) {
            file.remove();
        }
        if (i - 1 < m_s32MaxFile) {
            QFile file("./" + ls_FileName.at(i - 1));
            if (file.exists()) {
                if (!file.rename("./" + ls_FileName.at(i))) {
                    fprintf(stderr, "%s", "rename file failed!");
                }
            }
        }
    }
}

QString LoggerManagerPrivate::LogFormat(QtMsgType type,
                                        const QMessageLogContext &context,
                                        const QString &message,
                                        const QString &strDateTime)
{
    QString str_Ret  = "";
    QString str_file = context.file ? context.file : "";
    str_file.replace("\\", "/");
    // const QString str_function = context.function ? context.function : "";
    QString str_Type = "Info";
    if (SPLogMgr::hash_TypeStr.contains(type)) {
        str_Type = SPLogMgr::hash_TypeStr.value(type);
    }
    // str_Ret = SPLogMgr::str_LogFormat.arg(str_Type, strDateTime, str_file,
    // QString::number(context.line), str_function, message);
    str_Ret = SPLogMgr::str_LogFormat_NonFunction.arg(
        str_Type, strDateTime, str_file, QString::number(context.line), message);
    return str_Ret;
}

// ======private class LoggerManagerPrivate=====

LoggerManager *LoggerManager::m_pLogManaer = nullptr;
QMutex LoggerManager::m_MutexLogManaer;

LoggerManager::LoggerManager()
    : d_ptr(new LoggerManagerPrivate(this))
{
    if (d_ptr != nullptr) {
        d_ptr->OpenFile();
    }
}

LoggerManager::~LoggerManager()
{
    if (d_ptr != nullptr) {
        d_ptr->CloseFile();
    }

    if (d_ptr != nullptr) {
        delete d_ptr;
        d_ptr = nullptr;
    }
}
void LoggerManager::start()
{
    // 线程：重新更新状态库状态
    if (!isRunning()) {
        initialize();
        qDebug() << "LoggerManager Strat Runing Operator" << this;
        // ...
        setStatus(LifeCycleStatus::RUNNING);
    }
}

IBaseExport::ResourceFreeType LoggerManager::FreeType() const
{
    return ResourceFreeType::EXTRA;
}

void LoggerManager::stop()
{
    // 线程：处理库公共状态，重置为初始状态
    if (isRunning()) {
        qDebug() << "LoggerManager Stop Runing Operator" << this;
        // ...
        setStatus(LifeCycleStatus::FINISH);
    }
}

void LoggerManager::descripte()
{
    // std::cout << "cout output!" << std::endl;
    qDebug() << "LoggerManager::descripte!";
}

void LoggerManager::initialize()
{
    Q_D(LoggerManager);
    if (d->m_blFirstInit == true) {
        d->m_blFirstInit = false;
        // SetLoggerOutType((int)CLogManager::LogOutFile);
        // SetLoggerOutLevel(CLogManager::LogLevelWarning);
        qInstallMessageHandler(LoggerManager::handleMessage);
    }
}

void LoggerManager::release()
{
    qInstallMessageHandler(nullptr);
}
LoggerManager *LoggerManager::instance()
{
    if (m_pLogManaer == nullptr) {
        QMutexLocker lock(&m_MutexLogManaer);
        if (m_pLogManaer == nullptr) {
            m_pLogManaer = new LoggerManager;
        }
    }
    return m_pLogManaer;
}

int LoggerManager::LoggerOutType() const
{
    Q_D(const LoggerManager);
    return d->m_emOutType;
}

void LoggerManager::SetLoggerOutType(int outType)
{
    Q_D(LoggerManager);
    d->m_emOutType = outType;
}

int LoggerManager::LoggerOutLevel() const
{
    Q_D(const LoggerManager);
    return d->m_s32Level;
}

void LoggerManager::SetLoggerOutLevel(int outLevel)
{
    Q_D(LoggerManager);
    d->m_s32Level = outLevel;
}

void LoggerManager::handleMessage(QtMsgType type,
                                  const QMessageLogContext &context,
                                  const QString &message)
{
    QString str_DateTime    = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    LoggerManager *p_LogMgr = LoggerManager::instance();
    if (p_LogMgr == nullptr) {
        return;
    }
    int s32_OutType = p_LogMgr->LoggerOutType();

    if (p_LogMgr->IsFileterLevel(type)) {
        return;
    }

    if (s32_OutType & LoggerManager::LogOutFile) {
        p_LogMgr->LoggerOutFile(type, context, message, str_DateTime);
    }

    if (s32_OutType & LoggerManager::LogOutConsole) {
        p_LogMgr->LoggerOutConsole(type, context, message, str_DateTime);
    }
}

void LoggerManager::LoggerOutFile(QtMsgType type,
                                  const QMessageLogContext &context,
                                  const QString &message,
                                  const QString &strDateTime)
{
    Q_D(LoggerManager);
    QMutexLocker lock(&d->m_lock);
    if (d->m_pFileLog == nullptr) {
        return;
    }
    if (d->m_pFileLog->size() > d->m_fileSize) {
        d->m_pFileLog->flush();
        d->CloseFile();
        d->OpenFile();
    }
    if (d->m_pFileLog == nullptr) {
        return;
    }

    QTextStream textStream(d->m_pFileLog);
    QString str_log = d->LogFormat(type, context, message, strDateTime);
    textStream << str_log.toLocal8Bit();
    // 如果是严重错误，则退出程序
    if (type == QtFatalMsg) {
        d->m_pFileLog->flush();
        abort();
    }
}

bool LoggerManager::IsFileterLevel(QtMsgType type)
{
    Q_D(LoggerManager);
    bool bl_Ret = false;
    if (SPLogMgr::hash_TypeToLevel.contains(type)) {
        if (d->m_s32Level > SPLogMgr::hash_TypeToLevel.value(type)) {
            bl_Ret = true;
        }
    }
    return bl_Ret;
}

void LoggerManager::LoggerOutConsole(QtMsgType type,
                                     const QMessageLogContext &context,
                                     const QString &message,
                                     const QString &strDateTime)
{
    Q_D(LoggerManager);
    QString str_log     = d->LogFormat(type, context, message, strDateTime);
    QByteArray byte_log = str_log.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
    case QtInfoMsg:
        fprintf(stdout, "%s", byte_log.constData());
        break;
    case QtWarningMsg:
    case QtCriticalMsg:
    case QtFatalMsg:
        fprintf(stderr, "%s", byte_log.constData());
        break;
    }
    fflush(stdout);
    if (type == QtFatalMsg) {
        abort();
    }
}

extern "C" LOGGERMANAGER_EXPORT const void *Get()
{
    return static_cast<void *>(LoggerManager::instance());
}
