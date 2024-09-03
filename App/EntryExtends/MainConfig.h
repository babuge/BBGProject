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
 * 文件名称 ：   MainConfig.h
 * 文件标识 ：
 * 摘 要 ：     主要配置信息，配置加载模块信息
 * 当前版本 ：   v0.01.0
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.0.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/12
 ******************************************************************************/
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
