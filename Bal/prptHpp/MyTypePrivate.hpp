//-define-file header prptHpp/MyTypePrivate.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

//- {include-header}
#include "../hpp/SettingsConn.hpp" //- #include "../hpp/SettingsConn.h"

//-only-file null
/*[[[cog
import cog
from MyTypePrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class MyTypePrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString statusText READ statusText WRITE setStatusText NOTIFY statusTextChanged )
    Q_PROPERTY(SettingsConn * settingsConn READ settingsConn  NOTIFY settingsConnChanged )
    Q_PROPERTY(ConnStatus connStatus READ connStatus WRITE setConnStatus NOTIFY connStatusChanged )
    
    QML_ELEMENT
public:
    
    MyTypePrivate(QObject *parent):QObject(parent){}

    virtual ~MyTypePrivate() {
        
    }

    
enum class ConnStatus {
        NOT_CONNECTED, CONNECTED, ERR
    };
Q_ENUM(ConnStatus)

    
    QString statusText() const{return m_statusText;} 
    
void setStatusText(const QString &newStatusText)
    {
        if (m_statusText == newStatusText)
            return;
        m_statusText = newStatusText;
        emit statusTextChanged();
    }


    
    SettingsConn * settingsConn() const{return m_settingsConn;} 
    

    
    ConnStatus connStatus() const{return m_connStatus;} 
    
void setConnStatus(const ConnStatus &newConnStatus)
    {
        if (m_connStatus == newConnStatus)
            return;
        m_connStatus = newConnStatus;
        emit connStatusChanged();
    }


    
    
    
signals:
    void statusTextChanged();
    void settingsConnChanged();
    void connStatusChanged();
    

protected:
    SettingsConn * m_settingsConn = new SettingsConn(this);
    

private:
    QString m_statusText {"Not connected"};
    ConnStatus m_connStatus = ConnStatus::NOT_CONNECTED;
    
};
//-only-file null

//[[[end]]]
