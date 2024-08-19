#include "TitleBar.h"
#include <QDebug>

// 构造函数
TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
    , m_pParentWidget(parent)
    , m_blPress(false)
{
}

void TitleBar::setParentWidget(QWidget *parentWidget)
{
    this->m_pParentWidget = parentWidget;
}

// 鼠标点击事件
void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_blPress = true;
    }
    if (m_pParentWidget) {
        m_PointMove = event->globalPosition().toPoint() - m_pParentWidget->pos();
    }
}

// 鼠标释放事件
void TitleBar::mouseReleaseEvent(QMouseEvent *)
{
    m_blPress = false;
}

// 鼠标移动事件
void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (m_blPress && m_pParentWidget) {
        QPoint movePos = event->globalPosition().toPoint();
        m_pParentWidget->move(movePos - m_PointMove);
    }
}
