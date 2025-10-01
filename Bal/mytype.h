#pragma once

#include <QObject>
#include <qqmlregistration.h>

class MyType : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    QML_ELEMENT

signals:
    void nameChanged();

public:
    explicit MyType(QObject *parent = nullptr);

    QString name() const { return "FROM BACKEND"; };

    void setName(const QString &name)
    {
        m_name = name;
        emit nameChanged();
    }

private:
    QString m_name;
};

