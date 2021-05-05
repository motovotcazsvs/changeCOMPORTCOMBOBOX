#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QByteArray>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort;
    QSerialPortInfo::availablePorts().count();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        ui->comboBox->addItem(serialPortInfo.portName());
    }

    this->initSerial();

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotchange()));
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readslot);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotchange()
{
    //delete serial;
    this->initSerial();
}

void MainWindow::initSerial()
{
    qDebug() << ui->comboBox->currentText();

    //serial->setPortName("/dev/ttyUSB0"); // GPIO
    //serial->setPortName("/dev/ttyS0");

    //QString f = "COM9";
    QString s1;
    QString s2;
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
       s1 = serialPortInfo.portName();
    }
    delete serial;
    serial = new QSerialPort;
    QString f = ui->comboBox->currentText();
    //QByteArray ff;
    //ff.append(f);
    //qDebug() << ff[4];
    //QString f2 = "COM9";
    //qDebug() << f2.size();
    serial->setPortName(f);
    //serial->setPortName("COM9");
    //serial->setBaudRate(QSerialPort::Baud9600);
    serial->setBaudRate(QSerialPort::Baud115200);

    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop); // Is this correct?

    if (!serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "dispenseThread::run: ERROR: Cannot open serial port!";
        qDebug() << serial->errorString();
    }
}

void MainWindow::readslot()
{
    //QByteArray resp = serial->readAll();
    QByteArray responseData = serial->readAll();
    //const QString response2 = QString::fromUtf8(resp);
    while (serial->waitForReadyRead(10))
    {
        responseData += serial->readAll();
    }
    qDebug() << responseData;
}
