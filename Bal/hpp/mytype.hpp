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
#include <QGuiApplication>
#include <QClipboard>


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
        : MyTypePrivate(parent), m_serialMngr(new SerialMngr(this)) {


        m_serialMngr->processString = [this](const QString& s) {
            emit addTextToConsole(s);
            //qDebug() << "we have: " << s ;
        };

        m_serialMngr->processError = [this](const QString& connMsg) {
            setStatusText(connMsg);
            setConnStatus(ConnStatus::ERR);
        };

        QSettings settings;
        m_settingsConn->setSerialPortName(settings.value("serialPortId","").toString());
        m_settingsConn->setBaudRate(settings.value("baudRateId",9600).toInt());
        m_settingsConn->setDataBits(settings.value("dataBitsId",QSerialPort::DataBits::Data8).toInt());
        m_settingsConn->setParity(settings.value("parityId",QSerialPort::Parity::NoParity).toInt());
        m_settingsConn->setStopBits(settings.value("stopBitsId",QSerialPort::StopBits::OneStop).toInt());
        m_settingsConn->setFlowControl(settings.value("flowControlId",QSerialPort::FlowControl::NoFlowControl).toInt());
        m_settingsConn->setIsLocalEcho(settings.value("isLocalEchoId", false).toBool());
    }

    //-only-file header
public slots:
    //- {fn}
    QJsonArray getSerialPorts()
    //-only-file body
    {

        return m_serialMngr->getSerialPorts();
    }

    //- {fn}
    QString getClipboard()
    //-only-file body
    {
        QClipboard *clipboard = QGuiApplication::clipboard();
        QString originalText = clipboard->text();
        return originalText;
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
    void writeKeys(QString key)
    //-only-file body
    {
        m_serialMngr->writeKeys(key);
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

signals:
    void addTextToConsole(QString);

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
