//-define-file body hpp/mytype.cpp
//-define-file header hpp/mytype.h
//-only-file header //-
#pragma once

#include <QObject>
#include <qqmlregistration.h>
//-only-file body //-
//- #include "mytype.h"
#include<QSerialPortInfo>
//- {include-header}
#include "../prptHpp/MyTypePrivate.hpp" //- #include "../prptHpp/MyTypePrivate.h"

//-only-file header
//-var {PRE} "MyType::"mytype
class MyType : public MyTypePrivate
{
    Q_OBJECT
    QML_ELEMENT


public:
    //- {function} 1 1
    explicit MyType(QObject *parent = nullptr)
    //-only-file body
    : MyTypePrivate(parent)
    {
    }

    //-only-file header
    public slots:
    //- {fn}
    QString getClinked()
    //-only-file body
    {

        QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
        for (const QSerialPortInfo &port : ports) {
            qDebug() << "portName:" << port.portName();
            qDebug() << "systemLocation:" << port.systemLocation();
            if (!port.manufacturer().isEmpty()){
                qDebug() << "manufacture:" << port.manufacturer();
            }
            if (!port.description().isEmpty()){
                qDebug() << "description:" << port.description();
            }
            if (!port.serialNumber().isEmpty()){
                qDebug() << "serialNumber:" << port.serialNumber();
            }
            if (port.hasProductIdentifier()) {
                qDebug() << "productIdentifier:" << port.productIdentifier();
            }
            if (port.hasVendorIdentifier() ){
                qDebug() << "hasVendorIdentifier:" << port.vendorIdentifier();
            }
            qDebug() << "****************";

        }
        return "Clicked from backend";
    }

    //-only-file header
};
