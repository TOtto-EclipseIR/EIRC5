#pragma once

#include "VarMap.h"

class SystemId : public VarMap
{
public:
    enum Flag
    {
        noFlags = 0,
        SystemInfo      = 0x00000001,
        NetworkInfo     = 0x00000002,
    };
    Q_DECLARE_FLAGS(Flags, Flag);

public:
    SystemId(const Flags f=noFlags, const MultiName &name=MultiName());
    void addSystemInfo();
    void addNetworkInfo();
};

