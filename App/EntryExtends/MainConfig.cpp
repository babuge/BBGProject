#include "MainConfig.h"

#include <QJsonArray>

MainConfig::MainConfig() {}

MainConfig::MainConfig(const QStringList &core,
                       const QStringList &bussiness,
                       const QString &descript)
    : m_descript(descript), m_core(core), m_bussiness(bussiness)
{
}

void MainConfig::setDescript(const QString &descript)
{
    m_descript = descript;
}
QString MainConfig::descript() const
{
    return m_descript;
}

void MainConfig::setCore(const QStringList &core)
{
    m_core = core;
}
const QStringList &MainConfig::core() const
{
    return m_core;
}

void MainConfig::setBussiness(const QStringList &bussiness)
{
    m_bussiness = bussiness;
}

const QStringList &MainConfig::bussiness() const
{
    return m_bussiness;
}

void MainConfig::read(const QJsonObject &json)
{
    QJsonObject root = json["root"].toObject();
    m_core           = root["core"].toVariant().value<QStringList>();
    m_bussiness      = root["bussiness"].toVariant().value<QStringList>();
    m_descript       = root["descript"].toString();
}

void MainConfig::write(QJsonObject &json) const
{
    QJsonObject root;
    root["core"]      = QJsonArray::fromStringList(m_core);
    root["bussiness"] = QJsonArray::fromStringList(m_bussiness);
    root["descript"]  = m_descript;
    json["root"]      = root;
}
