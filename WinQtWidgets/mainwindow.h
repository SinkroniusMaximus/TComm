#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Data.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr, Data* dataSource = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
        Data* dataSource;
        QTimer timer;

    private slots:
        void timedLoop();
        void cmdMotorRunChanged(bool checked);
        void cmdMotorSpeedChanged(int newSpeed);
};
#endif // MAINWINDOW_H
