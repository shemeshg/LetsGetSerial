//-define-file body hpp/mytype.cpp
//-define-file header hpp/mytype.h
//-only-file header //-
#pragma once
#include <QObject>
#include <QSerialPort>
#include <qqmlregistration.h>

#include <QJSEngine>
#include <QtConcurrent>
//-only-file body //-
//- #include "mytype.h"
#include <QSerialPortInfo>
static constexpr std::chrono::seconds kWriteTimeout = std::chrono::seconds{5};

//- {include-header}
#include "../prptHpp/MyTypePrivate.hpp" //- #include "../prptHpp/MyTypePrivate.h"




//-only-file header
//-var {PRE} "MyType::"mytype
class MyType : public MyTypePrivate {
    Q_OBJECT
    QML_ELEMENT

public:
    //- {function} 1 1
    explicit MyType(QObject *parent = nullptr)
        //-only-file body
        : MyTypePrivate(parent),m_serial(new QSerialPort(this)),m_timer(new QTimer(this))
    {

    connect(m_serial, &QSerialPort::errorOccurred, this, &MyType::handleError);
    connect(m_timer, &QTimer::timeout, this, &MyType::handleWriteTimeout);
    m_timer->setSingleShot(true);

//! [2]
    connect(m_serial, &QSerialPort::readyRead, this, &MyType::readData);
    connect(m_serial, &QSerialPort::bytesWritten, this, &MyType::handleBytesWritten);

    //connect(m_console, &Console::getData, this, &MainWindow::writeData);
//! [3]
    }

    //-only-file header
public slots:
    //- {fn}
    QString printSerialPorts()
    //-only-file body
    {

        QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
        for (const QSerialPortInfo &port : ports) {
            qDebug() << "portName:" << port.portName();
            qDebug() << "systemLocation:" << port.systemLocation();
            if (!port.manufacturer().isEmpty()) {
                qDebug() << "manufacture:" << port.manufacturer();
            }
            if (!port.description().isEmpty()) {
                qDebug() << "description:" << port.description();
            }
            if (!port.serialNumber().isEmpty()) {
                qDebug() << "serialNumber:" << port.serialNumber();
            }
            if (port.hasProductIdentifier()) {
                qDebug() << "productIdentifier:" << port.productIdentifier();
            }
            if (port.hasVendorIdentifier()) {
                qDebug() << "hasVendorIdentifier:" << port.vendorIdentifier();
            }
            qDebug() << "****************";
        }
        return "Clicked from backend";
    }

    //- {fn}
    void openSerialPort()
    //-only-file body
    {
        m_serial->setPortName("cu.usbserial-833120");
        m_serial->setBaudRate(QSerialPort::BaudRate::Baud9600);
        m_serial->setDataBits(QSerialPort::DataBits::Data8);
        m_serial->setParity(QSerialPort::Parity::NoParity);
        m_serial->setStopBits(QSerialPort::StopBits::OneStop);
        m_serial->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
        if (m_serial->open(QIODevice::ReadWrite)) {
          /*  qDebug()<<tr("Connected to %1 : %2, %3, %4, %5, %6")
                            .arg(p.name, p.stringBaudRate, p.stringDataBits,
                                p.stringParity, p.stringStopBits, p.stringFlowControl);
                                */
             qDebug()<<"Connected";                  
        } else {
            qDebug()<<"Error"<<m_serial->errorString();
            qDebug()<<"Open error";
        }
    }

    //- {fn}
    void writeShalom()
    //-only-file body
    {
        writeData("shalom\r\n");
    }

    //- {fn}
    void closeSerialPort()
    //-only-file body
    {
        if (m_serial->isOpen()) {
            m_serial->close();
        }
    }
    //-only-file header

private slots:
    //- {fn}
    void writeData(const QByteArray &data)
     //-only-file body
{
    const qint64 written = m_serial->write(data);
    if (written == data.size()) {
        m_bytesToWrite += written;
        m_timer->start(kWriteTimeout);
    } else {
        const QString error = tr("Failed to write all data to port %1.\n"
                                 "Error: %2").arg(m_serial->portName(),
                                                  m_serial->errorString());
        qDebug()<<error;
    }
}

//- {fn}
void readData()
//-only-file body
{
    const QByteArray data = m_serial->readAll();
    qDebug()<<data;
}

//- {fn}
void handleError(QSerialPort::SerialPortError error)
//-only-file body
{
    if (error == QSerialPort::ResourceError) {
        qDebug()<<"Critical Error"<<m_serial->errorString();
        closeSerialPort();
    }
}

//- {fn}
void handleBytesWritten(qint64 bytes)
//-only-file body
{
    m_bytesToWrite -= bytes;
    if (m_bytesToWrite == 0)
        m_timer->stop();
}

//- {fn}
void handleWriteTimeout()
//-only-file body
{
    const QString error = tr("Write operation timed out for port %1.\n"
                             "Error: %2").arg(m_serial->portName(),
                                              m_serial->errorString());
    qDebug()<<error;
}

//-only-file header
private:
    QSerialPort *m_serial;
    QTimer *m_timer = nullptr;
    qint64 m_bytesToWrite = 0;

    template<typename T>
    void makeAsync(const QJSValue &callback, std::function<T()> func)
    {
        auto *watcher = new QFutureWatcher<T>(this);
        QObject::connect(watcher, &QFutureWatcher<T>::finished, this, [this, watcher, callback]() {
            T returnValue = watcher->result();
            QJSValue cbCopy(callback);
            QJSEngine *engine = qjsEngine(this);
            cbCopy.call(QJSValueList{engine->toScriptValue(returnValue)});
            watcher->deleteLater();
        });
        watcher->setFuture(QtConcurrent::run([=]() { return func(); }));
    }


};
