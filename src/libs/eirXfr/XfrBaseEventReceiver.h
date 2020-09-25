#pragma once

#include <QObject>

#include <QList>

class XfrBaseEventReceiver : public QObject
{
    Q_OBJECT
public:
    typedef QList<XfrBaseEventReceiver *> List;

public:
    explicit XfrBaseEventReceiver(QObject *parent = nullptr);
    ~XfrBaseEventReceiver();

signals:

private:
    static List smReceiverList;


};

