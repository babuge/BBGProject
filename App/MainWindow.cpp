#include "MainWindow.h"
#include "TryUtil.h"
#include "ui_MainWindow.h"

#include <QDateTime>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMouseEvent>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    init();
}

void MainWindow::init()
{
    ui->widgetTitle->setParentWidget(this);

    m_bootstrap.InitConfig();
    m_bootstrap.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
