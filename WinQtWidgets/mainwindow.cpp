#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Data* dataSource)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->dataSource = dataSource;
    connect(&timer, SIGNAL (timeout()), this, SLOT (timedLoop()));
    connect(ui->cmdMotorRun, SIGNAL(toggled(bool)), this, SLOT(cmdMotorRunChanged(bool)));
    connect(ui->cmdMotorSpeed, SIGNAL(valueChanged(int)), this, SLOT(cmdMotorSpeedChanged(int)));
    timer.start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timedLoop()
{
    Comm.Xchange();
    //Status
    ui->stsMotorSpeed->display(dataSource->stsMotorSpeed);
    if(!dataSource->stsMotorRun)
    {
        ui->stsMotorRun->setText("Stopped");
    }
    else
    {
        ui->stsMotorRun->setText("Running");
    }
    timer.start(1);
}

void MainWindow::cmdMotorRunChanged(bool checked)
{
    dataSource->cmdRunMotor = checked;
}
void MainWindow::cmdMotorSpeedChanged(int newSpeed)
{
    dataSource->cmdMotorSpeed = (float)newSpeed;
}
