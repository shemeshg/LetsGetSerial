//-define-file body hpp/SettingsConn.cpp
//-define-file header hpp/SettingsConn.h
//-only-file header //-
#pragma once
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QSerialPort>
#include <qqmlregistration.h>

//-only-file body //-
//- #include "SettingsConn.h"

//- {include-header}
#include "../prptHpp/SettingsConnPrivate.hpp" //- #include "../prptHpp/SettingsConnPrivate.h"

//-only-file header
//-var {PRE} "SettingsConn::"SettingsConn"
class SettingsConn : public SettingsConnPrivate {
    Q_OBJECT
    QML_ELEMENT

public:
    //- {function} 1 1
    explicit SettingsConn(QObject *parent = nullptr)
        //-only-file body
        : SettingsConnPrivate(parent) {}

    //-only-file header
public slots:
    //- {fn}
    QJsonArray getBaudRateBox()
    //-only-file body
    {
        QJsonArray ret;
        addComboboxItem(ret,QSerialPort::Baud9600, "9600");
        addComboboxItem(ret,QSerialPort::Baud19200, "19200");
        addComboboxItem(ret,QSerialPort::Baud38400, "38400");
        addComboboxItem(ret,QSerialPort::Baud115200, "115200");
        return ret;
    }


    //- {fn}
    QJsonArray getDataBitsBox()
    //-only-file body
    {
        QJsonArray ret;
        addComboboxItem(ret,QSerialPort::Data5, "5");
        addComboboxItem(ret,QSerialPort::Data6, "6");
        addComboboxItem(ret,QSerialPort::Data7, "7");
        addComboboxItem(ret,QSerialPort::Data8, "8");
        return ret;
    }

    //- {fn}
    QJsonArray getParityBox()
    //-only-file body
    {
        QJsonArray ret;
        addComboboxItem(ret,QSerialPort::NoParity, "None");
        addComboboxItem(ret,QSerialPort::EvenParity, "Even");
        addComboboxItem(ret,QSerialPort::OddParity, "Odd");
        addComboboxItem(ret,QSerialPort::MarkParity, "Mark");
        addComboboxItem(ret,QSerialPort::SpaceParity, "Space");
        return ret;
    }

    //- {fn}
    QJsonArray getStopBitsBox()
    //-only-file body
    {
        QJsonArray ret;
        addComboboxItem(ret,QSerialPort::OneStop, "1");
        #ifdef Q_OS_WIN
        addComboboxItem(ret,QSerialPort::OneAndHalfStop, "1.5");
        #endif
        addComboboxItem(ret,QSerialPort::TwoStop, "2");
        return ret;
    }

    //- {fn}
    QJsonArray getFlowControlBox()
    //-only-file body
    {
        QJsonArray ret;
        addComboboxItem(ret,QSerialPort::NoFlowControl, "None");
        addComboboxItem(ret,QSerialPort::HardwareControl, "RTS/CTS");
        addComboboxItem(ret,QSerialPort::SoftwareControl, "XON/XOFF");
        return ret;
    }


    //-only-file header
private slots:

private:
    //- {fn}
    void addComboboxItem(QJsonArray &ret, int val, QString str)
    //-only-file body
    {
    QJsonObject row;
    row["val"] = val;
    row["str"] = str;
    ret.append(row);
    }

    //-only-file header
};
