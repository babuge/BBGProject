#pragma once

#include <QByteArray>
#include <QCoreApplication>
#include <QDataStream>
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
        QString file = name + QString::fromLatin1(dllExport);
        QString dirStr =
            QCoreApplication::applicationDirPath() + QDir::separator() + "lib" + QDir::separator();

        QDir dir(dirStr);
        if (dir.exists()) {
            ScopedResource<QLibrary, QString> lib(dirStr + file);
            if (!lib->isLibrary(file)) {
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
    TryUtil() = delete;
    TryUtil(const TryUtil &) = delete;
};

