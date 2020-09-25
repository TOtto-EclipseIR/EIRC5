#pragma once

#include <QEvent>
#include <QQueue>

#include "XfrEntry.h"

class XfrEvent : public QEvent
{
public:
    enum Type
    {
        nullType = QEvent::User,
        Xfr0,
        maxType
    };
    typedef QQueue<XfrEvent> Queue;

public:
    XfrEvent(const XfrEntry &entry, const Type type=Xfr0);
    bool operator == (const XfrEvent &other);

private:
    const QUuid cmEntryUid;
    const XfrEntry cmEntry;
};

