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
 * 文件名称 ：   TryUtil.h
 * 文件标识 ：
 * 摘 要 ：     尝试动态库加载工具类头文件
 * 当前版本 ：   v0.01.0
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.0.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/14
 ******************************************************************************/
#pragma once

#include <QByteArray>
#include <QCoreApplication>
#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLibrary>
#include <QList>
#include <QVector>

#include "CommonBase.h"

typedef PtrType (*DllFunc)();
const int BASE_INT_LEN = 32;
#ifdef Q_OS_WIN
const char dllExport[BASE_INT_LEN] = ".dll";
#elif defined(Q_OS_LINUX)
const char dllExport[BASE_INT_LEN] = ".so";
#endif

class TryUtil final
{
public:
    template <typename RESTYPE, typename Arg>
    class ScopedResource final
    {
        Q_DISABLE_COPY(ScopedResource)
    public:
        explicit ScopedResource(const Arg &arg = "")
        {
            managedResource = new RESTYPE(arg);
        }

        ~ScopedResource()
        {
            delete managedResource;
        }

        RESTYPE *operator->() const
        {
            return managedResource;
        }

    private:
        RESTYPE *managedResource;
    };

public:
    static bool GetLibHandle(const QString &name, PtrType &out)
    {
        QString str_fileName = name + QString::fromLatin1(dllExport);
        QString str_filePath =
            QCoreApplication::applicationDirPath() + QDir::separator() + "lib" + QDir::separator();

        QFileInfo file_Name(str_filePath + str_fileName);
        if (!file_Name.isFile()) {
            str_fileName = "lib" + str_fileName;
            file_Name.setFile(str_filePath + str_fileName);
        }
        if (file_Name.isFile()) {
            ScopedResource<QLibrary, QString> lib(file_Name.filePath());
            if (!lib->isLibrary(file_Name.fileName())) {
                return false;
            }
            if (!lib->load()) {
                return false;
            }
            DllFunc get = (DllFunc)lib->resolve("Get");
            if (get != nullptr) {
                out = get();
                qDebug() << "load ptr:" << out;
                return true;
            }
        }
        return false;
    }

    static bool WriteJson(const QString &path, const QJsonObject &data)
    {
        QJsonDocument doc(data);
        QFile file(path);
        if (file.open(QFile::WriteOnly)) {
            file.write(doc.toJson());
            return true;
        }
        return false;
    }

    static const QJsonObject &ReadJson(const QString &path, QJsonObject &obj)
    {

        QFile file(path);
        if (file.open(QFile::ReadOnly)) {
            QByteArray arr    = file.readAll();
            QJsonDocument doc = QJsonDocument::fromJson(arr);
            if (doc.isObject()) {
                obj = doc.object();
            }
        }
        return obj;
    }

    template <typename T>
    static void VectorUniqueAdd(QVector<T> &__T, const T &__P)
    {
        if (!__T.contains(__P)) {
            __T.push_back(__P);
        }
    }

    template <typename T>
    static void ListUniqueAdd(QList<T> &__T, const T &__P)
    {
        if (!__T.contains(__P)) {
            __T.append(__P);
        }
    }

private:
    TryUtil()                = delete;
    TryUtil(const TryUtil &) = delete;
};
