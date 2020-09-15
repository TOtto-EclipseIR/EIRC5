#pragma once
#include "eirCascade.h"

#include <eirType/Enumeration.h>

#define CASCADETYPE_ENUM(NV) \
    NV(nullCascadeType, = 0)  \
    NV(PreScan,) \
    NV(PreScanAll,) \
    NV(Face,) \
    NV(LeftEye,) \
    NV(RighttEye,) \
    NV(BothEyes,) \
    NV(Nose,) \
    NV(Mouth,) \
    NV(sizeCascadeType,)   \

class EIRCASCADE_EXPORT CascadeType : public Enumeration
{
    DECLARE_ENUMERATION(CascadeType, CASCADETYPE_ENUM)
};

