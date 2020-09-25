#pragma once
#include "eirXfr.h"

#include "XfrEvent.h"

class EIRXFR_EXPORT XfrEventQueue
{
public:
    XfrEventQueue();

private:
    QQueue<XfrEvent> mEventQueue;
};

