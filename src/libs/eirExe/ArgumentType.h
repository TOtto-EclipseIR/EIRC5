#pragma once
#include "eirExe.h"

#include <eirType/Enumeration.h>

#define ARGUMENTTYPE_ENUM(NV)   \
    NV(nullArgumentType, = 0)   \
    NV(New, )                   \
    NV(BasicString, )           \
    NV(PathName, )              \
    NV(InputDir, )              \
    NV(InputDirOnly, )          \
    NV(InputFile, )             \
    NV(OutputFile, )            \
    NV(ConfigItem, )            \
    NV(IncludeFileName, )       \
    NV(IncludeTxtFile, )        \
    NV(sizeArgumentType, )

class EIREXE_EXPORT ArgumentType : public Enumeration
{
public:
    DECLARE_ENUMERATION(ArgumentType, ARGUMENTTYPE_ENUM)
};

