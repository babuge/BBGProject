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
 * 文件名称 :   TitleBar.cpp
 * 文件标识 :
 * 摘 要 :     
 * 当前版本 :   v0.01.1
 * 作 者 :     babuge
 * 完成日期 :
 * 取代版本 :   v0.01.0
 * 原作者   :  babuge
 * 完成日期 :  2024/08/12
 ******************************************************************************/

#include "TitleBar.h"
#include <QDebug>

// 构造函数
TitleBar::TitleBar( QWidget* parent ) : QWidget( parent ), m_pParentWidget( parent ), m_blPress( false ) {}

void TitleBar::setParentWidget( QWidget* parentWidget ) {
    this->m_pParentWidget = parentWidget;
}

// 鼠标点击事件
void TitleBar::mousePressEvent( QMouseEvent* event ) {
    if ( event->button() == Qt::LeftButton ) {
        m_blPress = true;
    }
    if ( m_pParentWidget ) {
#if QT_VERSION >= QT_VERSION_CHECK( 6, 0, 0 )
        m_PointMove = event->globalPosition().toPoint() - m_pParentWidget->pos();
#else
        m_PointMove = event->globalPos() - m_pParentWidget->pos();
#endif
    }
}

// 鼠标释放事件
void TitleBar::mouseReleaseEvent( QMouseEvent* ) {
    m_blPress = false;
}

// 鼠标移动事件
void TitleBar::mouseMoveEvent( QMouseEvent* event ) {
    if ( m_blPress && m_pParentWidget ) {

#if QT_VERSION >= QT_VERSION_CHECK( 6, 0, 0 )
        QPoint movePos = event->globalPosition().toPoint();
#else
        QPoint movePos = event->globalPos();
#endif
        m_pParentWidget->move( movePos - m_PointMove );
    }
}
