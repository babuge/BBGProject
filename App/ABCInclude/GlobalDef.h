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
 * 文件名称 ：   GlobalDef.h
 * 文件标识 ：
 * 摘 要 ：     
 * 当前版本 ：   v0.01.1
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.01.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/12
 ******************************************************************************/

#pragma once
#include <QSize>
#include <QString>

#ifndef LOAD_QSS
#define LOAD_QSS(qssFile)                                                                          \
    {                                                                                              \
        QFile file(qssFile);                                                                       \
        file.open(QFile::ReadOnly);                                                                \
        if (file.isOpen()) {                                                                       \
            if (qApp != nullptr) {                                                                 \
                qApp->setStyleSheet(file.readAll());                                               \
            }                                                                                      \
            file.close();                                                                          \
        }                                                                                          \
    }
#endif  // LOAD_QSS

namespace Global_Space
{
const QString STYLE_QSS_FILE_PATH = ":/qss/res/qss/stylesheet.qss";
const QString LOGO_PATH           = ":/img/res/img/babuge.png";
const QSize TITLE_ICON_SIZE       = QSize(20, 20);

};  // namespace Global_Space
