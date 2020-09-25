#pragma once

#include "XfrBaseEventReceiver.h"
#include <QObject>

class XfrTrollEventReceiver : public XfrBaseEventReceiver
{
    Q_OBJECT
public:
    XfrTrollEventReceiver(QObject *parent = nullptr);
};

