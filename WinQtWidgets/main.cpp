#include "Data.h"
#include "mainwindow.h"
#include <QApplication>
#include "../Lib/WinSerial.h"

Data dataSource;
HardwareSerial Serial{"COM1"};
SerialSubscriber serial;

int main(int argc, char *argv[])
{
    serial.Xinit(&Serial);
    QApplication a(argc, argv);
    MainWindow w(nullptr, &dataSource);
    w.show();
    return a.exec();
}
