#pragma once

#include <QJsonObject>
#include <QStringList>

class MainConfig
{
public:
    MainConfig();
    MainConfig(const QStringList &core, const QStringList &bussiness, const QString &descript);

    void setDescript(const QString &descript);
    QString descript() const;

    void setCore(const QStringList &core);
    const QStringList &core() const;

    void setBussiness(const QStringList &bussiness);
    const QStringList &bussiness() const;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    QString m_descript;
    QStringList m_core;
    QStringList m_bussiness;
};

