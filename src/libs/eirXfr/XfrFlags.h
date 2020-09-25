#pragma once
#include "eirXfr.h"

#include <QFlags>

class EIRXFR_EXPORT XfrFlags
{
public:
    enum Flag
    {
        NoFlag      = 0,
        Flag1       = 0x00000001,
    };
    Q_DECLARE_FLAGS(Flags, Flag);

public:
    XfrFlags();
};

