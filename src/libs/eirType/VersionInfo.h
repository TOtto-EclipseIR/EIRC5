#pragma once
#include "eirType.h"

#include "VarMap.h"

class EIRTYPE_EXPORT VersionInfo : public VarMap
{
public:
    VersionInfo();
    static VersionInfo version();
};

