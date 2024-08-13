#include "MainWindow.h"
#include "TryUtil.h"
#include "ui_MainWindow.h"

#include <QDateTime>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

void MainWindow::init()
{
    QString path = QDir::current().path() + QDir::separator() + ".config.json";
    QFile file(path);
    QJsonObject obj;
    if (file.exists()) {
        obj = TryUtil::ReadJson(path, obj);
        if (!obj.isEmpty()) {
        }
        qDebug() << "json: " << obj;
    }

    path = QDir::current().path() + QDir::separator()
           + QString(".config%1.json")
                 .arg(QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss_zzz"));
    if (TryUtil::WriteJson(path, obj)) {
        qDebug() << "WriteJson done!";
    }
    else {
        qDebug() << "WriteJson failed!";
    }

    m_bootstrap.setConfig(obj);
    m_bootstrap.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

