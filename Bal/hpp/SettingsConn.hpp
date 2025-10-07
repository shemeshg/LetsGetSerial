//-define-file body hpp/SettingsConn.cpp
//-define-file header hpp/SettingsConn.h
//-only-file header //-
#pragma once
#include <QObject>
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
        : SettingsConnPrivate(parent)
    {


    }

    //-only-file header
public slots:


private slots:


private:



};
