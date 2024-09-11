/**********************************************
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
 * 文件名称 ：   TitleBar.h
 * 文件标识 ：
 * 摘 要 ：     Window title bar头文件
 * 当前版本 ：   v0.01.0
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.0.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/19
 ******************************************************************************/
#pragma once

#include <QMouseEvent>
#include <QObject>
#include <QWidget>

class TitleBar : public QWidget {
    Q_OBJECT
public:
    explicit TitleBar( QWidget* parent = 0 );
    void setParentWidget( QWidget* parentWidget );

protected:
    void mousePressEvent( QMouseEvent* );
    void mouseReleaseEvent( QMouseEvent* );
    void mouseMoveEvent( QMouseEvent* );

protected:
    QWidget* m_pParentWidget;

private:
    bool   m_blPress;
    QPoint m_PointMove;
};
