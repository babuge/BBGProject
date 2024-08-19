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
 * 文件名称 ：   MainTitleBar.h
 * 文件标识 ：
 * 摘 要 ：     Window Main title头文件
 * 当前版本 ：   v0.01.0
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.0.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/19
 ******************************************************************************/
#pragma once

#include "TitleBar.h"
#include <QWidget>

namespace Ui
{
class MainTitleBar;
}

class MainTitleBar : public TitleBar
{
    Q_OBJECT

public:
    explicit MainTitleBar(QWidget *parent = 0);
    ~MainTitleBar();

private Q_SLOTS:
    void Slot_CloseClicked();
    void Slot_WindMinClicked();
    void Slot_WindMaxClicked();

private:
    Ui::MainTitleBar *ui;
};
