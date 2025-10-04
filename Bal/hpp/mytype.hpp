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
        : MyTypePrivate(parent) {}

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
    QString connectArduino()
    //-only-file body
    {
        return "connected";
    }

    //- {fn}
    void asyncConnectArduino(const QJSValue &callback)
    //-only-file body
    {
        makeAsync<QString>(callback, [=]() {
            connectArduino();
            return "Shalom Async";
        });
    }

    //-only-file header
private:
    QSerialPort m_serial();

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
