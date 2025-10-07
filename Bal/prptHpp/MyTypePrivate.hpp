//-define-file header prptHpp/MyTypePrivate.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>

//- {include-header}
#include "SettingsConnPrivate.hpp" //- #include "SettingsConnPrivate.h"

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
    Q_PROPERTY(SettingsConnPrivate * settingsConnPrivate READ settingsConnPrivate  NOTIFY settingsConnPrivateChanged )
    
    QML_ELEMENT
public:
    
    MyTypePrivate(QObject *parent):QObject(parent){}

    virtual ~MyTypePrivate() {
        
    }

    
    
    QString name() const{return m_name;} 
    

    
    SettingsConnPrivate * settingsConnPrivate() const{return m_settingsConnPrivate;} 
    

    
    
    
signals:
    void nameChanged();
    void settingsConnPrivateChanged();
    

protected:
    QString m_name {"The backend init val"};
    SettingsConnPrivate * m_settingsConnPrivate = new SettingsConnPrivate(this);
    

private:
    
};
//-only-file null

//[[[end]]]
