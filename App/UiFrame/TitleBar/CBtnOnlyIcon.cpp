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
 * 文件名称 ：   CBtnOnlyIcon.cpp
 * 文件标识 ：
 * 摘 要 ：     
 * 当前版本 ：   v0.01.1
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.01.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/12
 ******************************************************************************/
#include "CBtnOnlyIcon.h"
#include "CommonBase.h"
#include <QDebug>
#include <QEnterEvent>
#include <QIcon>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>

namespace BtnICON_Space
{
const int S32_ICON_WH = 20;  // 图标宽高
}  // namespace BtnICON_Space

CBtnOnlyIcon::CBtnOnlyIcon(QWidget *parent)
    : QPushButton(parent)
    , m_IconSize(BtnICON_Space::S32_ICON_WH, BtnICON_Space::S32_ICON_WH)
    , m_blChanged(true)
    , m_emState(IconType::em_normal)

{
    setIconSize(QSize(BtnICON_Space::S32_ICON_WH, BtnICON_Space::S32_ICON_WH));
    setFixedSize(BtnICON_Space::S32_ICON_WH, BtnICON_Space::S32_ICON_WH);
    connect(this, &QPushButton::clicked, this, &CBtnOnlyIcon::Slot_Clicked);
}

CBtnOnlyIcon::~CBtnOnlyIcon() {}

void CBtnOnlyIcon::AddActiveHover(const QString &path)
{
    if (m_ActiveHoverIcon.load(path)) {
        qDebug() << "Load success file :" << path;
    }
}

void CBtnOnlyIcon::AddNormalHover(const QString &path)
{
    if (m_NormalHoverIcon.load(path)) {
        qDebug() << "Load success file :" << path;
    }
}

void CBtnOnlyIcon::AddActive(const QString &path)
{
    if (m_ActiveIcon.load(path)) {
        qDebug() << "Load success file :" << path;
    }
}

void CBtnOnlyIcon::AddNormal(const QString &path)
{
    if (m_NormalIcon.load(path)) {
        qDebug() << "Load success file :" << path;
    }
}

void CBtnOnlyIcon::SetIconsSize(const QSize &size)
{
    m_IconSize   = size;
    m_NormalIcon = m_NormalIcon.scaled(m_IconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_ActiveIcon = m_ActiveIcon.scaled(m_IconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_NormalHoverIcon =
        m_NormalHoverIcon.scaled(m_IconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_ActiveHoverIcon =
        m_ActiveHoverIcon.scaled(m_IconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void CBtnOnlyIcon::paintEvent(QPaintEvent * /*pEvent*/)
{
    QPixmap pixmap;
    if ((m_emState & IconType::em_active) && (m_emState & IconType::em_hover)) {
        pixmap = m_ActiveHoverIcon;  // active_hover
    }
    else if (m_emState & IconType::em_hover) {
        pixmap = m_NormalHoverIcon;  // normal_active
    }
    else if (m_emState & IconType::em_active) {
        pixmap = m_ActiveIcon;  // active_normal
    }
    else {
        pixmap = m_NormalIcon;  // normal_normal
    }
    QPainter painter(this);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    // 设置渲染质量
    painter.setRenderHint(QPainter::Antialiasing, true);           // 抗锯齿
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);  // 平滑像素图形变换

    // 高度适应
    QRect rt_position(QPoint(0, 0), m_IconSize);
    pixmap = pixmap.scaledToWidth(m_IconSize.width(), Qt::SmoothTransformation);
    if (pixmap.height() < m_IconSize.height()) {
        int s32_Top = (m_IconSize.height() - pixmap.height()) / 2;
        rt_position.setTop(s32_Top);
    }
    pixmap = pixmap.scaledToWidth(m_IconSize.width(), Qt::SmoothTransformation);
    rt_position.setSize(pixmap.size());

    painter.drawPixmap(rt_position, pixmap);
}
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void CBtnOnlyIcon::enterEvent(QEnterEvent * /*event*/)
#else
    void CBtnOnlyIcon::enterEvent(QEvent * /*event*/)
#endif

{
    m_emState |= IconType::em_hover;
    m_blChanged = true;
}

void CBtnOnlyIcon::leaveEvent(QEvent * /*event*/)
{
    m_emState &= (~IconType::em_hover);
    m_blChanged = true;
}

void CBtnOnlyIcon::Slot_Clicked()
{
    if (m_emState & IconType::em_active) {
        m_emState &= (~IconType::em_active);
    }
    else {
        m_emState |= IconType::em_active;
    }
    m_blChanged = true;
}
