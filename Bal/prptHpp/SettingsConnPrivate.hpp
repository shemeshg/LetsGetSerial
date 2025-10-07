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
    Q_PROPERTY(QString serialPortName READ serialPortName WRITE setSerialPortName NOTIFY serialPortNameChanged )
    Q_PROPERTY(int baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged )
    Q_PROPERTY(int dataBits READ dataBits WRITE setDataBits NOTIFY dataBitsChanged )
    Q_PROPERTY(int parity READ parity WRITE setParity NOTIFY parityChanged )
    Q_PROPERTY(int stopBits READ stopBits WRITE setStopBits NOTIFY stopBitsChanged )
    Q_PROPERTY(int flowControl READ flowControl WRITE setFlowControl NOTIFY flowControlChanged )
    Q_PROPERTY(bool isLocalEcho READ isLocalEcho WRITE setIsLocalEcho NOTIFY isLocalEchoChanged )
    
    QML_ELEMENT
public:
    
    SettingsConnPrivate(QObject *parent):QObject(parent){}

    virtual ~SettingsConnPrivate() {
        
    }

    
    
    QString serialPortName() const{return m_serialPortName;} 
    
void setSerialPortName(const QString &newSerialPortName)
    {
        if (m_serialPortName == newSerialPortName)
            return;
        m_serialPortName = newSerialPortName;
        emit serialPortNameChanged();
    }


    
    int baudRate() const{return m_baudRate;} 
    
void setBaudRate(const int newBaudRate)
    {
        if (m_baudRate == newBaudRate)
            return;
        m_baudRate = newBaudRate;
        emit baudRateChanged();
    }


    
    int dataBits() const{return m_dataBits;} 
    
void setDataBits(const int newDataBits)
    {
        if (m_dataBits == newDataBits)
            return;
        m_dataBits = newDataBits;
        emit dataBitsChanged();
    }


    
    int parity() const{return m_parity;} 
    
void setParity(const int newParity)
    {
        if (m_parity == newParity)
            return;
        m_parity = newParity;
        emit parityChanged();
    }


    
    int stopBits() const{return m_stopBits;} 
    
void setStopBits(const int newStopBits)
    {
        if (m_stopBits == newStopBits)
            return;
        m_stopBits = newStopBits;
        emit stopBitsChanged();
    }


    
    int flowControl() const{return m_flowControl;} 
    
void setFlowControl(const int newFlowControl)
    {
        if (m_flowControl == newFlowControl)
            return;
        m_flowControl = newFlowControl;
        emit flowControlChanged();
    }


    
    bool isLocalEcho() const{return m_isLocalEcho;} 
    
void setIsLocalEcho(const bool newIsLocalEcho)
    {
        if (m_isLocalEcho == newIsLocalEcho)
            return;
        m_isLocalEcho = newIsLocalEcho;
        emit isLocalEchoChanged();
    }


    
    
    
signals:
    void serialPortNameChanged();
    void baudRateChanged();
    void dataBitsChanged();
    void parityChanged();
    void stopBitsChanged();
    void flowControlChanged();
    void isLocalEchoChanged();
    

protected:
    

private:
    QString m_serialPortName {""};
    int m_baudRate {9600};
    int m_dataBits {8};
    int m_parity {0};
    int m_stopBits {1};
    int m_flowControl {0};
    bool m_isLocalEcho {true};
    
};
//-only-file null

//[[[end]]]
