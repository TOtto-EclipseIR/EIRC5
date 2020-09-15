#pragma once

#include <eirType/Enumeration.h>

#define RECTFINDERCLASS_ENUM(NV) \
    NV(nullClass, = 0)  \
    NV(Face, ) \
    NV(LeftEye, ) \
    NV(RightEye, ) \
    NV(sizeClass, ) \

class RectFinderClass : public Enumeration
{
    DECLARE_ENUMERATION(RectFinderClass, RECTFINDERCLASS_ENUM);
};

