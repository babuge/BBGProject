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
