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
 * FileName :           MainTitleBar.cpp
 * FileIdentification :
 * Abstract :
 * CurrentVersion :     v0.01.1
 * author:              babuge
 * CompletionDate :
 * AlternateVersion :   v0.01.0
 * authorship :         babuge
 * CompletionDate :     2024/08/12
 ******************************************************************************/

#include "MainTitleBar.h"
#include "GlobalDef.h"
#include "ui_MainTitleBar.h"

MainTitleBar::MainTitleBar( QWidget* parent ) : TitleBar( parent ), ui( new Ui::MainTitleBar ) {
    ui->setupUi( this );

    QSize sz_icon = Global_Space::TITLE_ICON_SIZE;
    ui->PushBtnNormalMax->AddNormal( ":/img/res/img/normal_hover.png" );
    ui->PushBtnNormalMax->AddActive( ":/img/res/img/max_hover.png" );
    ui->PushBtnNormalMax->AddNormalHover( ":/img/res/img/max_normal.png" );
    ui->PushBtnNormalMax->AddActiveHover( ":/img/res/img/normal_normal.png" );
    ui->PushBtnMin->SetIconsSize( sz_icon );

    ui->PushBtnMin->AddNormal( ":/img/res/img/min_normal.png" );
    ui->PushBtnMin->AddActive( ":/img/res/img/min_normal.png" );
    ui->PushBtnMin->AddNormalHover( ":/img/res/img/min_hover.png" );
    ui->PushBtnMin->AddActiveHover( ":/img/res/img/min_hover.png" );
    ui->PushBtnMin->SetIconsSize( sz_icon );

    ui->PushBtnClose->AddNormal( ":/img/res/img/close_normal.png" );
    ui->PushBtnClose->AddActive( ":/img/res/img/close_normal.png" );
    ui->PushBtnClose->AddNormalHover( ":/img/res/img/close_hover.png" );
    ui->PushBtnClose->AddActiveHover( ":/img/res/img/close_hover.png" );
    ui->PushBtnClose->SetIconsSize( sz_icon );

    connect( ui->PushBtnMin, &QPushButton::clicked, this, &MainTitleBar::Slot_WindMinClicked );
    connect( ui->PushBtnNormalMax, &QPushButton::clicked, this, &MainTitleBar::Slot_WindMaxClicked );
    connect( ui->PushBtnClose, &QPushButton::clicked, this, &MainTitleBar::Slot_CloseClicked );
}

MainTitleBar::~MainTitleBar() {
    delete ui;
}

void MainTitleBar::Slot_CloseClicked() {
    if ( m_pParentWidget ) {
        m_pParentWidget->close();
    }
}

void MainTitleBar::Slot_WindMinClicked() {
    if ( m_pParentWidget ) {
        m_pParentWidget->showMinimized();
    }
}

void MainTitleBar::Slot_WindMaxClicked() {
    if ( m_pParentWidget == nullptr )
        return;
    if ( m_pParentWidget->isMaximized() ) {
        m_pParentWidget->showNormal();
    }
    else {
        m_pParentWidget->showMaximized();
    }
}
