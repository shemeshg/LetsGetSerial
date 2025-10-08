//-define-file body hpp/mytype.cpp
//-define-file header hpp/mytype.h
//-only-file header //-
#pragma once
#include <QObject>
#include <qqmlregistration.h>

#include <QJSEngine>
#include <QtConcurrent>
//-only-file body //-
//- #include "mytype.h"

//- {include-header}
#include "../prptHpp/MyTypePrivate.hpp" //- #include "../prptHpp/MyTypePrivate.h"
//- {include-header}
#include "SerialMngr.hpp" //- #include "SerialMngr.h"

//-only-file header
//-var {PRE} "MyType::"mytype
class MyType : public MyTypePrivate {
    Q_OBJECT
    QML_ELEMENT

public:
    //- {function} 1 1
    explicit MyType(QObject *parent = nullptr)
        //-only-file body
        : MyTypePrivate(parent), m_serialMngr(new SerialMngr(this)) {}

    //-only-file header
public slots:
    //- {fn}
    QJsonArray getSerialPorts()
    //-only-file body
    {

        return m_serialMngr->getSerialPorts();
    }



    //- {fn}
    void openSerialPort()
    //-only-file body
    {
            QString connMsg{};
            bool connSuccessfull = m_serialMngr->openSerialPort(
                settingsConn()->serialPortName(), settingsConn()->baudRate(),
                (QSerialPort::DataBits)settingsConn()->dataBits(),
                (QSerialPort::Parity)settingsConn()->parity(),
                (QSerialPort::StopBits)settingsConn()->stopBits(),
                (QSerialPort::FlowControl)settingsConn()->flowControl()
                ,connMsg
                );

            setStatusText(connMsg);
            if (connSuccessfull){
                setConnStatus(ConnStatus::CONNECTED);
            } else {
                setConnStatus(ConnStatus::ERR);
            }
    }

    //- {fn}
    void writeShalom()
    //-only-file body
    {
        m_serialMngr->writeShalom();
    }

    //- {fn}
    void closeSerialPort()
    //-only-file body
    {
        m_serialMngr->closeSerialPort();
        setStatusText("Disconnected");
        setConnStatus(ConnStatus::NOT_CONNECTED);
    }
    //-only-file header

private slots:

    //-only-file header
private:
    SerialMngr *m_serialMngr;

    template <typename T>
    void makeAsync(const QJSValue &callback, std::function<T()> func) {
        auto *watcher = new QFutureWatcher<T>(this);
        QObject::connect(watcher, &QFutureWatcher<T>::finished, this,
                         [this, watcher, callback]() {
            T returnValue = watcher->result();
            QJSValue cbCopy(callback);
            QJSEngine *engine = qjsEngine(this);
            cbCopy.call(
                QJSValueList{engine->toScriptValue(returnValue)});
            watcher->deleteLater();
        });
        watcher->setFuture(QtConcurrent::run([=]() { return func(); }));
    }
};
