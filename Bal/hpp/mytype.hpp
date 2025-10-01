//-define-file body hpp/mytype.cpp
//-define-file header hpp/mytype.h
//-only-file header //-
#pragma once

#include <QObject>
#include <qqmlregistration.h>
//-only-file body //-
//- #include "mytype.h"

//-only-file header
//-var {PRE} "MyType::"mytype
class MyType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    QML_ELEMENT

signals:
    void nameChanged();

public:
    //- {function} 1 1
    explicit MyType(QObject *parent = nullptr) 
    //-only-file body
    : QObject(parent)
    {
    }

    //- {fn}
    QString name() const 
    //-only-file body
    { 
        return "FROM BACKEND"; 
    };

    //- {fn}
    void setName(const QString &name)
    //-only-file body
    {
        m_name = name;
        emit nameChanged();
    }

    //-only-file header //-
private:
    QString m_name;
};
