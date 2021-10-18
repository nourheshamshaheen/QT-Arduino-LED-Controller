#include "mainwindow.h"
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(500, 300);
    w.setWindowTitle("LED CONTROLLER");
    w.show();
    return a.exec();
}
