//-define-file header prptHpp/SettingsConnPrivate.h
//-only-file header //-
#pragma once

#include <QObject>
#include <QObjectComputedProperty>
#include <QQmlEngine>


//-only-file null
/*[[[cog
import cog
from SettingsConnPrivate import prptClass


cog.outl(prptClass.getClassHeader(),
        dedent=True, trimblanklines=True)

]]] */
//-only-file header
class SettingsConnPrivate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name  NOTIFY nameChanged )
    
    QML_ELEMENT
public:
    
    SettingsConnPrivate(QObject *parent):QObject(parent){}

    virtual ~SettingsConnPrivate() {
        
    }

    
    
    QString name() const{return m_name;} 
    

    
    
    
signals:
    void nameChanged();
    

protected:
    QString m_name {"The backend init val"};
    

private:
    
};
//-only-file null

//[[[end]]]
