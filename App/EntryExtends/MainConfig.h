/******************************************************************************
 * Copyright (C) [2024] [github.com/babuge]
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
