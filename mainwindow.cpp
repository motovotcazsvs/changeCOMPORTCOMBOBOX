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
    ui->comboBox_2->addItem("9600");
    ui->comboBox_2->addItem("19200");
    ui->comboBox_2->addItem("57600");
    ui->comboBox_2->addItem("115200");

    this->initSerial();

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotchange()));
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(slotchange()));
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readslot);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotchange()
{
    serial->close();
    this->initSerial();
}

void MainWindow::initSerial()
{
    qDebug() << ui->comboBox->currentText();
    qDebug() << ui->comboBox_2->currentText();

    //serial->setPortName("/dev/ttyUSB0"); // GPIO
    //serial->setPortName("/dev/ttyS0");

    QString cp = ui->comboBox->currentText();
    serial->setPortName(cp);
    //serial->setPortName("COM9");

    //serial->setBaudRate(QSerialPort::Baud9600);
    //serial->setBaudRate(QSerialPort::Baud115200);
    QString br = ui->comboBox_2->currentText();
    if(br == "9600") serial->setBaudRate(QSerialPort::Baud9600);
    else if(br == "19200") serial->setBaudRate(QSerialPort::Baud19200);
    else if(br == "57600") serial->setBaudRate(QSerialPort::Baud57600);
    else if(br == "115200") serial->setBaudRate(QSerialPort::Baud115200);

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

void MainWindow::on_pushButton_clicked()
{
    serial->close();
    serial->setPortName("COM9");

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

void MainWindow::on_pushButton_2_clicked()
{
    serial->close();
    serial->setPortName("COM10");

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
