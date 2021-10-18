#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    uno = new QSerialPort;

    for(int i = 0; i < QSerialPortInfo::availablePorts().length(); i++)
    {
        const QSerialPortInfo &serialPortInfo = QSerialPortInfo::availablePorts().at(i);
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == 0x2341 && serialPortInfo.productIdentifier() == 0x43) // uno vendor/product id
            {
                    portName = serialPortInfo.portName();
                    available = true;
            }
        }

    }
    /*
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
           if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
               if(serialPortInfo.vendorIdentifier() == 0x2341 && serialPortInfo.productIdentifier() == 0x43) // uno vendor/product id
               {
                       portName = serialPortInfo.portName();
                       available = true;
               }
           }
       }
    */

    if(available)
    {
        uno->setPortName(portName);
        uno->open(QSerialPort::WriteOnly);
        uno->setBaudRate(QSerialPort::Baud9600);
        uno->setDataBits(QSerialPort::Data8);
        uno->setParity(QSerialPort::NoParity);
        uno->setStopBits(QSerialPort::OneStop);
        uno->setFlowControl(QSerialPort::NoFlowControl);
    }
    else
            qDebug() << "ERROR, NO ARDUINO UNO FOUND!";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_onButton_clicked() // what happens if we press ON button
{
    QString red = ui->redValue->text();
    QString blue = ui->blueValue->text();
    QString on = "R" + red + "B" + blue;
    writeToSerial(on);
    qDebug() << on;
}


void MainWindow::on_offButton_clicked() // what happens if we press OFF button
{
    QString off = "S";
    writeToSerial(off);
    qDebug() << off;
}


void MainWindow::writeToSerial(QString str)
{
    if(uno->isWritable()){
        uno->write(str.toStdString().c_str());
    }else{
        qDebug() << "ERROR, UNO ISN'T WRITABLE";
    }
}
