//-define-file body hpp/SerialMngr.cpp
//-define-file header hpp/SerialMngr.h
//-only-file header //-
#pragma once
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <qqmlregistration.h>
//-only-file body //-
//- #include "SerialMngr.h"
#include <QSerialPortInfo>
#include <qDebug>
static constexpr std::chrono::seconds kWriteTimeout = std::chrono::seconds{5};

//-only-file header
//-var {PRE} "SerialMngr::"SerialMngr
class SerialMngr : public QObject {
    Q_OBJECT
    QML_ELEMENT

public:
    //- {function} 1 1
    explicit SerialMngr(QObject *parent = nullptr)
        //-only-file body
        : QObject(parent), m_serial(new QSerialPort(this)),
        m_timer(new QTimer(this)) {

    connect(m_serial, &QSerialPort::errorOccurred, this,  &SerialMngr::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &SerialMngr::readData);

    connect(m_timer, &QTimer::timeout, this, &SerialMngr::handleWriteTimeout);
    m_timer->setSingleShot(true);
    connect(m_serial, &QSerialPort::bytesWritten, this,
            &SerialMngr::handleBytesWritten);

    //! [3]
    }

    //-only-file header
    virtual ~SerialMngr() {}

    //- {fn}
    bool openSerialPort(QString serialPortName, int baudRate,
                        QSerialPort::DataBits dataBits,
                        QSerialPort::Parity parity,
                        QSerialPort::StopBits stopBits,
                        QSerialPort::FlowControl flowControl, QString &connMsg)
    //-only-file body
    {
        m_serial->setPortName(serialPortName);
        m_serial->setBaudRate(baudRate);
        m_serial->setDataBits(dataBits);
        m_serial->setParity(parity);
        m_serial->setStopBits(stopBits);
        m_serial->setFlowControl(flowControl);
        if (m_serial->open(QIODevice::ReadWrite)) {

            connMsg = QString("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(serialPortName)
                          .arg(baudRate)
                          .arg(dataBits)
                          .arg(parity)
                          .arg(stopBits)
                          .arg(flowControl);

            return true;
        } else {
            connMsg = QString("Error %1").arg(m_serial->errorString());

            return false;
        }
    }

    //-only-file header
    std::function<void(const QString&)> processString = [](const QString& s) {
        qDebug() << "Received string: " << s ;
    };


    std::function<void(const QString&)> processError = [](const QString& s) {
        qDebug() << "Received string: " << s ;
    };

    //-only-file header
public slots:
    //- {fn}
    QJsonArray getSerialPorts()
    //-only-file body
    {
        QJsonArray ret;
        const QString blankString = "";
        QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
        for (const QSerialPortInfo &port : ports) {
            QJsonObject obj;
            const QString description = port.description();
            const QString manufacturer = port.manufacturer();
            const QString serialNumber = port.serialNumber();
            const auto vendorId = port.vendorIdentifier();
            const auto productId = port.productIdentifier();
            obj["portName"] = port.portName();
            obj["description"] = (!description.isEmpty() ? description : blankString);
            obj["manufacturer"] =
                (!manufacturer.isEmpty() ? manufacturer : blankString);
            obj["serialNumber"] =
                (!serialNumber.isEmpty() ? serialNumber : blankString);
            obj["systemLocation"] = port.systemLocation();
            obj["vendorId"] =
                (vendorId ? QString::number(vendorId, 16) : blankString);
            obj["productId"] =
                (productId ? QString::number(productId, 16) : blankString);
            ret.append(obj);
        }
        return ret;
    }

    //- {fn}
    void writeKey(QString key)
    //-only-file body
    {
        writeData(key.toLocal8Bit());
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
        const QString error =
            tr("Failed to write all data to port %1.\n"
                                 "Error: %2")
                                  .arg(m_serial->portName(), m_serial->errorString());
        qDebug() << error;
    }
    }

    //- {fn}
    void readData()
    //-only-file body
    {
        const QByteArray data = m_serial->readAll();
        processString(data);
    }

    //- {fn}
    void handleError(QSerialPort::SerialPortError error)
    //-only-file body
    {
    if (error == QSerialPort::ResourceError) {
       QString err = m_serial->errorString();
        closeSerialPort();
       processError(err);
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
    const QString error =
            tr("Write operation timed out for port %1.\n"
                                 "Error: %2")
                                  .arg(m_serial->portName(), m_serial->errorString());
    qDebug() << error;
    }

    //-only-file header
private:
    QSerialPort *m_serial;
    QTimer *m_timer = nullptr;
    qint64 m_bytesToWrite = 0;
};
