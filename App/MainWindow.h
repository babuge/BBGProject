#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "EntryExtends/BootstrapEntry.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class BootstrapEntry;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void init();

private:
    Ui::MainWindow *ui;
    BootstrapEntry m_bootstrap;
};
#endif // MAINWINDOW_H
