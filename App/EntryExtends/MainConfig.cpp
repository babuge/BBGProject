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
 * 文件名称 ：   MainConfig.cpp
 * 文件标识 ：
 * 摘 要 ：     
 * 当前版本 ：   v0.01.1
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.01.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/12
 ******************************************************************************/
#include "MainConfig.h"

#include <QJsonArray>
#include <QVariant>

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
