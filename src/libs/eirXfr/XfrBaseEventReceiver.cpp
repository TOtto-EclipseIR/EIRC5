#include "XfrBaseEventReceiver.h"

#include <QtDebug>

XfrBaseEventReceiver::List XfrBaseEventReceiver::smReceiverList;


XfrBaseEventReceiver::XfrBaseEventReceiver(QObject *parent) : QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
    smReceiverList.append(this);
}

XfrBaseEventReceiver::~XfrBaseEventReceiver()
{
    smReceiverList.removeAll(this);
    deleteLater();
}
