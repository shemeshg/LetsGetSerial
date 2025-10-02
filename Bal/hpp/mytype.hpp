//-define-file body hpp/mytype.cpp
//-define-file header hpp/mytype.h
//-only-file header //-
#pragma once

#include <QObject>
#include <qqmlregistration.h>
//-only-file body //-
//- #include "mytype.h"
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
        return "Clicked from backend";
    }

    //-only-file header
};
