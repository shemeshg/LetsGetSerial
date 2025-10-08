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
    Q_PROPERTY(QString name READ name  NOTIFY nameChanged )
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

    
    QString name() const{return m_name;} 
    

    
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
    void nameChanged();
    void settingsConnChanged();
    void connStatusChanged();
    

protected:
    QString m_name {"The backend init val"};
    SettingsConn * m_settingsConn = new SettingsConn(this);
    

private:
    ConnStatus m_connStatus = ConnStatus::NOT_CONNECTED;
    
};
//-only-file null

//[[[end]]]
