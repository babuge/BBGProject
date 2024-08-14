#pragma once

#include <QJsonObject>
#include <QMap>
#include <QObject>
#include <QReadWriteLock>
#include <QVector>

#include "CommonBase.h"
#include "FramWorkExtend.h"
#include "MainConfig.h"

class QJsonObject;

class BootstrapEntry : public QObject
{
    Q_OBJECT
    LIFECYCLE_STATUS
public:
    typedef QVector<QString> CoreType;
    typedef QVector<QMap<QString, int>> BussinessType;
    typedef QMap<QString, PtrType> CoreHandle;

    explicit BootstrapEntry(QObject *parent = nullptr);
    virtual ~BootstrapEntry();

    void setConfig(const QJsonObject &json);

    void restart();
    void start();
    void stop();
signals:

public slots:
private:
    void initBoostStrap();
    void init();
    void unInit();
    bool loadCore(const QString &);

    template <class T>
    T getObjPtr(const QString &name);

private:
    CoreType m_coreLibs;
    CoreHandle m_coreHandle;

    BussinessType m_bussinessLibs;

    QReadWriteLock m_lock;

    MainConfig m_config;
};

