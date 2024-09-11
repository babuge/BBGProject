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
 * 文件名称 ：   CBtnOnlyIcon.h
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

#include <QPushButton>

typedef enum BtnOnlyIconType
{
    em_normal = 0x00,
    em_active = 0x01,
    em_hover  = 0x02,
} IconType;

class QIcon;
class CBtnOnlyIcon : public QPushButton
{
public:
    explicit CBtnOnlyIcon(QWidget *parent = nullptr);
    virtual ~CBtnOnlyIcon();
    void AddActiveHover(const QString &path);
    void AddNormalHover(const QString &path);
    void AddActive(const QString &path);
    void AddNormal(const QString &path);
    void SetIconsSize(const QSize &);

protected:
    void paintEvent(QPaintEvent *event) override;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void enterEvent(QEnterEvent *event) override;
#else
    void enterEvent(QEvent *event) override;
#endif
    void leaveEvent(QEvent *event) override;

private Q_SLOTS:
    void Slot_Clicked();

private:
    QPixmap m_NormalIcon;
    QPixmap m_NormalHoverIcon;
    QPixmap m_ActiveIcon;
    QPixmap m_ActiveHoverIcon;
    QSize m_IconSize;
    bool m_blChanged;
    unsigned int m_emState;
};
